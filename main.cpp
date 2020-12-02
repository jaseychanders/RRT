//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include "RandomGenerator.h"
#include <iostream>

using namespace std;

using namespace std;

//TODO fix starting and ending points being in obstacles

int main(){
    RRT rrt;
    RandomGenerator randomGenerator;
    randomGenerator.initialize();
    string obstacles = randomGenerator.getObstacles(5);
    cout << obstacles << endl;
    rrt.resetDisplayMatrix();
    rrt.inputObstacles(obstacles);
    coordinate startingPosition = randomGenerator.getRandomPosition(5);
    coordinate endingPosition = randomGenerator.getRandomPosition(5);

 //   cout << startingPosition.column << ", " << startingPosition.row << "  " << endingPosition.column << ", " << endingPosition.row << endl;
   // cout << obstacles << endl;



  // vector<coordinate> path = rrt.runRRT(9,9,9,0);
    vector<coordinate> path = rrt.runRRT(startingPosition.row,startingPosition.column,endingPosition.row,endingPosition.column);
    cout << endl;
}