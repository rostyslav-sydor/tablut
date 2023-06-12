#ifndef TABLUTGAME_H
#define TABLUTGAME_H

#include <array>
#include <vector>
#include <iostream>
#include "board.h"

#include "SFML/Graphics.hpp"
#include "piece.h"
#include "tablutConstants.h"
#include "util.h"

namespace Tablut {
    using namespace tablutConstants;

    class TablutGame: public sf::Drawable{
    public:
        TablutGame(sf::Color bordCol1, sf::Color bordCol2);

        bool getSelected() const { return selected; }

        bool gameOver() const { return blackWin || whiteWin; }

        bool selectPiece(int pos);

        void moveSelected(int pos);

        void restart();

    private:
        std::array<std::shared_ptr<Piece>, tablutConstants::numSquares> board;
        std::vector<sf::RectangleShape> possibleMovesSquares;
        std::vector<int> border;
        std::string lastMove;

        GraphicBoard graphicBoard;
        sf::RectangleShape infoRestart;

        sf::Font font;
        sf::Text textRestart;
        sf::Text textTurn;
        sf::Text textSituation;
        sf::Text textLastMove;

        bool selected = false;
        int selectedPiecePos = -1;
        std::shared_ptr<Piece> selectedPiece = nullptr;
        Player playerTurn = WHITE;
        bool whiteWin = false;
        bool blackWin = false;
        int turn = 1;

        void calcBorder();
        void createMoveSquares();

        void calcPieceMoves(int move);

        void setupBoard();
        void clearBoard();

        void checkCapture(int pos);
        void checkCaptured(int pos);
        void checkWhiteWin();

        void updateInfo();
        static std::string posToStr(int pos);

        static int right(int pos);
        static int left(int pos);
        static int up(int pos);
        static int down(int pos);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };
}

#endif // TABLUTGAME_H