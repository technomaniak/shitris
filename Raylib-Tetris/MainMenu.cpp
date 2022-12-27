#include "MainMenu.h"
#include "Settings.h"

MainMenu::MainMenu(SoundManager sounds):
	GameRunning(false),
	menuLoaded(false),
	counter(0),
	sounds(sounds),
	mouseOverPlayButton(false),
	volume(0.0f)
{
}

void MainMenu::LoadMenu()
{
	//Texture2D texture = LoadTextureFromImage(GenImageColor(settings::screenWidth, settings::screenHeight, Color{ 0, 0, 0, 255 }));
	//DrawTexture(texture, 0, 0, WHITE);
	ClearBackground(BLACK);
	raycpp::DrawRectangleLinesEx(settings::playButtonPos, settings::playButtonSize, 5, RAYWHITE);
	raycpp::DrawText("PLAY", { settings::playButtonTextPos.GetX() - (settings::playButtonSize.GetX() / 2) + (settings::playButtonSize.GetX() - MeasureText("PLAY", settings::playButtonTextSize) / 2),
		settings::playButtonPos.GetY() - (settings::playButtonSize.GetY() / 2) + (int)(settings::playButtonSize.GetY() - MeasureTextEx(GetFontDefault(), "PLAY", settings::playButtonTextSize / 2, 20).y) },
		settings::playButtonTextSize, RAYWHITE);
	menuLoaded = true;
}

void MainMenu::Tick()
{
	PlayButton();
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
			counter++;
			if (counter > 0)
			{
				settings::playButtonTextSize += 5;
				counter = 0;
			}
		}
		mouseOverPlayButton = false;
	}
	if (mouseOverPlayButton)
	{
		if (settings::playButtonTextSize > settings::minPlayButtonTextSize)
		{
			counter++;
			if (counter > 0)
			{
				settings::playButtonTextSize -= 5;
				counter = 0;
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

}

bool MainMenu::GetGameRunning() const
{
	return GameRunning;
}

bool MainMenu::GetMenuLoaded() const
{
	return menuLoaded;
}

void MainMenu::StartGame()
{
	sounds.PlaySoundFromName("menuSound");
	GameRunning = true;
}
