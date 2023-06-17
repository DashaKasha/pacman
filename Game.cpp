#include "Game.h"
#include "Entity.h"
#include "Ghost.h"
#include <iostream>
#include <fstream>


Game::Game() {
    gameState = GameState::Playing;
    // create factory AbstractGhostFactory* ghostFactory;
    // read the text file with maze and positions of entities
    // if x - create wall and add into walls
    // if P - create pacman, add into objects
    // if b/p/i/c - create factories
    // create ghosts and add them into objects and ghosts
    // if . - create PacGum into objects
    // if o - create SuperPacGum
    // if - - create GhostHouse 
    // w - болото

    std::ifstream file("pacman.txt"); // Путь к текстовому файлу с лабиринтом

    if (file.is_open()) {
        std::string line;

        int i = 0;
        int xPos = 0;
        int yPos = 0;
        AbstractGhostFactory* factory = 0;
        while (std::getline(file, line)) {
            for (char symbol : line) {
                xPos = i % 25;
                yPos = i / 25;
                switch (symbol) {

                case 'x':
                    // Создание и добавление стены в вектор walls
                    cells.push_back(new Cell(xPos, yPos, 32.f));
                    break;

                case 'P':
                    // Создание Пакмана
                    pacman = new Pacman(xPos, yPos);
                    break;

                case 'b':
                    // Создание Блинки и добавление его в вектор ghosts
                    factory = new BlinkyFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;

                case 'p':
                    // Создание Пинки и добавление его в вектор ghosts
                    factory = new PinkyFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;

                case 'i':
                    // Создание Инки и добавление его в вектор ghosts
                    factory = new InkyFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;

                case 'c':
                    // Создание Клайда и добавление его в вектор ghosts
                    factory = new ClydeFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;
                   
                case '.':
                    // Создание и добавление PacGum в вектор objects
                    pucgums.push_back(new PacGum(xPos * 32.f + 16.f, yPos * 32.f + 16.f, 4.f));
                    break;
                    
                case 'o':
                    // Создание и добавление SuperPacGum в вектор objects
                    superPucGums.push_back(new SuperPacGum(xPos * 32.f + 16.f, yPos * 32.f + 16.f, 12.f));
                    break;
                case 'w':
                    // Создание болота
                    swamps.push_back(new Swamp(xPos * 32.f, yPos * 32.f));
                    break;
                    /*
                case '-':
                    // Создание и добавление GhostHouse в вектор objects
                    objects.push_back(new GhostHouse());
                    break;
                    */
                default:
                    // Неизвестный символ, игнорируем
                    break;
                }
                i++;
            }
        }

        file.close();
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }

    sf::Font font;
    if (!font.loadFromFile("D:\\SFML\\Project1\\Emulogic-zrEw.ttf")) // Загрузка шрифта
    {
        std::cerr << "Failed to load font." << std::endl;
    }

    uiPanel = new UIPanel(font, sf::Vector2f(6, 6));
}


void Game::updateGame(float elapsedTime) { 
        pacman->update(elapsedTime, getCells(), swamps);

        for (auto ghost : ghosts) {
            ghost->update(elapsedTime, getCells());
        }

        // Проверяем каждую жвачку на столкновение с пакманом
        int i = 0;
        for (PacGum* gum : pucgums) {
            sf::FloatRect gumBounds = gum->getBounds();
            sf::FloatRect pacmanBounds = pacman->getBounds();
            // Проверяем условие столкновения пакмана и стенки
            if (pacmanBounds.intersects(gumBounds)) {
                pucgums.erase(pucgums.begin() + i);
                uiPanel->increaseScore(10);
                break;
            }
            i++;
        }

        // Проверяем каждую супержвачку на столкновение с пакманом
        int j = 0;
        for (SuperPacGum* gum : superPucGums) {
            sf::FloatRect gumBounds = gum->getBounds();
            sf::FloatRect pacmanBounds = pacman->getBounds();
            // Проверяем условие столкновения пакмана и стенки
            if (pacmanBounds.intersects(gumBounds)) {
                superPucGums.erase(superPucGums.begin() + j);
                uiPanel->increaseScore(100);
                break;
            }
            j++;
        }
        // все жевачки съедены
        if (pucgums.size() == 0 && superPucGums.size()==0) {
            // ----------------- game over -------------------- //
            gameState = GameState::PlayerWon;
        }

        // Проверяем каждого призрака на столкновение с пакманом
        for (Ghost* ghost : ghosts) {
            sf::FloatRect ghostBounds = ghost->getBounds();
            sf::FloatRect pacmanBounds = pacman->getBounds();

            if (pacmanBounds.intersects(ghostBounds)) {
                // ----------------- game over -------------------- //
                gameState = GameState::PlayerLosed;

                break;
            }
            j++;
        }
  
};

void Game::render(sf::RenderWindow& window){

    if (gameState == GameState::Playing) {

        for (auto gum : pucgums) {
            gum->render(window);
        }
        for (auto Supergum : superPucGums) {
            Supergum->render(window);
        }

        for (auto ghost : ghosts) {
            ghost->render(window);
        }

        for (auto swamp : swamps) {
            swamp->render(window);
        }

        getPacman().render(window);

        for (auto cell : cells) {
            cell->render(window);
        }

        uiPanel->render(window);
    }

    if (gameState == GameState::PlayerLosed) {

        sf::Text losedText;
        sf::Text scoreText;
        sf::Font font = uiPanel->getFont();
        int score = uiPanel->getScore();
        losedText.setFont(font);
        losedText.setPosition(300, 350);
        losedText.setCharacterSize(20);
        losedText.setFillColor(sf::Color::White);
        losedText.setString("YOU LOSE :(");
        window.draw(losedText);

        scoreText.setFont(font);
        scoreText.setPosition(320, 400);
        scoreText.setCharacterSize(13);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString("your score: " + std::to_string(score));
        window.draw(scoreText);
    }


    if (gameState == GameState::PlayerWon) {
    
        sf::Text wonText;
        sf::Text scoreText;
        sf::Font font = uiPanel->getFont();
        int score = uiPanel->getScore();
        wonText.setFont(font);
        wonText.setPosition(300, 350);
        wonText.setCharacterSize(20);
        wonText.setFillColor(sf::Color::White);
        wonText.setString("YOU WON :)");
        window.draw(wonText);

        scoreText.setFont(font);
        scoreText.setPosition(320, 400);
        scoreText.setCharacterSize(13);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString("your score: " + std::to_string(score));
        window.draw(scoreText);
    
    }

};





