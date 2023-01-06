#pragma once
#include <vector>
#include "Vec2.h"
#include "SoundManager.h"
#include "InputManager.h"

class ModeSelectMenu
{
public:
	ModeSelectMenu(SoundManager& sounds1, InputManager& manager1, std::string& boardName1);

	void LoadModeSelect();
	void Tick();
	void Draw();

	void SetLoaded(bool val);
	bool GetLoaded();
	bool GetGameStart();
	void SetGameStart(bool val);

private:
	void DrawModePreviews();
	void FindAllBoardFiles();
	void ReturnButton();

	void ModePreviews();

	std::vector<std::string> boards;
	SoundManager& sounds;
	InputManager manager;

	bool menuLoaded;
	bool mouseOverReturnButton;
	int returnButtonCounter;

	std::vector<bool> mouseOverAPreviewButton;

	std::vector<Board> boardsBoards;
	std::vector<int> measurements;

	std::string& playBoardName;
	bool startGame;
};