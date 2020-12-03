//
// Created by Jasey Chanders on 11/30/20.
// CSCI 2275 Final Project
//

//This file is used to generate random points to be used by the rrt functions

#include "RandomGenerator.h"
#include <iostream>

using namespace std;

//Clears the obstacles array
void RandomGenerator::initialize(int size) {
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            obstacles[i][j] = 0;
        }
    }
}

//Generates random obstacles and produces a string that can be read in my the rrt input object method
string RandomGenerator::getObstacles(int size) {
    int numOfObjects = rand() % size * 2;
    cout << "Number of objects: " << numOfObjects << endl;
    string objectsString;
    for(int i = 0; i < numOfObjects; i++){
        int x = rand() % (size-1);
        int y = rand() % (size-1);
        if(x > -1 && x < size && y > -1 && y < size){
            objectsString.append(to_string(x));
            objectsString.append(",");
            objectsString.append(to_string(y));
            objectsString.append(";");
            obstacles[y][x] = 1;
        }
    }

    return objectsString;
}

//Returns a point in the field that is not an obstacle
coordinate RandomGenerator::getRandomPosition(int size) {

    while(true){
        int x = rand() % (size-1);
        int y = rand() % (size-1);
        if(x > -1 && x < size && y > -1 && y < size) {
            if (obstacles[y][x] == 0) {
                obstacles[y][x] = 1;
                return coordinate(x, y);
            }
        }
    }
}
