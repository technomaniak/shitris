#pragma once
#include <vector>
#include "Vec2.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "Tetrominoes.h"

class ModeSelectMenu
{
public:
	ModeSelectMenu(SoundManager& sounds1, InputManager& manager1, std::string& boardName1, int &style1, Board &board1);

	void LoadModeSelect();
	void Tick();
	void Draw();

	void SetLoaded(bool val);
	bool GetLoaded();
	bool GetGameStart();
	void SetGameStart(bool val);

private:
	void DrawModePreviews();
	void DrawTetrominoes();
	void DrawSideBar();
	void FindAllBoardFiles();
	void ReturnButton();

	void ModePreviews();
	void SideBar();
	void SideBarPlayButton();
	void DrawSideBarPlayButton();

	std::vector<std::string> boards;
	SoundManager& sounds;
	InputManager manager;

	bool menuLoaded;
	bool mouseOverReturnButton;
	bool mouseOverPlayButton;
	int playButtonCounter;
	int returnButtonCounter;
	int& style;
	bool sideBarEnabled;
	int whichSideBar;

	std::vector<bool> mouseOverAPreviewButton;

	std::vector<Board> boardsBoards;
	std::vector<int> measurements;
	std::vector<int> maxDimensions;

	std::string& playBoardName;
	bool startGame;
	Board& board;
	std::vector<std::vector<Tetromino>> PreviewMinoes;
};