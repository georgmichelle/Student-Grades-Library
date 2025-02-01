# Student-Grades-Library
C++
# Student Management System

## Overview

The Student Management System is a C++ application designed to manage student data, including student names, IDs, subjects, grades, and the generation of student reports. It allows users to add students, add grades, and view reports by either student ID or all students. The system saves data to a CSV file for persistence, and loads existing data when the program starts.

## Features

- **Add Student**: Allows adding a new student with a name and ID.
- **Add Grades to Student**: Add grades for a specific subject to an existing student.
- **Display Reports of All Students**: View reports of all students including their grades and average scores.
- **Display Student Report by ID**: View the report for a specific student by providing their ID.
- **Data Persistence**: The program saves data to a `students_data.csv` file and loads data from it at startup.
- **Letter Grading System**: Based on average grades, letter grades are assigned (A, B, C, D, F).

## Structure

### Classes

- **Subject**: Manages data related to a subject, including grades and average calculation.
- **Student**: Manages a student’s name, ID, and the subjects and grades they are enrolled in.
- **StudentManager**: Handles adding students, adding grades, displaying reports, and saving/loading data to/from a file.

### File Format (`students_data.csv`)

The data is stored in a CSV format, with each row representing a student and their associated data. The format includes:
- Student ID
- Student Name
- Subject Name(s)
- Grade(s)
