#include <iostream>
#include <SFML/Graphics.hpp>
#include "tablutGame.h"

int main(){
    using namespace Tablut;

    TablutGame tablut(sf::Color(0xf3bc7aff), sf::Color(0xae722bff));

    unsigned windowHeight = boardHeight;
    unsigned windowWidth = boardWidth + 256;

    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Tablut", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if ((0 <= event.mouseButton.x) && (event.mouseButton.x <= boardWidth) &&
                    (0 <= event.mouseButton.y) && (event.mouseButton.y <= boardHeight) && !tablut.gameOver()) {

                    int buttonPos = event.mouseButton.x / squareSize + (event.mouseButton.y / squareSize) * sideLen;
                    if(!tablut.getSelected())
                        tablut.selectPiece(buttonPos);
                    else
                        tablut.moveSelected(buttonPos);
                }
                else if ((boardWidth <= event.mouseButton.x) && (event.mouseButton.x <= windowWidth) && (5 <= event.mouseButton.y) && (event.mouseButton.y <= 45)) {
                    tablut.restart();
                }
            }
        }

        window.draw(tablut);
        window.display();
    }
}