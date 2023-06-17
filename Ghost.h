#pragma once
#include "Entity.h"
#include "Cell.h"

static const float GHOST_SPEED = 120.f; // pixels per second.
static const float GHOST_RADIUS = 14.f; // pixels


class Ghost:public MovingEntity
{
public:
    //GhostState* currentState;
    virtual void update(float elapsedTime, std::vector<Cell*> cells) = 0;

    void changeGhostDirection() {
        //const float step = GHOST_SPEED * elapsedTime;
        switch (direction)
        {
        case Direction::UP:
            direction = Direction::DOWN;
            break;
        case Direction::DOWN:
            direction = Direction::UP;
            break;
        case Direction::LEFT:
            direction = Direction::RIGHT;
            break;
        case Direction::RIGHT:
            direction = Direction::LEFT;
            break;
        case Direction::NONE:
            break;
        }

    }
    
    ~Ghost() {
        //delete currentState;
    }
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

        const float step = GHOST_SPEED * elapsedTime;
        sf::Vector2f movement(0.f, 0.f);
        //movement.y -= step;
        int d = 3;//std::rand() % 4;
        switch (d)
        {
        case 0:
            direction = Direction::UP;
            movement.y -= step;
            break;
        case 1:
            direction = Direction::DOWN;
            movement.y += step;
            break;
        case 2:
            direction = Direction::RIGHT;
            movement.x -= step;
            break;
        case 3:
            direction = Direction::LEFT;
            movement.x += step;
            break;
        case 4:
            changeGhostDirection();
            break;
        }



        for (Cell* cell : cells) {
            sf::FloatRect nextBounds = shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->getBounds();
            nextBounds.left += movement.x;
            nextBounds.top += movement.y;

            // Проверяем условие столкновения призрака и стенки
            if (nextBounds.intersects(cellBounds)) {
                    // Изменяем направление по горизонтальной оси на противоположное
                    //direction = -direction;
                changeGhostDirection();
            }
        }

        shape.move(movement);
    }
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
        const float step = GHOST_SPEED * elapsedTime;
        sf::Vector2f movement(0.f, 0.f);
        movement.y += step;

        for (Cell* cell : cells) {
            sf::FloatRect nextBounds = shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->getBounds();
            nextBounds.left += movement.x;
            nextBounds.top += movement.y;

            // Проверяем условие столкновения призрака и стенки
            if (nextBounds.intersects(cellBounds)) {
                movement = sf::Vector2f(-movement.x, -movement.y);
                this->changeGhostDirection();
                break;
            }
        }

        shape.move(movement);
    }
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
        const float step = GHOST_SPEED * elapsedTime;
        sf::Vector2f movement(0.f, 0.f);
        movement.x += step;

        for (Cell* cell : cells) {
            sf::FloatRect nextBounds = shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->getBounds();
            nextBounds.left += movement.x;
            nextBounds.top += movement.y;

            // Проверяем условие столкновения призрака и стенки
            if (nextBounds.intersects(cellBounds)) {
                movement = sf::Vector2f(-movement.x, -movement.y);
                this->changeGhostDirection();
                break;
            }
        }

        shape.move(movement);
    }
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
        const float step = GHOST_SPEED * elapsedTime;
        sf::Vector2f movement(0.f, 0.f);
        movement.x -= step;

        for (Cell* cell : cells) {
            sf::FloatRect nextBounds = shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->getBounds();
            nextBounds.left += movement.x;
            nextBounds.top += movement.y;

            // Проверяем условие столкновения призрака и стенки
            if (nextBounds.intersects(cellBounds)) {
                movement = sf::Vector2f(-movement.x, -movement.y);
                this->changeGhostDirection();
                break;
            }
        }

        shape.move(movement);
    }
};




//--------------------AbstractGhostFactory start----------------------------



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


//--------------------AbstractGhostFactory end----------------------------



//--------------------------State start---------------------------

/*
// Abstract base class for Ghost states
class GhostState
{
public:
    virtual ~GhostState() {}

    virtual void superPacGumEaten(Ghost& ghost) = 0;
    virtual void timeModeOver(Ghost& ghost) = 0;
    virtual void timeFrightenedMode(Ghost& ghost) = 0;
    virtual void eaten(Ghost& ghost) = 0;
    virtual void outsideHouse(Ghost& ghost) = 0;
    virtual void insideHouse(Ghost& ghost) = 0;
    virtual void computeNextDir(Ghost& ghost) = 0;
    virtual sf::Vector2f getTargetPosition(Ghost& ghost) = 0;
};

// HouseMode state
class HouseModeState : public GhostState
{
public:
    void superPacGumEaten(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

    void timeModeOver(Ghost& ghost) override
    {
        //ghost.setState(ghost.getChaseModeState()); // Transition to ChaseMode state
    }

    void timeFrightenedMode(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

    void eaten(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

    void outsideHouse(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

    void insideHouse(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

    void computeNextDir(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

    sf::Vector2f getTargetPosition(Ghost& ghost) override
    {
        // No action in HouseMode state
    }

};

// ChaseMode state
class ChaseModeState : public GhostState
{
public:
};

// ScatterMode state
class ScatterModeState : public GhostState
{
public:
};

// FrightenedMode state
class FrightenedModeState : public GhostState
{
public:
};

// EatenMode state
class EatenModeState : public GhostState
{
public:
};

*/