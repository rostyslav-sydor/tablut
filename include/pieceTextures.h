#ifndef PIECE_TEXTURES_H
#define PIECE_TEXTURES_H

#include <string>
#include <iostream>

#include "SFML/Graphics.hpp"

namespace Tablut {

    class PieceTextures {
    public:
        static sf::Texture whiteKing;
        static sf::Texture whitePawn;
        static sf::Texture blackPawn;

        static sf::Texture loadTexture(const std::string &str);
    };
}
#endif // PIECE_TEXTURES_H