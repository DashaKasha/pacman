#pragma once
#include "Entity.h"
#include<iostream>

class Cell : public StaticEntity
{
public:

	Cell(int x, int y, int s) {
		xPos = x;
		yPos = y;
		size = s;
	}
	void render(sf::RenderWindow& window) {
		shape.setFillColor(sf::Color(52, 93, 199));
		shape.setSize(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(xPos*size, yPos*size));
		window.draw(shape);
	}
};
