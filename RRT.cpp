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
vector<coordinate> RRT::runRRT(int startRow, int startColumn, int endRow, int endColumn) {

    srand(time(nullptr));
    cout << sideSize << endl;
    //Inputs start and end coordinates
    node * startNode = new node(nullptr, nullptr);
    startNode->coordinate = new coordinate(startRow, startColumn);
    displayMatrix[startRow*2+1][startColumn*2+1] = 6;
    displayMatrix[endRow*2+1][endColumn*2+1] = 7;

    display();

    //Add start node to graph
    graph.push_back(startNode);
    visited[startNode->coordinate->row][startNode->coordinate->column] = 1;

    coordinate * endCoordinate = new coordinate(endRow, endColumn);

    int numIterations = 0;

    //Loop until end node is found or you have gone though enough iterations that their isn't a path to the end
    while(!endNodeFound && numIterations < pow(sideSize, 5)){
        node * nextNode = getNextNode(endCoordinate);

        //Set the flag if this node is the end
        if(nextNode->coordinate != nullptr){
            if(nextNode->coordinate->row == endCoordinate->row && nextNode->coordinate->column == endCoordinate->column){
                endNodeFound = true;
            } else if (getManhattanDist(startNode->coordinate->column, startNode->coordinate->row, endCoordinate->column, endCoordinate->row) == 1){
                endNodeFound = true;
            }

            // If we have a new node add it to the graph and the display matrix
            if(nextNode->coordinate != nullptr){
                graph.push_back(nextNode);
                visited[nextNode->coordinate->row][nextNode->coordinate->column] = 1;
                if(displayMatrix[nextNode->coordinate->row*2+1][nextNode->coordinate->column*2+1] != 7 && displayMatrix[nextNode->coordinate->row*2+1][nextNode->coordinate->column*2+1] != 6){
                    displayMatrix[nextNode->coordinate->row*2+1][nextNode->coordinate->column*2+1] = 3;
                }
                int rowDif = nextNode->coordinate->row - nextNode->parent->coordinate->row;
                int columnDif = nextNode->coordinate->column - nextNode->parent->coordinate->column;
                if(rowDif > 0){
                    displayMatrix[(rowDif + nextNode->parent->coordinate->row)*2][(columnDif + nextNode->parent->coordinate->column)*2+1] = 5;
                } else if(rowDif < 0){
                    displayMatrix[(rowDif + nextNode->parent->coordinate->row)*2+2][(columnDif + nextNode->parent->coordinate->column)*2+1] = 8;
                }  else if (columnDif > 0) {
                    displayMatrix[(rowDif + nextNode->parent->coordinate->row)*2+1][(columnDif + nextNode->parent->coordinate->column)*2] = 4;
                } else if (columnDif < 0) {
                    displayMatrix[(rowDif + nextNode->parent->coordinate->row)*2+1][(columnDif + nextNode->parent->coordinate->column)*2+2] = 10;
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
    cout << goalCoordinate.column << " " << goalCoordinate.row << endl;
    node * nearestNode = getNearestNode(goalCoordinate);
    node * newNode = new node (nullptr, nullptr);

    if(nearestNode->coordinate != nullptr){
        cout << nearestNode->coordinate->column << " " << nearestNode->coordinate->row << endl;
        coordinate * newCoordinate = coordinateForNewNodeManhattan(nearestNode, goalCoordinate);
        if(newCoordinate->row != -1 && coordinateIsOpen(newCoordinate->column, newCoordinate->row)){
            newNode->parent = nearestNode;
            newNode->coordinate = newCoordinate;
        }
    }

    return newNode;
}

// Randomly generates a goal coordinate
coordinate RRT::getNextGoalCoordinate(coordinate * endCoordinate) {
    double goToGoal = rand() & 100;

    int row;
    int column;

    if(goToGoal <= 10){
        row = endCoordinate->row;
        column = endCoordinate->column;
    } else {
        row = rand() % sideSize;
        column = rand() % sideSize;
    }
    if(coordinateIsOpen(column, row)){
        return coordinate(row, column);
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
        int manhattanDistToGoal = getManhattanDist(current->coordinate->column, current->coordinate->row, goalCoordinate.column, goalCoordinate.row);
        bool blocked = true;
        //If any of the squares adjacent to the current node are open
        if(coordinateIsOpen(current->coordinate->row, current->coordinate->column + 1) ||
            coordinateIsOpen(current->coordinate->row, current->coordinate->column - 1) ||
            coordinateIsOpen(current->coordinate->row + 1, current->coordinate->column) ||
            coordinateIsOpen(current->coordinate->row - 1, current->coordinate->column))
        {
            blocked = false;
        }

        //If our current node is closer than the previous ones replace the shortest with this node
        if(!blocked && nearestNode->coordinate == nullptr){
            nearestNode = current;
            nearest = manhattanDistToGoal;
        } else {
            if(!blocked && manhattanDistToGoal < nearest){
                nearestNode = current;
                nearest = manhattanDistToGoal;
            }
        }
    }

    return nearestNode;
}

// Finds the coordinate for the next node using the closest node and going one square closer to the goal
coordinate *RRT::coordinateForNewNodeManhattan(node *closetNode, coordinate goalCoordinate) {
    double manhattanDistance = getManhattanDist((closetNode->coordinate->column), (closetNode->coordinate->row), goalCoordinate.column, goalCoordinate.row);

    if (manhattanDistance <= maxDistance){ // Goal coordinate is only one unit away
        return new coordinate(goalCoordinate.row, goalCoordinate.column);
    } else {
        coordinate * bestCoordinate = new coordinate(-1,-1);
        int shortestManhattanDist = INT_MAX;
        //Gets the distances from the four squares on each side of the nearest node
        int topSquareDist = -1;
        int rightSquareDist = -1;
        int bottomSquareDist = -1;
        int leftSquareDist = -1;

        if (coordinateIsOpen(closetNode->coordinate->column, closetNode->coordinate->row + 1)) {
            topSquareDist = getManhattanDist((closetNode->coordinate->column), (closetNode->coordinate->row + 1),
                                             goalCoordinate.column, goalCoordinate.row);
        }
        if (coordinateIsOpen(closetNode->coordinate->column + 1, closetNode->coordinate->row)) {
            rightSquareDist = getManhattanDist((closetNode->coordinate->column + 1), (closetNode->coordinate->row),
                                               goalCoordinate.column, goalCoordinate.row);
        }
        if (coordinateIsOpen(closetNode->coordinate->column, closetNode->coordinate->row - 1)) {
            bottomSquareDist = getManhattanDist((closetNode->coordinate->column), (closetNode->coordinate->row - 1),
                                                goalCoordinate.column, goalCoordinate.row);
        }
        if (coordinateIsOpen(closetNode->coordinate->column - 1, closetNode->coordinate->row)) {
            leftSquareDist = getManhattanDist((closetNode->coordinate->column - 1), (closetNode->coordinate->row),
                                              goalCoordinate.column, goalCoordinate.row);
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
                    bestCoordinate->column = closetNode->coordinate->column;
                    bestCoordinate->row = closetNode->coordinate->row + 1;
                }
            } else if (!rightChecked && (whichFirst == 1 || hasLoopedOnce)) {
                rightChecked = true;
                if (rightSquareDist != -1 && rightSquareDist < shortestManhattanDist) {
                    //Square to the right
                    shortestManhattanDist = rightSquareDist;
                    bestCoordinate->column = closetNode->coordinate->column + maxDistance;
                    bestCoordinate->row = closetNode->coordinate->row;
                }
            } else if (!bottomChecked && (whichFirst == 2 || hasLoopedOnce)) {
                bottomChecked = true;
                if (bottomSquareDist != -1 && bottomSquareDist < shortestManhattanDist) {
                    //Square below
                    shortestManhattanDist = bottomSquareDist;
                    bestCoordinate->column = closetNode->coordinate->column;
                    bestCoordinate->row = closetNode->coordinate->row - maxDistance;
                }
            } else if (!leftChecked && (whichFirst == 3 || hasLoopedOnce)) {
                leftChecked = true;
                if (leftSquareDist != -1 && leftSquareDist < shortestManhattanDist) {
                    //Square to the left
                    shortestManhattanDist = leftSquareDist;
                    bestCoordinate->column = closetNode->coordinate->column - maxDistance;
                    bestCoordinate->row = closetNode->coordinate->row;
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
int RRT::getManhattanDist(double column1, double row1, double column2, double row2){
    return (abs(column2 - column1) + abs(row2 - row1));
}


// Checks if a coordinate hasn't been visited and doesn't have an obstacle
bool RRT::coordinateIsOpen(int column, int row) {
    if(column < sideSize && column > -1 && row < sideSize && row > -1){
        bool hasBeenVisited = visited[row][column] == 0;
        bool isOpen = obstacles[row][column] != 1;
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

        if(displayMatrix[tmp->coordinate->row*2+1][tmp->coordinate->column*2+1] != 7 && displayMatrix[tmp->coordinate->row*2+1][tmp->coordinate->column*2+1] != 6){
            displayMatrix[tmp->coordinate->row*2+1][tmp->coordinate->column*2+1] = 3;
        }
        int rowDif = 0;
        int columnDif = 0;
        if(tmp->parent != nullptr){
            rowDif = tmp->coordinate->row - tmp->parent->coordinate->row;
            columnDif = tmp->coordinate->column - tmp->parent->coordinate->column;
        }
        if(rowDif > 0){
            displayMatrix[(rowDif + tmp->parent->coordinate->row)*2][(columnDif + tmp->parent->coordinate->column)*2+1] = 5;
        } else if(rowDif < 0){
            displayMatrix[(rowDif + tmp->parent->coordinate->row)*2+2][(columnDif + tmp->parent->coordinate->column)*2+1] = 8;
        }  else if (columnDif > 0) {
            displayMatrix[(rowDif + tmp->parent->coordinate->row)*2+1][(columnDif + tmp->parent->coordinate->column)*2] = 4;
        } else if (columnDif < 0) {
            displayMatrix[(rowDif + tmp->parent->coordinate->row)*2+1][(columnDif + tmp->parent->coordinate->column)*2+2] = 10;
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
    string rowRaw;
    string columnRaw;
    int row;
    int column;
    while(getline(obstaclesSS, coordinate, ';')){
        coordinateSS.clear();
        coordinateSS << coordinate;
        getline(coordinateSS, columnRaw, ',');
        getline(coordinateSS, rowRaw);
        row = stoi(rowRaw);
        column = stoi(columnRaw);

        obstacles[row][column] = 1;
        cout << "Adding " << column << ", " << row << endl;
        displayMatrix[row*2+1][column*2 +1] = 9;
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

void RRT::updateObstacles() {
    display();
    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            if(obstacles[i][j] != 0){
                displayMatrix[i*2+1][j*2+1] = 9;
            }
        }
    }
    cout << "updated" << endl;
    display();
}

