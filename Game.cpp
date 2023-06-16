#include "Game.h"
#include "Entity.h"
#include "Ghost.h"
#include <iostream>
#include <fstream>


Game::Game() {
    // create factory AbstractGhostFactory* ghostFactory;
    // read the text file with maze and positions of entities
    // if x - create wall and add into walls
    // if P - create pacman, add into objects
    // if b/p/i/c - create factories
    // create ghosts and add them into objects and ghosts
    // if . - create PacGum into objects
    // if o - create SuperPacGum
    // if - - create GhostHouse 

    std::ifstream file("pacman.txt"); // ���� � ���������� ����� � ����������

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
                    // �������� � ���������� ����� � ������ walls
                    cells.push_back(new Cell(xPos, yPos, 32.f));
                    break;

                case 'P':
                    // �������� �������
                    pacman = new Pacman(xPos, yPos);
                    break;

                case 'b':
                    // �������� ������ � ���������� ��� � ������ ghosts
                    factory = new BlinkyFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;

                case 'p':
                    // �������� ����� � ���������� ��� � ������ ghosts
                    factory = new PinkyFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;

                case 'i':
                    // �������� ���� � ���������� ��� � ������ ghosts
                    factory = new InkyFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;

                case 'c':
                    // �������� ������ � ���������� ��� � ������ ghosts
                    factory = new ClydeFactory();
                    ghosts.push_back(factory->createGhost(xPos, yPos));
                    break;
                   
                case '.':
                    // �������� � ���������� PacGum � ������ objects
                    pucgums.push_back(new PacGum(xPos * 32.f + 16.f, yPos * 32.f + 16.f, 4.f));
                    break;
                    
                case 'o':
                    // �������� � ���������� SuperPacGum � ������ objects
                    superPucGums.push_back(new SuperPacGum(xPos * 32.f + 16.f, yPos * 32.f + 16.f, 12.f));
                    break;
                    /*
                case '-':
                    // �������� � ���������� GhostHouse � ������ objects
                    objects.push_back(new GhostHouse());
                    break;
                    */
                default:
                    // ����������� ������, ����������
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
}


void Game::updateGame(float elapsedTime) { 
    
    pacman->update(elapsedTime, getCells(), pucgums);

    for (auto ghost : ghosts) {
        ghost->update(elapsedTime, getCells());
    }

    // ��������� ������ ������ �� ������������ � ��������
    int i = 0;
    for (PacGum* gum : pucgums) {
        sf::FloatRect gumBounds = gum->getBounds();
        sf::FloatRect pacmanBounds = pacman->getBounds();
        // ��������� ������� ������������ ������� � ������
        if (pacmanBounds.intersects(gumBounds)) {
            //movement = sf::Vector2f(-movement.x, -movement.y);
            pucgums.erase(pucgums.begin() + i);
            score = score + 50;
            break;
        }
        i++;
    }

};

void Game::render(sf::RenderWindow& window){
    for (auto gum : pucgums) {
        gum->render(window);
    }
    for (auto Supergum : superPucGums) {
        Supergum->render(window);
    }

    for (auto ghost : ghosts) {
        ghost->render(window);
    }

    getPacman().render(window);
    for (auto cell: cells) {
        cell->render(window);
    }
};





