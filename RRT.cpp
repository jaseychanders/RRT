//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include <math.h>
#include <sstream>
#include <iostream>

using namespace std;

RRT::RRT(){
    sideSize = 10;
    maxDistance = 1;

    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            visited[i][j] = 0;
            obstacles[i][j] = 0;
        }
    }
}

//Main function for running RRT
vector<coordinate> RRT::runRRT(int startX, int startY, int endX, int endY) {

    srand(time(nullptr));
    cout << "Side size: " <<  sideSize << endl;
    //Inputs start and end coordinates
    node * startNode = new node(nullptr, nullptr);
    startNode->coordinate = new coordinate(startX, startY);
    displayMatrix[startY * 2 + 1][startX * 2 + 1] = 6;
    displayMatrix[endY * 2 + 1][endX * 2 + 1] = 7;

    display();

    //Add start node to graph
    graph.push_back(startNode);
    visited[startNode->coordinate->y][startNode->coordinate->x] = 1;

    coordinate * endCoordinate = new coordinate(endX, endY);

    int numIterations = 0;

    //Loop until end node is found or you have gone though enough iterations that their isn't a path to the end
    while(!endNodeFound && numIterations < pow(sideSize, 5)){
        node * nextNode = getNextNode(endCoordinate);

      //  updateObstacles();

        //Set the flag if this node is the end
        if(nextNode->coordinate != nullptr){
            if(nextNode->coordinate->y == endCoordinate->y && nextNode->coordinate->x == endCoordinate->x){
                endNodeFound = true;
            } else if (getManhattanDist(startNode->coordinate->x, startNode->coordinate->y, endCoordinate->x, endCoordinate->y) == 1){
                endNodeFound = true;
            }

            // If we have a new node add it to the graph and the display matrix
            if(nextNode->coordinate != nullptr){
                graph.push_back(nextNode);
                visited[nextNode->coordinate->y][nextNode->coordinate->x] = 1;
                if(displayMatrix[nextNode->coordinate->y * 2 + 1][nextNode->coordinate->x * 2 + 1] != 7 && displayMatrix[nextNode->coordinate->y * 2 + 1][nextNode->coordinate->x * 2 + 1] != 6){
                    displayMatrix[nextNode->coordinate->y * 2 + 1][nextNode->coordinate->x * 2 + 1] = 3;
                }
                int xDif = nextNode->coordinate->y - nextNode->parent->coordinate->y;
                int yDif = nextNode->coordinate->x - nextNode->parent->coordinate->x;
                if(xDif > 0){
                    displayMatrix[(xDif + nextNode->parent->coordinate->y) * 2][(yDif + nextNode->parent->coordinate->x) * 2 + 1] = 5;
                } else if(xDif < 0){
                    displayMatrix[(xDif + nextNode->parent->coordinate->y) * 2 + 2][(yDif + nextNode->parent->coordinate->x) * 2 + 1] = 8;
                }  else if (yDif > 0) {
                    displayMatrix[(xDif + nextNode->parent->coordinate->y) * 2 + 1][(yDif + nextNode->parent->coordinate->x) * 2] = 4;
                } else if (yDif < 0) {
                    displayMatrix[(xDif + nextNode->parent->coordinate->y) * 2 + 1][(yDif + nextNode->parent->coordinate->x) * 2 + 2] = 10;
                }
                display();
            }
        }
        numIterations ++;

      //  if(numIterations % 10 == 0){
            if(!areStillOpenSpaces()){
                break;
            }
      //  }



    }
    cout << "Num iterations " << numIterations << endl;

    if(numIterations >= pow(sideSize, 5)){
        cout << "Too many iterations, goal is likely unreachable" << endl;
    }

    return printPath(getNode(*endCoordinate));
}

