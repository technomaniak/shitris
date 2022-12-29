#include "MainMenu.h"
#include "Settings.h"
#include <iostream>

MainMenu::MainMenu(SoundManager sounds):
	GameRunning(false),
	menuLoaded(false),
	playButtonCounter(0),
	sounds(sounds),
	mouseOverPlayButton(false),
	mouseOverMusicVolumeSlider(false),
	mouseClickedMusicVolumeSlider(false),
	volume(0.0f),
	menuTextRotation(-1),
	menuTextAnimationSymbol(-1),
	mainTextAnimationSpeed(1),
	mainMenuTextZoomCounter(0),
	volumeSliderTint(Color{ 0, 0, 0, 255 })
{
}

void MainMenu::LoadMenu()
{
	//Texture2D texture = LoadTextureFromImage(GenImageColor(settings::screenWidth, settings::screenHeight, Color{ 0, 0, 0, 255 }));
	//DrawTexture(texture, 0, 0, WHITE);
	menuLoaded = true;
}

void MainMenu::Tick()
{
	Draw();
	PlayButton();
	VolumeSettings();
	MainText();
	sounds.UpdateCurrentMusic();
	if (!sounds.CheckMusicPlaying())
	{
		sounds.PlayRandomMusic();
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
			StartGame();
		}
	}
}

void MainMenu::VolumeSettings()
{
	if (raycpp::GetMousePos() > settings::volumeSliderBorderPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::volumeSliderBorderPos - Vec2<int>{ 0, 15 } + settings::volumeSliderBorderSize)
	{
		if (mouseOverMusicVolumeSlider != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverMusicVolumeSlider = true;
		}
	}
	else
	{
		if (!mouseClickedMusicVolumeSlider)
		{
			mouseOverMusicVolumeSlider = false;
		}
	}

	if (mouseOverMusicVolumeSlider)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mouseClickedMusicVolumeSlider = true;
		}
		if (mouseClickedMusicVolumeSlider && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			float mouseVolumePosForFucksSake = ((((float)settings::volumeSliderPos.GetY() + settings::volumeSliderSize.GetY()) - raycpp::GetMousePos().GetY() - 20) / settings::volumeSliderSize.GetY());

			if (mouseVolumePosForFucksSake < 0)
			{
				sounds.SetAllMusicVolume(0.0f);
			}
			else if (mouseVolumePosForFucksSake > 1)
			{
				sounds.SetAllMusicVolume(1.0f);
			}
			else
			{
				sounds.SetAllMusicVolume(mouseVolumePosForFucksSake);
			}
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			mouseClickedMusicVolumeSlider = false;
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

	// Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX(), settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetMusicVolume() * 100))) },
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetMusicVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" V\n O\n L\n U\n M\n E\n%i", (int)(sounds.GetMusicVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 50, -3 }, 30, RAYWHITE);
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
	GameRunning = true;
}
