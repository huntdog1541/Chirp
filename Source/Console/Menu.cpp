#include "Menu.h"

#include <iostream>

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

void Page::Write(std::string txt)
{
	this->Text.at(0) = txt;
}

void Page::Write(int x,int y, std::string txt)
{
	this->Text.at(y).replace(x,txt.size(),txt);
}

void Menu::Update()
{
	for (auto& b : Buffer)
	{
		std::cout << b << std::endl;
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