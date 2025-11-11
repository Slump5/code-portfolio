# Author: Thomas Hoerger
# Copyright: Thomas Hoerger – Copyright © 2025 Housing Price Predictor
# File: app.py
# Date: November 10, 2025
# Description:
# Flask web app for predicting home prices using Ames Housing data.

from flask import Flask, render_template, request
import pandas as pd
import joblib

app = Flask(__name__)

# Load trained model
model = joblib.load("housing_model.pkl")

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/predict", methods=["POST"])
def predict():
    try:
        # Match exact feature names from training data (no spaces)
        input_data = pd.DataFrame([{
            "GrLivArea": float(request.form["GrLivArea"]),
            "BedroomAbvGr": float(request.form["BedroomAbvGr"]),
            "FullBath": float(request.form["FullBath"]),
            "GarageCars": float(request.form["GarageCars"]),
            "YearBuilt": float(request.form["YearBuilt"]),
            "LotArea": float(request.form["LotArea"])
        }])

        # Predict using trained model
        predicted_value = model.predict(input_data)[0]
        price = f"${predicted_value:,.0f}"
        message = f"Estimated Home Value: {price} 🏡"

        return render_template("result.html", prediction_text=message)

    except Exception as e:
        return render_template("result.html", prediction_text=f"⚠️ Error: {e}")

if __name__ == "__main__":
    app.run(debug=True)

