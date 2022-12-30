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
	void SetGameRunning(bool val);
	bool GetMenuLoaded() const;
	void SetMenuLoaded(bool val);
	void Draw() const;
	bool GetGameReset() const;
	void SetGameReset(bool val);
private:
	void StartGame();
	void MainText();
	void PlayButton();
	void QuitGameButton();
	void VolumeSettings();
	void SetAnimationValueMainText();

	bool GameRunning;
	bool menuLoaded;
	bool gameReset;

	bool mouseOverMusicVolumeSlider;
	bool mouseClickedMusicVolumeSlider;

	int playButtonCounter;
	bool mouseOverPlayButton;

	int quitGameButtonCounter;
	bool mouseOverQuitGameButton;

	int mainMenuTextZoomCounter;
	int menuTextAnimationSymbol;
	int menuTextRotation;
	int mainTextAnimationSpeed;

	float volume;
	SoundManager sounds;
	Color volumeSliderTint;

	int programCrasher;
};