# Shuffle File Utility

## Overview
This is a Python-based console utility that safely shuffles and randomizes files in subdirectories.  
The script is designed for dataset preparation and anonymization, allowing users to automatically or manually randomize filenames, modify timestamps, clean subdirectories, and log all actions. It combines robust file handling with detailed logging to ensure safe and repeatable file operations.

## Features
- **Automatic or Manual Execution:** Choose between continuous auto mode or one-time manual run.
- **Randomized File Renaming:** Safely renames files in each subdirectory with unique randomized numbers.
- **Timestamp Randomization:** Randomly adjusts file modification times within the past 10 days.
- **Subdirectory Cleanup:** Moves all files to parent directories and removes empty folders.
- **Logging System:** Records all rename, timestamp, and category changes in `shuffleLog.txt`.
- **Error-Resistant Design:** Prevents overwriting or duplicate file naming conflicts.
- **Fully Automated Flow:** Handles multiple subdirectories in a single run.

## File Structure
- **shuffle.py:** The main Python script containing all shuffle, rename, and logging logic.
- **shuffleLog.txt:** Auto-generated log file summarizing rename and timestamp changes for each run.
- **README.md:** Documentation and usage instructions for the shuffle utility.

## Requirements
- Python 3.10 or later  
- Standard Python libraries (`os`, `random`, `datetime`, `time`, `shutil`)  
- A writable directory with subfolders containing files to be shuffled  

## Running the Program
1. Clone or copy the project files:
	```bash
	git clone <repository-url>
	cd <repository-directory>
	```
2. Open `shuffle.py` and update the following line to your desired root directory:
	```python
	root_directory = r"E:\Your\Path\To\Data"
	```
3. Run the script:
	```bash
	python shuffle.py
	```
4. When prompted, select:
	- **A** — to run automatically every 30 seconds (3 times total), or  
	- **M** — to run once manually and exit.


## How It Works
1. The program scans all subdirectories within the root directory.
2. Each file is temporarily renamed to avoid conflicts, then assigned a randomized numerical name.
3. Modification timestamps are randomized within the past 10 days.
4. Files are moved up one level into their category directory.
5. Empty subdirectories are deleted.
6. Every operation (rename, timestamp, cleanup) is logged in `shuffleLog.txt`.


## Notes
- **Root Path:** The root directory is hard-coded for safety—edit `root_directory` before running.
- **Duplicate Safety:** File collisions are handled automatically using unique randomized names.
- **Log Location:** The `shuffleLog.txt` file is stored one directory above the root folder.
- **Timestamp Variance:** Randomized within the last 10 days to simulate realistic modification times.

## Future Improvements
- Add GUI interface for directory selection and progress tracking.
- Add configuration file for customizable time ranges and naming formats.
- Option to export summary reports in CSV format.
- Implement file filtering (by extension or size).

## License
This project is for personal and educational use.  
Retain the copyright:
**Thomas Hoerger - Copyright © 2024 Shuffle File Utility**


