#include "OptionsMenu.h"
#include "Settings.h"
#include <iostream>

OptionsMenu::OptionsMenu(SoundManager &sounds1):
	optionsLoaded(false),
	sounds(sounds1),
	volume(0.2f),
	volumeSliderTint(Color{ 0, 0, 0, 255 }),
	mouseClickedMusicVolumeSlider(false),
	mouseClickedSFXVolumeSlider(false),
	mouseOverReturnButton(false),
	mouseOverSFXVolumeSlider(false),
	mouseOverMusicVolumeSlider(false),
	mouseOverControlsButton(false),
	mouseOverAudioAndGraphicsButton(false),
	returnButtonCounter(0),
	controlsButtonCounter(0),
	audioAndGraphicsButtonCounter(0),
	whatOptionPart(0)
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
	if (IsKeyPressed(KEY_ESCAPE))
	{
		optionsLoaded = false;
		whatOptionPart = 0;
		settings::controlsTextSize = 60;
		settings::audioAndGraphicsTextSize = 60;
		sounds.PlaySoundFromName("menuSound");
	}
	switch (whatOptionPart)
	{
	case 0:
		VolumeSettings();
		break;
	case 1:
		break;
	}
}

void OptionsMenu::Draw()
{
	ClearBackground(BLACK);
	ManageOptionsSelection();

	// Selection Borders & Return Button
	raycpp::DrawText("RETURN", settings::returnButtonTextPos - Vec2<int>{ (settings::minReturnTextSize - settings::returnTextSize) * -2,
				    ((settings::minReturnTextSize - settings::returnTextSize) / 2) * -1}, settings::returnTextSize, WHITE);
	raycpp::DrawLineEx(settings::verticalDividerPos, settings::verticalDividerPos + Vec2<int>{ 0, settings::verticalDividerLength }, 5, WHITE);
	raycpp::DrawLineEx(settings::horizontalDividerPos, settings::horizontalDividerPos + Vec2<int>{ settings::horizontalDividerLength, 0 }, 5, WHITE);
	raycpp::DrawLineEx(settings::verticalDividerPos2, settings::verticalDividerPos2 + Vec2<int>{ 0, settings::verticalDividerLength2 }, 5, WHITE);
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
	if (raycpp::GetMousePos() > settings::verticalDividerPos2 - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::verticalDividerLength2 } - Vec2<int>{ 0, 25 })
	{
		if (mouseOverReturnButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverReturnButton = true;
		}
	}
	else
	{
		if (settings::returnTextSize > settings::minReturnTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnTextSize -= 5;
				returnButtonCounter = 0;
			}
		}
		mouseOverReturnButton = false;
	}
	if (mouseOverReturnButton)
	{
		if (settings::returnTextSize < settings::maxReturnTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnTextSize += 5;
				returnButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			whatOptionPart = 0;
			settings::controlsTextSize = 60;
			settings::audioAndGraphicsTextSize = 60;
			SetLoaded(false);
		}
	}
}

