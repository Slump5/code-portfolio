"""
G7 Finance Database Site
© 2024 G7 Finance. All rights reserved.

Backend API using Flask, SQLite, and MongoDB.
"""

from flask import Flask, jsonify, request, send_from_directory
from flask_cors import CORS
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address
from pathlib import Path
from contextlib import contextmanager
from dotenv import load_dotenv
import sqlite3
import json
import requests
import os
import logging
import requests
import time
from datetime import datetime, timedelta
from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi
from bson import ObjectId

# Load environment variables from .env file
load_dotenv()

BASE_DIR = Path(__file__).resolve().parent
CLIENT_DIR = BASE_DIR.parent / "client"
PAGES_DIR = CLIENT_DIR / "pages"
SCRIPTS_DIR = CLIENT_DIR / "scripts"
STATIC_DIR = CLIENT_DIR / "static"
DB_PATH = BASE_DIR / "db" / "assets.db"

# API Configuration
FINNHUB_API_KEY = os.environ.get('FH_API_KEY', '')
COINGECKO_API_KEY = os.environ.get('CG_API_KEY', '')  # Optional for CoinGecko free tier
FINNHUB_BASE_URL = 'https://finnhub.io/api/v1'
COINGECKO_BASE_URL = 'https://api.coingecko.com/api/v3'

# Validate API keys on startup
if not FINNHUB_API_KEY:
    print("⚠️  WARNING: FH_API_KEY not found in environment!")
    print("   Create a .env file in the server folder with: FH_API_KEY=your_key_here")
    print("   Get a free key at: https://finnhub.io/register")

if not COINGECKO_API_KEY:
    print("ℹ️  INFO: CG_API_KEY not found in environment")
    print("   CoinGecko free tier doesn't require an API key, but you can add one if you have it")
    print("   Get an API key at: https://www.coingecko.com/en/api/pricing")

# Trending assets to track
TRENDING_STOCKS = ['NVDA', 'AAPL', 'MSFT', 'GOOGL', 'AMZN']
TRENDING_CRYPTO = {
    'bitcoin': 'BTC',
    'ethereum': 'ETH', 
    'solana': 'SOL',
    'litecoin': 'LTC',
    'ripple': 'XRP'
}

# Helper: check if a symbol is crypto
def is_crypto(symbol):
    return symbol.upper() in TRENDING_CRYPTO.values()


# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)

app = Flask(__name__)
app.config['JSON_SORT_KEYS'] = False
CORS(app)

# Initialize rate limiter (no global limits, only specific endpoints)
limiter = Limiter(
    app=app,
    key_func=get_remote_address,
    default_limits=[],  # No global rate limits
    storage_uri="memory://",
    headers_enabled=True  # Add rate limit info to response headers
)

MONGO_DB_URI = os.environ.get('MONGO_DB_URI', '')
# Create a new client and connect to the server
client = MongoClient(str(MONGO_DB_URI), server_api=ServerApi('1'))
# Send a ping to confirm a successful connection
try:
    client.admin.command('ping')
    print("Pinged your deployment. You successfully connected to MongoDB!")
except Exception as e:
    print(e)

# MongoDB database and collection setup
mongo_db = client['g7_finance']
comments_collection = mongo_db['comments']

@contextmanager
def get_db_connection():
    """Context manager for database connections"""
    conn = sqlite3.connect(str(DB_PATH), detect_types=sqlite3.PARSE_DECLTYPES)
    conn.row_factory = sqlite3.Row
    try:
        yield conn
        conn.commit()
    except Exception:
        conn.rollback()
        raise
    finally:
        conn.close()


def init_db():
    """Initialize the database with schema from script.sql"""
    script_path = BASE_DIR / "db" / "script.sql"
    
    if not script_path.exists():
        logger.warning(f"Database schema file not found: {script_path}")
        return
    
    try:
        with get_db_connection() as conn:
            with open(script_path, "r", encoding="utf-8") as f:
                conn.executescript(f.read())
        logger.info("Database initialized successfully")
    except Exception as e:
        logger.error(f"Database initialization failed: {e}")
        raise

# ============================================================================
# Page routing
# ============================================================================

@app.route('/')
def index():
    """Serve the main landing page"""
    return send_from_directory(PAGES_DIR, "index.html")

@app.route('/<filename>')
def serve_root_files(filename):
    """Serve files from pages directory (CSS, HTML, etc.)"""
    if filename.endswith(('.css', '.ico', '.png', '.jpg', '.svg', '.html')):
        try:
            return send_from_directory(PAGES_DIR, filename)
        except FileNotFoundError:
            return jsonify({"error": "File not found"}), 404
    return jsonify({"error": "Not found"}), 404

@app.route('/pages/<path:filename>')
def serve_pages(filename):
    """Serve HTML pages"""
    try:
        return send_from_directory(PAGES_DIR, filename)
    except FileNotFoundError:
        return jsonify({"error": "Page not found"}), 404

@app.route('/scripts/<path:filename>')
def serve_scripts(filename):
    """Serve JavaScript files"""
    try:
        return send_from_directory(SCRIPTS_DIR, filename)
    except FileNotFoundError:
        return jsonify({"error": "Script not found"}), 404

@app.route('/static/<path:filename>')
def serve_static(filename):
    """Serve static files (JS, CSS, images, etc.)"""
    try:
        return send_from_directory(STATIC_DIR, filename)
    except FileNotFoundError:
        return jsonify({"error": "Static file not found"}), 404

# ============================================================================
# API Endpoints
# ============================================================================

