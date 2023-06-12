#ifndef UTIL_H
#define UTIL_H

#include "SFML/Graphics.hpp"
#include "tablutConstants.h"

namespace Tablut {
    using namespace tablutConstants;

    sf::Vector2f posToVec(int pos);
    int VecToPos(int x, int y);
}

#endif // UTIL_H
