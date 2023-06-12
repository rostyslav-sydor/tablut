#include "util.h"

namespace Tablut {
    sf::Vector2f posToVec(int pos) {
        using namespace tablutConstants;
        return sf::Vector2f((pos % sideLen) * squareSize, pos / sideLen * squareSize);
    }

    int vecToPos(int x, int y) {
        return x + y * tablutConstants::sideLen;
    }
}