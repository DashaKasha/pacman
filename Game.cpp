#include "Game.h"
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
        while (std::getline(file, line)) {
            for (char symbol : line) {
                switch (symbol) {
                case 'x':
                    // �������� � ���������� ����� � ������ walls
                    xPos = i % 25;
                    yPos = i / 25 ;
                    cells.push_back(new Cell(xPos, yPos, 32.f));
                    i++;
                    break;
                case 'P':
                    // �������� � ���������� ������� � ������ objects
                    xPos = i % 25;
                    yPos = i / 25;
                    pacman = new Pacman(xPos, yPos);
                    //pacman->setPos(xPos, yPos);
                    //objects.push_back(pacman);
                    i++;
                    break;
                //case 'b':
                //case 'p':
                //case 'i':
                //case 'c':
                    /*
                    // �������� ��������������� ������� ��������� � ������������ ��������� �� ��� ghostFactory
                    if (symbol == 'b') {
                        ghostFactory = new BGhostFactory();
                    }
                    else if (symbol == 'p') {
                        ghostFactory = new PGhostFactory();
                    }
                    else if (symbol == 'i') {
                        ghostFactory = new IGhostFactory();
                    }
                    else if (symbol == 'c') {
                        ghostFactory = new CGhostFactory();
                    }
                    break;
                    
                case '.':
                    // �������� � ���������� PacGum � ������ objects
                    objects.push_back(new PacGum());
                    break;
                case 'o':
                    // �������� � ���������� SuperPacGum � ������ objects
                    objects.push_back(new SuperPacGum());
                    break;
                case '-':
                    // �������� � ���������� GhostHouse � ������ objects
                    objects.push_back(new GhostHouse());
                    break;
                    */
                default:
                    // ����������� ������, ����������
                    i++;
                    break;
                }
            }
        }

        file.close();
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }
}


void Game::updateGame(float elapsedTime) { 
    pacman->update(elapsedTime);

};
void Game::render(sf::RenderWindow& window){
    getPacman().render(window);
    for (auto cell: cells) {
        cell->render(window);

    }
};





