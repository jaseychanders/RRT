//
// Created by Jasey Chanders on 11/27/20.
// CSCI 2275 Final Project
//

//This file runs the RRT (randomly exploring random trees) algorithm

#include "RRT.h"
#include <math.h>
#include <sstream>
#include <iostream>

using namespace std;

//Initializes the visited and obstacles arrays to zero
RRT::RRT(){

    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            visited[i][j] = 0;
            obstacles[i][j] = 0;
        }
    }
}

//Main function for running RRT
void RRT::runRRT(int startX, int startY, int endX, int endY) {

    srand(time(nullptr));
    //Inputs start and end coordinates
    node * startNode = new node(nullptr, nullptr);
    startNode->coordinate = new coordinate(startX, startY);

    display(startX, startY, endX, endY);

    //Add start node to tree
    tree.push_back(startNode);
    visited[startNode->coordinate->y][startNode->coordinate->x] = 1;

    coordinate * endCoordinate = new coordinate(endX, endY);

    int numIterations = 0;

    //Loop until end node is found or you have gone though enough iterations that their isn't a path to the end
    while(!endNodeFound && numIterations < pow(sideSize, 2)){
        node * nextNode = getNextNode(endCoordinate);

        //Set the flag if this node is the end
        if(nextNode->coordinate != nullptr){
            if(nextNode->coordinate->y == endCoordinate->y && nextNode->coordinate->x == endCoordinate->x){
                endNodeFound = true;
            } else if (getManhattanDist(startNode->coordinate->x, startNode->coordinate->y, endCoordinate->x, endCoordinate->y) == 1){
                endNodeFound = true;
            }

            // If we have a new node add it to the tree and the display matrix
            if(nextNode->coordinate != nullptr){
                tree.push_back(nextNode);
                visited[nextNode->coordinate->y][nextNode->coordinate->x] = 1;
                display(startX, startY, endX, endY);
            }
        }
        numIterations ++;

    }
    cout << "Number of iterations " << numIterations << endl;

    if(numIterations >= pow(sideSize, 5)){
        cout << "Too many iterations, goal is likely unreachable" << endl;
    }

    printPath(getNode(*endCoordinate), startX, startY, endX, endY);
}

//gets the next node to add to the tree
node * RRT::getNextNode(coordinate * endCoordinate) {
    coordinate goalCoordinate = getNextGoalCoordinate(endCoordinate);
    node * nearestNode = getNearestNode(goalCoordinate);
    node * newNode = new node (nullptr, nullptr);

    if(nearestNode->coordinate != nullptr){ // If nearest node is a valid location then add it to the tree
        coordinate * newCoordinate = coordinateForNewNode(nearestNode, goalCoordinate);
        if(newCoordinate->y != -1 && coordinateIsOpen(newCoordinate->x, newCoordinate->y)){
            newNode->parent = nearestNode;
            newNode->coordinate = newCoordinate;
        }
    }

    return newNode;
}

// Randomly generates a goal coordinate
coordinate RRT::getNextGoalCoordinate(coordinate * endCoordinate) {
    double goToGoal = rand() & 100;

    int y;
    int x;

    if(goToGoal <= 1){ // 1 percent of the time chose the end goal as the goal
        y = endCoordinate->y;
        x = endCoordinate->x;
    } else {
        y = rand() % sideSize;
        x = rand() % sideSize;
    }
    if(coordinateIsOpen(x, y)){ // Recursively call this function until a valid coordinate is found
        return coordinate(x, y);
    } else {
        coordinate coord = getNextGoalCoordinate(endCoordinate);
        return coord;
    }


}

