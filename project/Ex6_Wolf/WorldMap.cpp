#include "WorldMap.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace std;

void WorldMap::loadMap(std::string filename) {
    // TODO implement json loading this instead of the following
//    values.push_back( { 0, 0, 0,0} ); // -------> x   sample map of size 4 by 4
//    values.push_back( { 0,-1,-1,2} ); // |            inner vector define tiles in the x axis
//    values.push_back( { 0,-1,-1,9} ); // |            outer vector define tiles in the z axis
//    values.push_back( { 0, 0, 0,0} ); // v z


    // you can use the json slides in lecture 4 as a reference
     using namespace rapidjson;
     ifstream fis(filename);
     IStreamWrapper isw(fis);
     Document d;
     d.ParseStream(isw);
    startingPosition.x = d["spawn"]["x"].GetFloat();
    startingPosition.y = d["spawn"]["y"].GetFloat();
    startingRotation = d["spawn"]["angle"].GetFloat();

    for (int i = 0; i < d["tileMap"].Size(); i++)
    {
        std::vector<int> tile;
        for (int j = 0; j < d["tileMap"][i].Size(); j++)
        {
            tile.push_back(d["tileMap"][i][j].GetInt());
        }
        values.push_back(tile);
    }
}

int WorldMap::getTile(int x, int y) {
    return values.at(y).at(x);
}

int WorldMap::getWidth() {
    return values[0].size();
}

int WorldMap::getHeight() {
    return values.size();
}

glm::vec2 WorldMap::getStartingPosition() {
    return startingPosition;
}

float WorldMap::getStartingRotation() {
    return startingRotation;
}

glm::vec4 WorldMap::getFloorColor() {
    return floorColor;
}

glm::vec4 WorldMap::getCeilColor() {
    return ceilColor;
}