//gets the next node to add to the graph
node * RRT::getNextNode(coordinate * endCoordinate) {
    coordinate goalCoordinate = getNextGoalCoordinate(endCoordinate);
    cout << goalCoordinate.x << "," << goalCoordinate.y << endl;
    node * nearestNode = getNearestNode(goalCoordinate);
    node * newNode = new node (nullptr, nullptr);

    if(nearestNode->coordinate != nullptr){
        cout << nearestNode->coordinate->x << " " << nearestNode->coordinate->y << endl;
        coordinate * newCoordinate = coordinateForNewNodeManhattan(nearestNode, goalCoordinate);
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

    if(goToGoal <= 5){
        y = endCoordinate->y;
        x = endCoordinate->x;
    } else {
        y = rand() % sideSize;
        x = rand() % sideSize;
    }
    if(coordinateIsOpen(x, y)){
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
    for(node * current : graph){//Loop through the nodes in the graph
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
coordinate *RRT::coordinateForNewNodeManhattan(node *closetNode, coordinate goalCoordinate) {
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

//Calculates the distance between two points only going in strait lines and truning 90 degrees
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

// Clears the display matrix and then puts only the path that has been found in the matrix and prints it
vector<coordinate> RRT::printPath(node * endNode) {
    resetDisplayMatrixPathOnly();
    vector<coordinate> path;
    node * tmp = endNode;
    while(tmp != nullptr){ //Loops back though the trail of parent pointers
        path.push_back(*tmp->coordinate);

        if(displayMatrix[tmp->coordinate->y * 2 + 1][tmp->coordinate->x * 2 + 1] != 7 && displayMatrix[tmp->coordinate->y * 2 + 1][tmp->coordinate->x * 2 + 1] != 6){
            displayMatrix[tmp->coordinate->y * 2 + 1][tmp->coordinate->x * 2 + 1] = 3;
        }
        int yDif = 0;
        int xDif = 0;
        if(tmp->parent != nullptr){
            yDif = tmp->coordinate->y - tmp->parent->coordinate->y;
            xDif = tmp->coordinate->x - tmp->parent->coordinate->x;
        }
        if(yDif > 0){
            displayMatrix[(yDif + tmp->parent->coordinate->y) * 2][(xDif + tmp->parent->coordinate->x) * 2 + 1] = 5;
        } else if(yDif < 0){
            displayMatrix[(yDif + tmp->parent->coordinate->y) * 2 + 2][(xDif + tmp->parent->coordinate->x) * 2 + 1] = 8;
        }  else if (xDif > 0) {
            displayMatrix[(yDif + tmp->parent->coordinate->y) * 2 + 1][(xDif + tmp->parent->coordinate->x) * 2] = 4;
        } else if (xDif < 0) {
            displayMatrix[(yDif + tmp->parent->coordinate->y) * 2 + 1][(xDif + tmp->parent->coordinate->x) * 2 + 2] = 10;
        }
        tmp = tmp->parent;
    }
    reverse(path.begin(), path.end());
    display();
    return path;
}

//Searches though nodes in the graph and returns the node with the same coordinates or null if none mathch
node *RRT::getNode(coordinate coordinate) {
    for(node * current : graph){
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
        displayMatrix[y*2+1][x*2 +1] = 9;
    }
    cout << endl;
}

//Prints the display matrix
void RRT::display(){
    for(int i = sideSize * 2; i >= 0; i --){
        for(int j = 0; j < (sideSize * 2) + 1; j ++){
            int num = displayMatrix[i][j];
            if(num == 0){
                cout << "   ";
            } else if(num == 1){
                cout << "---";
            } else if(num == 2){
                cout << "|";
            } else if(num == 3){
                cout << " x ";
            } else if(num == 4){
                cout << "→";
            }else if(num == 5){
                cout << " ↑ ";
            }else if(num == 6){
                cout << " S ";
            }else if(num == 7){
                cout << " E ";
            }else if(num == 8){
                cout << " ↓ ";
            }else if(num == 9){
                cout << " # ";
            }else if(num == 10){
                cout << "←";
            }
        }
        cout << endl;
    }
    cout << endl;
}

//Clears everything except the grid from the matrix
void RRT::resetDisplayMatrix(){
    for(int i = 0; i < sideSize * 2 + 1; i ++){
        for(int j = 0; j < sideSize * 2 + 1; j ++){
           displayMatrix[i][j] = emptyDisplayMatrix[i][j];
        }
    }
}


//Clears paths out of the matrix but leave starting, ending and obstacles
void RRT::resetDisplayMatrixPathOnly(){
    for(int i = 0; i < sideSize * 2 + 1; i ++){
        for(int j = 0; j < sideSize * 2 + 1; j ++){
            if(displayMatrix[i][j] != 9 && displayMatrix[i][j] != 6 && displayMatrix[i][j] != 7){
                displayMatrix[i][j] = emptyDisplayMatrix[i][j];
            }
        }
    }
}

bool RRT::areStillOpenSpaces() {
    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            if(visited[i][j] == 0 && obstacles[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}

RRT::~RRT(){
    for(node * del: graph){
        delete del->coordinate;
        delete del;
    }
}
//
//void RRT::updateObstacles() {
//    display();
//    for(int i = 0; i < sideSize; i++){
//        for(int j = 0; j < sideSize; j++){
//            if(obstacles[i][j] != 0){
//                displayMatrix[i*2+1][j*2+1] = 9;
//            }
//        }
//    }
//    cout << "updated" << endl;
//    display();
//}

