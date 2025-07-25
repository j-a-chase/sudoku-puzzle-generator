/*******************************************************************************
 * AUTHOR: James A. Chase
 * FILE: puzzleGenerator.h
 * SUMMARY: Header file for PuzzleGenerator class
 * 180625
*******************************************************************************/
#pragma once

#include <string>
#include <array>
#include <random>

class PuzzleGenerator {
public:
   // constructors
   PuzzleGenerator() : n(0), filename(std::string("puzzles.txt")), rng(std::random_device{}()) { }
   PuzzleGenerator(int n) : n(n), filename(std::string("puzzles.txt")), rng(std::random_device{}()) { }
   PuzzleGenerator(int n, const std::string& filename) : n(n), filename(filename), rng(std::random_device{}()) { }

   // destructor
   ~PuzzleGenerator() = default;

   // other methods
   void generate() const;

private:
   int n; // number of puzzles to generate
   std::string filename; // file to save the puzzles
   mutable std::mt19937 rng; // persistant random number generator, ensures all puzzles are different when created in succession
   
   // private helper methods
   std::array<int, 81> buildPuzzle(int minClues = 30) const;
   bool isCellValid(const std::array<int, 81>& puzzle, std::pair<int, int> cell, int value) const;
   bool isPuzzleValid(std::array<int, 81>& puzzle, int maxSolutions = 2) const;
   int countSolutions(std::array<int, 81>& puzzle, int index, int& count, int max) const;
   bool randomize(std::array<int, 81>& puzzle) const;
   bool fillCell(std::array<int, 81>& puzzle, int index) const;
};
