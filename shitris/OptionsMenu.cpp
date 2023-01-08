#include "OptionsMenu.h"
#include "Settings.h"
#include <iostream>
#include <fstream>

OptionsMenu::OptionsMenu(SoundManager& sounds1, std::vector<std::vector<int>>& keyBindsList1) :
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
	whatOptionPart(0),
	keyBindsList(keyBindsList1),
	waitingForInput(KeyBinds::NONE),
	keyPressed(0),
	justFoundKey(false)
{
	LoadKeysFromSettings();
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
	if (waitingForInput == KeyBinds::NONE)
	{
		if (justFoundKey == false)
		{
			if (IsKeyPressed(KEY_ESCAPE))
			{
				optionsLoaded = false;
				whatOptionPart = 0;
				SaveKeysInSettings();
				settings::controlsTextSize = 60;
				settings::audioAndGraphicsTextSize = 60;
				sounds.PlaySoundFromName("menuSound");
			}
		}
		else
		{
			justFoundKey = false;
		}
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
				    ((settings::minReturnTextSize - settings::returnTextSize) / 2) * -1}, settings::returnTextSize, RAYWHITE);
	raycpp::DrawLineEx(settings::verticalDividerPos, settings::verticalDividerPos + Vec2<int>{ 0, settings::verticalDividerLength }, 5, RAYWHITE);
	raycpp::DrawLineEx(settings::horizontalDividerPos, settings::horizontalDividerPos + Vec2<int>{ settings::horizontalDividerLength, 0 }, 5, RAYWHITE);
	raycpp::DrawLineEx(settings::verticalDividerPos2, settings::verticalDividerPos2 + Vec2<int>{ 0, settings::verticalDividerLength2 }, 5, RAYWHITE);
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

