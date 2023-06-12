#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "pieceTextures.h"
#include "tablutConstants.h"

namespace Tablut {
    using namespace tablutConstants;

    enum Player {
        BLACK = 0,
        WHITE
    };

    class Piece : public sf::Drawable {
    public:
        Piece() = delete;

        Piece(Player player, bool isKing, int pos) : mPlayer{player}, mIsKing{isKing} {
            setTexture();
            move(pos);
        }

        bool isKing() const { return mIsKing; }

        Player getPlayer() const { return mPlayer; }

        std::vector<int> &getPossibleMoves() { return possibleMoves; }

        void addPossibleMove(int pos) { possibleMoves.push_back(pos); }

        void move(int pos);

    private:
        sf::Sprite mSprite;
        std::vector<int> possibleMoves;
        Player mPlayer;

        bool mIsKing;

        void setTexture();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override { target.draw(mSprite); }
    };
}
#endif // PIECE_H