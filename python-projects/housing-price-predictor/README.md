# Housing Price Predictor

## Overview
This is a Flask-based web application that predicts home prices using a trained **Random Forest regression model** built from the **Ames Housing dataset**.  
Users can input basic home attributes — such as square footage, number of bedrooms, bathrooms, garage size, year built, and lot area — and receive an estimated market value.  
The model is trained using `train-new-model.py` and deployed through the Flask server `app.py`.

## Features
- **Interactive Web Form:** Simple and user-friendly interface to input housing details.  
- **Machine Learning Integration:** Uses a trained Random Forest model for accurate price prediction.  
- **Error Handling:** Displays clear messages for missing inputs or invalid values.  
- **Reusable Model:** The trained model is saved as `housing_model.pkl` and can be reloaded instantly.  
- **Clean UI Design:** Minimalist HTML/CSS interface optimized for readability and responsiveness.  
- **Modular Structure:** Training and deployment are separated into distinct scripts for clarity.  

## File Structure
- **train-new-model.py:** Trains a Random Forest regression model on the Ames Housing dataset and saves it as `housing_model.pkl`. :contentReference[oaicite:0]{index=0}
- **app.py:** Flask web app that loads the saved model, handles input, and returns predictions. :contentReference[oaicite:1]{index=1}
- **index.html:** Main user interface with a form to enter housing details. :contentReference[oaicite:2]{index=2}
- **result.html:** Displays the predicted price or any error messages. :contentReference[oaicite:3]{index=3}
- **style.css:** Provides clean, modern styling for all HTML templates. :contentReference[oaicite:4]{index=4}
- **housing_model.pkl:** Serialized trained model created by the training script.

## Requirements
- Python 3.10 or later  
- Required libraries:
  ```bash
  pip install flask pandas scikit-learn joblib numpy
  ```
- Web browser (Chrome, Firefox, Edge, etc.)

## How to Run
1. Train the Model (Run the training script):
  ```bash
  python train-new-model.py
  ```
2. Launch the Web App (Start the Flask server)
  ```bash
  python app.py
  ```
  The application will start on:
  ```cpp
  http://127.0.0.1:5000/
  ```
3. Use the Predictor:
	1. Open the link in a browser.
	2. Enter housing attributes (square footage, bedrooms, bathrooms, etc.).
	3. Click “Predict Price” to receive the estimated value.
	4. To test another home, click “← Try Another Prediction.”

## Technical Details
- Model: Random Forest Regressor (n_estimators=150, random_state=42)
- Dataset: Ames Housing (via fetch_openml)
- Evaluation Metric: Root Mean Squared Error (RMSE)
- Framework: Flask (for serving and UI rendering)
- Frontend: HTML5 + CSS3

## Future Improvements
- Add more input features (e.g., neighborhood, overall quality).
- Display model confidence intervals or range predictions.
- Integrate a map API for location-based visualization.
- Deploy on a live cloud service (Heroku, Render, or AWS).

## License
This project is for educational and personal use.
Retain the copyright notice:
“Thomas Hoerger – Copyright © 2025 Housing Price Predictor”