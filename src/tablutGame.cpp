#include "tablutGame.h"
#include <functional>

namespace Tablut {

    TablutGame::TablutGame(sf::Color bordCol1, sf::Color bordCol2)
        : graphicBoard(bordCol1, bordCol2) {
        font.loadFromFile("Textures/arial.ttf");

        infoRestart.setFillColor(sf::Color::White);
        infoRestart.setOutlineThickness(-5.f);
        infoRestart.setOutlineColor(sf::Color::Black);
        infoRestart.setPosition(sf::Vector2f(boardWidth, 0.f));
        infoRestart.setSize(sf::Vector2f(256.f, 50.f));

        textRestart.setFont(font);
        textRestart.setString("RESTART");
        textRestart.setCharacterSize(24);
        textRestart.setStyle(sf::Text::Bold);
        textRestart.setFillColor(sf::Color::Black);
        textRestart.setPosition(infoRestart.getPosition().x + 75.f, infoRestart.getPosition().y + 10.f);

        textTurn.setFont(font);
        textTurn.setCharacterSize(24);
        textTurn.setStyle(sf::Text::Bold);
        textTurn.setFillColor(sf::Color::White);
        textTurn.setPosition(boardWidth + 20, 70.f);

        textSituation.setFont(font);
        textSituation.setCharacterSize(24);
        textSituation.setStyle(sf::Text::Bold);
        textSituation.setFillColor(sf::Color::White);
        textSituation.setPosition(boardWidth + 20, 110.f);

        textLastMove.setFont(font);
        textLastMove.setCharacterSize(24);
        textLastMove.setStyle(sf::Text::Bold);
        textLastMove.setFillColor(sf::Color::White);
        textLastMove.setPosition(boardWidth + 20, 200.f);

        calcBorder();

        restart();
    }

    void TablutGame::clearBoard() {
        for (auto &i: board) {
            i = nullptr;
        }
    }

    void TablutGame::setupBoard() {
        auto addPiece = [this] (int pos, Player player, bool isKing) {
            board[pos] = std::make_shared<Piece>(player, isKing, pos);
        };

        addPiece(3, BLACK, false);
        addPiece(4, BLACK, false);
        addPiece(5, BLACK, false);
        addPiece(13, BLACK, false);
        addPiece(27, BLACK, false);
        addPiece(35, BLACK, false);
        addPiece(36, BLACK, false);
        addPiece(37, BLACK, false);
        addPiece(43, BLACK, false);
        addPiece(44, BLACK, false);
        addPiece(45, BLACK, false);
        addPiece(53, BLACK, false);
        addPiece(67, BLACK, false);
        addPiece(75, BLACK, false);
        addPiece(76, BLACK, false);
        addPiece(77, BLACK, false);
        addPiece(22, WHITE, false);
        addPiece(31, WHITE, false);
        addPiece(38, WHITE, false);
        addPiece(39, WHITE, false);
        addPiece(40, WHITE, true); // King
        addPiece(41, WHITE, false);
        addPiece(42, WHITE, false);
        addPiece(49, WHITE, false);
        addPiece(58, WHITE, false);
    }

    void TablutGame::restart() {
        selected = false;
        playerTurn = WHITE;
        blackWin = false;
        whiteWin = false;
        turn = 1;

        clearBoard();
        setupBoard();

        textLastMove.setString("");
        updateInfo();
    }

    void TablutGame::updateInfo() {
        textTurn.setString("Turn: " + std::to_string(turn));
        textLastMove.setString(lastMove);

        if (blackWin)
            textSituation.setString("Black Wins");
        else if (whiteWin)
            textSituation.setString("White Wins");
        else if (playerTurn == WHITE)
            textSituation.setString("White turn");
        else
            textSituation.setString("Black turn");
    }

    void TablutGame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.clear(sf::Color::Black);

        target.draw(graphicBoard);
        target.draw(infoRestart);
        target.draw(textRestart);
        target.draw(textTurn);
        target.draw(textSituation);
        target.draw(textLastMove);

        if ((selectedPiece != nullptr) && (selected)) {
            for (const auto &possibleMovesSquare: possibleMovesSquares) {
                target.draw(possibleMovesSquare);
            }
        }

