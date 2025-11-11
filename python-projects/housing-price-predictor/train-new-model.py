# Author: Thomas Hoerger
# Copyright: Thomas Hoerger – Copyright © 2025 Housing Price Predictor
# File: train-new-model.py
# Date: November 10, 2025
# Description:
# Trains a Random Forest regression model using the Ames Housing dataset
# loaded directly from OpenML (permanent). Saves trained model as housing_model.pkl.


import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error
from sklearn.datasets import fetch_openml
import joblib


# 1. Load dataset from OpenML
print("📥 Loading dataset from OpenML (Ames Housing)...")
df = fetch_openml(name="house_prices", as_frame=True).frame
print(f"✅ Dataset loaded successfully with {df.shape[0]} rows and {df.shape[1]} columns.\n")


# 2. Select relevant columns
columns = ["GrLivArea", "BedroomAbvGr", "FullBath", "GarageCars", "YearBuilt", "LotArea"]
target = "SalePrice"

df = df[columns + [target]].dropna()
X = df[columns]
y = df[target]


# 3. Split into training/testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
print(f"Training samples: {X_train.shape[0]} | Testing samples: {X_test.shape[0]}")


# 4. Train model
print("\n🚀 Training Random Forest model...")
model = RandomForestRegressor(n_estimators=150, random_state=42, n_jobs=-1)
model.fit(X_train, y_train)

# 5. Evaluate model
preds = model.predict(X_test)
rmse = np.sqrt(mean_squared_error(y_test, preds))
print(f"✅ Training complete. RMSE on test set: {rmse:,.2f}")

# 6. Save trained model
joblib.dump(model, "housing_model.pkl")
print("💾 Model saved as housing_model.pkl (ready for Flask app)\n")

print("Done! You can now run 'python app.py' to use the new model.")