bool OptionsMenu::MoveRightKeyBind()
{
	if (raycpp::GetMousePos() > settings::moveRightKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateMoveRightKeyButtonTextPos.GetX(), settings::alternateMoveRightKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverMoveRight != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverMoveRight = true;
		}
	}
	else
	{
		if (settings::moveRightKeyTextSize > settings::minMoveRightKeyTextSize)
		{
			moveRightCounter++;
			if (moveRightCounter > 0)
			{
				settings::moveRightKeyTextSize -= 5;
				moveRightCounter = 0;
			}
		}
		mouseOverMoveRight = false;
	}
	if (mouseOverMoveRight)
	{
		if (settings::moveRightKeyTextSize < settings::maxMoveRightKeyTextSize)
		{
			moveRightCounter++;
			if (moveRightCounter > 0)
			{
				settings::moveRightKeyTextSize += 5;
				moveRightCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::MoveLeftKeyBind()
{
	if (raycpp::GetMousePos() > settings::moveLeftKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateMoveLeftKeyButtonTextPos.GetX(), settings::alternateMoveLeftKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverMoveLeft != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverMoveLeft = true;
		}
	}
	else
	{
		if (settings::moveLeftKeyTextSize > settings::minMoveLeftKeyTextSize)
		{
			moveLeftCounter++;
			if (moveLeftCounter > 0)
			{
				settings::moveLeftKeyTextSize -= 5;
				moveLeftCounter = 0;
			}
		}
		mouseOverMoveLeft = false;
	}
	if (mouseOverMoveLeft)
	{
		if (settings::moveLeftKeyTextSize < settings::maxMoveLeftKeyTextSize)
		{
			moveLeftCounter++;
			if (moveLeftCounter > 0)
			{
				settings::moveLeftKeyTextSize += 5;
				moveLeftCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::RotateRightKeyBind()
{
	if (raycpp::GetMousePos() > settings::rotateLeftKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateRotateLeftKeyButtonTextPos.GetX(), settings::alternateRotateLeftKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverRotateLeft != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverRotateLeft = true;
		}
	}
	else
	{
		if (settings::rotateLeftKeyTextSize > settings::minRotateLeftKeyTextSize)
		{
			rotateLeftCounter++;
			if (rotateLeftCounter > 0)
			{
				settings::rotateLeftKeyTextSize -= 5;
				rotateLeftCounter = 0;
			}
		}
		mouseOverRotateLeft = false;
	}
	if (mouseOverRotateLeft)
	{
		if (settings::rotateLeftKeyTextSize < settings::maxRotateLeftKeyTextSize)
		{
			rotateLeftCounter++;
			if (rotateLeftCounter > 0)
			{
				settings::rotateLeftKeyTextSize += 5;
				rotateLeftCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::RotateLeftKeyBind()
{
	if (raycpp::GetMousePos() > settings::rotateRightKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateRotateRightKeyButtonTextPos.GetX(), settings::alternateRotateRightKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverRotateRight != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverRotateRight = true;
		}
	}
	else
	{
		if (settings::rotateRightKeyTextSize > settings::minRotateRightKeyTextSize)
		{
			rotateRightCounter++;
			if (rotateRightCounter > 0)
			{
				settings::rotateRightKeyTextSize -= 5;
				rotateRightCounter = 0;
			}
		}
		mouseOverRotateRight = false;
	}
	if (mouseOverRotateRight)
	{
		if (settings::rotateRightKeyTextSize < settings::maxRotateRightKeyTextSize)
		{
			rotateRightCounter++;
			if (rotateRightCounter > 0)
			{
				settings::rotateRightKeyTextSize += 5;
				rotateRightCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::ResetKeyBind()
{
	if (raycpp::GetMousePos() > settings::resetKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateResetKeyButtonTextPos.GetX(), settings::alternateResetKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverReset != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverReset = true;
		}
	}
	else
	{
		if (settings::resetKeyTextSize > settings::minResetKeyTextSize)
		{
			resetCounter++;
			if (resetCounter > 0)
			{
				settings::resetKeyTextSize -= 5;
				resetCounter = 0;
			}
		}
		mouseOverReset = false;
	}
	if (mouseOverReset)
	{
		if (settings::resetKeyTextSize < settings::maxResetKeyTextSize)
		{
			resetCounter++;
			if (resetCounter > 0)
			{
				settings::resetKeyTextSize += 5;
				resetCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::MenuKeyBind()
{
	if (raycpp::GetMousePos() > settings::menuKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateMenuKeyButtonTextPos.GetX(), settings::alternateMenuKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverMenu != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverMenu = true;
		}
	}
	else
	{
		if (settings::menuKeyTextSize > settings::minMenuKeyTextSize)
		{
			menuCounter++;
			if (menuCounter > 0)
			{
				settings::menuKeyTextSize -= 5;
				menuCounter = 0;
			}
		}
		mouseOverMenu = false;
	}
	if (mouseOverMenu)
	{
		if (settings::menuKeyTextSize < settings::maxMenuKeyTextSize)
		{
			menuCounter++;
			if (menuCounter > 0)
			{
				settings::menuKeyTextSize += 5;
				menuCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::HardDropKeyBind()
{
	if (raycpp::GetMousePos() > settings::hardDropKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateHardDropKeyButtonTextPos.GetX(), settings::alternateHardDropKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverHardDrop != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverHardDrop = true;
		}
	}
	else
	{
		if (settings::hardDropKeyTextSize > settings::minHardDropKeyTextSize)
		{
			hardDropCounter++;
			if (hardDropCounter > 0)
			{
				settings::hardDropKeyTextSize -= 5;
				hardDropCounter = 0;
			}
		}
		mouseOverHardDrop = false;
	}
	if (mouseOverHardDrop)
	{
		if (settings::hardDropKeyTextSize < settings::maxHardDropKeyTextSize)
		{
			hardDropCounter++;
			if (hardDropCounter > 0)
			{
				settings::hardDropKeyTextSize += 5;
				hardDropCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::SoftDropKeyBind()
{
	if (raycpp::GetMousePos() > settings::softDropKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateSoftDropKeyButtonTextPos.GetX(), settings::alternateSoftDropKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverSoftDrop != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverSoftDrop = true;
		}
	}
	else
	{
		if (settings::softDropKeyTextSize > settings::minSoftDropKeyTextSize)
		{
			softDropCounter++;
			if (softDropCounter > 0)
			{
				settings::softDropKeyTextSize -= 5;
				softDropCounter = 0;
			}
		}
		mouseOverSoftDrop = false;
	}
	if (mouseOverSoftDrop)
	{
		if (settings::softDropKeyTextSize < settings::maxSoftDropKeyTextSize)
		{
			softDropCounter++;
			if (softDropCounter > 0)
			{
				settings::softDropKeyTextSize += 5;
				softDropCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::SwapKeyBind()
{
	if (raycpp::GetMousePos() > settings::swapKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::alternateSwapKeyButtonTextPos.GetX(), settings::alternateSwapKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (mouseOverSwap != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverSwap = true;
		}
	}
	else
	{
		if (settings::swapKeyTextSize > settings::minSwapKeyTextSize)
		{
			swapCounter++;
			if (swapCounter > 0)
			{
				settings::swapKeyTextSize -= 5;
				swapCounter = 0;
			}
		}
		mouseOverSwap = false;
	}
	if (mouseOverSwap)
	{
		if (settings::swapKeyTextSize < settings::maxSwapKeyTextSize)
		{
			swapCounter++;
			if (swapCounter > 0)
			{
				settings::swapKeyTextSize += 5;
				swapCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateMoveRightKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateMoveRightKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateMoveRightKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverMoveRight != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverMoveRight = true;
		}
	}
	else
	{
		if (settings::alternateMoveRightKeyTextSize > settings::minMoveRightKeyTextSize)
		{
			alternateMoveRightCounter++;
			if (alternateMoveRightCounter > 0)
			{
				settings::alternateMoveRightKeyTextSize -= 5;
				alternateMoveRightCounter = 0;
			}
		}
		alternateMouseOverMoveRight = false;
	}
	if (alternateMouseOverMoveRight)
	{
		if (settings::alternateMoveRightKeyTextSize < settings::maxMoveRightKeyTextSize)
		{
			alternateMoveRightCounter++;
			if (alternateMoveRightCounter > 0)
			{
				settings::alternateMoveRightKeyTextSize += 5;
				alternateMoveRightCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateMoveLeftKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateMoveLeftKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateMoveLeftKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverMoveLeft != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverMoveLeft = true;
		}
	}
	else
	{
		if (settings::alternateMoveLeftKeyTextSize > settings::minMoveLeftKeyTextSize)
		{
			alternateMoveLeftCounter++;
			if (alternateMoveLeftCounter > 0)
			{
				settings::alternateMoveLeftKeyTextSize -= 5;
				alternateMoveLeftCounter = 0;
			}
		}
		alternateMouseOverMoveLeft = false;
	}
	if (alternateMouseOverMoveLeft)
	{
		if (settings::alternateMoveLeftKeyTextSize < settings::maxMoveLeftKeyTextSize)
		{
			alternateMoveLeftCounter++;
			if (alternateMoveLeftCounter > 0)
			{
				settings::alternateMoveLeftKeyTextSize += 5;
				alternateMoveLeftCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateRotateRightKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateRotateRightKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateRotateRightKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverRotateRight != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverRotateRight = true;
		}
	}
	else
	{
		if (settings::alternateRotateRightKeyTextSize > settings::minRotateRightKeyTextSize)
		{
			alternateRotateRightCounter++;
			if (alternateRotateRightCounter > 0)
			{
				settings::alternateRotateRightKeyTextSize -= 5;
				alternateRotateRightCounter = 0;
			}
		}
		alternateMouseOverRotateRight = false;
	}
	if (alternateMouseOverRotateRight)
	{
		if (settings::alternateRotateRightKeyTextSize < settings::maxRotateRightKeyTextSize)
		{
			alternateRotateRightCounter++;
			if (alternateRotateRightCounter > 0)
			{
				settings::alternateRotateRightKeyTextSize += 5;
				alternateRotateRightCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateRotateLeftKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateRotateLeftKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateRotateLeftKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverRotateLeft != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverRotateLeft = true;
		}
	}
	else
	{
		if (settings::alternateRotateLeftKeyTextSize > settings::minRotateLeftKeyTextSize)
		{
			alternateRotateLeftCounter++;
			if (alternateRotateLeftCounter > 0)
			{
				settings::alternateRotateLeftKeyTextSize -= 5;
				alternateRotateLeftCounter = 0;
			}
		}
		alternateMouseOverRotateLeft = false;
	}
	if (alternateMouseOverRotateLeft)
	{
		if (settings::alternateRotateLeftKeyTextSize < settings::maxRotateLeftKeyTextSize)
		{
			alternateRotateLeftCounter++;
			if (alternateRotateLeftCounter > 0)
			{
				settings::alternateRotateLeftKeyTextSize += 5;
				alternateRotateLeftCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateResetKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateResetKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateResetKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverReset != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverReset = true;
		}
	}
	else
	{
		if (settings::alternateResetKeyTextSize > settings::minResetKeyTextSize)
		{
			alternateResetCounter++;
			if (alternateResetCounter > 0)
			{
				settings::alternateResetKeyTextSize -= 5;
				alternateResetCounter = 0;
			}
		}
		alternateMouseOverReset = false;
	}
	if (alternateMouseOverReset)
	{
		if (settings::alternateResetKeyTextSize < settings::maxResetKeyTextSize)
		{
			alternateResetCounter++;
			if (alternateResetCounter > 0)
			{
				settings::alternateResetKeyTextSize += 5;
				alternateResetCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateMenuKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateMenuKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateMenuKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverMenu != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverMenu = true;
		}
	}
	else
	{
		if (settings::alternateMenuKeyTextSize > settings::minMenuKeyTextSize)
		{
			alternateMenuCounter++;
			if (alternateMenuCounter > 0)
			{
				settings::alternateMenuKeyTextSize -= 5;
				alternateMenuCounter = 0;
			}
		}
		alternateMouseOverMenu = false;
	}
	if (alternateMouseOverMenu)
	{
		if (settings::alternateMenuKeyTextSize < settings::maxMenuKeyTextSize)
		{
			alternateMenuCounter++;
			if (alternateMenuCounter > 0)
			{
				settings::alternateMenuKeyTextSize += 5;
				alternateMenuCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateHardDropKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateHardDropKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateHardDropKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverHardDrop != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverHardDrop = true;
		}
	}
	else
	{
		if (settings::alternateHardDropKeyTextSize > settings::minHardDropKeyTextSize)
		{
			alternateHardDropCounter++;
			if (alternateHardDropCounter > 0)
			{
				settings::alternateHardDropKeyTextSize -= 5;
				alternateHardDropCounter = 0;
			}
		}
		alternateMouseOverHardDrop = false;
	}
	if (alternateMouseOverHardDrop)
	{
		if (settings::alternateHardDropKeyTextSize < settings::maxHardDropKeyTextSize)
		{
			alternateHardDropCounter++;
			if (alternateHardDropCounter > 0)
			{
				settings::alternateHardDropKeyTextSize += 5;
				alternateHardDropCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateSoftDropKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateSoftDropKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateSoftDropKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverSoftDrop != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverSoftDrop = true;
		}
	}
	else
	{
		if (settings::alternateSoftDropKeyTextSize > settings::minSoftDropKeyTextSize)
		{
			alternateSoftDropCounter++;
			if (alternateSoftDropCounter > 0)
			{
				settings::alternateSoftDropKeyTextSize -= 5;
				alternateSoftDropCounter = 0;
			}
		}
		alternateMouseOverSoftDrop = false;
	}
	if (alternateMouseOverSoftDrop)
	{
		if (settings::alternateSoftDropKeyTextSize < settings::maxSoftDropKeyTextSize)
		{
			alternateSoftDropCounter++;
			if (alternateSoftDropCounter > 0)
			{
				settings::alternateSoftDropKeyTextSize += 5;
				alternateSoftDropCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
}

bool OptionsMenu::AlternateSwapKeyBind()
{
	if (raycpp::GetMousePos() > settings::alternateSwapKeyButtonTextPos - Vec2<int>{ 100, 50 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::alternateSwapKeyButtonTextPos.GetY() + 100 } - Vec2<int>{ 100, 50 })
	{
		if (alternateMouseOverSwap != true)
		{
			sounds.PlaySoundFromName("menuSound");
			alternateMouseOverSwap = true;
		}
	}
	else
	{
		if (settings::alternateSwapKeyTextSize > settings::minSwapKeyTextSize)
		{
			alternateSwapCounter++;
			if (alternateSwapCounter > 0)
			{
				settings::alternateSwapKeyTextSize -= 5;
				alternateSwapCounter = 0;
			}
		}
		alternateMouseOverSwap = false;
	}
	if (alternateMouseOverSwap)
	{
		if (settings::alternateSwapKeyTextSize < settings::maxSwapKeyTextSize)
		{
			alternateSwapCounter++;
			if (alternateSwapCounter > 0)
			{
				settings::alternateSwapKeyTextSize += 5;
				alternateSwapCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			return true;
		}
	}
	return false;
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
			sounds.PlaySoundFromName("menuSound");
			SaveKeysInSettings();
			whatOptionPart = 0;
			settings::controlsTextSize = 60;
			settings::audioAndGraphicsTextSize = 60;
			waitingForInput = KeyBinds::NONE;
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
	raycpp::DrawText("MOVE RIGHT", settings::moveRightKeyTextPos, settings::minMoveRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][0]).c_str(), 
			settings::moveRightKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][0]).c_str(), settings::minMoveRightKeyTextSize) 
			- MeasureText(KeyBindName(keyBindsList[0][0]).c_str(), settings::moveRightKeyTextSize))) / 2, 
			(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][0]).c_str(), (int)settings::minMoveRightKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][0]).c_str(), (float)settings::moveRightKeyTextSize, 20).y)) / 2) },
			settings::moveRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][0]).c_str(),
			settings::alternateMoveRightKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][0]).c_str(), settings::minMoveRightKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][0]).c_str(), settings::alternateMoveRightKeyTextSize))) / 2,
			(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][0]).c_str(), (int)settings::minMoveRightKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][0]).c_str(), (float)settings::alternateMoveRightKeyTextSize, 20).y)) / 2) },
			settings::alternateMoveRightKeyTextSize, RAYWHITE);

	raycpp::DrawText("MOVE LEFT", settings::moveLeftKeyTextPos, settings::minMoveLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][1]).c_str(),
		settings::moveLeftKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][1]).c_str(), settings::minMoveLeftKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][1]).c_str(), settings::moveLeftKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][1]).c_str(), (int)settings::minMoveLeftKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][1]).c_str(), (float)settings::moveLeftKeyTextSize, 20).y)) / 2) },
		settings::moveLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][1]).c_str(),
		settings::alternateMoveLeftKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][1]).c_str(), settings::minMoveLeftKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][1]).c_str(), settings::alternateMoveLeftKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][1]).c_str(), (int)settings::minMoveLeftKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][1]).c_str(), (float)settings::alternateMoveLeftKeyTextSize, 20).y)) / 2) },
		settings::alternateMoveLeftKeyTextSize, RAYWHITE);

	raycpp::DrawText("ROTATE RIGHT", settings::rotateRightKeyTextPos, settings::minRotateRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][2]).c_str(),
		settings::rotateRightKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][2]).c_str(), settings::minRotateRightKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][2]).c_str(), settings::rotateRightKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][2]).c_str(), (int)settings::minRotateRightKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][2]).c_str(), (float)settings::rotateRightKeyTextSize, 20).y)) / 2) },
		settings::rotateRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][2]).c_str(),
		settings::alternateRotateRightKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][2]).c_str(), settings::minRotateRightKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][2]).c_str(), settings::alternateRotateRightKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][2]).c_str(), (int)settings::minRotateRightKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][2]).c_str(), (float)settings::alternateRotateRightKeyTextSize, 20).y)) / 2) },
		settings::alternateRotateRightKeyTextSize, RAYWHITE);

	raycpp::DrawText("ROTATE LEFT", settings::rotateLeftKeyTextPos, settings::minRotateLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][3]).c_str(),
		settings::rotateLeftKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][3]).c_str(), settings::minRotateLeftKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][3]).c_str(), settings::rotateLeftKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][3]).c_str(), (int)settings::minRotateLeftKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][3]).c_str(), (float)settings::rotateLeftKeyTextSize, 20).y)) / 2) },
		settings::rotateLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][3]).c_str(),
		settings::alternateRotateLeftKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][3]).c_str(), settings::minRotateLeftKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][3]).c_str(), settings::alternateRotateLeftKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][3]).c_str(), (int)settings::minRotateLeftKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][3]).c_str(), (float)settings::alternateRotateLeftKeyTextSize, 20).y)) / 2) },
		settings::alternateRotateLeftKeyTextSize, RAYWHITE);

	raycpp::DrawText("RESET", settings::resetKeyTextPos, settings::minResetKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][4]).c_str(),
		settings::resetKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][4]).c_str(), settings::minResetKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][4]).c_str(), settings::resetKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][4]).c_str(), (int)settings::minResetKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][4]).c_str(), (float)settings::resetKeyTextSize, 20).y)) / 2) },
		settings::resetKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][4]).c_str(),
		settings::alternateResetKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][4]).c_str(), settings::minResetKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][4]).c_str(), settings::alternateResetKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][4]).c_str(), (int)settings::minResetKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][4]).c_str(), (float)settings::alternateResetKeyTextSize, 20).y)) / 2) },
		settings::alternateResetKeyTextSize, RAYWHITE);

	raycpp::DrawText("OPEN MENU", settings::menuKeyTextPos, settings::minMenuKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][5]).c_str(),
		settings::menuKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][5]).c_str(), settings::minMenuKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][5]).c_str(), settings::menuKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][5]).c_str(), (int)settings::minMenuKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][5]).c_str(), (float)settings::menuKeyTextSize, 20).y)) / 2) },
		settings::menuKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][5]).c_str(),
		settings::alternateMenuKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][5]).c_str(), settings::minMenuKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][5]).c_str(), settings::alternateMenuKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][5]).c_str(), (int)settings::minMenuKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][5]).c_str(), (float)settings::alternateMenuKeyTextSize, 20).y)) / 2) },
		settings::alternateMenuKeyTextSize, RAYWHITE);

	raycpp::DrawText("HARD DROP", settings::hardDropKeyTextPos, settings::minHardDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][6]).c_str(),
		settings::hardDropKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][6]).c_str(), settings::minHardDropKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][6]).c_str(), settings::hardDropKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][6]).c_str(), (int)settings::minHardDropKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][6]).c_str(), (float)settings::hardDropKeyTextSize, 20).y)) / 2) },
		settings::hardDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][6]).c_str(),
		settings::alternateHardDropKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][6]).c_str(), settings::minHardDropKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][6]).c_str(), settings::alternateHardDropKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][6]).c_str(), (int)settings::minHardDropKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][6]).c_str(), (float)settings::alternateHardDropKeyTextSize, 20).y)) / 2) },
		settings::alternateHardDropKeyTextSize, RAYWHITE);

	raycpp::DrawText("SOFT DROP", settings::softDropKeyTextPos, settings::minSoftDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][7]).c_str(),
		settings::softDropKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][7]).c_str(), settings::minSoftDropKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][7]).c_str(), settings::softDropKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][7]).c_str(), (int)settings::minSoftDropKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][7]).c_str(), (float)settings::softDropKeyTextSize, 20).y)) / 2) },
		settings::softDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][7]).c_str(),
		settings::alternateSoftDropKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][7]).c_str(), settings::minSoftDropKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][7]).c_str(), settings::alternateSoftDropKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][7]).c_str(), (int)settings::minSoftDropKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][7]).c_str(), (float)settings::alternateSoftDropKeyTextSize, 20).y)) / 2) },
		settings::alternateSoftDropKeyTextSize, RAYWHITE);

	raycpp::DrawText("HOLD PIECE", settings::swapKeyTextPos, settings::minSwapKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][8]).c_str(),
		settings::swapKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][8]).c_str(), settings::minSwapKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[0][8]).c_str(), settings::swapKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][8]).c_str(), (int)settings::minSwapKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][8]).c_str(), (float)settings::swapKeyTextSize, 20).y)) / 2) },
		settings::swapKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][8]).c_str(),
		settings::alternateSwapKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[1][8]).c_str(), settings::minSwapKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][8]).c_str(), settings::alternateSwapKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][8]).c_str(), (int)settings::minSwapKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][8]).c_str(), (float)settings::alternateSwapKeyTextSize, 20).y)) / 2) },
		settings::alternateSwapKeyTextSize, RAYWHITE);
}

