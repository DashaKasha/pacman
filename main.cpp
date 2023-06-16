#include <SFML/Graphics.hpp>
#include "game.h"


void handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        //   
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void update(sf::Clock& clock, Game& game)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    game.updateGame(elapsedTime);
}

void render(sf::RenderWindow& window, Game& game)
{
    window.clear();
    game.render(window);
    window.display();
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "PacMan Game Clone", sf::Style::Close);
    sf::Clock clock;

    Game game;
    /*
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) // �������� ������
    {
        return -1;
    }
    */


    while (window.isOpen())
    {
        handleEvents(window);
        update(clock, game);
        render(window, game);
    }

    return 0;
}