#include "Debug.h"

#include <iostream>

namespace Debug
{
	void MakeMenu()
	{
		Menu UI;
		UI.Init();

		Page Main;
		Button Yeet;

		Yeet.Label = "Yetty yeet, this is a button";

		Main.Text.at(0) = "Chirp debug interface";
		Main.Text.at(1) = "---------------------------------------------------------------";
		Main.Text.at(2) = "\"Does this look good yet ?\" - Binkiklou";

		Main.Buttons.push_back(Yeet);

		UI.Push(Main);
		UI.Load(&Main);
		UI.Update();
		UI.Activate();
	}
}