        for (const auto &square: board) {
            if (square != nullptr)
                target.draw(*square);
        }
    }

    void TablutGame::createMoveSquares() {
        using namespace tablutConstants;
        if (selectedPiece == nullptr)
            return;

        possibleMovesSquares.clear();

        for (int i: selectedPiece->getPossibleMoves()) {
            sf::RectangleShape tmp;
            tmp.setPosition(posToVec(i));
            tmp.setSize(sf::Vector2f(squareSize, squareSize));
            tmp.setFillColor(sf::Color(0x66b4cc50));
            possibleMovesSquares.push_back(tmp);
        }

        sf::RectangleShape tmp;
        tmp.setPosition(posToVec(selectedPiecePos));
        tmp.setSize(sf::Vector2f(squareSize, squareSize));
        tmp.setFillColor(sf::Color(0x0));
        tmp.setOutlineColor(sf::Color::Red);
        tmp.setOutlineThickness(-3.f);
        possibleMovesSquares.push_back(tmp);
    }

    bool TablutGame::selectPiece(int pos) {
        if (board[pos] != nullptr && board[pos]->getPlayer() == playerTurn) {
            selectedPiecePos = pos;
            selectedPiece = board[pos];
            selected = true;
            calcPieceMoves(selectedPiecePos);
        } else {
            selectedPiecePos = -1;
            selectedPiece = nullptr;
            selected = false;
        }

        return selected;
    }

    void TablutGame::moveSelected(int pos) {
        if (!selected)
            return;

        const auto &possibleMoves = selectedPiece->getPossibleMoves();
        if (std::find(possibleMoves.begin(), possibleMoves.end(), pos) != possibleMoves.end()) {
            selectedPiece->move(pos);
            std::swap(board[selectedPiecePos], board[pos]);

            lastMove = "Last Turn: " + posToStr(selectedPiecePos) + " - " + posToStr(pos);

            if (playerTurn == WHITE)
                playerTurn = BLACK;
            else {
                playerTurn = WHITE;
                turn++;
            }

            checkCapture(pos);
            checkWhiteWin();
        }

        selected = false;
        selectedPiece = nullptr;
        selectedPiecePos = -1;

        updateInfo();
    }

    void TablutGame::calcPieceMoves(int pos) {
        using namespace tablutConstants;
        board[pos]->getPossibleMoves().clear();

        auto calcMovesInDirection = [this](const std::function<int (int)>& move, int startingPos) {
            for (int nextPos = move(startingPos); nextPos != -1; nextPos = move(nextPos)) {
                if (board[nextPos] != nullptr)
                    break;
                board[startingPos]->addPossibleMove(nextPos);
            }
        };

        calcMovesInDirection(up, pos);
        calcMovesInDirection(down, pos);
        calcMovesInDirection(left, pos);
        calcMovesInDirection(right, pos);

        createMoveSquares();
    }

    void TablutGame::checkCapture(int pos) {
        auto checkSide = [this](int curPos) { if (curPos != -1 && board[curPos] != nullptr) checkCaptured(curPos); };

        checkSide(left(pos));
        checkSide(right(pos));
        checkSide(up(pos));
        checkSide(down(pos));
    }

    void TablutGame::checkCaptured(int pos) {
        auto checkSide = [this](int origPos, int pos1, int pos2) {
            return (pos1 != -1 && pos2 != -1 &&
                    board[pos1] != nullptr && board[pos2] != nullptr &&
                    board[pos1]->getPlayer() != board[origPos]->getPlayer() &&
                    board[pos2]->getPlayer() != board[origPos]->getPlayer());
        };

        if (checkSide(pos, left(pos), right(pos)) ||
            checkSide(pos, up(pos), down(pos))) {

            if (board[pos]->isKing())
                blackWin = true;
            board[pos] = nullptr;
        }
    }

    void TablutGame::calcBorder() {
        for (int i = 0; i < numSquares; ++i)
            if (i < sideLen || i % sideLen == 0 || i % sideLen == sideLen - 1 || i > numSquares - sideLen)
                border.push_back(i);
    }

    void TablutGame::checkWhiteWin() {
        for (int i: border) {
            if (board[i] != nullptr && board[i]->isKing())
                whiteWin = true;
        }
    }

    std::string TablutGame::posToStr(int pos) {
        std::string tmp;
        tmp += static_cast<char>(65 + pos % sideLen);
        tmp += std::to_string(pos / sideLen + 1);
        return tmp;
    }

    int TablutGame::right(int pos) {
        using namespace tablutConstants;
        if (pos % sideLen == sideLen - 1)
            return -1;
        return pos + 1;
    }

    int TablutGame::left(int pos) {
        using namespace tablutConstants;
        if (pos % sideLen == 0)
            return -1;
        return pos - 1;
    }

    int TablutGame::up(int pos) {
        using namespace tablutConstants;
        if (pos / sideLen == 0)
            return -1;
        return pos - sideLen;
    }

    int TablutGame::down(int pos) {
        using namespace tablutConstants;
        if (pos / sideLen == sideLen - 1)
            return -1;
        return pos + sideLen;
    }
}