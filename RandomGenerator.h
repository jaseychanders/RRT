//
// Created by Jasey Chanders on 11/30/20.
// CSCI 2275 Final Project
//

//This file is used to generate random points to be used by the rrt functions


#include <iostream>
#include "RRT.h"
#ifndef RRT_RANDOMGENERATOR_H
#define RRT_RANDOMGENERATOR_H

using namespace std;

class RandomGenerator {
private:
    int obstacles[sideSize][sideSize]; //Stores obstacles
public:
    void initialize(int size); //Clears obstacles
    coordinate getRandomPosition(int size);//Gets a random position that is not an obstacle
    string getObstacles(int size);//Generates random obstacles
};

#endif //RRT_RANDOMGENERATOR_H
