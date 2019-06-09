#include "Menu.h"

#include <iostream>



//===PAGE
Page::Page()
{
	std::string blank;

	for (int i = 0; i < 120; i++)
	{
		blank.append(1, ' ');
	}

	for (int i = 0; i < 30; i++)
	{
		this->Text.push_back(blank);
	}
}

void Menu::Write(std::string txt)
{
	this->Buffer.at(0) = txt;
}

void Menu::Write(int x, int y, std::string txt)
{
	this->Buffer.at(y).replace(x, txt.size(), txt);
}

//===MENU
void Menu::Init()
{
	std::string blank;

#ifdef _WIN32
	std::system("mode con:cols=120 lines=30");
#endif

	for (int i = 0; i < 120; i++)
	{
		blank.append(1, ' ');
	}

	for (int i = 0; i < 30; i++)
	{
		Buffer.push_back(blank);
	}
}

void Menu::Update()
{
	for (auto& txt : this->Buffer)
	{
		std::cout << txt << std::endl;
	}
}

void Menu::Activate()
{
	while (true)
	{
		int Key = Key::Get();

		if (Key == 72) // Up
		{
			CursorPos++;
		}
		else if (Key == 80) // Down
		{
			CursorPos--;
		}

	//	this->Current->Write(0,0,std::string("Current cursor position is:"));

		Update();
	}
}

void Menu::Push(Page p)
{
	p.ButtonPos = DOWN; // Default
	p.PosInVector = this->Index.size();
	this->Index.push_back(p);
}

void Menu::Load(Page* p)
{
	int pos = 0;

	this->Current = p;

	for (auto& txt : p->Text)
	{
		pos++;
		try
		{
			this->Buffer.at(pos) = txt;
		}
		catch (...)
		{
			// This is bad, but this is bad
			std::cout << "Handled exception" << std::endl;
		}
	}
}