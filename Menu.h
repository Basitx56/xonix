#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


const int Max_menu = 4;
const int pauseMenu = 4;

// Function declarations for the main menu and other related features
void showMenu(RenderWindow* window); 
void showOptions(RenderWindow* window);  // Function to display options
void showEndMenu(RenderWindow* window, int score);
void showMEndMenu(RenderWindow* window, int score, string string);
void showPauseMenu(RenderWindow* window) ;
void showGameMode(RenderWindow* window); // Function to display game mode options
void showDifficulty(RenderWindow* window); // Function to display difficulty options
void showSound(RenderWindow* window); // Function to display sound options
void showResetSettings(RenderWindow* window); // Function to reset settings
void showScoreBoard(RenderWindow* window); 


//helper function 

void drawMenu(RenderWindow& window, Font& font, Text menu[Max_menu]);
void moveUp(int& menuSelected, int Max_menu);
void moveDown(int& menuSelected, int Max_menu);
void drawCommonUI(RenderWindow* window, Sprite& background, Sprite& logo);

