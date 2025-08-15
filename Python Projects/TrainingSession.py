import os
import random
from datetime import datetime, timedelta
import time
import shutil

# Define the root directory where data is located
root_directory = r'C:\Users\teher\Desktop\data'

# Define the categories
categories = ['takeoff', 'land', 'right', 'left', 'forward', 'backward']

# Function to display file info before and after changing
def display_file_info(file_path, original_modification_time, new_modification_time):
    print(f'File: {file_path}')
    print(f'Original Modification Time: {original_modification_time}')
    print(f'New Modification Time: {new_modification_time}')
    print('-' * 40)

# Function to rename text files to sequential order from 1 to n
def rename_text_files_in_subdirs(directory):
    for subdir, _, files in os.walk(directory):
        for file_name in files:
            if file_name.lower().endswith('.txt'):
                file_path = os.path.join(subdir, file_name)
                original_modification_time = datetime.fromtimestamp(os.path.getmtime(file_path))

                # Get the current file extension
                file_extension = os.path.splitext(file_path)[1]

                # Rename the file to a sequential number (1 to n)
                new_name = None
                counter = 1
                while True:
                    new_name = f'{counter:04d}{file_extension}'
                    new_path = os.path.join(subdir, new_name)
                    if not os.path.exists(new_path):
                        break
                    counter += 1

                os.rename(file_path, new_path)
                new_modification_time = datetime.fromtimestamp(os.path.getmtime(new_path))                

# Function to change file modification timestamp to a random date and time within the last 10 days
def change_modification_timestamp(directory):
    now = datetime.now()
    for subdir, _, files in os.walk(directory):
        for file_name in files:
            if file_name.lower().endswith('.txt'):
                file_path = os.path.join(subdir, file_name)
                original_modification_time = datetime.fromtimestamp(os.path.getmtime(file_path))

                modification_time = now - timedelta(days=random.randint(0, 10))
                os.utime(file_path, (os.path.getatime(file_path), modification_time.timestamp()))
                new_modification_time = datetime.fromtimestamp(os.path.getmtime(file_path))
                display_file_info(file_path, original_modification_time, new_modification_time)

# Function to move files to their designated directories
def move_files_by_category(directory):
    for subdir, _, files in os.walk(directory):
        for file_name in files:
            if file_name.lower().endswith('.txt'):
                file_path = os.path.join(subdir, file_name)
                for category in categories:
                    if category in subdir:
                        category_directory = os.path.join(root_directory, category)
                        destination = os.path.join(category_directory, file_name)
                        if not os.path.exists(destination):
                            original_modification_time = datetime.fromtimestamp(os.path.getmtime(file_path))
                            shutil.move(file_path, destination)
                            new_modification_time = datetime.fromtimestamp(os.path.getmtime(destination))
                            
# Function to clean up subdirectories with the original files
def clean_up_subdirectories(directory):
    for subdir, _, _ in os.walk(directory):
        if subdir != directory:
            shutil.rmtree(subdir)

def main():
    # Perform the tasks for each category
    for category in categories:
        category_directory = os.path.join(root_directory, category)
        rename_text_files_in_subdirs(category_directory)
        change_modification_timestamp(category_directory)
        move_files_by_category(category_directory)
        clean_up_subdirectories(category_directory)

    print("Tasks completed.")

# User input prompt for automatic or manual execution
while True:
    choice = input("Do you want to run the program automatically every 30 seconds (A) or manually (M)? ").strip().lower()
    if choice == 'a':
        auto_execution = True
        break
    elif choice == 'm':
        auto_execution = False
        main()  # Execute once in manual mode
        break
    else:
        print("Invalid choice. Please enter 'A' for automatic or 'M' for manual.")

# Automatic execution loop
if auto_execution:
    run_counter = 0
    while run_counter < 3:
        main()
        run_counter += 1
        time.sleep(30)  # Wait for 30 seconds
        print("Automatic execution after 30 seconds Finished")

