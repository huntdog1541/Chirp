#pragma once

#include "Tree.h"

#include <vector>
#include <string>
#include <stdexcept> // Very important, might create errors if not there on certain system


/*
Most important class for the compiler. Everything is happening here iet's a
pretty way to do stuff.
*/
class Parsed
{
public: // Ok so you can see that the lower you go, the later the compiler is gonna work on it
	Parsed(std::string);

	void Tokenize (); // Makes the text into tokens
	void MakeTree (); // Creates the parse tree
	void MakeIndex (); // Read the tree and create an index to make reading it easier
	void ReadIndex (); // Goes trought the index and parses it

	Tree ParseTree;
	std::vector<int> Index;

	std::vector<std::string> Processed; // All words in the code, are in the vector
	std::vector<Token> Cluster; // Replacement for classified

	int EntryPos;

	std::string Text; // section .text
	std::string BSS; // section .bss
	std::string Data; // section .data

	std::string Output;
};