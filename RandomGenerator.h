//
// Created by Jasey Chanders on 11/30/20.
//
#include <iostream>
#ifndef RRT_RANDOMGENERATOR_H
#define RRT_RANDOMGENERATOR_H

using namespace std;

struct randCoordinate {
    int row;
    int column;

    randCoordinate(int row, int column) {
        this->row = row;
        this->column = column;
    }
};

class RandomGenerator {
private:
    int randGenObstacles[10][10];
    int randomObstacles[10][10];
public:
    void initialize(int size);
    randCoordinate getRandomPosition(int size);
    string getObstacles(int size);
};


#endif //RRT_RANDOMGENERATOR_H
