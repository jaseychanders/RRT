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
        if(randomObstacles[y][x] == 0){
            randomObstacles[y][x] = 1;
            return randCoordinate(y, x);
        }
    }

}

string RandomGenerator::getObstacles(int size) {
    int numOfObjects = rand() % size;
    cout << numOfObjects << endl;
    string objectsString;
    for(int i = 0; i < numOfObjects; i++){
      //  int radiusOfObject = round(rand() % (size / 3));
        int x = rand() % (size-1);
        int y = rand() % (size-1);
      //  if(radiusOfObject == 0){
            objectsString.append(to_string(x));
            objectsString.append(",");
            objectsString.append(to_string(y));
            objectsString.append(";");
            randomObstacles[y][x] = 1;
           // cout << randGenObstacles[y][x] << endl;
//        } else {
//            for(int j = -radiusOfObject; j < radiusOfObject; j++){
//                int xLoc = x+j;
//                for(int k = -radiusOfObject; k < radiusOfObject; k++){
//                    int yLoc = y+k;
//                    if(xLoc >=0 && xLoc < size && yLoc >=0 && yLoc < size){
//                        char xChar = char(xLoc);
//                        char yChar = char(yLoc);
//                        objectsString.append(to_string(xChar));
//                        objectsString.append(",");
//                        objectsString.append(to_string(yChar));
//                        objectsString.append(";");
//                        randomObstacles[y][x] = 1;
//                      //  cout << randGenObstacles[y][x] << endl;
//                    }
//                }
        //}

      //  }

    }

    for(int i = size-1; i > -1; i--){
        for(int j = 0; j < size; j++){
           cout << randomObstacles[i][j] << " ";
        }
        cout << endl;
    }

    return objectsString;
}
