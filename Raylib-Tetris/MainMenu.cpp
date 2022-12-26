#include "MainMenu.h"
#include "Settings.h"

MainMenu::MainMenu():
	GameRunning(false),
	menuLoaded(false)
{
}

void MainMenu::LoadMenu()
{
	Texture2D texture = LoadTextureFromImage(GenImageColor(settings::screenWidth, settings::screenHeight, Color{ 0, 0, 0, 255 }));
	DrawTexture(texture, 0, 0, WHITE);
	raycpp::DrawRectangle({ 0, 0 }, { settings::screenWidth, settings::screenHeight }, Color{ 0, 0, 0, 255 });
	menuLoaded = true;
}

void MainMenu::Tick()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		StartGame();
	}
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
	GameRunning = true;
}
