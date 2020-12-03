//
// Created by Jasey Chanders on 11/30/20.
//

#include "RandomGenerator.h"
#include <iostream>

using namespace std;

void RandomGenerator::initialize(int size) {
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            randomObstacles[i][j] = 0;
        }
    }
}

randCoordinate RandomGenerator::getRandomPosition(int size) {

    while(true){
        int x = rand() % (size-1);
        int y = rand() % (size-1);
        if(x > -1 && x < size && y > -1 && y < size) {
            if (randomObstacles[y][x] == 0) {
                randomObstacles[y][x] = 1;
                return randCoordinate(y, x);
            }
        }
    }

}

string RandomGenerator::getObstacles(int size) {
    int numOfObjects = rand() % size;
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
            randomObstacles[y][x] = 1;
        }
    }

    return objectsString;
}
