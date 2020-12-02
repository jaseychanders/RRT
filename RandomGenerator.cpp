//
// Created by Jasey Chanders on 11/30/20.
//

#include "RandomGenerator.h"
#include <iostream>

using namespace std;

void RandomGenerator::initialize() {
    srand(time(NULL));
}

coordinate RandomGenerator::getRandomPosition(int size) {
    int x = rand() % size;
    int y = rand() % size;

    if(obstacles[y][x] != 1){
        return coordinate(y, x);
    } else {
       coordinate coord = getRandomPosition(size);
        return coord;
    }

}

string RandomGenerator::getObstacles(int size) {
    int numOfObjects = rand() % size /2;
    cout << numOfObjects << endl;
    string objectsString;
    for(int i = 0; i < numOfObjects; i++){
        int radiusOfObject = round(rand() % (size / 3));
        int x = rand() % (size-1);
        int y = rand() % (size-1);
        if(radiusOfObject == 0){
            objectsString.append(to_string(x));
            objectsString.append(",");
            objectsString.append(to_string(y));
            objectsString.append(";");
            obstacles[y][x] = 1;
        } else {
            for(int j = -radiusOfObject; j < radiusOfObject; j++){
                int xLoc = x+j;
                for(int k = -radiusOfObject; k < radiusOfObject; k++){
                    int yLoc = y+k;
                    if(xLoc >=0 && yLoc >=0){
                        char xChar = char(xLoc);
                        char yChar = char(yLoc);
                        objectsString.append(to_string(xChar));
                        objectsString.append(",");
                        objectsString.append(to_string(yChar));
                        objectsString.append(";");
                        obstacles[y][x] = 1;
                    }
                }
        }

        }

    }
    return objectsString;
}
