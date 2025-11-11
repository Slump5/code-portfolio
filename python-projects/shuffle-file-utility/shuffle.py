# Author: Thomas Hoerger – Shuffle File Utility
# Copyright: Thomas Hoerger - Copyright © 2024 Shuffle File Utility
# Date: June 10, 2024
# Description:
# Safely shuffles and randomizes files in subdirectories:
# moves, renames, changes timestamps, cleans folders, and logs all actions.
# Designed for dataset preparation and anonymization.

import os            # Provides file and directory operations
import random        # Used for randomizing filenames and timestamps
from datetime import datetime, timedelta  # Handles timestamps
import time          # For delays and interval control
import shutil        # For moving and deleting files/directories


#  CONFIGURATION
# Hard-coded root directory (change this to your target path)
root_directory = r"date folder path"   # <--- Change to your actual data path (Set to the folder that contains data and data subfolders)
log_file_path = os.path.join(os.path.dirname(root_directory), "shuffleLog.txt")  # Log file stored one level above the root data folder


#  LOGGING UTILITIES
def log(message):
    """Writes a message to the shuffle log with timestamp."""
    # Appends messages to the log file with current datetime
    with open(log_file_path, "a", encoding="utf-8") as logFile:
        logFile.write(f"{datetime.now().strftime('%Y-%m-%d %H:%M:%S')} - {message}\n")

def display_file_info(file_names_record, timestamp_record, category_path):
    """Logs detailed file rename and timestamp info."""
    # Opens the same log file and writes rename/timestamp history for each category
    with open(log_file_path, "a", encoding="utf-8") as logFile:
        logFile.write("\n" + "*" * 90 + "\n")  # Section divider for readability
        logFile.write(f"Category: {category_path}\n")
        logFile.write("-" * 90 + "\n")

        # If directory is empty, note that
        if not file_names_record and not timestamp_record:
            logFile.write("No files found in this directory.\n")

        # Logs old vs. new filenames
        for i in range(len(file_names_record)):
            old, new = file_names_record[i][1], file_names_record[i][0]
            logFile.write(f"File Rename | Old: {old}, New: {new}\n")

        # Logs old vs. new timestamps
        for i in range(len(timestamp_record)):
            f, old_t, new_t = timestamp_record[i]
            logFile.write(f"Timestamps  | File: {f}, Old: {old_t}, New: {new_t}\n")

        logFile.write("-" * 90 + "\n")


#  CORE FUNCTIONS
def rename_files_in_subdirs(directory):
    """Safely renames all files in subdirectories with unique random numbers."""
    file_name_change_record = []  # Records old/new names for logging
    temp_name_record = []         # Temporary rename mapping

    # Walk through each subdirectory in the given path
    for subdir, _, files in os.walk(directory):
        if not files:  # Skip empty folders
            continue

        target_files = [f for f in files]
        num_files = len(target_files)

        # Assign temporary unique names to avoid overwriting
        for file_name in target_files:
            ext = os.path.splitext(file_name)[1]  # Keep original file extension

            # Generate a guaranteed-unique temporary name
            while True:
                temp_new = f"temp_{random.randint(1000, 9999)}{ext}"  # e.g., temp_5823.txt
                temp_path = os.path.join(subdir, temp_new)
                if not os.path.exists(temp_path):  # Ensure no duplicates
                    break

            # Rename the file to its temporary name
            os.rename(os.path.join(subdir, file_name), temp_path)
            temp_name_record.append([temp_new, file_name])

        # Rename with random numbers (final shuffled filenames)
        random_numbers = random.sample(range(1, num_files + 1), num_files)  # Random non-repeating sequence
        for temp_new, old_name in temp_name_record:
            ext = os.path.splitext(temp_new)[1]
            new_name = f"{random_numbers.pop()}{ext}"  # Example: 5.txt, 12.txt

            src = os.path.join(subdir, temp_new)
            dst = os.path.join(subdir, new_name)

            # Ensure the destination name also doesn’t already exist (edge case)
            counter = 1
            while os.path.exists(dst):
                new_name = f"{new_name.split('.')[0]}_{counter}{ext}"  # Adds suffix like _1, _2
                dst = os.path.join(subdir, new_name)
                counter += 1

            # Rename the temp file to its final name
            os.rename(src, dst)
            file_name_change_record.append([new_name, old_name])

    # Sort records alphabetically for cleaner log output
    file_name_change_record.sort()
    return file_name_change_record


def change_modification_timestamp(directory):
    """Randomizes modification timestamps within the last 10 days."""
    now = datetime.now()  # Current time for reference
    time_change_record = []  # Store before/after timestamps

    for subdir, _, files in os.walk(directory):
        for file_name in files:
            file_path = os.path.join(subdir, file_name)
            old_time = datetime.fromtimestamp(os.path.getmtime(file_path))  # Original timestamp
            new_time = now - timedelta(days=random.randint(0, 10))  # Random past date (0–10 days ago)
            # Apply new modification time while keeping access time the same
            os.utime(file_path, (os.path.getatime(file_path), new_time.timestamp()))
            time_change_record.append([file_name, old_time, new_time])

    time_change_record.sort()  # Sort for consistent log order
    return time_change_record


def move_files_by_category(directory):
    """Moves all files from subdirectories into the main category directory."""
    for subdir, _, files in os.walk(directory):
        for file_name in files:
            src = os.path.join(subdir, file_name)   # Current file path
            dest = os.path.join(directory, file_name)  # Destination (parent folder)
            if not os.path.exists(dest):  # Prevent overwriting same name
                shutil.move(src, dest)  # Move the file safely


def clean_up_subdirectories(directory):
    """Deletes empty subdirectories after moving files."""
    for subdir, _, _ in os.walk(directory):
        if subdir != directory:  # Don’t delete the root folder itself
            shutil.rmtree(subdir, ignore_errors=True)  # Remove folder quietly


#  MAIN FUNCTION
def main():
    # List all immediate subdirectories inside the root directory
    categories = [
        subdir for subdir in os.listdir(root_directory)
        if os.path.isdir(os.path.join(root_directory, subdir))
    ]

    # Process each category folder one by one
    for category in categories:
        category_dir = os.path.join(root_directory, category)

        # 1. Move all files up from nested subdirectories
        move_files_by_category(category_dir)

        # 2. Delete empty subfolders after moving
        clean_up_subdirectories(category_dir)

        # 3. Rename files randomly (collision-safe)
        name_changes = rename_files_in_subdirs(category_dir)

        # 4. Change modification timestamps randomly
        time_changes = change_modification_timestamp(category_dir)

        # 5. Log detailed changes
        display_file_info(name_changes, time_changes, category_dir)

    log("✅ All tasks completed.\n")  # Record summary completion


#  EXECUTION CONTROL
if __name__ == "__main__":
    print("File Shuffle Utility")
    print("====================")
    print(f"Root directory: {root_directory}\n")

    while True:
        # Ask user whether to run automatically or manually
        choice = input("Run automatically every 30s (A) or manually once (M)? ").strip().lower()
        if choice == "a":
            # Auto mode: runs every 30 seconds, 3 times
            for run in range(3):
                print(f"\n[Auto Run {run + 1}/3]")
                log(f"Auto Run {run + 1} started.")
                main()
                time.sleep(30)  # Delay between runs
            break
        elif choice == "m":
            # Manual mode: runs only once
            log("Manual run started.")
            main()
            break
        else:
            # Invalid input handling
            print("Invalid input. Please enter 'A' or 'M'.")


