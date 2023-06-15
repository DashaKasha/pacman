#pragma once
#include "Cell.h"
//#include "Entity.h"
#include <vector>


static sf::FloatRect moveRect(const sf::FloatRect& rect, sf::Vector2f& offset)
{
    return { rect.left + offset.x, rect.top + offset.y, rect.width, rect.height };
}

static float getBottom(const sf::FloatRect& rect)
{
    return rect.top + rect.height;
}

static float getRight(const sf::FloatRect& rect)
{
    return rect.left + rect.width;
}

static bool isBetween(float value, float minValue, float maxValue)
{
    return (value >= minValue) && (value <= maxValue);
}


static Direction selectShiftDirection(float leftShift, float rightShift,
    float topShift, float bottomShift,
    float minShift, float maxShift)
{
    Direction result = Direction::NONE;
    float bestShift = 800 * 16.f;
    if (isBetween(leftShift, minShift, maxShift) && (leftShift < bestShift))
    {
        result = Direction::LEFT;
        bestShift = leftShift;
    }
    if (isBetween(rightShift, minShift, maxShift) && (rightShift < bestShift))
    {
        result = Direction::RIGHT;
        bestShift = rightShift;
    }
    if (isBetween(topShift, minShift, maxShift) && (topShift < bestShift))
    {
        result = Direction::UP;
        bestShift = topShift;
    }
    if (isBetween(bottomShift, minShift, maxShift) && bottomShift < bestShift)
    {
        result = Direction::DOWN;
        bestShift = bottomShift;
    }

    return result;
}


static const sf::Color PACKMAN_COLOR = sf::Color(255, 216, 0);
static const float PACKMAN_SPEED = 120.f; // pixels per second.
static const float PACKMAN_RADIUS = 16.f; // pixels

/*
bool checkCollision(sf::FloatRect packmanBounds) {
    return false;
};
*/

class Pacman : public MovingEntity
{
private:
    Direction prevDirection;
public:
    Pacman(int xPos, int yPos) {
        direction = Direction::NONE;
        shape.setRadius(PACKMAN_RADIUS);
        shape.setFillColor(PACKMAN_COLOR);
        shape.setPosition(sf::Vector2f(xPos * 32.f, yPos * 32.f));
    }



    void updatePacmanDirection() {
        direction = Direction::NONE;
        prevDirection = Direction::NONE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            direction = Direction::UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            direction = Direction::DOWN;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction = Direction::LEFT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction = Direction::RIGHT;
        }

    }

    void update(float elapsedTime, std::vector<Cell*> cells) {
        const float step = PACKMAN_SPEED * elapsedTime;

        updatePacmanDirection();

        sf::Vector2f movement(0.f, 0.f);
        switch (direction)
        {
        case Direction::UP:
            movement.y -= step;
            break;
        case Direction::DOWN:
            movement.y += step;
            break;
        case Direction::LEFT:
            movement.x -= step;
            break;
        case Direction::RIGHT:
            movement.x += step;
            break;
        case Direction::NONE:
            break;
        }



        const sf::FloatRect pacmanBounds = shape.getGlobalBounds();
        sf::FloatRect newBounds = moveRect(pacmanBounds, movement);
        bool changed = false;
        for (Cell* cell : cells) {
            sf::FloatRect cellBounds = cell->getBounds();
            // Проверяем условие столкновения пакмана и стенки
            if (pacmanBounds.intersects(cellBounds)) {
                const float bottomShift = getBottom(cellBounds) - newBounds.top;
                const float topShift = getBottom(newBounds) - cellBounds.top;
                const float rightShift = getRight(cellBounds) - newBounds.left;
                const float leftShift = getRight(newBounds) - cellBounds.left;
                const float movementShift = std::max(std::abs(movement.x), std::abs(movement.y));

                Direction direction = selectShiftDirection(leftShift, rightShift,
                    topShift, bottomShift,
                    movementShift + std::numeric_limits<float>::epsilon(), 0.5f *16.f);
                
                if (direction == Direction::NONE)
                {
                    direction = selectShiftDirection(leftShift, rightShift,
                        topShift, bottomShift,
                        0, 0.5f * 16.f);
                }
                switch (direction)
                {
                case Direction::UP:
                    movement.y -= topShift;
                    break;
                case Direction::DOWN:
                    movement.y += bottomShift;
                    break;
                case Direction::LEFT:
                    movement.x -= leftShift;
                    break;
                case Direction::RIGHT:
                    movement.x += rightShift;
                    break;
                case Direction::NONE:
                    break;
                }
                changed = true;
                newBounds = moveRect(pacmanBounds, movement);
            }
        }
        direction = Direction::NONE;


        
        /*
        bool collisionDetected = false;

        // Проверяем каждую стенку на столкновение с пакманом
        for (Cell* cell : cells) {
            sf::FloatRect cellBounds = cell->getBounds();

            // Проверяем условие столкновения пакмана и стенки
            if (pacmanBounds.intersects(cellBounds)) {
       
        */
       shape.move(movement);


    }
};

