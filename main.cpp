//
// Created by Jasey Chanders on 11/27/20.
// CSCI 2275 Final Project
//

// Main driver file for running the RRT (Randomly Exploring Random Trees) algorithm
/*
 * RRT is an algorithm used in robotics application for mapping areas and finding paths from a
 * given start point to a given end point.
 * The process consists of building a tree of connected location in a field by
 * generating random goal locations, finding the closest node in the tree to that location
 * and then going a certain distance towards that goal and adding a new node to the graph
 */

//In order to run this code simply compile it and everything should be taken care of
//the process and the final path will be outputted to the terminal
//If you want to change the size of the field it can be change in the RRT.h file
//If you want to specify starting and ending locations instead of using random ones uncomment the
// specified line below

#include "RRT.h"
#include "RandomGenerator.h"
#include <iostream>

using namespace std;

int main(){

    //Handles the random generation of obstacles and starting and ending points
    RandomGenerator randomGenerator;
    randomGenerator.initialize(sideSize);
    string stringOfObstacles = randomGenerator.getObstacles(sideSize);
    coordinate startingPosition = randomGenerator.getRandomPosition(sideSize);
    coordinate endingPosition = randomGenerator.getRandomPosition(sideSize);

    //Runs the RRT algorithm
    RRT rrt;
    rrt.inputObstacles(stringOfObstacles);
    //Runs RRT with random starting and ending locations
    rrt.runRRT(startingPosition.x, startingPosition.y, endingPosition.x, endingPosition.y);

    //Runs RRT with user specified starting and ending locations
    //rrt.runRRT(0, 0, 24, 24);
}