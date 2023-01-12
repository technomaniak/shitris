#include "MainMenu.h"
#include "Settings.h"
#include <iostream>

MainMenu::MainMenu(SoundManager& sounds1, Texture2D& cogwheel1, Texture2D& quitTexture1, std::vector<std::vector<int>>& keyBindsList1, InputManager& manager1, std::string& boardName1, Board& board1, int& style) :
	GameRunning(false),
	menuLoaded(false),
	sounds(sounds1),
	mouseOverPlayButton(false),
	mouseOverSettingsButton(false),
	menuTextRotation(-1),
	menuTextAnimationSymbol(-1),
	mainTextAnimationSpeed(1),
	mainMenuTextZoomCounter(0),
	quitGameButtonCounter(0),
	playButtonCounter(0),
	settingsButtonCounter(0),
	creditsButtonCounter(0),
	gameReset(true),
	mouseOverQuitGameButton(false),
	mouseOverCreditsButton(false),
	keyBindsList(keyBindsList1),
	options(OptionsMenu(sounds, keyBindsList)),
	cogwheel(cogwheel1),
	modeSelect(ModeSelectMenu(sounds, manager, boardName, style, board)),
	manager(manager1),
	board(board1),
	boardName(boardName1),
	quitGameTexture(quitTexture1),
	creditsMenu(CreditsMenu(sounds))
{
}

void MainMenu::LoadMenu()
{
	menuLoaded = true;
}

void MainMenu::Tick()
{
	if (!options.GetLoaded())
	{
		if (modeSelect.GetLoaded())
		{
			modeSelect.Tick();
		}
		else if (creditsMenu.GetMenuLoaded())
		{
			creditsMenu.Tick();
		}
		else
		{
			Draw();
			PlayButton();
			QuitGameButton();
			SettingsButton();
			CreditsButton();
			MainText();
			if (modeSelect.GetGameStart())
			{
				modeSelect.SetGameStart(false);
				StartGame();
			}
		}
	}
	else
	{
		options.Tick();
	}
}

