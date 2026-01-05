# Competitive Programming Performance Analyzer

A C++ tool to analyze competitive programming practice data, identify difficulty trends, and recommend topics for improvement.

## Features
- Analyzes solved problems from CSV input
- Identifies problem difficulty distribution
- Recommends weak topics based on solve patterns
- Designed for ICPC-style preparation

## Tech Stack
- C++
- STL
- File Handling

## Usage
1. Prepare a CSV file with problem data
2. Compile the program:
   g++ main.cpp -o analyzer
3. Run:
   ./analyzer

### Sample Input
A sample `data.csv` file is included to demonstrate the expected input format.

## Motivation
Built as part of my ICPC preparation to systematically analyze performance and improve weak areas.

## Future Improvements
- Tracks practice consistency and streaks
- Graph-based visualizations
- Support for multiple platforms (Codeforces, AtCoder, LeetCode)