@app.route('/api/users', methods=['POST'])
def create_user():
    """Create a new user account"""
    try:
        data = request.get_json()
        logger.info(f"Received signup request: {data}")
        
        # Validate required fields
        required_fields = ['name', 'email', 'password']
        missing_fields = [field for field in required_fields if not data.get(field)]
        
        if missing_fields:
            logger.warning(f"Missing fields: {missing_fields}")
            return jsonify({
                "success": False,
                "error": f"Missing required fields: {', '.join(missing_fields)}"
            }), 400
        
        # Basic email validation
        email = data.get('email').strip()
        if '@' not in email:
            return jsonify({
                "success": False,
                "error": "Invalid email format"
            }), 400
        
        # Insert user into database
        with get_db_connection() as conn:
            cursor = conn.execute(
                '''INSERT INTO users (name, email, password) 
                   VALUES (?, ?, ?)''',
                (data.get('name').strip(), email, data.get('password'))
            )
            user_id = cursor.lastrowid
        
        logger.info(f"Created user {user_id}: {email}")
        return jsonify({
            "success": True,
            "message": "User created successfully",
            "data": {
                "user_id": user_id,
                "name": data.get('name'),
                "email": email
            }
        }), 201
        
    except sqlite3.IntegrityError as e:
        logger.error(f"Integrity error (duplicate email?): {e}")
        return jsonify({
            "success": False,
            "error": "Email already exists"
        }), 409
    except Exception as e:
        logger.error(f"Error creating user: {e}", exc_info=True)
        return jsonify({"success": False, "error": str(e)}), 500

@app.route('/api/login', methods=['POST'])
def login_user():
    """Authenticate user by email and password"""
    try:
        data = request.get_json()

        # Validate input
        email = data.get('email', '').strip()
        password = data.get('password', '').strip()

        if not email or not password:
            return jsonify({
                "success": False,
                "error": "Email and password are required"
            }), 400

        # Query the database for user
        with get_db_connection() as conn:
            user = conn.execute('''
                SELECT user_id, name, email, password, creation_time, money_total, gains_losses
                FROM users
                WHERE email = ?
            ''', (email,)).fetchone()

        # Verify user exists
        if not user:
            return jsonify({
                "success": False,
                "error": "Invalid email or password"
            }), 401

        # Compare plain passwords (use hashing later)
        if password != user['password']:
            return jsonify({
                "success": False,
                "error": "Invalid email or password"
            }), 401

        # Successful login
        logger.info(f"User {email} logged in successfully")

        # Check if trending assets are already seeded
        try:
            with get_db_connection() as conn:
                # Check if any trending assets exist in the database
                trending_symbols = TRENDING_STOCKS + list(TRENDING_CRYPTO.values())
                placeholders = ','.join('?' * len(trending_symbols))
                
                existing_assets = conn.execute(f'''
                    SELECT COUNT(*) as count FROM assets
                    WHERE ticker_symbol IN ({placeholders})
                ''', trending_symbols).fetchone()
                
                if existing_assets['count'] >= len(trending_symbols):
                    # Assets already seeded, check if prices need updating
                    # Get the most recent update time
                    most_recent_update = conn.execute(f'''
                        SELECT MAX(update_time) as last_update FROM assets
                        WHERE ticker_symbol IN ({placeholders})
                    ''', trending_symbols).fetchone()
                    
                    # Only refresh if prices are stale (older than 5 minutes)
                    needs_update = should_update_price(most_recent_update['last_update'], minutes=5)
                    
                    if needs_update:
                        logger.info(f"Trending assets prices are stale, refreshing for user {email}")
                        
                        # Call the internal refresh logic
                        updated_count = 0
                        
                        # Fetch and update stock prices from Finnhub
                        for symbol in TRENDING_STOCKS:
                            try:
                                price_data = fetch_stock_price(symbol)
                                if price_data:
                                    conn.execute('''
                                        UPDATE assets 
                                        SET current_price = ?, high_24h = ?, low_24h = ?, price_change_24h = ?,
                                            update_time = CURRENT_TIMESTAMP
                                        WHERE ticker_symbol = ? AND asset_type = 'stock'
                                    ''', (price_data['current_price'], price_data['high_24h'], 
                                          price_data['low_24h'], price_data['price_change_24h'], symbol))
                                    updated_count += 1
                                    time.sleep(1)  # Rate limiting
                            except Exception as e:
                                logger.warning(f"Failed to fetch price for stock {symbol}: {e}")
                        
                        # Fetch and update crypto prices from CoinGecko
                        crypto_symbols = list(TRENDING_CRYPTO.values())
                        if crypto_symbols:
                            try:
                                crypto_to_gecko_id = {
                                    'BTC': 'bitcoin',
                                    'ETH': 'ethereum',
                                    'SOL': 'solana',
                                    'LTC': 'litecoin',
                                    'XRP': 'ripple'
                                }
                                gecko_ids = [crypto_to_gecko_id.get(sym, sym.lower()) for sym in crypto_symbols]
                                
                                crypto_prices = fetch_crypto_prices(gecko_ids)
                                
                                for gecko_id, symbol in zip(gecko_ids, crypto_symbols):
                                    if gecko_id in crypto_prices:
                                        price_data = crypto_prices[gecko_id]
                                        current_price = price_data.get('usd', 0)
                                        price_change = price_data.get('usd_24h_change', 0)
                                        
                                        conn.execute('''
                                            UPDATE assets 
                                            SET current_price = ?, price_change_24h = ?,
                                                update_time = CURRENT_TIMESTAMP
                                            WHERE ticker_symbol = ? AND asset_type = 'crypto'
                                        ''', (current_price, price_change, symbol))
                                        updated_count += 1
                            except Exception as e:
                                logger.warning(f"Failed to fetch crypto prices: {e}")
                        
                        logger.info(f"Refreshed prices for {updated_count} trending assets on login")
                    else:
                        logger.info(f"Trending asset prices are still fresh, skipping refresh for user {email}")
                else:
                    # Assets not fully seeded, seed them now
                    logger.info(f"Seeding trending assets for user {email}")
                    added_count = 0
                    
                    # Seed trending stocks
                    stock_names = {
                        'NVDA': 'NVIDIA Corporation',
                        'AAPL': 'Apple Inc.',
                        'MSFT': 'Microsoft Corporation',
                        'GOOGL': 'Alphabet Inc.',
                        'AMZN': 'Amazon.com Inc.'
                    }
                    
                    for symbol in TRENDING_STOCKS:
                        try:
                            conn.execute('''
                                INSERT OR IGNORE INTO assets (ticker_symbol, name, asset_type, current_price)
                                VALUES (?, ?, 'stock', 0)
                            ''', (symbol, stock_names.get(symbol, symbol)))
                            added_count += 1
                        except sqlite3.IntegrityError:
                            pass
                    
                    # Seed trending crypto
                    crypto_names = {
                        'BTC': 'Bitcoin',
                        'ETH': 'Ethereum',
                        'SOL': 'Solana',
                        'LTC': 'Litecoin',
                        'XRP': 'Ripple'
                    }
                    
                    for symbol in TRENDING_CRYPTO.values():
                        try:
                            conn.execute('''
                                INSERT OR IGNORE INTO assets (ticker_symbol, name, asset_type, current_price)
                                VALUES (?, ?, 'crypto', 0)
                            ''', (symbol, crypto_names.get(symbol, symbol)))
                            added_count += 1
                        except sqlite3.IntegrityError:
                            pass
                    
                    logger.info(f"Seeded {added_count} trending assets on login for user {email}")
                    
        except Exception as e:
            logger.warning(f"Failed to handle trending assets on login: {e}")

        # Trigger portfolio refresh (optional)
        # refresh_user_portfolio(user['user_id'])

        return jsonify({
            "success": True,
            "message": "Login successful",
            "data": {
                "user_id": user['user_id'],
                "name": user['name'],
                "email": user['email'],
                "creation_time": user['creation_time'],
                "money_total": user['money_total'],
                "gains_losses": user['gains_losses']
            }
        }), 200

    except Exception as e:
        logger.error(f"Error during login: {e}")
        return jsonify({"success": False, "error": str(e)}), 500

    
