//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include "RandomGenerator.h"
#include <iostream>

using namespace std;

int main(){

    RandomGenerator randomGenerator;
    randomGenerator.initialize(sideSize);
    string stringOfObstacles = randomGenerator.getObstacles(sideSize);
    cout <<"Obstacles string: " << stringOfObstacles << endl;
    coordinate startingPosition = randomGenerator.getRandomPosition(sideSize);
    coordinate endingPosition = randomGenerator.getRandomPosition(sideSize);
    cout << "Starting x,y: " << startingPosition.x << "," << startingPosition.y << " \nEnding x,y " << endingPosition.x << "," << endingPosition.y << endl;


    RRT rrt;
    rrt.inputObstacles(stringOfObstacles);
    vector<coordinate> path = rrt.runRRT(startingPosition.x, startingPosition.y, endingPosition.x, endingPosition.y);
}