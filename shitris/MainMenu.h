#pragma once
#include "raylibCpp.h"
#include "SoundManager.h"
#include "OptionsMenu.h"
#include "ModeSelectMenu.h"
#include "InputManager.h"
#include "CreditsMenu.h"

class MainMenu
{
public:
	MainMenu(SoundManager& sounds1, Texture2D& cogwheel1, Texture2D& quitTexture1, std::vector<std::vector<int>>& keyBindsList1, InputManager& manager1, std::string& boardname, Board& board1, int& style);

	void LoadMenu();
	void Tick();
	bool GetGameRunning() const;
	void SetGameRunning(bool val);
	bool GetMenuLoaded() const;
	void SetMenuLoaded(bool val);
	void Draw() const;
	bool GetGameReset() const;
	void SetGameReset(bool val);
	void UpdateTextures(Texture2D& cogwheel1);
	void LoadOptions();
	void UnLoadOptions();
	bool GetOptionsLoaded();

private:
	void StartGame();
	void MainText();
	void PlayButton();
	void SettingsButton();
	void QuitGameButton();
	void SetAnimationValueMainText();
	void CreditsButton();

	bool GameRunning;
	bool menuLoaded;
	bool gameReset;

	int playButtonCounter;
	bool mouseOverPlayButton;

	int creditsButtonCounter;
	bool mouseOverCreditsButton;

	int quitGameButtonCounter;
	bool mouseOverQuitGameButton;

	int mainMenuTextZoomCounter;
	int menuTextAnimationSymbol;
	int menuTextRotation;
	int mainTextAnimationSpeed;

	bool mouseOverSettingsButton;
	int settingsButtonCounter;

	SoundManager& sounds;

	std::string& boardName;
	Board& board;

	std::vector<std::vector<int>>& keyBindsList;
	OptionsMenu options;
	Texture2D& cogwheel;
	Texture2D& quitGameTexture;
	InputManager& manager;
	ModeSelectMenu modeSelect;
	CreditsMenu creditsMenu;
};