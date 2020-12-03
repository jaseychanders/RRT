//
// Created by Jasey Chanders on 11/30/20.
//
#include <iostream>
#include "RRT.h"
#ifndef RRT_RANDOMGENERATOR_H
#define RRT_RANDOMGENERATOR_H

using namespace std;

class RandomGenerator {
private:
    int randomObstacles[sideSize][sideSize];
public:
    void initialize(int size);
    coordinate getRandomPosition(int size);
    string getObstacles(int size);
};


#endif //RRT_RANDOMGENERATOR_H
