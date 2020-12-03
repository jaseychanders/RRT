//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include "RandomGenerator.h"
#include <iostream>

using namespace std;

int main(){
    RandomGenerator randomGenerator;
    randomGenerator.initialize(10);
    string stringOfObstacles = randomGenerator.getObstacles(10);
    cout <<"Obstacles string: " << stringOfObstacles << endl;
    randCoordinate startingPosition = randomGenerator.getRandomPosition(10);
    randCoordinate endingPosition = randomGenerator.getRandomPosition(10);
    cout << "Starting x,y: " <<  startingPosition.row << "," << startingPosition.column << " \nEnding x,y " << endingPosition.row << "," << endingPosition.column << endl;


    RRT rrt;
    rrt.resetDisplayMatrix();
    rrt.inputObstacles(stringOfObstacles);
   // rrt.updateObstacles();
    vector<coordinate> path = rrt.runRRT(startingPosition.row,startingPosition.column,endingPosition.row,endingPosition.column);
}