#pragma once
#include "raylibCpp.h"
#include "SoundManager.h"
#include "OptionsMenu.h"

class MainMenu
{
public:
	MainMenu(SoundManager &sounds1, Texture2D &cogwheel1);

	void LoadMenu();
	void Tick();
	bool GetGameRunning() const;
	void SetGameRunning(bool val);
	bool GetMenuLoaded() const;
	void SetMenuLoaded(bool val);
	void Draw() const;
	bool GetGameReset() const;
	void SetGameReset(bool val);
	void UpdateTextures(Texture2D &cogwheel1);
	void LoadOptions();
	bool GetOptionsLoaded();

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

	SoundManager &sounds;

	OptionsMenu options;
	Texture2D cogwheel;
};