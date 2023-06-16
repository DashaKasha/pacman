#pragma once
#include "Entity.h"
#include "Cell.h"

static const float GHOST_SPEED = 120.f; // pixels per second.
static const float GHOST_RADIUS = 16.f; // pixels

class Ghost:public MovingEntity
{
public:
    //int xPos;
    //int yPos;
    //int size = GHOST_RADIUS;

    virtual void update(float elapsedTime, std::vector<Cell*> cells) = 0;
    // Other member functions and variables common to all ghosts
};

class Pinky : public Ghost
{
public:

    Pinky(int xPos, int yPos, float size) {

        direction = Direction::NONE;
        shape.setRadius(GHOST_RADIUS);
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(sf::Vector2f(xPos * 32.f, yPos * 32.f));
    
    }

    void update(float elapsedTime, std::vector<Cell*> cells) override
    {
        // Pinky's update logic
    }
    // Pinky-specific member functions and variables
};

class Inky : public Ghost
{
public:

    Inky(int xPos, int yPos, float size) {

        direction = Direction::NONE;
        shape.setRadius(GHOST_RADIUS);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(sf::Vector2f(xPos * 32.f, yPos * 32.f));

    }



    void update(float elapsedTime, std::vector<Cell*> cells) override
    {
        // Inky's update logic
    }
    // Inky-specific member functions and variables
};

class Clyde : public Ghost
{
public:

    Clyde(int xPos, int yPos, float size) {

        direction = Direction::NONE;
        shape.setRadius(GHOST_RADIUS);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(sf::Vector2f(xPos * 32.f, yPos * 32.f));

    }


    void update(float elapsedTime, std::vector<Cell*> cells) override
    {
        // Clyde's update logic
    }
    // Clyde-specific member functions and variables
};

class Blinky : public Ghost
{
public:

    Blinky(int xPos, int yPos, float size) {

        direction = Direction::NONE;
        shape.setRadius(GHOST_RADIUS);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(sf::Vector2f(xPos * 32.f, yPos * 32.f));

    }


    void update(float elapsedTime, std::vector<Cell*> cells) override
    {
        // Blinky's update logic
    }
    // Blinky-specific member functions and variables
};








class AbstractGhostFactory
{
public:
    virtual Ghost* createGhost(int xPos, int yPos, int size=GHOST_RADIUS) = 0;
};

class PinkyFactory : public AbstractGhostFactory
{
public:
    Ghost* createGhost(int xPos, int yPos, int size= GHOST_RADIUS) override
    {
        return new Pinky(xPos, yPos, size);
    }
};

class InkyFactory : public AbstractGhostFactory
{
public:
    Ghost* createGhost(int xPos, int yPos, int size=GHOST_RADIUS) override
    {
        return new Inky(xPos, yPos, size);
    }
};

class ClydeFactory : public AbstractGhostFactory
{
public:
    Ghost* createGhost(int xPos, int yPos, int size= GHOST_RADIUS) override
    {
        return new Clyde(xPos, yPos, size);
    }
};

class BlinkyFactory : public AbstractGhostFactory
{
public:
    Ghost* createGhost(int xPos, int yPos, int size= GHOST_RADIUS) override
    {
        return new Blinky(xPos, yPos, size);
    }
};