void MainMenu::PlayButton()
{
	if (raycpp::GetMousePos() > settings::playButtonPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::playButtonPos - Vec2<int>{ 0, 25 } + settings::playButtonSize)
	{
		if (mouseOverPlayButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverPlayButton = true;
		}
	}
	else
	{
		if (settings::playButtonTextSize < settings::maxPlayButtonTextSize)
		{
			playButtonCounter++;
			if (playButtonCounter > 0)
			{
				settings::playButtonTextSize += 5;
				playButtonCounter = 0;
			}
		}
		mouseOverPlayButton = false;
	}
	if (mouseOverPlayButton)
	{
		if (settings::playButtonTextSize > settings::minPlayButtonTextSize)
		{
			playButtonCounter++;
			if (playButtonCounter > 0)
			{
				settings::playButtonTextSize -= 5;
				playButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			gameReset = true;
			sounds.PlaySoundFromName("menuSound");
			modeSelect.LoadModeSelect();
		}
	}
}

void MainMenu::SettingsButton()
{
	if (raycpp::GetMousePos() > settings::settingsButtonPos - Vec2<int>{ 0, 29 }
	&& raycpp::GetMousePos() < settings::settingsButtonPos - Vec2<int>{ 0, 21 } + settings::settingsButtonSize)
	{
		if (mouseOverSettingsButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverSettingsButton = true;
		}
	}
	else
	{
		if (settings::settingsButtonTextureSize < settings::maxSettingsButtonTextureSize)
		{
			settingsButtonCounter++;
			if (settingsButtonCounter > 0)
			{
				settings::settingsButtonTextureSize += 0.01f;
				settingsButtonCounter = 0;
			}
		}
		mouseOverSettingsButton = false;
	}
	if (mouseOverSettingsButton)
	{
		if (settings::settingsButtonTextureSize > settings::minSettingsButtonTextureSize)
		{
			settingsButtonCounter++;
			if (settingsButtonCounter > 0)
			{
				settings::settingsButtonTextureSize -= 0.01f;
				settingsButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			options.LoadOptions();
		}
	}
}

void MainMenu::QuitGameButton()
{
	if (raycpp::GetMousePos() > settings::quitGameButtonPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::quitGameButtonPos - Vec2<int>{ 0, 25 } + settings::quitGameButtonSize)
	{
		if (mouseOverQuitGameButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverQuitGameButton = true;
		}
	}
	else
	{
		if (settings::quitGameButtonTextureSize < settings::maxQuitGameButtonTextureSize)
		{
			quitGameButtonCounter++;
			if (quitGameButtonCounter > 0)
			{
				settings::quitGameButtonTextureSize += (float)0.01;
				quitGameButtonCounter = 0;
			}
		}
		mouseOverQuitGameButton = false;
	}
	if (mouseOverQuitGameButton)
	{
		if (settings::quitGameButtonTextureSize > settings::minQuitGameButtonTextureSize)
		{
			quitGameButtonCounter++;
			if (quitGameButtonCounter > 0)
			{
				settings::quitGameButtonTextureSize -= (float)0.01;
				quitGameButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.CloseSound();
			exit(0);
		}
	}
}

void MainMenu::SetAnimationValueMainText()
{
	if (settings::mainTextSize >= 300)
	{
		menuTextAnimationSymbol = -1;
	}
	else if (settings::mainTextSize >= 295)
	{
		mainTextAnimationSpeed = 1;
	}
	else if (settings::mainTextSize >= 285)
	{
		mainTextAnimationSpeed = 2;
	}
	else if (settings::mainTextSize >= 270)
	{
		mainTextAnimationSpeed = 3;
	}
	else if (settings::mainTextSize >= 255)
	{
		mainTextAnimationSpeed = 2;
	}
	else if (settings::mainTextSize >= 247)
	{
		mainTextAnimationSpeed = 1;
	}
	else if (settings::mainTextSize <= 247)
	{
		menuTextAnimationSymbol = 1;
	}
}

void MainMenu::CreditsButton()
{
	if (raycpp::GetMousePos() > settings::creditsButtonPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::creditsButtonPos - Vec2<int>{ 0, 25 } + settings::creditsButtonSize)
	{
		if (mouseOverCreditsButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverCreditsButton = true;
		}
	}
	else
	{
		if (settings::creditsButtonTextSize < settings::maxCreditsButtonTextSize)
		{
			creditsButtonCounter++;
			if (creditsButtonCounter > 0)
			{
				settings::creditsButtonTextSize += 5;
				creditsButtonCounter = 0;
			}
		}
		mouseOverCreditsButton = false;
	}
	if (mouseOverCreditsButton)
	{
		if (settings::creditsButtonTextSize > settings::minCreditsButtonTextSize)
		{
			creditsButtonCounter++;
			if (creditsButtonCounter > 0)
			{
				settings::creditsButtonTextSize -= 5;
				creditsButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			gameReset = true;
			sounds.PlaySoundFromName("menuSound");
			creditsMenu.LoadCreditsMenu();
		}
	}
}

bool MainMenu::GetGameRunning() const
{
	return GameRunning;
}

void MainMenu::SetGameRunning(bool val)
{
	GameRunning = val;
}

bool MainMenu::GetMenuLoaded() const
{
	return menuLoaded;
}

void MainMenu::SetMenuLoaded(bool val)
{
	menuLoaded = val;
}

void MainMenu::Draw() const
{
	// Background
	ClearBackground(BLACK);

	// Play Button
	raycpp::DrawRectangleLinesEx(settings::playButtonPos, settings::playButtonSize, 5, RAYWHITE);
	raycpp::DrawText("PLAY", { settings::playButtonTextPos.GetX() - (settings::playButtonSize.GetX() / 2) + (settings::playButtonSize.GetX() - MeasureText("PLAY", settings::playButtonTextSize) / 2),
		settings::playButtonPos.GetY() - (settings::playButtonSize.GetY() / 2) + (int)(settings::playButtonSize.GetY() - MeasureTextEx(GetFontDefault(), "PLAY", (float)(settings::playButtonTextSize / 2), 20).y) },
		settings::playButtonTextSize, RAYWHITE);

	// Credits Button
	raycpp::DrawRectangleLinesEx(settings::creditsButtonPos, settings::creditsButtonSize, 5, RAYWHITE);
	raycpp::DrawText("CREDITS", { settings::creditsButtonTextPos.GetX() - (settings::creditsButtonSize.GetX() / 2) + (settings::creditsButtonSize.GetX() - MeasureText("CREDITS", settings::creditsButtonTextSize) / 2),
		settings::creditsButtonPos.GetY() - (settings::creditsButtonSize.GetY() / 2) + (int)(settings::creditsButtonSize.GetY() - MeasureTextEx(GetFontDefault(), "CREDITS", (float)(settings::creditsButtonTextSize / 2), 20).y) },
		settings::creditsButtonTextSize, RAYWHITE);

	// Quit Game button
	raycpp::DrawRectangleLinesEx(settings::quitGameButtonPos, settings::quitGameButtonSize, 5, RAYWHITE);
	raycpp::DrawTextureEx(quitGameTexture, settings::quitGameButtonTexturePos + (int)(((19.53125 - (settings::quitGameButtonTextureSize * 100)) * 5.12) / 2) + Vec2<int>{ 6, 7 }, 0.0f, settings::quitGameButtonTextureSize, RAYWHITE);

	// Settings Button
	raycpp::DrawRectangleLinesEx(settings::settingsButtonPos, settings::settingsButtonSize, 5, RAYWHITE);
	raycpp::DrawTextureEx(cogwheel, settings::settingsButtonTexturePos + (int)(((19.53125 - (settings::settingsButtonTextureSize * 100)) * 5.12) / 2), 0.0f, settings::settingsButtonTextureSize, RAYWHITE);

}

bool MainMenu::GetGameReset() const
{
	return gameReset;
}

void MainMenu::SetGameReset(bool val)
{
	gameReset = val;
}

void MainMenu::UpdateTextures(Texture2D& cogwheel1)
{
	cogwheel = cogwheel1;
}

void MainMenu::LoadOptions()
{
	options.LoadOptions();
}

void MainMenu::UnLoadOptions()
{
	options.SetLoaded(false);
}

bool MainMenu::GetOptionsLoaded()
{
	return options.GetLoaded();
}

void MainMenu::MainText()
{
	if (menuTextRotation == -1)
	{
		srand((int)time(NULL));
		if (rand() % 2 == 1)
		{
			menuTextRotation = rand() % 13;
		}
		else
		{
			menuTextRotation = 365 - (rand() % 13);
		}
	}

	DrawTextPro(GetFontDefault(), "SHITRIS", { settings::screenWidth / 2, settings::screenHeight / 2 }, { (float)MeasureText("SHITRIS", settings::mainTextSize) / 2 - 25,
											   MeasureTextEx(GetFontDefault(), "SHITRIS", (float)settings::mainTextSize, 5).y }, (float)menuTextRotation, (float)settings::mainTextSize, 5, RAYWHITE);

	SetAnimationValueMainText();

	mainMenuTextZoomCounter++;
	if (mainMenuTextZoomCounter > 2)
	{
		settings::mainTextSize += (mainTextAnimationSpeed * menuTextAnimationSymbol);
		mainMenuTextZoomCounter = 0;
	}
}

void MainMenu::StartGame()
{
	sounds.PlaySoundFromName("menuSound");
	manager.LoadBoard(boardName, board);
	GameRunning = true;
}
