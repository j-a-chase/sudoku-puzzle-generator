/*******************************************************************************
 * AUTHOR: James A. Chase
 * FILE: main.cpp
 * SUMMARY: Main entry point for the program.
 * 180625
*******************************************************************************/
#include "userInput.h"
#include "puzzleGenerator.h"
#include <iostream>

using namespace std;

int main() {
   int n = UserInput::getInt("How many puzzles do you want? ");

   try {
      PuzzleGenerator(n).generate();
   } catch (const runtime_error& e) {
      cerr << "Error: " << e.what() << endl;
      return 1; // Return a non-zero value to indicate an error
   }

   return 0;
}
