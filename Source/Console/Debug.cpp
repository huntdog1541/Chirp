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
		Button Oof;
		Button Lmao;

		Yeet.Label = "Button 1";
		Oof.Label = "Button 2";
		Lmao.Label = "Button 3";

		Main.Text.at(0) = "Chirp debug interface";
		Main.Text.at(1) = "---------------------------------------------------------------";
		Main.Text.at(2) = "\"Does this look good yet ?\" - Binkiklou";

		Main.Buttons.push_back(Yeet);
		Main.Buttons.push_back(Oof);
		Main.Buttons.push_back(Lmao);

		Main.ButtonPos = 5;

		UI.Push(Main);
		UI.Load(&Main);
		UI.Update();
		UI.Activate();
	}
}