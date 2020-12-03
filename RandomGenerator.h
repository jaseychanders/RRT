//
// Created by Jasey Chanders on 11/30/20.
//
#include <iostream>
#ifndef RRT_RANDOMGENERATOR_H
#define RRT_RANDOMGENERATOR_H

using namespace std;

struct randCoordinate {
    int y;
    int x;

    randCoordinate(int x, int y) {
        this->y = y;
        this->x = x;
    }
};

class RandomGenerator {
private:
    int randomObstacles[10][10];
public:
    void initialize(int size);
    randCoordinate getRandomPosition(int size);
    string getObstacles(int size);
};


#endif //RRT_RANDOMGENERATOR_H