OptionsMenu::KeyBinds OptionsMenu::SelectKeyBind()
{
	if (waitingForInput == KeyBinds::NONE)
	{
		if (MoveRightKeyBind())
		{
			waitingForInput = KeyBinds::MOVERIGHT;
			return KeyBinds::MOVERIGHT;
		}
		if (AlternateMoveRightKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATEMOVERIGHT;
			return KeyBinds::ALTERNATEMOVERIGHT;
		}
		if (MoveLeftKeyBind())
		{
			waitingForInput = KeyBinds::MOVELEFT;
			return KeyBinds::MOVELEFT;
		}
		if (AlternateMoveLeftKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATEMOVELEFT;
			return KeyBinds::ALTERNATEMOVELEFT;
		}
		if (RotateRightKeyBind())
		{
			waitingForInput = KeyBinds::ROTATERIGHT;
			return KeyBinds::ROTATERIGHT;
		}
		if (AlternateRotateRightKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATEROTATERIGHT;
			return KeyBinds::ALTERNATEROTATERIGHT;
		}
		if (RotateLeftKeyBind())
		{
			waitingForInput = KeyBinds::ROTATELEFT;
			return KeyBinds::ROTATELEFT;
		}
		if (AlternateRotateLeftKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATEROTATELEFT;
			return KeyBinds::ALTERNATEROTATELEFT;
		}
		if (ResetKeyBind())
		{
			waitingForInput = KeyBinds::RESET;
			return KeyBinds::RESET;
		}
		if (AlternateResetKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATERESET;
			return KeyBinds::ALTERNATERESET;
		}
		if (MenuKeyBind())
		{
			waitingForInput = KeyBinds::MENU;
			return KeyBinds::MENU;
		}
		if (AlternateMenuKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATEMENU;
			return KeyBinds::ALTERNATEMENU;
		}
		if (HardDropKeyBind())
		{
			waitingForInput = KeyBinds::HARDDROP;
			return KeyBinds::HARDDROP;
		}
		if (AlternateHardDropKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATEHARDDROP;
			return KeyBinds::ALTERNATEHARDDROP;
		}
		if (SoftDropKeyBind())
		{
			waitingForInput = KeyBinds::SOFTDROP;
			return KeyBinds::SOFTDROP;
		}
		if (AlternateSoftDropKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATESOFTDROP;
			return KeyBinds::ALTERNATESOFTDROP;
		}
		if (SwapKeyBind())
		{
			waitingForInput = KeyBinds::SWAPPIECE;
			return KeyBinds::SWAPPIECE;
		}
		if (AlternateSwapKeyBind())
		{
			waitingForInput = KeyBinds::ALTERNATESWAPPIECE;
			return KeyBinds::ALTERNATESWAPPIECE;
		}
	}
	return waitingForInput;
}

