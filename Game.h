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
	sf::Font font;
	sf::Vector2f position;

	UIPanel(sf::Font& font_, sf::Vector2f position_)
	{
		score = 0;
		font = font_;
		position = position_;
	}
	void increaseScore(int amount)
	{
		score += amount;
	}

	void render(sf::RenderWindow& window)
	{	
		scoreText.setFont(font);
		scoreText.setPosition(position);
		scoreText.setCharacterSize(20);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setString("Score: " + std::to_string(score));
		window.draw(scoreText);
	}

	sf::Font getFont() {
		return font;
	}

	int getScore() {
		return score;
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
