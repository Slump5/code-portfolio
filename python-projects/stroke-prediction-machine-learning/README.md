# Stroke Prediction Using Machine Learning

🎥 **Demo Video:** Included in this repository (`stroke-prediction-demo.mp4`)

---

## Overview
This project explores the use of **machine learning models** to predict stroke risk using real-world patient health data.

The goal is to determine:
- Which model performs best for stroke prediction  
- Which features are most important  
- How class imbalance affects model performance  

The project uses a dataset of over **5,000 patient records**, including demographic, lifestyle, and medical factors.

---

## Key Features
- Multiple machine learning models:
  - Logistic Regression  
  - Random Forest  
  - Gradient Boosting  
  - Neural Network  

- Data preprocessing:
  - Missing value handling (BMI imputation)  
  - One-hot encoding for categorical variables  
  - Feature scaling (StandardScaler)  

- Model evaluation:
  - Precision, Recall, F1-score, ROC-AUC  
  - K-fold cross-validation  

- Class imbalance handling:
  - SMOTE oversampling  
  - Class weighting  

- Feature importance analysis:
  - Identifies key predictors such as age, glucose level, BMI, and hypertension  

---

## Results
- **Best Model:** Gradient Boosting  
- **Top Predictive Features:**
  - Age  
  - Average glucose level  
  - BMI  
  - Hypertension  

- Handling class imbalance significantly improved recall and overall model performance.

---

## Files Included
- `stroke-prediction-model.ipynb` → Full machine learning pipeline and implementation  
- `stroke-prediction-report.pdf` → Detailed project report and analysis  
- `stroke-prediction-presentation.pptx` → Summary presentation  
- `stroke-prediction-demo.mp4` → Demo of model workflow and results  
- `project-instructions.pdf` → Assignment guidelines  

---

## Technologies Used
- Python  
- Pandas  
- NumPy  
- Scikit-learn  
- Matplotlib  

---

## Project Highlights
- Applied machine learning to a **real-world healthcare problem**  
- Addressed **class imbalance**, a key issue in medical datasets  
- Compared multiple models to identify the most effective approach  
- Provided **interpretable insights** using feature importance  

---

## Future Improvements
- Use a larger dataset for improved model performance  
- Further tune neural network architecture  
- Deploy as a web application for real-time predictions  

---

## Author
**Thomas Hoerger**