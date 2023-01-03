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
	moveRightCounter(0),
	mouseOverMoveRight(false),
	alternateMoveRightCounter(0),
	alternateMouseOverMoveRight(false),
	waitingForInput(KeyBinds::NONE),
	keyPressed(0)
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
	return false;
}

bool OptionsMenu::RotateRightKeyBind()
{
	return false;
}

bool OptionsMenu::RotateLeftKeyBind()
{
	return false;
}

bool OptionsMenu::ResetKeyBind()
{
	return false;
}

bool OptionsMenu::MenuKeyBind()
{
	return false;
}

bool OptionsMenu::HardDropKeyBind()
{
	return false;
}

bool OptionsMenu::SoftDropKeyBind()
{
	return false;
}

bool OptionsMenu::SwapKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateMoveRightKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateMoveLeftKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateRotateRightKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateRotateLeftKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateResetKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateMenuKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateHardDropKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateSoftDropKeyBind()
{
	return false;
}

bool OptionsMenu::AlternateSwapKeyBind()
{
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
			SaveKeysInSettings();
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
	raycpp::DrawText("MOVE RIGHT", settings::moveRightKeyTextPos, settings::minMoveRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][0]).c_str(), 
			settings::moveRightKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[0][0]).c_str(), settings::minMoveRightKeyTextSize) 
			- MeasureText(KeyBindName(keyBindsList[0][0]).c_str(), settings::moveRightKeyTextSize))) / 2, 
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][0]).c_str(), (int)settings::minMoveRightKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[0][0]).c_str(), (float)settings::moveRightKeyTextSize, 20).y)) / 2) },
			settings::moveRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][0]).c_str(),
		settings::alternateMoveRightKeyButtonTextPos - Vec2<int>{ (int)(-1 * (MeasureText(KeyBindName(keyBindsList[01][0]).c_str(), settings::minMoveRightKeyTextSize)
			- MeasureText(KeyBindName(keyBindsList[1][0]).c_str(), settings::alternateMoveRightKeyTextSize))) / 2,
		(int)((-1 * (MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][0]).c_str(), (int)settings::minMoveRightKeyTextSize, 20).y - MeasureTextEx(GetFontDefault(), KeyBindName(keyBindsList[1][0]).c_str(), (float)settings::alternateMoveRightKeyTextSize, 20).y)) / 2) },
		settings::alternateMoveRightKeyTextSize, RAYWHITE);

	raycpp::DrawText("MOVE LEFT", settings::moveLeftKeyTextPos, settings::minMoveLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][1]).c_str(), settings::moveLeftKeyButtonTextPos, settings::moveLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][1]).c_str(), settings::alternateMoveLeftKeyButtonTextPos, settings::alternateMoveLeftKeyTextSize, RAYWHITE);

	raycpp::DrawText("ROTATE RIGHT", settings::rotateRightKeyTextPos, settings::minRotateRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][2]).c_str(), settings::rotateRightKeyButtonTextPos, settings::rotateRightKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][2]).c_str(), settings::alternateRotateRightKeyButtonTextPos, settings::alternateRotateRightKeyTextSize, RAYWHITE);

	raycpp::DrawText("ROTATE LEFT", settings::rotateLeftKeyTextPos, settings::minRotateLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][3]).c_str(), settings::rotateLeftKeyButtonTextPos, settings::rotateLeftKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][3]).c_str(), settings::alternateRotateLeftKeyButtonTextPos, settings::alternateRotateLeftKeyTextSize, RAYWHITE);

	raycpp::DrawText("RESET", settings::resetKeyTextPos, settings::minResetKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][4]).c_str(), settings::resetKeyButtonTextPos, settings::resetKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][4]).c_str(), settings::alternateResetKeyButtonTextPos, settings::alternateResetKeyTextSize, RAYWHITE);

	raycpp::DrawText("OPEN MENU", settings::menuKeyTextPos, settings::minMenuKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][5]).c_str(), settings::menuKeyButtonTextPos, settings::menuKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][5]).c_str(), settings::alternateMenuKeyButtonTextPos, settings::alternateMenuKeyTextSize, RAYWHITE);

	raycpp::DrawText("HARD DROP", settings::hardDropKeyTextPos, settings::minHardDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][6]).c_str(), settings::hardDropKeyButtonTextPos, settings::hardDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][6]).c_str(), settings::alternateHardDropKeyButtonTextPos, settings::alternateHardDropKeyTextSize, RAYWHITE);

	raycpp::DrawText("SOFT DROP", settings::softDropKeyTextPos, settings::minSoftDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][7]).c_str(), settings::softDropKeyButtonTextPos, settings::softDropKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][7]).c_str(), settings::alternateSoftDropKeyButtonTextPos, settings::alternateSoftDropKeyTextSize, RAYWHITE);

	raycpp::DrawText("HOLD PIECE", settings::swapKeyTextPos, settings::minSwapKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[0][8]).c_str(), settings::swapKeyButtonTextPos, settings::swapKeyTextSize, RAYWHITE);
	raycpp::DrawText(KeyBindName(keyBindsList[1][8]).c_str(), settings::alternateSwapKeyButtonTextPos, settings::alternateSwapKeyTextSize, RAYWHITE);
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
		//if (AlternateMoveRightKeyBind)
		//{
		//	return KeyBinds::ALTERNATEMOVERIGHT;
		//}
		//if (MoveLeftKeyBind)
		//{
		//	return KeyBinds::MOVELEFT;
		//}
		//if (AlternateMoveLeftKeyBind)
		//{
		//	return KeyBinds::ALTERNATEMOVELEFT;
		//}
		//if (RotateRightKeyBind)
		//{
		//	return KeyBinds::ROTATERIGHT;
		//}
		//if (AlternateRotateRightKeyBind)
		//{
		//	return KeyBinds::ALTERNATEROTATERIGHT;
		//}
		//if (RotateLeftKeyBind)
		//{
		//	return KeyBinds::ROTATELEFT;
		//}
		//if (AlternateRotateLeftKeyBind)
		//{
		//	return KeyBinds::ALTERNATEROTATELEFT;
		//}
	}
	return waitingForInput;
}

