#pragma once
#include "Vec2.h"
#include <vector>

namespace settings
{
    // Window settings
    inline constexpr int screenWidth = 1920;
    inline constexpr int screenHeight = 1080;
    inline constexpr int fps = 60;

    // Board settings
    inline constexpr int cellSize = 45;
    inline constexpr int padding = 5;
    inline constexpr Vec2<int> boardPosition { 300, 100 };  // 250 70
    inline Vec2<int> boardWidthHeight { 10, 20 };

    // Score/Level settings
    inline constexpr Vec2<int> scoreCounterPosition{ 1220, 100 };
    inline constexpr int scoreCounterSize = 92;
    inline constexpr Vec2<int> levelCounterPosition{ 1220, 375 };
    inline constexpr int levelCounterSize = 80;
    inline constexpr Vec2<int> linesCounterPosition{ 1220, 625 };
    inline constexpr int linesCounterSize = 80;

    // Main Menu 

    // Play Button
    inline constexpr Vec2<int> playButtonSize{ 500, 150 };
    inline constexpr int minPlayButtonTextSize = 80;
    inline constexpr int maxPlayButtonTextSize = 100;
    inline int playButtonTextSize = 100;
    inline constexpr Vec2<int> playButtonPos{ (screenWidth / 2) - (playButtonSize.GetX() / 2), ((screenHeight / 3) * 2) };
    inline Vec2<int> playButtonTextPos{ playButtonPos.GetX(), playButtonPos.GetY() };

    // Volume Slider
    inline constexpr Vec2<int> volumeSliderBorderSize{ 25, 250 };
    inline constexpr Vec2<int> volumeSliderBorderPos{ screenWidth - volumeSliderBorderSize.GetX() * 5, screenHeight - (int)(volumeSliderBorderSize.GetY() * 1.3) };
    inline Vec2<int> volumeSliderSize = volumeSliderBorderSize - 6;
    inline constexpr Vec2<int> volumeSliderPos = volumeSliderBorderPos + 3;

    // Main Text
    inline int mainTextSize = 300;
}