void OptionsMenu::SelectKey(KeyBinds selection)
{
	switch (selection)
	{
	case OptionsMenu::KeyBinds::ROTATELEFT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][3])
			{
				keyBindsList[0][3] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][3] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ROTATERIGHT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][2])
			{
				keyBindsList[0][2] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][2] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::RESET:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][4])
			{
				keyBindsList[0][4] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][4] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::SWAPPIECE:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][8])
			{
				keyBindsList[0][8] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][8] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::MENU:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][5])
			{
				keyBindsList[0][5] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][5] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::MOVERIGHT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][0])
			{
				keyBindsList[0][0] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][0] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::MOVELEFT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][1])
			{
				keyBindsList[0][1] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][1] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::HARDDROP:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][6])
			{
				keyBindsList[0][6] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][6] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::SOFTDROP:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[0][7])
			{
				keyBindsList[0][7] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[0][7] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATEROTATELEFT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][3])
			{
				keyBindsList[1][3] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][3] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATEROTATERIGHT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][2])
			{
				keyBindsList[1][2] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][2] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATERESET:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][4])
			{
				keyBindsList[1][4] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][4] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATESWAPPIECE:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][8])
			{
				keyBindsList[1][8] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][8] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATEMENU:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][5])
			{
				keyBindsList[1][5] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][5] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATEMOVERIGHT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][0])
			{
				keyBindsList[1][0] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][0] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATEMOVELEFT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][1])
			{
				keyBindsList[1][1] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][1] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATEHARDDROP:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][6])
			{
				keyBindsList[1][6] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][6] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	case OptionsMenu::KeyBinds::ALTERNATESOFTDROP:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			if (keyPressed == keyBindsList[1][7])
			{
				keyBindsList[1][7] = 0;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
			else
			{
				keyBindsList[1][7] = keyPressed;
				waitingForInput = KeyBinds::NONE;
				justFoundKey = true;
			}
		}
		break;
	}
}

