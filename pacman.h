#pragma once
#include "Cell.h"
#include "Entity.h"
#include <vector>

static const sf::Color PACKMAN_COLOR = sf::Color(255, 216, 0);
static const float PACKMAN_SPEED = 120.f; // pixels per second.
static const float PACKMAN_RADIUS = 14.f; // pixels


class Pacman : public MovingEntity
{
public:
    Pacman(int xPos, int yPos) {
        direction = Direction::NONE;
        shape.setRadius(PACKMAN_RADIUS);
        shape.setFillColor(PACKMAN_COLOR);
        shape.setPosition(sf::Vector2f(xPos * 32.f, yPos * 32.f));
    }



    void updatePacmanDirection() {
        direction = Direction::NONE;
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

    void update(float elapsedTime, std::vector<Cell*> cells, std::vector<Swamp*> swamps) {
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            movement = movement + movement;
        }



        // Проверяем каждое болото на столкновение с болотом

        for (Swamp* swamp : swamps) {
            sf::FloatRect pacmanBounds = getBounds();
            sf::FloatRect swampBounds = swamp->getBounds();

            // Проверяем условие столкновения пакмана и болота
            if (swampBounds.intersects(pacmanBounds)) {
                movement = movement / 2.0f;
                direction = Direction::NONE;
                break;
            }
        }


        // Проверяем каждую стенку на столкновение с пакманом

        for (Cell* cell : cells) {
            sf::FloatRect nextBounds = shape.getGlobalBounds();
            sf::FloatRect cellBounds = cell->getBounds();
            nextBounds.left += movement.x;
            nextBounds.top += movement.y;

            // Проверяем условие столкновения пакмана и стенки
            if (nextBounds.intersects(cellBounds)) {
                movement = sf::Vector2f(-movement.x, -movement.y);
                break;
            }
        }

       
        
       shape.move(movement);


    }
};

