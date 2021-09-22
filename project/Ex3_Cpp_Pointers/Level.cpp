//
// Created by Morten Nobel-Jørgensen on 06/09/2017.
//

#include "Level.hpp"

void Level::init(int width, int height) {
    blocks.clear();
    this->width = width;
    this->height = height;


    for (int x=0;x<width;x++){             // init vectors
        blocks.emplace_back(height,0);  // add vector filled with 0 elements (with size of height)
    }
    for (int x=0;x<width;x++){             // init levels (top and bottom walls)
        blocks[x][0] = 1;
        blocks[x][height-1] = 1;
    }
    for (int y=1;y<height-1;y++){          // init levels (left and right walls)
        blocks[0][y] = 1;
        blocks[width-1][y] = 1;
    }
}

bool Level::isBlocked(int x, int y) const {
    return blocks[x][y] == 1;
}

bool Level::snakeCollide(int x, int y) const {
    return blocks[x/4][y/4] == 1;
}

int Level::getWidth() const {
    return width;
}

int Level::getHeight() const {
    return height;
}
