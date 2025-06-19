/*******************************************************************************
 * AUTHOR: James A. Chase
 * FILE: userInput.h
 * SUMMARY: Header file for UserInput class
 * 170625
*******************************************************************************/
#pragma once

#include <string>
#include <iostream>

/*******************************************************************************
 * USER INPUT
 * Class that handles user input for the Sudoku game.
*******************************************************************************/
class UserInput {
public:
   static int getInt(const std::string& prompt, std::istream& in = std::cin);

private:
   static void clearInputBuffer(std::istream& in);
};
