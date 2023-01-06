#include "ModeSelectMenu.h"
#include "Settings.h"
#include "raylibCpp.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

ModeSelectMenu::ModeSelectMenu(SoundManager& sounds1, InputManager& manager1, std::string& boardName1) :
	boards({}),
	sounds(sounds1),
	manager(manager1),
	playBoardName(boardName1),
	startGame(false)
{
	FindAllBoardFiles();
	measurements.clear();
	measurements.push_back(settings::positionOfElement1.GetY() - 25);
}

void ModeSelectMenu::LoadModeSelect()
{
	menuLoaded = true;
}

void ModeSelectMenu::Tick()
{
	Draw();
	ReturnButton();
	ModePreviews();
}

void ModeSelectMenu::Draw()
{
	ClearBackground(BLACK);
	DrawModePreviews();
	raycpp::DrawText("RETURN", settings::returnButtonTextPos - Vec2<int>{ (settings::minReturnTextSize - settings::returnTextSize) * -2,
		((settings::minReturnTextSize - settings::returnTextSize) / 2) * -1}, settings::returnTextSize, RAYWHITE);
}

void ModeSelectMenu::SetLoaded(bool val)
{
	menuLoaded = val;
}

bool ModeSelectMenu::GetLoaded()
{
	return menuLoaded;
}

bool ModeSelectMenu::GetGameStart()
{
	return startGame;
}

void ModeSelectMenu::SetGameStart(bool val)
{
	startGame = val;
}

void ModeSelectMenu::DrawModePreviews()
{
	int measurement = (int)MeasureTextEx(GetFontDefault(), "I|", settings::nameTextSize, 1).y + settings::positionOfElement1.GetX();
	int toDraw = 0;
	int currentAdd;

	currentAdd = ((boardsBoards[0].GetHeight() * (boardsBoards[0].GetCellSize() + 1)) + 25);
	measurement += currentAdd;
	while (measurement < 1820)
	{
		measurements.push_back(measurement);
		raycpp::DrawText(boards[toDraw].c_str(), Vec2<int>{ 100, measurements[toDraw] }, settings::nameTextSize, RAYWHITE);
		boardsBoards[toDraw].Draw(2, false);
		toDraw++;
		if (toDraw >= boards.size())
		{
			break;
		}
		else
		{
			boardsBoards[toDraw].SetPos(Vec2<int>{ 100, measurement + (int)MeasureTextEx(GetFontDefault(), "I|", settings::nameTextSize, 1).y });
		}
		currentAdd = ((boardsBoards[toDraw].GetHeight() * (boardsBoards[toDraw].GetCellSize() + 1)) + 25);
		measurement += currentAdd;
	}
}

void ModeSelectMenu::FindAllBoardFiles()
{
	std::string path("./");
	std::string extension(".board");
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == extension)
		{
			boards.push_back(p.path().stem().string());
		}
	}
	for (int i = 0; i < boards.size(); i++)
	{
		boardsBoards.push_back(Board(settings::positionOfElement1, settings::selectMenuCellSize, settings::selectMenuPadding));
		manager.LoadBoard(boards[i], boardsBoards[i]);
	}
	mouseOverAPreviewButton.resize(boards.size());
}

void ModeSelectMenu::ReturnButton()
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
			SetLoaded(false);
		}
	}
}

void ModeSelectMenu::ModePreviews()
{
	for (int i = 0; i < boards.size(); i++)
	{
		if (raycpp::GetMousePos() > Vec2<int>{ 100, measurements[i] } - Vec2<int>{ 0, 25 }
		&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth / 2, measurements[i+1] } - Vec2<int>{ 0, 25 })
		{
			if (mouseOverAPreviewButton[i] != true)
			{
				sounds.PlaySoundFromName("menuSound");
				mouseOverAPreviewButton[i] = true;
			}
		}
		else
		{
			mouseOverAPreviewButton[i] = false;
		}
		if (mouseOverAPreviewButton[i])
		{
			raycpp::DrawRectangle({ 1, measurements[i] }, { 7, measurements[i + 1] - measurements[i] }, Color{255, 255, 255, 69});
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				sounds.PlaySoundFromName("menuSound");
				playBoardName = boards[i];
				SetLoaded(false);
				SetGameStart(true);
			}
		}
	}
}
