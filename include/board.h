#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <memory>
#include <utility>

#include "SFML/Graphics.hpp"
#include "tablutConstants.h"

namespace Tablut {
    using namespace tablutConstants;

    class GraphicBoard : public sf::Drawable {
    public:
        GraphicBoard(sf::Color col1, sf::Color col2);

        void load(sf::Color col1, sf::Color col2);

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        std::array<sf::RectangleShape, tablutConstants::numSquares> mBoardSquares;
    };
}
#endif // BOARD_H