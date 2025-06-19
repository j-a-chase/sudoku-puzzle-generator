/*******************************************************************************
 * AUTHOR: James A. Chase
 * FILE: userInput.cpp
 * SUMMARY: Implementation file for UserInput class
 * 180625
*******************************************************************************/
#include "userInput.h"
#include <limits>

using namespace std;

/*******************************************************************************
 * USER INPUT :: GET INT
 * Prompts the user for an integer input and returns it.
*******************************************************************************/
int UserInput::getInt(const string& prompt, istream& in) {
   int value;
   while (true) {
      cout << prompt;
      in >> value;

      if (in.fail() || value < 0) {
         in.clear(); // Clear the error flag
         clearInputBuffer(in); // Discard invalid input
         cout << "Invalid input. Please enter an integer." << endl;
      } else {
         clearInputBuffer(in); // Clear any remaining input
         return value; // Return the valid integer
      }
   }
}

/*******************************************************************************
 * USER INPUT :: CLEAR INPUT BUFFER
 * Clears the input buffer to remove any invalid input.
*******************************************************************************/
void UserInput::clearInputBuffer(istream& in) {
   in.clear(); // Clear any error flags
   in.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line
}
