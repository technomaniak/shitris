#pragma once
#include "raylibCpp.h"
#include "SoundManager.h"

class MainMenu
{
public:
	MainMenu(SoundManager sounds);

	void LoadMenu();
	void Tick();
	bool GetGameRunning() const;
	bool GetMenuLoaded() const;
	void Draw() const;
private:
	void StartGame();
	void MainText();
	void PlayButton();
	void VolumeSettings();
	void SetAnimationValueMainText();
	bool GameRunning;
	bool menuLoaded;

	bool mouseOverPlayButton;
	int playButtonCounter;

	int mainMenuTextZoomCounter;
	int menuTextAnimationSymbol;
	int menuTextRotation;
	int mainTextAnimationSpeed;

	float volume;
	SoundManager sounds;
};