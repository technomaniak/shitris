#include "ModeSelectMenu.h"
#include "Settings.h"
#include "raylibCpp.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

ModeSelectMenu::ModeSelectMenu(SoundManager& sounds1, InputManager& manager1, std::string& boardName1, int& style1, Board& board1) :
	boards({}),
	sounds(sounds1),
	manager(manager1),
	playBoardName(boardName1),
	startGame(false),
	board(board1),
	PreviewMinoes(),
	style(style1),
	sideBarEnabled(false),
	whichSideBar(-1),
	playButtonCounter(0),
	mouseOverPlayButton(false)
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
	if (sideBarEnabled)
	{
		SideBarPlayButton();
	}
	ModePreviews();
}

void ModeSelectMenu::Draw()
{
	ClearBackground(BLACK);
	DrawModePreviews();
	DrawTetrominoes();
	raycpp::DrawText("RETURN", settings::returnButtonTextPos - Vec2<int>{ (settings::minReturnTextSize - settings::returnTextSize) * -2,
		((settings::minReturnTextSize - settings::returnTextSize) / 2) * -1}, settings::returnTextSize, RAYWHITE);
	if (sideBarEnabled)
	{
		DrawSideBar();
	}
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

void ModeSelectMenu::DrawTetrominoes()
{
	for (int i = 0; i < boards.size(); i++)
	{
		for (int z = 0; z < PreviewMinoes[i].size(); z++)
		{
			std::vector<bool> shape(PreviewMinoes[i][z].GetDimension() * PreviewMinoes[i][z].GetDimension());
			for (int y = 0; y < PreviewMinoes[i][z].GetDimension(); y++)
			{
				for (int x = 0; x < PreviewMinoes[i][z].GetDimension(); x++)
				{
					bool cell = false;

					shape = PreviewMinoes[i][z].GetShape();
					cell = shape[y * PreviewMinoes[i][z].GetDimension() + x];

					if (cell)
					{
						board.DrawPreviewCell({ 150 + (x * (settings::selectMenuCellSize + settings::selectMenuPadding) * 3) + (boardsBoards[i].GetWidth() * boardsBoards[i].GetCellSize()) + (z * manager.GetMaxDimension() * (settings::selectMenuCellSize + 2) * 3),
							measurements[i] + (int)MeasureTextEx(GetFontDefault(), "I|", settings::nameTextSize, 1).y + (y * (settings::selectMenuCellSize + settings::selectMenuPadding) * 3)},
							PreviewMinoes[i][z].GetColor(),
							PreviewMinoes[i][z].GetAlternateColor(),
							PreviewMinoes[i][z].GetAlternateColor2(), style);
						
					}
				}
			}
		}
	}
	
}

void ModeSelectMenu::DrawSideBar()
{
	raycpp::DrawLineEx({ settings::screenWidth / 2, 100 }, { settings::screenWidth / 2, settings::screenHeight }, 3, RAYWHITE);
	DrawSideBarPlayButton();
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
		maxDimensions.push_back(manager.GetMaxDimension());
		PreviewMinoes.push_back({});
		manager.SetTetrominoList(PreviewMinoes[i]);
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
			sideBarEnabled = false;
			sideBarEnabled = false;
			whichSideBar = -1;
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
				sideBarEnabled = true;
				whichSideBar = i;
			}
		}
	}
}

void ModeSelectMenu::SideBar()
{
	SideBarPlayButton();
}

void ModeSelectMenu::SideBarPlayButton()
{
	if (raycpp::GetMousePos() > Vec2<int>{ settings::screenWidth / 4 * 3 - 250, settings::screenHeight / 6 * 5 - 25 } - Vec2<int>{ 0, 25 }
		&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth / 4 * 3 + 250, settings::screenHeight / 6 * 5 + 25 } + Vec2<int>{ 0, 75 })
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
			sounds.PlaySoundFromName("menuSound");
			SetLoaded(false);
			SetGameStart(true);
			sideBarEnabled = false;
			whichSideBar = -1;
		}
	}
}

void ModeSelectMenu::DrawSideBarPlayButton()
{
	raycpp::DrawRectangleLinesEx({ settings::screenWidth / 4 * 3 - 250, settings::screenHeight / 6 * 5 - 25 }, settings::playButtonSize, 3, RAYWHITE);
	raycpp::DrawText("PLAY", { (settings::screenWidth / 4 * 3 - 250) - (settings::playButtonSize.GetX() / 2) + (settings::playButtonSize.GetX() - MeasureText("PLAY", settings::playButtonTextSize) / 2),
		(settings::screenHeight / 6 * 5 - 25) - (settings::playButtonSize.GetY() / 2) + (int)(settings::playButtonSize.GetY() - MeasureTextEx(GetFontDefault(), "PLAY", (float)(settings::playButtonTextSize / 2), 20).y) },
		settings::playButtonTextSize, RAYWHITE);
}