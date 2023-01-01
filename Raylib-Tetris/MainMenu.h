#pragma once
#include "raylibCpp.h"
#include "SoundManager.h"
#include "OptionsMenu.h"

class MainMenu
{
public:
	MainMenu(SoundManager &sounds, Texture2D &cogwheel1);

	void LoadMenu();
	void Tick();
	bool GetGameRunning() const;
	void SetGameRunning(bool val);
	bool GetMenuLoaded() const;
	void SetMenuLoaded(bool val);
	void Draw() const;
	bool GetGameReset() const;
	void SetGameReset(bool val);
	void LoadOptions();
	void UpdateTextures(Texture2D &cogwheel1);
private:
	void StartGame();
	void MainText();
	void PlayButton();
	void SettingsButton();
	void QuitGameButton();
	void SetAnimationValueMainText();

	bool GameRunning;
	bool menuLoaded;
	bool gameReset;
	bool optionsLoad;

	int playButtonCounter;
	bool mouseOverPlayButton;

	int quitGameButtonCounter;
	bool mouseOverQuitGameButton;

	int mainMenuTextZoomCounter;
	int menuTextAnimationSymbol;
	int menuTextRotation;
	int mainTextAnimationSpeed;

	bool mouseOverSettingsButton;
	int settingsButtonCounter;

	SoundManager sounds;

	OptionsMenu options;
	Texture2D cogwheel;

	int programCrasher;
};