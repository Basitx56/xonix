#pragma once

#include <SFML/Graphics.hpp>


struct Enemy;


void updateScore(int capturedTiles);
void updateTop5Scores(int score, float totalGameTime);
void displayTopScores(RenderWindow* window, Font& font) ;

void drop(int y, int x);
void moveZigZag(Enemy& enemy, float deltaTime);
void moveDriftingSpiral(Enemy& enemy, float deltaTime);



void SingleGame(sf::RenderWindow* window, int difficulty);
void MultiGame(sf::RenderWindow* window, int difficulty);
