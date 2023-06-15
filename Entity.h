#pragma once
#include <SFML/Graphics.hpp>

enum struct Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class Entity
{
protected:
	int xPos;
	int yPos;
	int size;


public:
	virtual sf::FloatRect getBounds() = 0;
	//virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};

class StaticEntity : public Entity {
protected:
	sf::FloatRect bounds;
	sf::RectangleShape shape;
public:
	sf::FloatRect getBounds() override {
		return shape.getGlobalBounds();
	}
};

class PacGum : public StaticEntity
{

public:
	PacGum(int x, int y, int s) {
		xPos = x;
		yPos = y;
		size = s;

	}
	void render(sf::RenderWindow& window) {
		shape.setFillColor(sf::Color(sf::Color::White));
		shape.setSize(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(xPos, yPos));
		window.draw(shape);
	}

};




class SuperPacGum : public StaticEntity
{
public:

	SuperPacGum(int x, int y, int s) {
		xPos = x;
		yPos = y;
		size = s;
	}
	void render(sf::RenderWindow& window) {
		shape.setFillColor(sf::Color(sf::Color::White));
		shape.setSize(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(xPos, yPos));
		window.draw(shape);
	}
};


class MovingEntity : public Entity {
protected:
	int speed;
	sf::Vector2i speedVec;
	Direction direction;
	sf::CircleShape shape;

	//etc.

public:
	void unpdatePosition() {

	}
	void render(sf::RenderWindow& window) {
		window.draw(shape);
	}
	sf::FloatRect getBounds() {
		return shape.getGlobalBounds();
	}
	//setters, getters, etc. 
};