void OptionsMenu::AudioAndGraphicsButton()
{
	if (raycpp::GetMousePos() >= Vec2<int>{ 0, 0 }
	&& raycpp::GetMousePos() < settings::verticalDividerPos - Vec2<int>{ 0, 25 - settings::verticalDividerLength })
	{
		if (mouseOverControlsButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverControlsButton = true;
		}
	}
	else
	{
		if (settings::controlsTextSize > settings::minControlsTextSize)
		{
			controlsButtonCounter++;
			if (controlsButtonCounter > 0)
			{
				settings::controlsTextSize -= 5;
				controlsButtonCounter = 0;
			}
		}
		mouseOverControlsButton = false;
	}
	if (mouseOverControlsButton)
	{
		if (settings::controlsTextSize < settings::maxControlsTextSize)
		{
			controlsButtonCounter++;
			if (controlsButtonCounter > 0)
			{
				settings::controlsTextSize += 5;
				controlsButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			whatOptionPart = 1;
		}
	}
}

void OptionsMenu::DrawControlsKeyBinds()
{
	raycpp::DrawText("ROTATE LEFT", settings::rotateLeftKeyTextPos, settings::rotateLeftKeyTextSize, WHITE);
	raycpp::DrawText("Z", settings::rotateLeftKeyButtonTextPos, settings::rotateLeftKeyTextSize, WHITE);

	raycpp::DrawText("ROTATE RIGHT", settings::rotateRightKeyTextPos, settings::rotateRightKeyTextSize, WHITE);
	raycpp::DrawText("X", settings::rotateRightKeyButtonTextPos, settings::rotateRightKeyTextSize, WHITE);

	raycpp::DrawText("MOVE RIGHT", settings::moveRightKeyTextPos, settings::moveRightKeyTextSize, WHITE);
	raycpp::DrawText("RIGHT ARROW", settings::moveRightKeyButtonTextPos, settings::moveRightKeyTextSize, WHITE);

	raycpp::DrawText("MOVE LEFT", settings::moveLeftKeyTextPos, settings::moveLeftKeyTextSize, WHITE);
	raycpp::DrawText("LEFT ARROW", settings::moveLeftKeyButtonTextPos, settings::moveLeftKeyTextSize, WHITE);

	raycpp::DrawText("RESET", settings::resetKeyTextPos, settings::resetKeyTextSize, WHITE);
	raycpp::DrawText("R", settings::resetKeyButtonTextPos, settings::resetKeyTextSize, WHITE);

	raycpp::DrawText("OPEN MENU", settings::menuKeyTextPos, settings::menuKeyTextSize, WHITE);
	raycpp::DrawText("ESC", settings::menuKeyButtonTextPos, settings::menuKeyTextSize, WHITE);

	raycpp::DrawText("HARD DROP", settings::hardDropKeyTextPos, settings::hardDropKeyTextSize, WHITE);
	raycpp::DrawText("SPACE", settings::hardDropKeyButtonTextPos, settings::hardDropKeyTextSize, WHITE);

	raycpp::DrawText("SOFT DROP", settings::softDropKeyTextPos, settings::softDropKeyTextSize, WHITE);
	raycpp::DrawText("ARROW DOWN", settings::softDropKeyButtonTextPos, settings::softDropKeyTextSize, WHITE);

	raycpp::DrawText("HOLD PIECE", settings::swapKeyTextPos, settings::swapKeyTextSize, WHITE);
	raycpp::DrawText("C", settings::swapKeyButtonTextPos, settings::swapKeyTextSize, WHITE);
}

OptionsMenu::KeyBinds OptionsMenu::SelectKeyBind()
{
	return KeyBinds::ROTATERIGHT;
}

KeyboardKey OptionsMenu::SelectKey()
{
	return KeyboardKey();
}

void OptionsMenu::SetKeysInSettings()
{
}

void OptionsMenu::ControlsButton()
{
	if (raycpp::GetMousePos() > settings::verticalDividerPos - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < settings::verticalDividerPos2 + Vec2<int>{ 0, settings::verticalDividerLength2 } - Vec2<int>{ 0, 25 })
	{
		if (mouseOverAudioAndGraphicsButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverAudioAndGraphicsButton = true;
		}
	}
	else
	{
		if (settings::audioAndGraphicsTextSize > settings::minAudioAndGraphicsTextSize)
		{
			audioAndGraphicsButtonCounter++;
			if (audioAndGraphicsButtonCounter > 0)
			{
				settings::audioAndGraphicsTextSize -= 5;
				audioAndGraphicsButtonCounter = 0;
			}
		}
		mouseOverAudioAndGraphicsButton = false;
	}
	if (mouseOverAudioAndGraphicsButton)
	{
		if (settings::audioAndGraphicsTextSize < settings::maxAudioAndGraphicsTextSize)
		{
			audioAndGraphicsButtonCounter++;
			if (audioAndGraphicsButtonCounter > 0)
			{
				settings::audioAndGraphicsTextSize += 5;
				audioAndGraphicsButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			whatOptionPart = 0;
		}
	}
}

void OptionsMenu::ControlsSelection()
{
	// Selection Buttons
	raycpp::DrawText("AUDIO / GRAPHICS", settings::audioAndGraphicsTextPos - Vec2<int>{ (int)((settings::minAudioAndGraphicsTextSize - settings::audioAndGraphicsTextSize) * -4.85),
		((settings::minAudioAndGraphicsTextSize - settings::audioAndGraphicsTextSize) / 2) * -1 }, settings::audioAndGraphicsTextSize, WHITE);
	raycpp::DrawText("CONTROLS", settings::controlsTextPos - Vec2<int>{ (int)((settings::minControlsTextSize - settings::maxControlsTextSize) * -2.5),
		((settings::minControlsTextSize - settings::maxControlsTextSize) / 2) * -1 }, settings::maxControlsTextSize, WHITE);

}

void OptionsMenu::ManageOptionsSelection()
{
	switch (whatOptionPart)
	{
	case 0:
		AudioAndGraphics();
		break;
	case 1:
		Controls();
		break;
	}
	ReturnButton();
}

void OptionsMenu::AudioAndGraphics()
{
	AudioAndGraphicsButton();
	AudioAndGraphicsSelection();
}

void OptionsMenu::AudioAndGraphicsSelection()
{
	// Selection Buttons
	raycpp::DrawText("AUDIO / GRAPHICS", settings::audioAndGraphicsTextPos - Vec2<int>{ (int)((settings::minAudioAndGraphicsTextSize - settings::maxAudioAndGraphicsTextSize) * -4.85),
		((settings::minAudioAndGraphicsTextSize - settings::maxAudioAndGraphicsTextSize) / 2) * -1 }, settings::maxAudioAndGraphicsTextSize, WHITE);
	raycpp::DrawText("CONTROLS", settings::controlsTextPos - Vec2<int>{ (int)((settings::minControlsTextSize - settings::controlsTextSize) * -2.5),
		((settings::minControlsTextSize - settings::controlsTextSize) / 2) * -1 }, settings::controlsTextSize, WHITE);

	// Music Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX(), settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetMusicVolume() * 100))) },
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetMusicVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" M\n U\n S\n I\n C\n%i", (int)(sounds.GetMusicVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 63, -3 }, 36, RAYWHITE);

	// Sounds Volume
	raycpp::DrawRectangleLinesEx(settings::volumeSliderBorderPos - Vec2<int>{ 123, 0 }, settings::volumeSliderBorderSize, 2, RAYWHITE);
	raycpp::DrawRectangle({ settings::volumeSliderPos.GetX() - 123, settings::volumeSliderPos.GetY() + (settings::volumeSliderSize.GetY() / 100 * (100 - (int)(sounds.GetSFXVolume() * 100))) },
		{ settings::volumeSliderSize.GetX(), (settings::volumeSliderSize.GetY() / 100) * (int)(sounds.GetSFXVolume() * 100) }, RAYWHITE);
	raycpp::DrawText(TextFormat(" \n\n S\n F\n X\n%i", (int)(sounds.GetSFXVolume() * 100)), settings::volumeSliderBorderPos - Vec2<int>{ 185, -5 }, 36, RAYWHITE);
}

void OptionsMenu::Controls()
{
	ControlsButton();
	ControlsSelection();
	DrawControlsKeyBinds();
}
