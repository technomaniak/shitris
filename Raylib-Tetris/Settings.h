#pragma once
#include "Vec2.h"
#include <vector>

namespace settings
{
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Window settings
        inline constexpr int screenWidth = 1920;
        inline constexpr int screenHeight = 1080;
        inline constexpr int fps = 60;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Board settings
        inline constexpr int cellSize = 45;
        inline constexpr int padding = 5;
        inline constexpr Vec2<int> boardPosition { 300, 100 };  // 250 70
        inline Vec2<int> boardWidthHeight { 10, 20 };

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Score/Level settings
        inline constexpr Vec2<int> scoreCounterPosition{ 1220, 100 };
        inline constexpr int scoreCounterSize = 92;
        inline constexpr Vec2<int> levelCounterPosition{ 1220, 375 };
        inline constexpr int levelCounterSize = 80;
        inline constexpr Vec2<int> linesCounterPosition{ 1220, 625 };
        inline constexpr int linesCounterSize = 80;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Main Menu 

        // Play Button
            inline constexpr Vec2<int> playButtonSize{ 500, 150 };
            inline constexpr int minPlayButtonTextSize = 80;
            inline constexpr int maxPlayButtonTextSize = 100;
            inline int playButtonTextSize = 100;
            inline constexpr Vec2<int> playButtonPos{ (screenWidth / 2) - (playButtonSize.GetX() / 2), ((screenHeight / 5) * 3) };
            inline Vec2<int> playButtonTextPos{ playButtonPos.GetX(), playButtonPos.GetY() };

        // Volume Slider
            inline constexpr Vec2<int> volumeSliderBorderSize{ 25, 306 };
            inline constexpr Vec2<int> volumeSliderBorderPos{ screenWidth - volumeSliderBorderSize.GetX() * 5, screenHeight - (int)(volumeSliderBorderSize.GetY() * 1.3) };
            inline Vec2<int> volumeSliderSize = volumeSliderBorderSize - 6;
            inline constexpr Vec2<int> volumeSliderPos = volumeSliderBorderPos + 3;

        // Main Text
            inline int mainTextSize = 300;

        // Settings Button
            inline constexpr Vec2<int> settingsButtonSize{ 110, 110 };
            inline constexpr float maxSettingsButtonTextureSize = 0.1853125f;
            inline constexpr float minSettingsButtonTextureSize = 0.1353125f;
            inline float settingsButtonTextureSize = 0.1853125f;
            inline constexpr Vec2<int> settingsButtonPos{ 75, 75 };
            inline Vec2<int> settingsButtonTexturePos = settingsButtonPos + Vec2<int>{ 6, 6 };

        // Quit Game Button
            inline constexpr Vec2<int> quitGameButtonSize{ 500, 150 };
            inline constexpr int minQuitGameButtonTextSize = 80;
            inline constexpr int maxQuitGameButtonTextSize = 100;
            inline int quitGameButtonTextSize = 100;
            inline constexpr Vec2<int> quitGameButtonPos = playButtonPos + Vec2<int>{ 0, 200 };
            inline Vec2<int> quitGameButtonTextPos{ quitGameButtonPos.GetX(), quitGameButtonPos.GetY() };

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Setting Menu

            // Return Button
                inline constexpr Vec2<int> returnButtonSize{ 250, 75 };
                inline constexpr int minReturnButtonTextSize = 40;
                inline constexpr int maxReturnButtonTextSize = 50;
                inline int returnButtonTextSize = 50;
                inline constexpr Vec2<int> returnButtonPos{ screenWidth - 350, 75 };
                inline Vec2<int> returnButtonTextPos{ returnButtonPos.GetX(), returnButtonPos.GetY() };

        // Options Selection
    
            // Dividers

            // Vertical
                inline constexpr Vec2<int> verticalDividerPos{ 450, 0 };
                inline constexpr int verticalDividerLength = 75;
    
            // Horizontal
                inline constexpr Vec2<int> horizontalDividerPos{ 0, 90 };
                inline constexpr int horizontalDividerLength = screenWidth;

        // Controls
            inline constexpr Vec2<int> controlsTextPos{ 250, 75 };
            inline constexpr int controlsTextSize = 60;

        // Audio And Graphic
            inline constexpr Vec2<int> audioAndGraphicsTextPos{ 750, 75 };
            inline constexpr int audioAndGraphicsTextSize = 60;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Game Over Screen
    
        // Text
            inline constexpr Vec2<int> gameOverTextPosition{ levelCounterPosition.GetX() - 400, 300 };
            inline constexpr Vec2<int> newBestTextPosition = gameOverTextPosition - Vec2<int>{ 0, -300 };
            inline constexpr int gameOverAllRegularTextsSize = 92;
    
        // Restart Button
            inline constexpr Vec2<int> restartButtonPos = gameOverTextPosition + Vec2<int>{ 0, 250 };
            inline constexpr Vec2<int> restartButtonSize{ 257, 75 };
            inline constexpr int minRestartButtonTextSize = 30;
            inline constexpr int maxRestartButtonTextSize = 35;
            inline int restartButtonTextSize = 35;

        // Main Menu Button
            inline constexpr Vec2<int> mainMenuButtonPos = restartButtonPos + Vec2<int>{ 0, 100 };
            inline constexpr Vec2<int> mainMenuButtonSize{ 257, 75 };
            inline constexpr int minMainMenuButtonTextSize = 30;
            inline constexpr int maxMainMenuButtonTextSize = 35;
            inline int mainMenuButtonTextSize = 35;

        // Reuses Options Button From Below

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // In Game Pause Menu

        // Reuses Restart Button and Main Menu Button

        // Options Button Pos
            inline constexpr Vec2<int> optionsButtonPos = mainMenuButtonPos + Vec2<int>{ 0, 100 };
            inline constexpr Vec2<int> optionsButtonSize{ 257, 75 };
            inline constexpr int minOptionsButtonTextSize = 30;
            inline constexpr int maxOptionsButtonTextSize = 35;
            inline int optionsButtonTextSize = 35;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
}