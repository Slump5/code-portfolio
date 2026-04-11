# Quick Start Guide - Portfolio Refresh API

## 🚀 Setup Steps

### 1. Install Dependencies

```bash
cd server
pip install -r requirements.txt
```

### 2. Get Finnhub API Key

1. Visit https://finnhub.io/register
2. Sign up for a free account
3. Copy your API key from the dashboard

### 3. Create .env File

Create a file named `.env` in the `server` folder:

```env
FH_API_KEY=paste_your_finnhub_key_here
CG_API_KEY=
```

**Example:**

```env
FH_API_KEY=ctabcdefg123456789
CG_API_KEY=
```

### 4. Start the Server

```bash
python app.py
```

### 5. Seed Trending Assets (One-time)

```bash
curl -X POST http://127.0.0.1:5000/api/seed-trending-assets
```

This populates the database with:

- **Stocks:** NVDA, AAPL, MSFT, GOOGL, AMZN
- **Crypto:** BTC, ETH, SOL, LTC, XRP

## 📊 Using the Portfolio Refresh

### On User Login - Call This Endpoint:

```bash
POST http://127.0.0.1:5000/api/users/<user_id>/refresh-portfolio
```

**Example:**

```bash
curl -X POST http://127.0.0.1:5000/api/users/1/refresh-portfolio
```

**What It Does:**

1. ✅ Fetches current prices for user's owned assets (Finnhub + CoinGecko)
2. ✅ Updates trending assets (if stale > 15 minutes)
3. ✅ Calculates total portfolio value
4. ✅ Updates user's `money_total` in database
5. ✅ Returns updated portfolio stats

**Response:**

```json
{
	"success": true,
	"message": "Portfolio refreshed successfully",
	"data": {
		"user_id": 1,
		"prices_updated": 8,
		"total_portfolio_value": 12500.5,
		"asset_count": 5
	}
}
```

## 🎯 Integration with Frontend

```javascript
// On user login (after authentication):
async function onUserLogin(userId) {
	try {
		const response = await fetch(
			`http://127.0.0.1:5000/api/users/${userId}/refresh-portfolio`,
			{ method: 'POST' }
		);
		const data = await response.json();

		if (data.success) {
			console.log(`Portfolio refreshed: $${data.data.total_portfolio_value}`);
			// Redirect to dashboard
			window.location.href = '/dashboard.html';
		}
	} catch (error) {
		console.error('Failed to refresh portfolio:', error);
		// Still allow login, just use cached prices
		window.location.href = '/dashboard.html';
	}
}
```

## 🔧 Features

### Smart Caching

- Prices are cached for 15 minutes
- Multiple logins within 15 min won't hit APIs
- Reduces API calls and speeds up login

### Rate Limiting

- Finnhub: 1 request/second (under 60/min limit)
- CoinGecko: Batch calls for multiple crypto prices
- Prevents hitting rate limits

### Error Handling

- If API fails, uses last cached price
- Logs errors for debugging
- Won't crash on API timeout

## 📈 API Call Budget

**Per User Login (worst case):**

- User's stocks: ~5 calls (Finnhub)
- User's crypto: 1 call (CoinGecko batch)
- Trending assets: ~10 calls (if all stale)
- **Total:** ~16 API calls

**With 15-min caching:**

- Subsequent logins within 15 min: 0 API calls!

**Finnhub Daily Budget:**

- Unlimited logins (no daily limit!)
- Only limited by 60/min rate

## 🐛 Troubleshooting

### "No valid price data" error

- Check your Finnhub API key is correct
- Verify the stock symbol exists (use valid tickers)

### Rate limit exceeded

- App includes 1-second delays between calls
- Should not happen under normal use
- If it does, prices will use cached values

### Database not initialized

- Make sure you ran the server at least once
- Check `server/db/assets.db` exists
- Run seed endpoint to populate trending assets

## 📝 Next Steps

1. **Add more assets:** Insert into `assets` table
2. **Track purchases:** Add purchase price to `personal_assets`
3. **Calculate gains:** Compare current vs purchase price
4. **Display trending:** Query assets with `ticker_symbol IN (...)`
