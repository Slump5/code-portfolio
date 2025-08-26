# Sleep Study Dataset Analysis

## Overview
This is an R Markdown-based analysis of sleep habits, academic outcomes, and well-being among college students using the SleepStudy dataset from Lock5Stat. The project loads CSV data, performs data cleaning and grouping, generates boxplot visualizations, conducts two-sample t-tests for 10 research questions, and outputs results in an HTML report. It explores relationships between variables like GPA, sleep quality, depression, alcohol use, and chronotype (lark/owl). The analysis includes summary statistics, filtered subsets for specific comparisons, and full R code in an appendix. The project fulfills a statistical methods assignment, includes historical R commands from .Rhistory, and provides both source (Rmd) and rendered (HTML) formats.

## Features
- **Data Loading and Preview:** Reads SleepStudy.csv using read.csv() and tidyverse, provides glimpses and summaries of 253 observations across 27 variables.
- **Visualizations:** Boxplots for each research question (GPA by Gender, Cognition Z-Score by Chronotype) using ggplot2.
- **Statistical Tests:** Two-sample Welch t-tests for comparing means across groups, with conclusions including means, p-values, and 95% confidence intervals.
- **Data Grouping and Filtering:** Creates custom factors (EarlyYears vs. Other for class years, Lark vs. Owl excluding Neither) and subsets (alcohol abstain vs. heavy).
- **Research Questions Addressed:** 10 targeted questions on differences in GPA, early classes, cognition, classes missed, happiness, sleep quality, stress, drinks, bedtime, and weekend sleep.
- **Report Structure:** Introduction, data description, analysis sections per RQ with plots and conclusions, summary, implications, references, and appendix with full t-test code.
- **Error Handling and Validation:** Checks unique values, converts to factors, filters NA/invalid rows, and ensures two-level factors for t-tests.
- **Output Generation:** Knitted HTML report with TOC, numbered sections, and embedded plots; supports re-knitting for updates.
- **Historical Commands:** .Rhistory captures iterative development, including package installs, data views, and plot/test refinements.
- **Dataset Insights:** Covers demographics, academics, sleep, psychology, and lifestyle; sourced from surveys for relational analysis.

## File Structure
- **.Rhistory:** Log of R commands executed during development, including library loads, data reads, glimpses, plots, and t-tests.
- **sleepstudy-dataset-thomashoerger.Rmd:** Main R Markdown source file with code chunks for setup, introduction, data preview, analysis per RQ, summary, and appendix.
- **sleepstudy.csv:** Input CSV dataset with 253 rows and 27 columns (Gender, GPA, LarkOwl, PoorSleepQuality); truncated in upload but full in analysis.
- **sleepstudy-dataset-thomashoerger.html:** Rendered HTML output from knitting the Rmd, including interactive TOC, plots, and t-test results.

## Requirements
- R 4.0 or later
- R packages: tidyverse (includes ggplot2, dplyr, readr), knitr
- Input file (sleepstudy.csv) must be in the working directory
- Optional: RStudio for easier knitting and viewing; web browser for HTML output

## Compilation and Running
1. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Install required packages (if not already):
	```r
	install.packages(c("tidyverse", "knitr"))```
3. Set the working directory to the project folder (containing sleepstudy.csv).
4. Knit the Rmd to HTML:
	- In R console:
		```r
		library(rmarkdown)
		render("sleepstudy-dataset-thomashoerger.Rmd")```
	- In RStudio: Open the Rmd and click "Knit" (outputs HTML).

## How to Use
1. Ensure sleepstudy.csv is in the current directory.
2. Run the knitting command as described above.
3. The process will:
	- Load and preview data.
	- Generate boxplots and run t-tests for each RQ.
	- Output conclusions with stats.
	- Produce sleepstudy-dataset-thomashoerger.html for viewing.
4. Open the HTML in a browser to read the report, view plots, and check results.
5. To modify: Edit the Rmd (add new RQs or change filters), re-knit, and review updates.
6. Explore history: Load .Rhistory in R for session replay if needed.
7. Check console for any warnings (NA handling) during knitting.

## Project Notes
- **Dataset Details:** 253 observations; variables include categorical (Gender: 0=Male, 1=Female; LarkOwl) and numeric (GPA, CognitionZscore); sourced from Lock5Stat for educational use.
- **Analysis Methods:** Welch t-tests assume unequal variances; groups ensured as factors with 2 levels; filtering excludes irrelevant categories ("Neither" for Lark/Owl).
- **Visuals:** Boxplots show distributions; titles and labels for clarity.
- **Conclusions:** Significant findings (GPA by gender, p=0.0001) highlighted; non-significant noted (cognition by chronotype, p=0.423).
- **Date Handling:** Report dated 4/15/2025; analysis timeless but assumes current data.
- **Performance:** Efficient for small dataset; sequential processing with dplyr.
- **Dependencies:** Assumes CSV structure (columns like GPA, NumEarlyClass); primary focus on t-tests.
- **Testing:** Iterative via .Rhistory; appendix runs all t-tests for verification.
- **Output Format:** HTML with sections; no external CSVs generated beyond report embeds.
- **Limitations:** No advanced stats (ANOVA); assumes normal-ish distributions for t-tests.

## Future Improvements
- Add more advanced stats (ANOVA for multi-level factors, regression models).
- Incorporate interactive plots (via plotly) for HTML.
- Support parameterized reports (filter by variable via YAML params).
- Include data cleaning script for handling missing values programmatically.
- Add correlation heatmaps or scatterplots for broader insights.
- Optimize for larger datasets with data.table.
- Create a Shiny app for interactive RQ exploration.
- Generate PDF output alongside HTML via pandoc.
- Develop test scripts (unit tests with testthat) for t-test reproducibility.
- Expand to multi-dataset comparison or longitudinal analysis.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 Sleep Study Dataset Analysis".