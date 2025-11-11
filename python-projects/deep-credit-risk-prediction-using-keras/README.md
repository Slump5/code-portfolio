# Deep Credit Risk Prediction using Keras

## Overview
This project implements a **Deep Multi-Layer Perceptron (MLP)** using **TensorFlow/Keras** to classify credit applicants as either **good** or **bad credit risks** based on the **German Credit Risk dataset**.  
The workflow includes data preprocessing, model building, training with dropout and early stopping, evaluation, and hyperparameter tuning using **Keras Tuner**.  
The final model achieves **~78% accuracy** on the test dataset, demonstrating reliable predictive performance and strong generalization.

## Features
- **Deep Neural Network (MLP):** Built with two hidden layers (64 and 32 neurons) using ReLU activation.
- **Regularization:** Includes dropout layers (30%) and early stopping to prevent overfitting.
- **Hyperparameter Optimization:** Tuned using **Keras Tuner** for neurons, dropout rates, and learning rate.
- **Visualization:** Uses **TensorBoard** and Matplotlib for training/validation curves.
- **Data Preprocessing:** Automatically encodes categorical features and normalizes numeric ones.
- **Performance:** Achieved consistent learning curves and stable test accuracy.

## File Structure
- **dataset_31_credit-g.arff:** Original German Credit dataset in ARFF format.
- **Project 3 - Group 22.ipynb:** Jupyter Notebook containing all preprocessing, model training, evaluation, and tuning steps.
- **best_model.keras:** Saved trained model (best validation checkpoint).
- **Project 3 - Group 22 Report.pdf:** Written summary of the project results and findings.
- **best_model.keras:** Saved trained model (best validation checkpoint for reproducibility).  

## Requirements
- Python 3.10 or later  
- TensorFlow 2.16+  
- Scikit-learn  
- Pandas  
- NumPy  
- Matplotlib  
- Keras Tuner  
- TensorBoard  

Install all dependencies using:
```bash
pip install tensorflow scikit-learn pandas numpy matplotlib keras-tuner
```
## How to Run
1. Clone the repository:
```bash
git clone <repository-url>
cd <repository-directory>
```
2. Launch the Jupyter Notebook:
```bash
jupyter notebook "deep-credit-risk-prediction-keras.ipynb"
```
3. (Optional) Run TensorBoard to view training logs:
```bash
tensorboard --logdir logs/
```
4. Evaluate the saved model manually:
```python
from tensorflow.keras.models import load_model
best_model = load_model('best_model.keras')
best_model.evaluate(X_test, y_test)
```

## Model Results
- Training Accuracy	= ~80%
- Validation Accuracy =	~78%
- Test Accuracy = 0.78
- Test Loss = 0.48

## Future Improvements
- Explore ensemble methods (Random Forest + MLP hybrid).
- Integrate transformer-based architectures for tabular data.
- Add explainability tools like SHAP or LIME.
- Deploy the model as a web service using Flask or FastAPI.

## License
This project is for portfolio and personal purposes.
Retain the copyright notice:
"Thomas Hoerger – Copyright © 2024 Deep Credit Risk Prediction"