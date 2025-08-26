# HomesForSale Data Analysis

## Overview
This project analyzes the "HomesForSale" dataset to investigate the influence of home characteristics (size, number of bedrooms, number of bathrooms) and location (state) on home sale prices. The analysis focuses primarily on California homes, using linear regression to examine the impact of individual and combined features, and ANOVA to compare prices across four states (CA, NY, NJ, PA). The project includes an R Markdown report with statistical models, visualizations, and detailed conclusions, fulfilling statistical analysis requirements for a data science or statistics course.

## Features
- **Data Loading and Filtering:** Reads the `HomesForSale.csv` dataset using R and filters for California-specific analyses or four-state comparisons (CA, NY, NJ, PA).
- **Linear Regression Models:** Analyzes the relationship between home price and size, bedrooms, bathrooms individually (for California), and their combined effect using multiple regression.
- **ANOVA Analysis:** Tests for significant price differences across four states (CA, NY, NJ, PA).
- **Visualizations:** Generates scatterplots with regression lines for California data (Price vs. Size, Bedrooms, Bathrooms), actual vs. predicted price plots, residual plots, and a boxplot for state price comparisons.
- **Statistical Summaries:** Provides detailed R output summaries for all models, including p-values, R-squared, coefficients, and F-statistics.
- **Comprehensive Report:** Includes an introduction, data description, analysis sections for five research questions, summary, implications, conclusions, references, and an appendix with full R summaries.
- **Reproducible Workflow:** Uses R Markdown to combine code, visualizations, and narrative for a fully reproducible report.

## File Structure
- **homesforsale-dataset-thomashoerger.Rmd:** R Markdown source file containing the analysis code, visualizations, and report narrative.
- **homesforsale.csv:** Input CSV dataset with home listings (State, Price, Size, Beds, Baths).
- **homesforsale-dataset-thomashoerger.html:** Rendered HTML report generated from the R Markdown file.
- **.Rhistory:** R session history file with commands related to data processing and analysis (includes unrelated SleepStudy.csv commands).

## Requirements
- **R Environment:** R (version 4.0 or later recommended).
- **R Packages:** 
  - `tidyverse` (for data manipulation and visualization)
  - `knitr` (for R Markdown rendering)
- **Input File:** `HomesForSale.csv` must be in the working directory.
- **Optional:** RStudio for easier R Markdown rendering and visualization.
- **Optional:** Web browser to view the rendered HTML report.

## Compilation and Running
1. Ensure `HomesForSale.csv` is in the working directory.
2. Install required R packages:
   ```R
   install.packages("tidyverse")
   install.packages("knitr")```
3. Open `homesforsale-dataset-thomashoerger.Rmd` in RStudio or an R environment.
4. Set the working directory to the project folder:
	``language-R
	setwd("path/to/project/directory")``
5. Render the R Markdown file to HTML:
	```language-R
	rmarkdown::render("homesforsale-dataset-thomashoerger.Rmd")```
6. View the generated `homesforsale-dataset-thomashoerger.html` in a web browser.

## How to Use
1. Place homesforsale.csv in the same directory as homesforsale-dataset-thomashoerger.Rmd.
2. Open R or RStudio and install required packages (see Requirements).
3. Run the R Markdown file as described above to generate the HTML report.
4. Review the HTML report (homesforsale-dataset-thomashoerger.html) for analysis results, including:
	- Scatterplots and regression lines for California home price vs. size, bedrooms, and bathrooms.
	- Actual vs. predicted price and residual plots for the multiple regression model.
	- Boxplot comparing home prices across CA, NY, NJ, and PA.
	- Statistical summaries and conclusions for each research question.
5. Optionally, inspect .Rhistory for additional context on R commands used (note: includes unrelated SleepStudy.csv commands).

## Project Notes
- **Dataset:** The HomesForSale.csv contains home listings with columns: State, Price (USD, in thousands), Size (square feet), Beds (number of bedrooms), Baths (number of bathrooms).
- **Key Findings:**
	- Size is the most significant predictor of home price in California (p = 0.00046, $339 per sq ft).
	- Bathrooms have a significant effect (p = 0.0041, ~$195,000 per bathroom).
	- Bedrooms are not significant (p = 0.255).
	- In multiple regression, only size is significant (p = 0.026).
	- State location significantly affects price (ANOVA, p = 0.00015).
- **Visualizations:** Created using base R plotting functions (plot, abline, boxplot).
- **Output:** The HTML report is self-contained, combining code, plots, and narrative.
- **Data Source:** Lock5Stat dataset (referenced in the report).

## Future Improvements
- Incorporate additional predictors (lot size, year built) if available in an expanded dataset.
- Use ggplot2 for enhanced visualizations (colored regression lines, faceted plots).
- Perform post-hoc tests (Tukey HSD) for RQ5 to identify specific state differences.
- Add interactive visualizations using plotly or shiny for dynamic exploration.
- Include data cleaning steps to handle potential outliers or missing values.
- Expand the analysis to other states or regions in the dataset.
- Create a PDF version of the report using LaTeX for broader compatibility.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 HomesForSale Data Analysis".