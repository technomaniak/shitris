#pragma once
#include "raylibCpp.h"
#include "SoundManager.h"

class MainMenu
{
public:
	MainMenu(SoundManager sounds);

	void LoadMenu();
	void Tick();
	void PlayButton();
	void VolumeSettings();
	bool GetGameRunning() const;
	bool GetMenuLoaded() const;
private:
	void StartGame();
	bool GameRunning;
	bool menuLoaded;
	bool mouseOverPlayButton;
	int counter;
	float volume;
	SoundManager sounds;
};