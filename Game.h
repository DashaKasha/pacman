#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include "Entity.h"
#include "Ghost.h"
#include "Cell.h"

class Game
{
	int width;
	int height;
	std::vector<PacGum*> pucgums;
	std::vector<SuperPacGum*> superPucGums;
	std::vector<Ghost*> ghosts;
	std::vector<Cell*> cells;
	int score = 0;
	Pacman *pacman;

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

