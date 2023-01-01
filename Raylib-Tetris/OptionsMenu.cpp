#include "OptionsMenu.h"
#include "Settings.h"
#include <iostream>

OptionsMenu::OptionsMenu(SoundManager &sounds1):
	optionsLoaded(false),
	sounds(sounds1),
	volume(0.2f),
	volumeSliderTint(Color{ 0, 0, 0, 255 }),
	mouseOverMusicVolumeSlider(false),
	mouseClickedMusicVolumeSlider(false),
	mouseOverReturnButton(false),
	mouseOverSFXVolumeSlider(false),
	mouseClickedSFXVolumeSlider(false),
	returnButtonCounter(0)
{
}

void OptionsMenu::LoadOptions()
{
	optionsLoaded = true;
}

void OptionsMenu::SetLoaded(bool val)
{
	optionsLoaded = val;
}

bool OptionsMenu::GetLoaded()
{
	return optionsLoaded;
}

void OptionsMenu::Tick()
{
	Draw();
	ReturnButton();
	VolumeSettings();
}

void OptionsMenu::Draw()
{
	ClearBackground(BLACK);

	// Music Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX(), settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetMusicVolume() * 100))) },
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetMusicVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" M\n U\n S\n I\n C\n%i", (int)(sounds.GetMusicVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 53, -3 }, 36, RAYWHITE);

	// Sounds Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos - Vec2<int>{ 103, 0 }, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX() - 103, settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetSFXVolume() * 100)))},
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetSFXVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" \n\n S\n F\n X\n%i", (int)(sounds.GetSFXVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 155, -3 }, 36, RAYWHITE);

	// Return Button
	raycpp::DrawRectangleLinesEx(settings::returnButtonPos, settings::returnButtonSize, 5, RAYWHITE);
	raycpp::DrawText("RETURN", { settings::returnButtonTextPos.GetX() - (settings::returnButtonSize.GetX() / 2) + (settings::returnButtonSize.GetX() - MeasureText("RETURN", settings::returnButtonTextSize) / 2),
		settings::returnButtonPos.GetY() - (settings::returnButtonSize.GetY() / 2) + (int)(settings::returnButtonSize.GetY() - MeasureTextEx(GetFontDefault(), "RETURN", (float)(settings::returnButtonTextSize / 2), 20).y) },
		settings::returnButtonTextSize, RAYWHITE);


}

void OptionsMenu::VolumeSettings()
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


	if (raycpp::GetMousePos() > settings::volumeSliderBorderPos - Vec2<int>{ 103, 25 }
	&& raycpp::GetMousePos() < settings::volumeSliderBorderPos - Vec2<int>{ 103, 15 } + settings::volumeSliderBorderSize)
	{
		if (mouseOverSFXVolumeSlider != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverSFXVolumeSlider = true;
		}
	}
	else
	{
		if (!mouseClickedSFXVolumeSlider)
		{
			mouseOverSFXVolumeSlider = false;
		}
	}

	if (mouseOverSFXVolumeSlider)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mouseClickedSFXVolumeSlider = true;
		}
		if (mouseClickedSFXVolumeSlider && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			float mouseVolumePosForFucksSake = ((((float)settings::volumeSliderPos.GetY() + settings::volumeSliderSize.GetY()) - raycpp::GetMousePos().GetY() - 20) / settings::volumeSliderSize.GetY());

			if (mouseVolumePosForFucksSake < 0)
			{
				sounds.SetAllSFXVolume(0.0f);
			}
			else if (mouseVolumePosForFucksSake > 1)
			{
				sounds.SetAllSFXVolume(1.0f);
			}
			else
			{
				sounds.SetAllSFXVolume(mouseVolumePosForFucksSake);
			}
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			mouseClickedSFXVolumeSlider = false;
		}
	}
}

void OptionsMenu::ReturnButton()
{
	if (raycpp::GetMousePos() > settings::returnButtonPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::returnButtonPos - Vec2<int>{ 0, 25 } + settings::returnButtonSize)
	{
		if (mouseOverReturnButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverReturnButton = true;
		}
	}
	else
	{
		if (settings::returnButtonTextSize < settings::maxReturnButtonTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnButtonTextSize += 5;
				returnButtonCounter = 0;
			}
		}
		mouseOverReturnButton = false;
	}
	if (mouseOverReturnButton)
	{
		if (settings::returnButtonTextSize > settings::minReturnButtonTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnButtonTextSize -= 5;
				returnButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			SetLoaded(false);
		}
	}
}
