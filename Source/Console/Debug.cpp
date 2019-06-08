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

		Main.Write("Chirp debug menu");

		Main.Buttons.push_back(Yeet);

		UI.Push(Main);
		UI.Load(&Main);
		UI.Update();

		while (true) {}
	}
}