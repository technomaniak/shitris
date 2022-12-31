#include "OptionsMenu.h"
#include "Settings.h"
#include <iostream>

OptionsMenu::OptionsMenu(SoundManager &sounds1):
	optionsLoaded(false),
	sounds(sounds1),
	volume(sounds.GetMusicVolume()),
	volumeSliderTint(Color{ 0, 0, 0, 255 }),
	mouseOverMusicVolumeSlider(false),
	mouseClickedMusicVolumeSlider(false)
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
	VolumeSettings();
}

void OptionsMenu::Draw()
{
	ClearBackground(BLACK);

	// Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX(), settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetMusicVolume() * 100))) },
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetMusicVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" V\n O\n L\n U\n M\n E\n%i", (int)(sounds.GetMusicVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 50, -3 }, 30, RAYWHITE);
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
}