@app.route('/api/users/<int:user_id>', methods=['GET'])
def get_user(user_id):
    """Get user data by user_id"""
    try:
        with get_db_connection() as conn:
            user = conn.execute('''
                SELECT user_id, name, email, creation_time, update_time, gains_losses, money_total
                FROM users
                WHERE user_id = ?
            ''', (user_id,)).fetchone()
            
            if not user:
                return jsonify({
                    "success": False,
                    "error": "User not found"
                }), 404
            
            return jsonify({
                "success": True,
                "data": dict(user)
            })
    except Exception as e:
        logger.error(f"Error fetching user {user_id}: {e}")
        return jsonify({"success": False, "error": str(e)}), 500

@app.route('/api/users/<int:user_id>/add-money', methods=['POST'])
def add_money(user_id):
    """Add money to user's total balance"""
    try:
        data = request.get_json()
        amount = data.get('amount')
        
        # Validate amount
        if not amount or not isinstance(amount, (int, float)) or amount <= 0:
            return jsonify({
                "success": False,
                "error": "Invalid amount. Must be a positive number."
            }), 400
        
        logger.info(f"Adding ${amount} to user {user_id} balance")
        
        # Update user's money_total in database
        with get_db_connection() as conn:
            # First check if user exists
            user = conn.execute('SELECT user_id, money_total FROM users WHERE user_id = ?', (user_id,)).fetchone()
            
            if not user:
                return jsonify({
                    "success": False,
                    "error": "User not found"
                }), 404
            
            current_balance = user['money_total'] or 0
            new_balance = current_balance + amount
            
            # Update the balance
            conn.execute('''
                UPDATE users 
                SET money_total = ? 
                WHERE user_id = ?
            ''', (new_balance, user_id))
            
            logger.info(f"✓ Updated user {user_id} balance: ${current_balance} → ${new_balance}")
        
        return jsonify({
            "success": True,
            "message": f"Successfully added ${amount:.2f}",
            "data": {
                "user_id": user_id,
                "amount_added": amount,
                "previous_balance": current_balance,
                "new_balance": new_balance
            }
        }), 200
        
    except Exception as e:
        logger.error(f"Error adding money to user {user_id}: {e}", exc_info=True)
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/favorites', methods=['GET'])
def get_user_favorites():
    """Get favorites for a specific user"""
    try:
        user_id = request.args.get('user_id')
        
        if not user_id:
            return jsonify({
                "success": False,
                "error": "user_id parameter is required"
            }), 400
        
        with get_db_connection() as conn:
            # Check if user exists
            user = conn.execute('SELECT user_id FROM users WHERE user_id = ?', (user_id,)).fetchone()
            if not user:
                return jsonify({
                    "success": False,
                    "error": "User not found"
                }), 404
            
            favorites = conn.execute('''
                SELECT f.favorite_id, f.user_id, f.asset_id, f.creation_time,
                a.name as asset_name, a.ticker_symbol, a.asset_type,
                a.current_price, a.image,
                a.price_change_24h  
                FROM favorites f
                JOIN assets a ON f.asset_id = a.asset_id
                WHERE f.user_id = ?
                ORDER BY f.creation_time DESC
            ''', (user_id,)).fetchall()
            
            return jsonify({
                "success": True,
                "count": len(favorites),
                "data": [dict(row) for row in favorites]
            })
    except Exception as e:
        logger.error(f"Error fetching favorites: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/add-favorites', methods=['POST'])
def add_favorite():
    """Add an asset to user's favorites"""
    try:
        data = request.get_json()
        
        # Validate required fields
        required_fields = ['user_id', 'asset_id']
        missing_fields = [field for field in required_fields if not data.get(field)]
        
        if missing_fields:
            return jsonify({
                "success": False,
                "error": f"Missing required fields: {', '.join(missing_fields)}"
            }), 400
        
        with get_db_connection() as conn:
            # Check if user exists
            user = conn.execute('SELECT user_id FROM users WHERE user_id = ?', (data['user_id'],)).fetchone()
            if not user:
                return jsonify({"success": False, "error": "User not found"}), 404
            
            # Check if asset exists
            asset = conn.execute('SELECT * FROM assets WHERE asset_id = ?', (data['asset_id'],)).fetchone()
            if not asset:
                return jsonify({"success": False, "error": "Asset not found"}), 404
            
            # Add to favorites
            cursor = conn.execute(
                'INSERT INTO favorites (user_id, asset_id) VALUES (?, ?)',
                (data['user_id'], data['asset_id'])
            )
            
            favorite_id = cursor.lastrowid
            
            logger.info(f"User {data['user_id']} added {asset['ticker_symbol']} to favorites")
            
            return jsonify({
                "success": True,
                "message": "Added to favorites",
                "data": {
                    "favorite_id": favorite_id,
                    "asset_symbol": asset['ticker_symbol'],
                    "asset_name": asset['name'],
                    "asset_type": asset['asset_type']
                }
            }), 201
            
    except sqlite3.IntegrityError:
        return jsonify({
            "success": False,
            "error": "This asset is already in your favorites"
        }), 409
    except Exception as e:
        logger.error(f"Error adding favorite: {e}")
        return jsonify({"success": False, "error": str(e)}), 500

def get_asset_type(symbol):
    with get_db_connection() as conn:
        row = conn.execute(
            "SELECT asset_type FROM assets WHERE ticker_symbol = ?",
            (symbol.upper(),)
        ).fetchone()
        return row["asset_type"] if row else None


# Price history endpoint
@app.route("/api/price-history/<symbol>")
def price_history(symbol):
    try:
        symbol = symbol.upper()
        period = request.args.get("period", "7d").lower()

        # ----------------------------
        # Check asset type
        # ----------------------------
        with get_db_connection() as conn:
            asset = conn.execute("""
                SELECT asset_type
                FROM assets
                WHERE ticker_symbol = ?
            """, (symbol,)).fetchone()

        if not asset:
            return jsonify({"success": False, "error": "Unknown asset"}), 404

        # ==========================================================
        #  CRYPTO (CoinGecko) WITH CACHE
        # ==========================================================
        if asset["asset_type"] == "crypto":

            gecko_map = {
                "BTC": "bitcoin",
                "ETH": "ethereum",
                "SOL": "solana",
                "LTC": "litecoin",
                "XRP": "ripple"
            }
            gecko_id = gecko_map.get(symbol, symbol.lower())

            cache_ttl = 300  # 5 minutes
            
            # Use combined key for caching (symbol + period)
            cache_key = f"{symbol}_{period}"

            # 1) Try to load from cache
            with get_db_connection() as conn:
                cached = conn.execute("""
                    SELECT history_json, update_time
                    FROM price_history
                    WHERE ticker_symbol = ?
                    LIMIT 1
                """, (cache_key,)).fetchone()

            cached_history = None
            cached_time = None

            if cached:
                cached_history = json.loads(cached["history_json"])
                cached_time = cached["update_time"]

            # 2) Check if cache is still fresh
            if cached_time:
                try:
                    if isinstance(cached_time, str):
                        last = datetime.strptime(cached_time, "%Y-%m-%d %H:%M:%S")
                    else:
                        last = cached_time

                    age = (datetime.now() - last).total_seconds()
                    if age < 0:
                        age = 0

                    if age < cache_ttl:
                        print(f"✔ CACHE HIT for {symbol} ({period}) age={age}")
                        return jsonify({"success": True, "prices": cached_history})

                except Exception as e:
                    print("Cache timestamp parse error:", e)

            # 3) CACHE MISS → fetch from CoinGecko
            print(f"⚠ CACHE MISS → CoinGecko fetch ({symbol}, {period})")

            if period == "24h":
                url = f"https://api.coingecko.com/api/v3/coins/{gecko_id}/market_chart?vs_currency=usd&days=1"
            else:
                url = f"https://api.coingecko.com/api/v3/coins/{gecko_id}/market_chart?vs_currency=usd&days=7"

            r = requests.get(url)
            data = r.json()
            prices = [p[1] for p in data.get("prices", [])]

            # Save to cache
            if prices:
                with get_db_connection() as conn:

                    # Remove old cache with wrong key
                    conn.execute("DELETE FROM price_history WHERE ticker_symbol = ?", (symbol,))

                    # Delete old cache entry for this symbol+period combination
                    conn.execute("""
                        DELETE FROM price_history WHERE ticker_symbol = ?
                    """, (cache_key,))
                    
                    # Insert fresh data
                    conn.execute("""
                        INSERT INTO price_history (ticker_symbol, history_json)
                        VALUES (?, ?)
                    """, (cache_key, json.dumps(prices)))

            return jsonify({"success": True, "prices": prices})

        # ==========================================================
        #  STOCKS — SYNTHETIC PRICE HISTORY (NO API CALLS)
        # ==========================================================
        with get_db_connection() as conn:
            row = conn.execute("""
                SELECT current_price, price_change_24h
                FROM assets
                WHERE ticker_symbol = ?
            """, (symbol,)).fetchone()

        if not row:
            return jsonify({"success": False, "error": "Missing price data"}), 404

        current_price = float(row["current_price"])
        percent_change = float(row["price_change_24h"])  # ex: -1.10

        # Determine number of chart points
        if period == "24h":
            points = 24   # hourly
        else:
            points = 80    # daily

        # Starting price based on % change
        start_price = current_price / (1 + (percent_change / 100))

        prices = []
        import random

        import hashlib

        def stable_noise(symbol, period, index):
            # deterministic pseudo-noise based on symbol+period+index
            seed = f"{symbol}_{period}_{index}".encode()
            hash_val = hashlib.md5(seed).hexdigest()
            num = int(hash_val[:8], 16)  # take first 8 hex chars
            return (num / 0xFFFFFFFF) * 2 - 1  # map to [-1, 1]

        prices = []
        for i in range(points):
            progress = i / (points - 1)
            baseline = start_price + (current_price - start_price) * progress

            # deterministic noise
            base_noise = 0.0002 if abs(percent_change) < 0.3 else 0.002
            noise = stable_noise(symbol, period, i) * base_noise

            price = baseline * (1 + noise)
            prices.append(round(price, 2))


        return jsonify({"success": True, "prices": prices})

    except Exception as e:
        return jsonify({"success": False, "error": str(e)})



# Delete favorite endpoint
@app.route('/api/remove-favorite/<int:favorite_id>', methods=['DELETE'])
def remove_favorite(favorite_id):
    try:
        with get_db_connection() as conn:
            fav = conn.execute(
                'SELECT * FROM favorites WHERE favorite_id = ?',
                (favorite_id,)
            ).fetchone()

            if not fav:
                return jsonify({"success": False, "error": "Favorite not found"}), 404

            conn.execute('DELETE FROM favorites WHERE favorite_id = ?', (favorite_id,))
        
        return jsonify({"success": True, "message": "Favorite removed"}), 200

    except Exception as e:
        return jsonify({"success": False, "error": str(e)}), 500


# GET Asset by Symbol Endpoint
@app.route('/api/assets', methods=['GET'])
def get_asset_by_symbol():
    symbol = request.args.get('symbol', '').strip().upper()
    if not symbol:
        return jsonify({"success": False, "error": "symbol is required"}), 400

    with get_db_connection() as conn:
        asset = conn.execute(
            "SELECT * FROM assets WHERE ticker_symbol = ?",
            (symbol,)
        ).fetchone()

        if not asset:
            return jsonify({"success": False, "error": "Asset not found"}), 404

        return jsonify({"success": True, "data": dict(asset)}), 200




@app.route('/api/personal-assets', methods=['GET'])
def get_user_personal_assets():
    """Get personal assets for a specific user"""
    try:
        user_id = request.args.get('user_id')
        
        if not user_id:
            return jsonify({
                "success": False,
                "error": "user_id parameter is required"
            }), 400
        
        with get_db_connection() as conn:
            # Check if user exists
            user = conn.execute('SELECT user_id FROM users WHERE user_id = ?', (user_id,)).fetchone()
            if not user:
                return jsonify({
                    "success": False,
                    "error": "User not found"
                }), 404
            
            personal_assets = conn.execute('''
SELECT pa.personal_asset_id, pa.user_id, pa.asset_id, pa.quantity,
           pa.purchase_price, pa.purchase_date,  -- ADDED THESE
           a.name as asset_name, a.ticker_symbol, a.asset_type, a.current_price, a.image,
           (pa.quantity * a.current_price) as total_value,
           (pa.quantity * a.current_price) - (pa.quantity * pa.purchase_price) as gain_loss  -- ADDED THIS
    FROM personal_assets pa
    JOIN assets a ON pa.asset_id = a.asset_id
    WHERE pa.user_id = ?
    ORDER BY pa.personal_asset_id
            ''', (user_id,)).fetchall()
            
            return jsonify({
                "success": True,
                "count": len(personal_assets),
                "data": [dict(row) for row in personal_assets]
            })
    except Exception as e:
        logger.error(f"Error fetching personal assets: {e}")
        return jsonify({"success": False, "error": str(e)}), 500

# ============================================================================
# API Helper Functions
# ============================================================================

def fetch_stock_price(symbol):
    """Fetch current stock price and 24h data from Finnhub"""
    try:
        url = f"{FINNHUB_BASE_URL}/quote"
        params = {
            'symbol': symbol,
            'token': FINNHUB_API_KEY
        }
        response = requests.get(url, params=params, timeout=10)
        response.raise_for_status()
        data = response.json()
        
        # Finnhub returns: c=current, h=high, l=low, pc=previous close, dp=change percent
        if 'c' in data and data['c'] > 0:
            return {
                'current_price': data['c'],
                'high_24h': data.get('h', 0),
                'low_24h': data.get('l', 0),
                'price_change_24h': data.get('dp', 0)  # daily percent change
            }
        
        logger.warning(f"No valid price data for {symbol}")
        return None
    except Exception as e:
        logger.error(f"Error fetching stock price for {symbol}: {e}")
        return None


def fetch_crypto_prices(coin_ids):
    """Fetch multiple crypto prices from CoinGecko in one call"""
    try:
        url = f"{COINGECKO_BASE_URL}/simple/price"
        params = {
            'ids': ','.join(coin_ids),
            'vs_currencies': 'usd',
            'include_24hr_change': 'true'
        }
        response = requests.get(url, params=params, timeout=10)
        response.raise_for_status()
        return response.json()
    except Exception as e:
        logger.error(f"Error fetching crypto prices: {e}")
        return {}


def should_update_price(update_time_str, minutes=15):
    """Check if price is stale (older than specified minutes)"""
    if not update_time_str:
        return True
    
    try:
        # Parse SQLite timestamp
        last_update = datetime.fromisoformat(update_time_str.replace(' ', 'T'))
        time_diff = datetime.now() - last_update
        return time_diff > timedelta(minutes=minutes)
    except Exception:
        return True


# ============================================================================
# Portfolio Refresh Endpoint
# ============================================================================

@app.route('/api/users/<int:user_id>/refresh-portfolio', methods=['POST'])
@limiter.limit("1 per 5 minutes")
def refresh_user_portfolio(user_id):
    """
    Refresh portfolio on user login:
    1. Fetch current prices for user's assets
    2. Update trending assets (top 5 stocks + 5 crypto)
    3. Calculate portfolio totals and gains/losses
    4. Update user stats
    """
    try:
        with get_db_connection() as conn:
            # Check if user exists
            user = conn.execute('SELECT * FROM users WHERE user_id = ?', (user_id,)).fetchone()
            if not user:
                return jsonify({
                    "success": False,
                    "error": "User not found"
                }), 404
            
            # Get user's personal assets with asset details
            personal_assets = conn.execute('''
                SELECT pa.*, a.ticker_symbol, a.asset_type, a.current_price, a.update_time
                FROM personal_assets pa
                JOIN assets a ON pa.asset_id = a.asset_id
                WHERE pa.user_id = ?
            ''', (user_id,)).fetchall()
            
            # Collect unique assets that need updating
            stocks_to_update = set()
            crypto_to_update = set()
            
            for asset in personal_assets:
                if should_update_price(asset['update_time']):
                    if asset['asset_type'] == 'stock':
                        stocks_to_update.add((asset['asset_id'], asset['ticker_symbol']))
                    elif asset['asset_type'] == 'crypto':
                        crypto_to_update.add((asset['asset_id'], asset['ticker_symbol']))
            
            # Also update trending assets
            trending_assets = conn.execute('''
                SELECT asset_id, ticker_symbol, asset_type, update_time
                FROM assets
                WHERE ticker_symbol IN (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
            ''', TRENDING_STOCKS + list(TRENDING_CRYPTO.values())).fetchall()
            
            for asset in trending_assets:
                if should_update_price(asset['update_time']):
                    if asset['asset_type'] == 'stock':
                        stocks_to_update.add((asset['asset_id'], asset['ticker_symbol']))
                    elif asset['asset_type'] == 'crypto':
                        crypto_to_update.add((asset['asset_id'], asset['ticker_symbol']))
            
            # Fetch and update stock prices (with rate limiting)
            updated_count = 0
            for asset_id, symbol in stocks_to_update:
                price_data = fetch_stock_price(symbol)
                if price_data:
                    conn.execute(
                        '''UPDATE assets 
                           SET current_price = ?, high_24h = ?, low_24h = ?, price_change_24h = ?,
                               update_time = CURRENT_TIMESTAMP 
                           WHERE asset_id = ?''',
                        (price_data['current_price'], price_data['high_24h'], 
                         price_data['low_24h'], price_data['price_change_24h'], asset_id)
                    )
                    updated_count += 1
                    time.sleep(1)  # Rate limiting: 1 request/second (under 60/min limit)
            
            # Fetch and update crypto prices (batch call)
            if crypto_to_update:
                # Map ticker symbols to CoinGecko IDs
                crypto_id_map = {v: k for k, v in TRENDING_CRYPTO.items()}
                crypto_ids = [crypto_id_map.get(symbol) for _, symbol in crypto_to_update if crypto_id_map.get(symbol)]
                
                if crypto_ids:
                    crypto_prices = fetch_crypto_prices(crypto_ids)
                    
                    for asset_id, symbol in crypto_to_update:
                        coin_id = crypto_id_map.get(symbol)
                        if coin_id and coin_id in crypto_prices:
                            price = crypto_prices[coin_id].get('usd')
                            if price:
                                conn.execute(
                                    'UPDATE assets SET current_price = ?, update_time = CURRENT_TIMESTAMP WHERE asset_id = ?',
                                    (price, asset_id)
                                )
                                updated_count += 1
            
            # Calculate user's total portfolio value and gains/losses
            portfolio_data = conn.execute('''
                SELECT 
                    SUM(pa.quantity * a.current_price) as total_value,
                    SUM(pa.quantity * pa.purchase_price) as total_invested,
                    COUNT(*) as asset_count
                FROM personal_assets pa
                JOIN assets a ON pa.asset_id = a.asset_id
                WHERE pa.user_id = ?
            ''', (user_id,)).fetchone()
            
            total_value = portfolio_data['total_value'] or 0
            total_invested = portfolio_data['total_invested'] or 0
            gains_losses = total_value - total_invested
            
            # Update user stats with calculated portfolio totals
            conn.execute(
                '''UPDATE users 
                   SET money_total = ?, gains_losses = ?, update_time = CURRENT_TIMESTAMP 
                   WHERE user_id = ?''',
                (total_value, gains_losses, user_id)
            )
            
            logger.info(f"Refreshed portfolio for user {user_id}: {updated_count} prices updated, total value: ${total_value:.2f}, gains/losses: ${gains_losses:.2f}")
            
            return jsonify({
                "success": True,
                "message": "Portfolio refreshed successfully",
                "data": {
                    "user_id": user_id,
                    "prices_updated": updated_count,
                    "total_portfolio_value": round(total_value, 2),
                    "total_invested": round(total_invested, 2),
                    "gains_losses": round(gains_losses, 2),
                    "gains_losses_percentage": round((gains_losses / total_invested * 100) if total_invested > 0 else 0, 2),
                    "asset_count": portfolio_data['asset_count']
                }
            })
            
    except Exception as e:
        logger.error(f"Error refreshing portfolio for user {user_id}: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


# ============================================================================
# API Health Check
# ============================================================================

@app.route('/api/personal-assets', methods=['POST'])
def add_personal_asset():
    """Add an asset to user's portfolio (buy stock/crypto)"""
    try:
        data = request.get_json()
        
        # Validate required fields
        required_fields = ['user_id', 'asset_id', 'quantity', 'purchase_price']
        missing_fields = [field for field in required_fields if not data.get(field)]
        
        if missing_fields:
            return jsonify({
                "success": False,
                "error": f"Missing required fields: {', '.join(missing_fields)}"
            }), 400
        
        with get_db_connection() as conn:
            # Check if user exists
            user = conn.execute('SELECT user_id FROM users WHERE user_id = ?', (data['user_id'],)).fetchone()
            if not user:
                return jsonify({"success": False, "error": "User not found"}), 404
            
            # Check if asset exists
            asset = conn.execute('SELECT * FROM assets WHERE asset_id = ?', (data['asset_id'],)).fetchone()
            if not asset:
                return jsonify({"success": False, "error": "Asset not found"}), 404
            
            # Add to personal_assets
            cursor = conn.execute(
                '''INSERT INTO personal_assets (user_id, asset_id, quantity, purchase_price)
                   VALUES (?, ?, ?, ?)''',
                (data['user_id'], data['asset_id'], data['quantity'], data['purchase_price'])
            )
            
            personal_asset_id = cursor.lastrowid
            
            logger.info(f"User {data['user_id']} bought {data['quantity']} of {asset['ticker_symbol']} at ${data['purchase_price']}")
            
            return jsonify({
                "success": True,
                "message": "Asset added to portfolio",
                "data": {
                    "personal_asset_id": personal_asset_id,
                    "asset_symbol": asset['ticker_symbol'],
                    "asset_name": asset['name'],
                    "quantity": data['quantity'],
                    "purchase_price": data['purchase_price'],
                    "total_cost": round(data['quantity'] * data['purchase_price'], 2)
                }
            }), 201
            
    except sqlite3.IntegrityError:
        return jsonify({
            "success": False,
            "error": "You already own this asset. Use update endpoint to modify quantity."
        }), 409
    except Exception as e:
        logger.error(f"Error adding personal asset: {e}")
        return jsonify({"success": False, "error": str(e)}), 500
    
@app.route('/api/personal-assets', methods=['PUT'])
def update_personal_asset():
    data = request.get_json()

    asset_id = data.get('personal_asset_id')
    quantity = data.get('quantity')
    purchase_price = data.get('purchase_price')

    with get_db_connection() as conn:
        conn.execute("""
            UPDATE personal_assets
            SET quantity = ?, purchase_price = ?
            WHERE personal_asset_id = ?
        """, (quantity, purchase_price, asset_id))
        conn.commit()

    return jsonify({"success": True, "message": "Asset updated"}), 200

# Delete endpoint
@app.route('/api/personal-assets', methods=['DELETE'])
def delete_personal_asset():
    data = request.get_json()
    asset_id = data.get('personal_asset_id')

    with get_db_connection() as conn:
        conn.execute("""
            DELETE FROM personal_assets
            WHERE personal_asset_id = ?
        """, (asset_id,))
        conn.commit()

    return jsonify({"success": True, "message": "Asset removed"}), 200


@app.route('/api/assets/search', methods=['GET'])
def search_assets():
    """Search for assets by ticker symbol or name"""
    try:
        query = request.args.get('q', '').strip()
        
        if not query:
            return jsonify({
                "success": False,
                "error": "Query parameter 'q' is required"
            }), 400
        
        with get_db_connection() as conn:
            # Search by ticker_symbol or name (case-insensitive)
            assets = conn.execute('''
                SELECT * FROM assets
                WHERE UPPER(ticker_symbol) LIKE UPPER(?) 
                   OR UPPER(name) LIKE UPPER(?)
                ORDER BY ticker_symbol
                LIMIT 20
            ''', (f'%{query}%', f'%{query}%')).fetchall()
            
            return jsonify({
                "success": True,
                "count": len(assets),
                "data": [dict(row) for row in assets]
            })
    except Exception as e:
        logger.error(f"Error searching assets: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/assets/trending', methods=['GET'])
def get_trending_assets():
    """Get the trending assets (top 5 stocks + 5 crypto) from database"""
    try:
        with get_db_connection() as conn:
            # Get trending symbols
            trending_symbols = TRENDING_STOCKS + list(TRENDING_CRYPTO.values())
            placeholders = ','.join('?' * len(trending_symbols))
            
            assets = conn.execute(f'''
                SELECT * FROM assets
                WHERE ticker_symbol IN ({placeholders})
                ORDER BY 
                    CASE 
                        WHEN asset_type = 'stock' THEN 0
                        WHEN asset_type = 'crypto' THEN 1
                    END,
                    COALESCE(price_change_24h, 0) DESC
            ''', trending_symbols).fetchall()
            
            return jsonify({
                "success": True,
                "count": len(assets),
                "data": [dict(row) for row in assets]
            })
    except Exception as e:
        logger.error(f"Error fetching trending assets: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/assets/trending/refresh', methods=['POST'])
@limiter.limit("1 per 5 minutes")
def refresh_trending_assets_prices():
    """Refresh prices for trending assets from APIs (Finnhub and CoinGecko)"""
    try:
        with get_db_connection() as conn:
            # Get trending symbols
            stocks = TRENDING_STOCKS
            crypto_symbols = list(TRENDING_CRYPTO.values())
            updated_count = 0
            
            # Fetch and update stock prices from Finnhub
            for symbol in stocks:
                try:
                    price_data = fetch_stock_price(symbol)
                    if price_data:
                        conn.execute('''
                            UPDATE assets 
                            SET current_price = ?, price_change_24h = ?
                            WHERE ticker_symbol = ? AND asset_type = 'stock'
                        ''', (price_data['current_price'], price_data['price_change_24h'], symbol))
                        updated_count += 1
                except Exception as e:
                    logger.warning(f"Failed to fetch price for stock {symbol}: {e}")
            
            # Fetch and update crypto prices from CoinGecko
            if crypto_symbols:
                try:
                    crypto_to_gecko_id = {
                        'BTC': 'bitcoin',
                        'ETH': 'ethereum',
                        'SOL': 'solana',
                        'LTC': 'litecoin',
                        'XRP': 'ripple'
                    }
                    gecko_ids = [crypto_to_gecko_id.get(sym, sym.lower()) for sym in crypto_symbols]
                    
                    crypto_prices = fetch_crypto_prices(gecko_ids)
                    
                    for gecko_id, symbol in zip(gecko_ids, crypto_symbols):
                        if gecko_id in crypto_prices:
                            price_data = crypto_prices[gecko_id]
                            current_price = price_data.get('usd', 0)
                            price_change = price_data.get('usd_24h_change', 0)
                            
                            conn.execute('''
                                UPDATE assets 
                                SET current_price = ?, price_change_24h = ?
                                WHERE ticker_symbol = ? AND asset_type = 'crypto'
                            ''', (current_price, price_change, symbol))
                            updated_count += 1
                except Exception as e:
                    logger.warning(f"Failed to fetch crypto prices: {e}")
            
            logger.info(f"Refreshed prices for {updated_count} trending assets")
            
            return jsonify({
                "success": True,
                "message": "Trending asset prices refreshed successfully",
                "data": {
                    "assets_updated": updated_count
                }
            })
    except Exception as e:
        logger.error(f"Error refreshing trending asset prices: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/seed-trending-assets', methods=['POST'])
@limiter.limit("1 per 5 minutes")
def seed_trending_assets():
    """
    Seed the database with trending stocks and crypto.
    Call this once to populate the assets table with the 10 trending assets.
    """
    try:
        with get_db_connection() as conn:
            added_count = 0
            
            # Seed trending stocks
            stock_names = {
                'NVDA': 'NVIDIA Corporation',
                'AAPL': 'Apple Inc.',
                'MSFT': 'Microsoft Corporation',
                'GOOGL': 'Alphabet Inc.',
                'AMZN': 'Amazon.com Inc.'
            }
            
            for symbol in TRENDING_STOCKS:
                try:
                    conn.execute('''
                        INSERT OR IGNORE INTO assets (ticker_symbol, name, asset_type, current_price)
                        VALUES (?, ?, 'stock', 0)
                    ''', (symbol, stock_names.get(symbol, symbol)))
                    added_count += 1
                except sqlite3.IntegrityError:
                    pass  # Asset already exists
            
            # Seed trending crypto
            crypto_names = {
                'BTC': 'Bitcoin',
                'ETH': 'Ethereum',
                'SOL': 'Solana',
                'LTC': 'Litecoin',
                'XRP': 'Ripple'
            }
            
            for symbol in TRENDING_CRYPTO.values():
                try:
                    conn.execute('''
                        INSERT OR IGNORE INTO assets (ticker_symbol, name, asset_type, current_price)
                        VALUES (?, ?, 'crypto', 0)
                    ''', (symbol, crypto_names.get(symbol, symbol)))
                    added_count += 1
                except sqlite3.IntegrityError:
                    pass
            
            logger.info(f"Seeded {added_count} trending assets")
            
            return jsonify({
                "success": True,
                "message": "Trending assets seeded successfully",
                "data": {
                    "assets_added": added_count,
                    "stocks": TRENDING_STOCKS,
                    "crypto": list(TRENDING_CRYPTO.values())
                }
            })
    except Exception as e:
        logger.error(f"Error seeding trending assets: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


# ============================================================================
# Comments API (MongoDB)
# ============================================================================

@app.route('/api/comments', methods=['GET'])
def get_comments():
    """Get all comments from MongoDB"""
    try:
        # Get comments sorted by creation time (newest first)
        comments = list(comments_collection.find().sort('created_at', -1).limit(100))
        
        # Convert ObjectId to string for JSON serialization
        for comment in comments:
            comment['_id'] = str(comment['_id'])
        
        return jsonify({
            "success": True,
            "count": len(comments),
            "data": comments
        })
    except Exception as e:
        logger.error(f"Error fetching comments: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/comments', methods=['POST'])
@limiter.limit("10 per minute")
def create_comment():
    """Create a new comment in MongoDB"""
    try:
        data = request.get_json()
        
        # Validate required fields
        if not data.get('user_id') or not data.get('user_name') or not data.get('comment_text'):
            return jsonify({
                "success": False,
                "error": "user_id, user_name, and comment_text are required"
            }), 400
        
        # Create comment document
        comment = {
            'user_id': int(data['user_id']),
            'user_name': data['user_name'],
            'comment_text': data['comment_text'].strip(),
            'created_at': datetime.now().isoformat()
        }
        
        # Insert into MongoDB
        result = comments_collection.insert_one(comment)
        comment['_id'] = str(result.inserted_id)
        
        logger.info(f"User {data['user_name']} posted a comment")
        
        return jsonify({
            "success": True,
            "message": "Comment posted successfully",
            "data": comment
        }), 201
        
    except Exception as e:
        logger.error(f"Error creating comment: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/comments/<comment_id>', methods=['DELETE'])
def delete_comment(comment_id):
    """Delete a comment from MongoDB"""
    try:
        # Delete the comment
        result = comments_collection.delete_one({'_id': ObjectId(comment_id)})
        
        if result.deleted_count == 0:
            return jsonify({
                "success": False,
                "error": "Comment not found"
            }), 404
        
        logger.info(f"Deleted comment {comment_id}")
        
        return jsonify({
            "success": True,
            "message": "Comment deleted successfully"
        })
        
    except Exception as e:
        logger.error(f"Error deleting comment: {e}")
        return jsonify({"success": False, "error": str(e)}), 500


@app.route('/api/health')
def health_check():
    """API health check endpoint"""
    return jsonify({
        "message": "G7 Finance API",
        "status": "running",
        "version": "1.0.0",
        "database": "connected" if DB_PATH.exists() else "not found"
    })

@app.errorhandler(404)
def not_found(e):
    """Handle 404 errors"""
    return jsonify({"success": False, "error": "Resource not found"}), 404


@app.errorhandler(500)
def internal_error(e):
    """Handle 500 errors"""
    logger.error(f"Internal server error: {e}")
    return jsonify({"success": False, "error": "Internal server error"}), 500

# ============================================================================
# Application Entry Point
# ============================================================================

if __name__ == '__main__':
    # Initialize database on startup
    logger.info("Starting G7 Finance application...")
    init_db()
    
    # Get configuration from environment
    port = int(os.environ.get('PORT', 5000))
    debug = os.environ.get('FLASK_ENV') == 'development'
    
    # Run Flask app
    logger.info(f"Server running on http://127.0.0.1:{port}")
    app.run(debug=True, host='0.0.0.0', port=port)
