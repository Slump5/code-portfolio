# Analysis of CollegeScores4yr Dataset

## Overview
This is an R-based analysis project for processing and exploring the CollegeScores4yr dataset, which contains information on U.S. colleges including SAT scores, tuition fees, graduation rates, acceptance rates, and more. The project cleans the data, computes descriptive statistics (means, medians, correlations), generates visualizations (histograms, boxplots, bar charts, pie charts), and answers 10 specific questions about college characteristics. It uses R Markdown for reproducible reporting, outputting an HTML file with embedded results and plots. The analysis compares public vs. private colleges, identifies distributions and outliers, and provides insights into regional and institutional differences. The project includes data loading from CSV, NA handling, and ggplot2-based visualizations, fulfilling a data analysis task with a focus on educational metrics.

## Features
- **Data Loading and Cleaning:** Reads college data from `CollegeScores4yr.csv`, handles missing values with `na.omit()`, and converts columns as needed (e.g., numeric graduation rates).
- **Descriptive Statistics:** Calculates means (graduation rates, tuition), medians (SAT scores), standard deviations (student-faculty ratios), correlations (SAT and graduation rates), and more.
- **Visualizations:** Generates bar charts (colleges by region, tuition/SAT by control), histograms (tuition distribution), boxplots (acceptance rates), and pie charts (public vs. private proportions) using ggplot2 and dplyr.
- **Group Comparisons:** Aggregates data by control (public/private) and region for means and counts; identifies distributions and outliers.
- **Question Answering:** Directly addresses 10 curated questions on averages, medians, deviations, distributions, correlations, proportions, and comparisons.
- **Reproducible Reporting:** R Markdown file knits to HTML with embedded code chunks, results, and plots for easy sharing and verification.
- **Error Handling:** Checks for NA values, uses `na.rm = TRUE` for stats, and ensures data structure integrity with `str()`.
- **Conclusion Section:** Summarizes key findings, takeaways, and insights from the analysis.
- **Documentation Support:** Inline comments in R code, R history file for session tracking, and a PDF with question selection process.

## File Structure
- **project-1-college-data-questions-thomashoeger.pdf:** PDF document outlining 10 simple questions, ChatGPT-generated questions, and final selected questions for analysis, with methods.
- **analysis-of-collegescores4yr-dataset-thomashoeger.Rmd:** Main R Markdown file with introduction, methods, results (code chunks for stats and plots), and conclusion.
- **collegescores4yr.csv:** Input CSV dataset with college metrics (Name, State, SAT, Tuition, Graduation Rate, etc.).
- **analysis-of-collegescores4yr-dataset-thomashoeger.html:** Knitted HTML output from the Rmd file, including interactive table of contents, results, and embedded visualizations.

## Requirements
- R version 4.0 or later
- R packages: ggplot2, dplyr, readr, knitr (install via `install.packages(c("ggplot2", "dplyr", "readr", "knitr"))`)
- Standard R libraries (base, utils)
- An R environment (RStudio recommended for knitting Rmd files)
- Input file (`collegescores4yr.csv`) must be in the same directory as the Rmd
- Optional: PDF viewer for .pdf files, web browser for .html output

## Installation and Running
1. Install R and required packages if not already available:
	```R
	install.packages(c("ggplot2", "dplyr", "readr", "knitr"))```
2. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
3. Open the Rmd file in RStudio:
	- Load the project or set working directory to the folder containing the files.
	- Run: setwd("path/to/directory")
4. Knit the Rmd to generate/update the HTML:
	- In RStudio: Click the "Knit" button or run:
		```language-R
		rmarkdown::render("analysis-of-collegescores4yr-dataset-thomashoeger.Rmd")```
	- From R console: Source the Rmd or execute chunks manually.

## How to Use
1. Ensure collegescores4yr.csv is in the current working directory.
2. Open analysis-of-collegescores4yr-dataset-thomashoeger.Rmd in RStudio.
3. Knit the file to produce analysis-of-collegescores4yr-dataset-thomashoeger.html (automatically loads data, runs stats, and generates plots).
4. View the HTML in a browser for results, including answers to the 10 questions, statistics, and visualizations.
5. To reproduce or modify: Edit the Rmd (add new questions or plots), re-knit, and check outputs.
6. Reference the PDF for question rationale and the .Rhistory for command history.
7. For interactive exploration: Run individual code chunks in RStudio console.

## Project Notes
- **Data Assumptions:** CSV columns include GraduationRate, AvgSAT, TuitionFTE, Region, TuitionIn, AdmitRate, CompRate, Control, etc.; handles NAs and non-numeric issues.
- **Question Focus:** Selected 10 questions cover central tendency, spread, distributions, correlations, proportions, and public/private comparisons.
- **Visual Customizations:** Uses steelblue/blue fills, specific bin widths (5000 for tuition histogram), and polar coordinates for pie charts.
- **Statistics Details:** Correlation uses complete.obs; groups via dplyr group_by() and summarise().
- **Output Format:** HTML with TOC and numbered sections; results inline (e.g., mean values printed, plots displayed).
- **Performance:** Efficient for the dataset size (~thousands of rows); uses vectorized operations.
- **Dependencies:** Relies on relative paths for CSV; assumes no additional data transformations beyond cleaning.
- **Testing:** Re-run knitting to verify; .Rhistory shows development steps like package installs and views.

## Future Improvements
- Add interactive plots using plotly or shiny for dynamic exploration (hover on boxplots).
- Incorporate hypothesis testing (t-tests for public/private differences) beyond descriptive stats.
- Expand to machine learning (predict graduation rates from SAT/tuition via linear models).
- Handle larger datasets with data.table for speed.
- Create a Shiny app for user-input questions and custom visualizations.
- Include more regions or filters (by locale or enrollment size).
- Automate testing with testthat for stats and plots.

## License

This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 Analysis of CollegeScores4yr Dataset".
