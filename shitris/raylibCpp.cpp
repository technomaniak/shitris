#include "raylibCpp.h"
#include <assert.h>

void raycpp::DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color)
{
	//assert(pos.GetX() >= 0 && pos.GetY() >= 0 && pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight()); // checks if we are drawing in a possible spot
	DrawRectangle(pos.GetX(), pos.GetY(), widthHeight.GetX(), widthHeight.GetY(), color);
}

void raycpp::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThick, Color color)
{
	//assert(pos.GetX() >= 0 && pos.GetY() >= 0 && pos.GetX() < GetScreenWidth() && pos.GetY() < GetScreenHeight()); // checks if we are drawing in a possible spot
	assert(lineThick > 0); // checks if border is valid

	DrawRectangleLinesEx({ (float)pos.GetX(), (float)pos.GetY(), (float)widthHeight.GetX(), (float)widthHeight.GetY() }, (float)lineThick, color);
}

void raycpp::DrawText(const char* text, Vec2<int> pos, int fontSize, Color color)
{
	DrawText(text, pos.GetX(), pos.GetY(), fontSize, color);
}

void raycpp::DrawTextureEx(Texture2D texture, Vec2<int> pos, float rotation, float scale, Color color)
{
	DrawTextureEx(texture, Vector2{ (float)pos.GetX(), (float)pos.GetY() }, rotation, scale, color);
}

void raycpp::DrawLineEx(Vec2<int> startPos, Vec2<int> endPos, float thick, Color color)
{
	DrawLineEx(Vector2{ (float)startPos.GetX(), (float)startPos.GetY() }, Vector2{ (float)endPos.GetX(), (float)endPos.GetY() }, thick, color);
}

Vec2<int> raycpp::GetMousePos()
{
	return { GetMouseX(), GetMouseY() };
}
