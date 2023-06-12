#include "board.h"

namespace Tablut {
    GraphicBoard::GraphicBoard(sf::Color col1, sf::Color col2) {
        load(col1, col2);
    }

    void GraphicBoard::load(sf::Color col1, sf::Color col2) {
        using namespace tablutConstants;

        for (unsigned i = 0; i < sideLen; i++) {
            for (unsigned j = 0; j < sideLen; j++) {
                sf::RectangleShape &rect = mBoardSquares[j + (i * sideLen)];

                rect.setPosition(sf::Vector2f(j * squareSize, i * squareSize));
                rect.setSize(sf::Vector2f(squareSize, squareSize));
                rect.setFillColor(col1);
                rect.setOutlineColor(col2);
                rect.setOutlineThickness(-1.5f);
            }
        }
    }

    void GraphicBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for (const auto &square: mBoardSquares) {
            target.draw(square);
        }
    }
}