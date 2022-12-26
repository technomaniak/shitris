#pragma once
#include "raylibCpp.h"

class MainMenu
{
public:
	MainMenu();

	void LoadMenu();
	void Tick();
	bool GetGameRunning() const;
	bool GetMenuLoaded() const;
private:
	void StartGame();
	bool GameRunning;
	bool menuLoaded;
};