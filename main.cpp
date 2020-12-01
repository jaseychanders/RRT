//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include "RandomGenerator.h"
#include <iostream>

using namespace std;

using namespace std;

int main(){
    RRT rrt;
    RandomGenerator randomGenerator;
  //  randomGenerator.initialize();
   // string obstacles = randomGenerator.getObstacles(10);
    rrt.resetDisplayMatrix();
    rrt.inputObjects("1,8;1,9;2,8;2,9;1,6;1,7;1,8;1,9;2,6;2,7;2,8;2,9;3,6;");
   // int * obstaclesArray = rrt.getObstacles();
   // coordinate startingPosition = randomGenerator.getRandomPosition(10, obstaclesArray);
    //coordinate endingPosition = randomGenerator.getRandomPosition(10, obstaclesArray);

 //   cout << startingPosition.column << ", " << startingPosition.row << "  " << endingPosition.column << ", " << endingPosition.row << endl;
   // cout << obstacles << endl;



   vector<coordinate> path = rrt.runRRT(0,0,9,9);
   // vector<coordinate> path = rrt.runRRT(startingPosition.row,startingPosition.column,endingPosition.row,endingPosition.column);
    cout << endl;
}