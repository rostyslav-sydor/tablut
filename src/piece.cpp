#include "piece.h"

namespace Tablut {
    void Piece::move(int pos) {
        mSprite.setPosition(sf::Vector2f(((pos % sideLen) + 0.5) * squareSize, ((pos / sideLen) + 0.5) * squareSize));
    }

    void Piece::setTexture() {
        mSprite = sf::Sprite();
        if (mPlayer == WHITE)
            mSprite.setTexture(mIsKing ? PieceTextures::whiteKing : PieceTextures::whitePawn);
        else
            mSprite.setTexture(PieceTextures::blackPawn);

        mSprite.setOrigin(sf::Vector2f(mSprite.getTexture()->getSize().x / 2, mSprite.getTexture()->getSize().y / 2));
        mSprite.setScale(sf::Vector2f(0.375f, 0.375f));
    }
}