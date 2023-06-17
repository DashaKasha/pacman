#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include "Entity.h"
#include "Ghost.h"
#include "Cell.h"

enum class GameState
{
	Playing,
	PlayerLosed,
	PlayerWon,
};

class UIPanel {
public:
	int score;
	sf::Text scoreText;

	//void updateScoreText()
	//{
	//	scoreText.setString("Score: " + std::to_string(score));
	//}

	UIPanel(sf::Font& font, sf::Vector2f position)
	{
		score = 0;
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(position);
	}
	void increaseScore(int amount)
	{
		score += amount;
		//updateScoreText();
	}

	void render(sf::RenderWindow& window)
	{
		scoreText.setString("Score: " + std::to_string(score));
		window.draw(scoreText);
	}

};



class Game
{
	int width;
	int height;
	std::vector<PacGum*> pucgums;
	std::vector<SuperPacGum*> superPucGums;
	std::vector<Ghost*> ghosts;
	std::vector<Cell*> cells;
	std::vector<Swamp*> swamps;
	UIPanel* uiPanel;
	//int score = 0;
	Pacman *pacman;
	GameState gameState;


public:

	Game();
	std::vector<PacGum*> getPucGums() {
		return pucgums;
	};
	std::vector<SuperPacGum*> getSuperPucQums() {
		return superPucGums;
	};

	std::vector<Cell*> getCells() {
		return cells;

	};
	Pacman getPacman() {
		return *pacman;
	};
	void updateGame(float elapsedTime); // изменения координат объектов
	void render(sf::RenderWindow& window); // отрисовка
	~Game() = default;

};