// Gets the node closest to the goal coordinate
node *RRT::getNearestNode(coordinate goalCoordinate) {

    node * nearestNode = new node(nullptr, nullptr);
    double nearest = INT_MAX;
    for(node * current : tree){//Loop through the nodes in the tree
        int manhattanDistToGoal = getManhattanDist(current->coordinate->x, current->coordinate->y, goalCoordinate.x, goalCoordinate.y);
        bool blocked = true;
        //If any of the squares adjacent to the current node are open
        if(coordinateIsOpen(current->coordinate->x, current->coordinate->y + 1) ||
           coordinateIsOpen(current->coordinate->x, current->coordinate->y - 1) ||
           coordinateIsOpen(current->coordinate->x + 1, current->coordinate->y) ||
           coordinateIsOpen(current->coordinate->x - 1, current->coordinate->y))
        {
            blocked = false;
        }

        //If our current node is closer than the previous ones replace the shortest with this node
        if(!blocked && manhattanDistToGoal < nearest) {
            nearestNode = current;
            nearest = manhattanDistToGoal;
        }
    }

    return nearestNode;
}

// Finds the coordinate for the next node using the closest node and going one square closer to the goal
coordinate *RRT::coordinateForNewNode(node *closetNode, coordinate goalCoordinate) {

    double manhattanDistance = getManhattanDist((closetNode->coordinate->x), (closetNode->coordinate->y), goalCoordinate.x, goalCoordinate.y);

    if (manhattanDistance <= maxDistance){ // Goal coordinate is only one unit away
        return new coordinate(goalCoordinate.x, goalCoordinate.y);
    } else {
        coordinate * bestCoordinate = new coordinate(-1,-1);
        int shortestManhattanDist = INT_MAX;
        //Gets the distances from the four squares on each side of the nearest node
        int topSquareDist = -1;
        int rightSquareDist = -1;
        int bottomSquareDist = -1;
        int leftSquareDist = -1;

        if (coordinateIsOpen(closetNode->coordinate->x, closetNode->coordinate->y + 1)) {
            topSquareDist = getManhattanDist((closetNode->coordinate->x), (closetNode->coordinate->y + 1),
                                             goalCoordinate.x, goalCoordinate.y);
        }
        if (coordinateIsOpen(closetNode->coordinate->x + 1, closetNode->coordinate->y)) {
            rightSquareDist = getManhattanDist((closetNode->coordinate->x + 1), (closetNode->coordinate->y),
                                               goalCoordinate.x, goalCoordinate.y);
        }
        if (coordinateIsOpen(closetNode->coordinate->x, closetNode->coordinate->y - 1)) {
            bottomSquareDist = getManhattanDist((closetNode->coordinate->x), (closetNode->coordinate->y - 1),
                                                goalCoordinate.x, goalCoordinate.y);
        }
        if (coordinateIsOpen(closetNode->coordinate->x - 1, closetNode->coordinate->y)) {
            leftSquareDist = getManhattanDist((closetNode->coordinate->x - 1), (closetNode->coordinate->y),
                                              goalCoordinate.x, goalCoordinate.y);
        }

        //Randomization so it doesn't preferentially go one direction every time if multiple square are the same distance away
        int whichFirst = rand() % 4;
        bool allHaveBeenChecked = false;
        bool hasLoopedOnce = false;
        bool topChecked = false;
        bool rightChecked = false;
        bool bottomChecked = false;
        bool leftChecked = false;

        while (!allHaveBeenChecked) { // Loop though all four squares and find the one that is closest
            if (!topChecked && (whichFirst == 0 || hasLoopedOnce)) {
                topChecked = true;
                if (topSquareDist != -1 && topSquareDist < shortestManhattanDist) {
                    //Square above
                    shortestManhattanDist = topSquareDist;
                    bestCoordinate->x = closetNode->coordinate->x;
                    bestCoordinate->y = closetNode->coordinate->y + 1;
                }
            } else if (!rightChecked && (whichFirst == 1 || hasLoopedOnce)) {
                rightChecked = true;
                if (rightSquareDist != -1 && rightSquareDist < shortestManhattanDist) {
                    //Square to the right
                    shortestManhattanDist = rightSquareDist;
                    bestCoordinate->x = closetNode->coordinate->x + maxDistance;
                    bestCoordinate->y = closetNode->coordinate->y;
                }
            } else if (!bottomChecked && (whichFirst == 2 || hasLoopedOnce)) {
                bottomChecked = true;
                if (bottomSquareDist != -1 && bottomSquareDist < shortestManhattanDist) {
                    //Square below
                    shortestManhattanDist = bottomSquareDist;
                    bestCoordinate->x = closetNode->coordinate->x;
                    bestCoordinate->y = closetNode->coordinate->y - maxDistance;
                }
            } else if (!leftChecked && (whichFirst == 3 || hasLoopedOnce)) {
                leftChecked = true;
                if (leftSquareDist != -1 && leftSquareDist < shortestManhattanDist) {
                    //Square to the left
                    shortestManhattanDist = leftSquareDist;
                    bestCoordinate->x = closetNode->coordinate->x - maxDistance;
                    bestCoordinate->y = closetNode->coordinate->y;
                }
            }
            hasLoopedOnce = true;
            if (topChecked && rightChecked && bottomChecked && leftChecked) {
                allHaveBeenChecked = true;
            }
        }
        return bestCoordinate;
    }
}

