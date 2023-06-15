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
	std::vector<Entity*> objects;
	std::vector<Ghost*> ghosts;
	std::vector<Cell*> cells;
	Pacman *pacman;

public:

	Game();
	std::vector<Entity*> getEntities() {
		return objects;
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

