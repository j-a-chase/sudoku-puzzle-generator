/*******************************************************************************
 * AUTHOR: James A. Chase
 * FILE: puzzleGenerator.cpp
 * SUMMARY: Implementation file for PuzzleGenerator class
 * 180625
*******************************************************************************/
#include "puzzleGenerator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for std::shuffle

using namespace std;

void PuzzleGenerator::generate() const {
   cout << "Generating " << n << " puzzles to " << filename << endl;

   // create the output file
   ofstream outFile(filename);
   if (!outFile)
      throw runtime_error("Could not open file for writing: " + filename);

   // generate the puzzles
   for (int i = 0; i < n; ++i) {
      array<int, 81> puzzle = buildPuzzle();

      for (int j = 0; j < 81; ++j)
         outFile << puzzle[j];
      outFile << endl; // Separate puzzles with a blank line
   }

   outFile.close();
   cout << "Puzzles generated successfully!" << endl;
}

array<int, 81> PuzzleGenerator::buildPuzzle(int minClues) const {
   // create the empty puzzle, initialized to zeros to prevent garbage values
   array<int, 81> puzzle{};

   // randomly generate the puzzle
   randomize(puzzle);

   // create vector of indices and shuffle
   vector<int> indices(81);
   iota(indices.begin(), indices.end(), 0); // Fill starting from 0 to 80
   shuffle(indices.begin(), indices.end(), rng);

   // fill the puzzle with valid numbers
   for (int index : indices) {
      int backup = puzzle[index]; // backup the original value
      puzzle[index] = 0; // reset the cell

      // if the puzzle solution is not valid, replace with the backup value
      if (!isPuzzleValid(puzzle))
         puzzle[index] = backup;

      int filled = count_if(puzzle.begin(), puzzle.end(), [](int v) { return v != 0; });
      if (filled <= minClues)
         break;
   }

   return puzzle;
}

bool PuzzleGenerator::isCellValid(const array<int, 81>& puzzle, pair<int, int> cell, int value) const {
   // validate the row / col
   for (int i = 0; i < 9; ++i)
      if (puzzle[cell.first * 9 + i] == value || puzzle[i * 9 + cell.second] == value)
         return false;
   
   // validate the subgrid
   int subRow = cell.first / 3 * 3;
   int subCol = cell.second / 3 * 3;
   for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
         if (puzzle[(subRow + i) * 9 + (subCol + j)] == value)
            return false;
   
   return true;
}

bool PuzzleGenerator::isPuzzleValid(array<int, 81>& puzzle, int maxSolutions) const {
   int count = 0;
   countSolutions(puzzle, 0, count, maxSolutions); // Count solutions, max 2 to check for uniqueness
   return count == 1; // A valid puzzle should have exactly one solution
}

int PuzzleGenerator::countSolutions(array<int, 81>& puzzle, int index, int& count, int max) const {
   // will return the number of solutions found
   if (count >= max)
      return count;
   
   // Found a solution
   if (index == 81)
      return ++count;

   // Skip filled cells
   if (puzzle[index] != 0)
      return countSolutions(puzzle, index + 1, count, max);

   int row = index / 9;
   int col = index % 9;

   for (int val = 1; val < 10; ++val) {
      if (isCellValid(puzzle, {row, col}, val)) {
         puzzle[index] = val; // Place the value
         countSolutions(puzzle, index + 1, count, max); // Recur to the next cell
         puzzle[index] = 0; // Reset the cell
      }
   }

   return count;
}

bool PuzzleGenerator::randomize(array<int, 81>& puzzle) const {
   return fillCell(puzzle, 0);
}

bool PuzzleGenerator::fillCell(array<int, 81>& puzzle, int index) const {
   // if we're at the end of the puzzle, return true
   if (index == 81) return true;

   // grab row and col
   int row = index / 9;
   int col = index % 9;

   // create possible numbers and shuffle selection
   vector<int> numbers{1,2,3,4,5,6,7,8,9};
   shuffle(numbers.begin(), numbers.end(), rng);

   for (int num : numbers) {
      if (isCellValid(puzzle, {row, col}, num)) {
         puzzle[row * 9 + col] = num;
         if (fillCell(puzzle, index + 1))
            return true;
         puzzle[row * 9 + col] = 0; // backtrack
      }
   }

   return false;
}
