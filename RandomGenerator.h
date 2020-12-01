//
// Created by Jasey Chanders on 11/30/20.
//

#include "RRT.h"

#ifndef RRT_RANDOMGENERATOR_H
#define RRT_RANDOMGENERATOR_H


class RandomGenerator {
public:
    void initialize();
    coordinate getRandomPosition(int size);
    string getObstacles(int size);
};


#endif //RRT_RANDOMGENERATOR_H