void OptionsMenu::SaveKeysInSettings()
{
	std::ofstream outputFile("Controls.setting");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < keyBindsList[0].size(); j++)
		{
			outputFile << keyBindsList[i][j] << "\n";
		}
	}
}

void OptionsMenu::LoadKeysFromSettings()
{
	std::string input;
	std::ifstream inputFile("Controls.setting");
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][0] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][1] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][2] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][3] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][4] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][5] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][6] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][7] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[0][8] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][0] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][1] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][2] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][3] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][4] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][5] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][6] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][7] = std::stoi(input);
	}
	getline(inputFile, input);
	if (input != "")
	{
		keyBindsList[1][8] = std::stoi(input);
	}
}

std::string OptionsMenu::KeyBindName(int key)
{
	switch (key)
	{
	case 0:
		return "NONE";
	case 32:
		return "SPACE";
	case 39:
		return "'";
	case 44:
		return ",";
	case 45:
		return "-";
	case 46:
		return ".";
	case 47:
		return "/";
	case 48:
		return "0";
	case 49:
		return "1";
	case 50:
		return "2";
	case 51:
		return "3";
	case 52:
		return "4";
	case 53:
		return "5";
	case 54:
		return "6";
	case 55:
		return "7";
	case 56:
		return "8";
	case 57:
		return "9";
	case 59:
		return ";";
	case 61:
		return "=";
	case 65:
		return "A";
	case 66:
		return "B";
	case 67:
		return "C";
	case 68:
		return "D";
	case 69:
		return "E";
	case 70:
		return "F";
	case 71:
		return "G";
	case 72:
		return "H";
	case 73:
		return "I";
	case 74:
		return "J";
	case 75:
		return "K";
	case 76:
		return "L";
	case 77:
		return "M";
	case 78:
		return "N";
	case 79:
		return "O";
	case 80:
		return "P";
	case 81:
		return "Q";
	case 82:
		return "R";
	case 83:
		return "S";
	case 84:
		return "T";
	case 85:
		return "U";
	case 86:
		return "V";
	case 87:
		return "W";
	case 88:
		return "X";
	case 89:
		return "Y";
	case 90:
		return "Z";
	case 91:
		return "[";
	case 92:
		return "\\";
	case 93:
		return "]";
	case 96:
		return "`";
	case 256:
		return "ESC";
	case 257:
		return "ENTER";
	case 258:
		return "TAB";
	case 259:
		return "BACKSPACE";
	case 260:
		return "INSERT";
	case 261:
		return "DEL";
	case 262:
		return "ARROW RIGHT";
	case 263:
		return "ARROW LEFT";
	case 264:
		return "ARROW DOWN";
	case 265:
		return "ARROW UP";
	case 266:
		return "PAGE UP";
	case 267:
		return "PAGE DOWN";
	case 268:
		return "HOME";
	case 269:
		return "END";
	case 280:
		return "CAPS LOCK";
	case 281:
		return "SCROLL LOCK";
	case 282:
		return "NUM LOCK";
	case 283:
		return "PRINT SCREEN";
	case 284:
		return "PAUSE";
	case 290:
		return "F1";
	case 291:
		return "F2";
	case 292:
		return "F3";
	case 293:
		return "F4";
	case 294:
		return "F5";
	case 295:
		return "F6";
	case 296:
		return "F7";
	case 297:
		return "F8";
	case 298:
		return "F9";
	case 299:
		return "F10";
	case 300:
		return "F11";
	case 301:
		return "F12";
	case 320:
		return "KEYPAD 0";	
	case 321:
		return "KEYPAD 1";	
	case 322:
		return "KEYPAD 2";	
	case 323:
		return "KEYPAD 3";	
	case 324:
		return "KEYPAD 4";	
	case 325:
		return "KEYPAD 5";	
	case 326:
		return "KEYPAD 6";	
	case 327:
		return "KEYPAD 7";	
	case 328:
		return "KEYPAD 8";
	case 329:
		return "KEYPAD 9";
	case 330:
		return "KEYPAD .";
	case 331:
		return "KEYPAD /";
	case 332:
		return "KEYPAD *";
	case 333:
		return "KEYPAD -";
	case 334:
		return "KEYPAD +";
	case 335:
		return "KEYPAD ENTER";	
	case 336:
		return "KEYPAD =";
	case 340:
		return "LEFT SHIFT";
	case 341:
		return "LEFT CONTROL";
	case 342:
		return "LEFT ALT";
	case 343:
		return "LEFT SUPER";
	case 344:
		return "RIGHT SHIFT";
	case 345:
		return "RIGHT CONTROL";
	case 346:
		return "RIGHT ALT";
	case 347:
		return "RIGHT SUPER";
	case 348:
		return "KB MENU";
	}
	return "INVALID KEY";
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
		((settings::minAudioAndGraphicsTextSize - settings::audioAndGraphicsTextSize) / 2) * -1 }, settings::audioAndGraphicsTextSize, RAYWHITE);
	raycpp::DrawText("CONTROLS", settings::controlsTextPos - Vec2<int>{ (int)((settings::minControlsTextSize - settings::maxControlsTextSize) * -2.5),
		((settings::minControlsTextSize - settings::maxControlsTextSize) / 2) * -1 }, settings::maxControlsTextSize, RAYWHITE);

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
		((settings::minAudioAndGraphicsTextSize - settings::maxAudioAndGraphicsTextSize) / 2) * -1 }, settings::maxAudioAndGraphicsTextSize, RAYWHITE);
	raycpp::DrawText("CONTROLS", settings::controlsTextPos - Vec2<int>{ (int)((settings::minControlsTextSize - settings::controlsTextSize) * -2.5),
		((settings::minControlsTextSize - settings::controlsTextSize) / 2) * -1 }, settings::controlsTextSize, RAYWHITE);

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
	SelectKey(SelectKeyBind());
	DrawControlsKeyBinds();
}
