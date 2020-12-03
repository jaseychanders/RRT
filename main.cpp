//
// Created by Jasey Chanders on 11/27/20.
// CSCI 2275 Final Project
//

// Main driver file for running the RRT (Randomly Exploring Random Trees) algorithm
/*
 * RRT is an algorithm used in robotics application for mapping areas and finding paths from a
 * given start point to a given end point. The process consists of building a tree of connected
 * locations in an unknown field by generating random goal locations, finding the closest node in
 * the tree to that location and then going a certain distance towards that goal and adding a new
 * node to the graph. My version of RRT uses what is called Manhattan distance to find the nearest
 * node which is the distance between two points only using straight line and 90 degree turns. The
 * result of RRT is a map of the area and a path (not necessarily the shortest) from the starting
 * location to the ending location.
 */

//In order to run this code simply compile using
// g++ -std=c++11 main.cpp RandomGenerator.cpp RRT.cpp
// and everything should be taken care of
//The process and the final path will be outputted to the terminal
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