//Calculates the distance between two points only going in strait lines and turning 90 degrees
int RRT::getManhattanDist(double x1, double y1, double x2, double y2){
    return (abs(x2 - x1) + abs(y2 - y1));
}


// Checks if a coordinate hasn't been visited and doesn't have an obstacle
bool RRT::coordinateIsOpen(int x, int y) {
    if(x < sideSize && x > -1 && y < sideSize && y > -1){
        bool hasBeenVisited = visited[y][x] == 0;
        bool isOpen = obstacles[y][x] != 1;
        return hasBeenVisited && isOpen;
    } else {
        return false;
    }

}

// field and then prints only the path to the end
void RRT::printPath(node * endNode, int startX, int startY, int endX, int endY) {
    node * tmp = endNode;

    //clears all paths
    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            visited[i][j] = 0;
        }
    }

    while(tmp != nullptr){ //Loops back though the trail of parent pointers

        visited[tmp->coordinate->y][tmp->coordinate->x] = 1;
        tmp = tmp->parent;
    }

    display(startX, startY, endX, endY);
}

//Searches though nodes in the tree and returns the node with the same coordinates or null if none mathch
node *RRT::getNode(coordinate coordinate) {
    for(node * current : tree){
        if (*current->coordinate == coordinate){
            return current;
        }
    }
    return nullptr;
}

//Inputs obstacles into the obstacles array
//The string to be passed in is formatted (x1,y1;x2,y2;)
void RRT::inputObstacles(string csvOfObstacles){
    stringstream obstaclesSS;
    stringstream coordinateSS;
    obstaclesSS << csvOfObstacles;
    string coordinate;
    string yRaw;
    string xRaw;
    int y;
    int x;
    while(getline(obstaclesSS, coordinate, ';')){
        coordinateSS.clear();
        coordinateSS << coordinate;
        getline(coordinateSS, xRaw, ',');
        getline(coordinateSS, yRaw);
        y = stoi(yRaw);
        x = stoi(xRaw);

        obstacles[y][x] = 1;
    }
    cout << endl;
}

//Displays the current field
void RRT::display(int startX, int startY, int endX, int endY) {
    for(int i = 0; i < sideSize; i++){
        cout << "---";
    }
    cout << "---" << endl;
    for(int i = sideSize -1; i > -1; i--){
        cout << "|";
        for(int j = 0; j < sideSize; j++){
            if(j == startX && i == startY){
                cout << " S ";
            } else if (j == endX && i == endY){
                cout << " E ";
            } else if(visited[i][j] == 1){
                cout << " * ";
            } else if (obstacles[i][j] == 1){
                cout << " ▢ ";
            } else {
                cout << "   ";
            }
        }
        cout << "|" << endl;
    }
    for(int i = 0; i < sideSize; i++){
        cout << "---";
    }
    cout << "---" << endl;
}

//Cleans up memory
RRT::~RRT(){
    for(node * del: tree){
        delete del->coordinate;
        delete del;
    }
}

