-- G7 Finance Database Site
-- © 2024 G7 Finance. All rights reserved.

-- G7 Finance Database Schema (SQLite)

-- assets table
CREATE TABLE IF NOT EXISTS assets (
    asset_id      INTEGER PRIMARY KEY AUTOINCREMENT,
    asset_type    TEXT NOT NULL CHECK(asset_type IN ('stock', 'crypto')),
    name          TEXT NOT NULL,
    current_price REAL DEFAULT 0,
    ticker_symbol TEXT NOT NULL,
    image         TEXT,
    price_change_24h REAL DEFAULT 0,  -- 24-hour price change percentage
    high_24h      REAL DEFAULT 0,     -- 24-hour high price
    low_24h       REAL DEFAULT 0,     -- 24-hour low price
    update_time   TEXT DEFAULT CURRENT_TIMESTAMP,
    UNIQUE (ticker_symbol, asset_type)
);

-- users table
CREATE TABLE IF NOT EXISTS users (
    user_id       INTEGER PRIMARY KEY AUTOINCREMENT,
    name          TEXT NOT NULL,
    email         TEXT UNIQUE NOT NULL,
    password      TEXT NOT NULL,
    creation_time TEXT DEFAULT CURRENT_TIMESTAMP,
    update_time   TEXT DEFAULT CURRENT_TIMESTAMP,
    gains_losses  REAL DEFAULT 0, 
    money_total   REAL DEFAULT 0
);

-- personal_assets table (user's owned assets)
CREATE TABLE IF NOT EXISTS personal_assets (
    personal_asset_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id           INTEGER NOT NULL,
    asset_id          INTEGER NOT NULL,
    quantity          REAL NOT NULL CHECK (quantity >= 0),
    purchase_price    REAL NOT NULL,  -- Price when user bought this asset
    purchase_date     TEXT DEFAULT CURRENT_TIMESTAMP,
    UNIQUE (user_id, asset_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (asset_id) REFERENCES assets(asset_id) ON DELETE RESTRICT
);

-- favorites table
CREATE TABLE IF NOT EXISTS favorites (
    favorite_id   INTEGER PRIMARY KEY AUTOINCREMENT,
    creation_time TEXT DEFAULT CURRENT_TIMESTAMP,
    user_id       INTEGER NOT NULL,
    asset_id      INTEGER NOT NULL,
    UNIQUE (user_id, asset_id),
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (asset_id) REFERENCES assets(asset_id) ON DELETE CASCADE
);

-- price_history table
CREATE TABLE IF NOT EXISTS price_history (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    ticker_symbol TEXT NOT NULL,
    history_json TEXT NOT NULL,
    update_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- indexes for better query performance
CREATE INDEX IF NOT EXISTS idx_personal_assets_user ON personal_assets(user_id);
CREATE INDEX IF NOT EXISTS idx_personal_assets_asset ON personal_assets(asset_id);
CREATE INDEX IF NOT EXISTS idx_favorites_user ON favorites(user_id);
CREATE INDEX IF NOT EXISTS idx_favorites_asset ON favorites(asset_id);

-- triggers to update timestamp on user updates
CREATE TRIGGER IF NOT EXISTS update_users_timestamp 
AFTER UPDATE ON users
BEGIN
    UPDATE users SET update_time = CURRENT_TIMESTAMP WHERE user_id = NEW.user_id;
END;

CREATE TRIGGER IF NOT EXISTS update_assets_timestamp 
AFTER UPDATE ON assets
BEGIN
    UPDATE assets SET update_time = CURRENT_TIMESTAMP WHERE asset_id = NEW.asset_id;
END;

SELECT * FROM users;

select * from assets;