void OptionsMenu::SelectKey(KeyBinds selection)
{
	switch (selection)
	{
	case OptionsMenu::KeyBinds::ROTATELEFT:
		break;
	case OptionsMenu::KeyBinds::ROTATERIGHT:
		break;
	case OptionsMenu::KeyBinds::RESET:
		break;
	case OptionsMenu::KeyBinds::SWAPPIECE:
		break;
	case OptionsMenu::KeyBinds::MENU:
		break;
	case OptionsMenu::KeyBinds::MOVERIGHT:
		keyPressed = GetKeyPressed();
		if (keyPressed != KEY_NULL)
		{
			keyBindsList[0][0] = keyPressed;
			waitingForInput = KeyBinds::NONE;
		}
		break;
	case OptionsMenu::KeyBinds::MOVELEFT:
		break;
	case OptionsMenu::KeyBinds::HARDDROP:
		break;
	case OptionsMenu::KeyBinds::SOFTDROP:
		break;
	case OptionsMenu::KeyBinds::ALTERNATEROTATELEFT:
		break;
	case OptionsMenu::KeyBinds::ALTERNATEROTATERIGHT:
		break;
	case OptionsMenu::KeyBinds::ALTERNATERESET:
		break;
	case OptionsMenu::KeyBinds::ALTERNATESWAPPIECE:
		break;
	case OptionsMenu::KeyBinds::ALTERNATEMENU:
		break;
	case OptionsMenu::KeyBinds::ALTERNATEMOVERIGHT:
		break;
	case OptionsMenu::KeyBinds::ALTERNATEMOVELEFT:
		break;
	case OptionsMenu::KeyBinds::ALTERNATEHARDDROP:
		break;
	case OptionsMenu::KeyBinds::ALTERNATESOFTDROP:
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
