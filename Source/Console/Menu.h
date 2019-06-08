#pragma once

#include <vector>
#include <string>

#define UP 1
#define DOWN 0

class Button
{
public:
	std::string Label;
	int Destination; // Position inside the buffer vector
};

class Page
{
public:
	Page();

	int PosInVector; // Position in the vector index
	int ButtonPos; // Position of button on the page
	int CursorPos; // Cursor of button

	void Write(std::string);
	void Write(int, int, std::string);

	std::vector<std::string> Text;
	std::vector<Button> Buttons;
};


class Menu
{
public:
	void Init();
	void Update();

	int Current;

	void Push(Page); // Push a page
	void Load(Page*);

	std::vector<std::string> Buffer;
	std::vector<Page> Index; // Not the index page, but like idk
};