#include "pieceTextures.h"
namespace Tablut {
    sf::Texture PieceTextures::loadTexture(const std::string& str){
        sf::Texture tmp;
        if (!tmp.loadFromFile(str))
            std::cout << "Error loading file " << str << std::endl;
        return tmp;
    }

    sf::Texture PieceTextures::whiteKing = PieceTextures::loadTexture("Textures/w_king.png");
    sf::Texture PieceTextures::whitePawn = PieceTextures::loadTexture("Textures/w_pawn.png");
    sf::Texture PieceTextures::blackPawn = PieceTextures::loadTexture("Textures/b_pawn.png");
}