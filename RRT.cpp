//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include <math.h>

vector<coordinate> RRT::runRRT(int startRow, int startColumn, int endRow, int endColumn) {

    srand(time(nullptr));
    node * startNode = new node(nullptr, nullptr);
    startNode->coordinate = new coordinate(startRow, startColumn);
    graph.push_back(startNode);
    coordinate * endCoordinate = new coordinate(endRow, endColumn);

    while(!endNodeFound){
        node * nextNode = getNextNode(endCoordinate);
        if(nextNode->coordinate != nullptr){
            if(nextNode->coordinate->row == endCoordinate->row && nextNode->coordinate->column == endCoordinate->column){
                endNodeFound = true;
            }

            if(nextNode->coordinate != nullptr){
                graph.push_back(nextNode);
                visited[nextNode->coordinate->row][nextNode->coordinate->column] = 1;
            }
        }

    }

    return getPath(getNode(*endCoordinate));
}

node * RRT::getNextNode(coordinate * endCoordinate) {
    coordinate goalCoordinate = getNextGoalCoordinate(endCoordinate);
    node * nearestNode = getNearestNode(goalCoordinate);
    coordinate * newCoordinate = coordinateForNewNode(nearestNode, goalCoordinate);
    node * newNode = new node (nullptr, nullptr);
    if(coordinateIsOpen(goalCoordinate)){
        newNode->parent = nearestNode;
        newNode->coordinate = newCoordinate;
    }
    return newNode;
}

coordinate RRT::getNextGoalCoordinate(coordinate * endCoordinate) {
    int goToGoal = rand() & 10;

    int row;
    int column;

    if(goToGoal <= 2){
        row = endCoordinate->row;
        column = endCoordinate->column;
    } else {
        row = rand() % size;
        column = rand() % size;
    }

  //  cout << row << " " << column << endl;

    return coordinate(row, column);
}

node *RRT::getNearestNode(coordinate coordinate) {
    node * nearestNode = nullptr;
    for(node * current : graph){
        if(nearestNode == nullptr){
            nearestNode = current;
        } else {
            if(*current->coordinate < coordinate){
                nearestNode = current;
            }
        }
    }

    return nearestNode;
}


coordinate *RRT::coordinateForNewNode(node * closetNode, coordinate coordinate) {
    double hypotenuse = sqrt(pow((coordinate.row - closetNode->coordinate->row), 2) + pow((coordinate.column - closetNode->coordinate->column), 2));
    double sin = (coordinate.row - closetNode->coordinate->row) / hypotenuse;
    double cos = (coordinate.column - closetNode->coordinate->column) / hypotenuse;

    if (hypotenuse <= maxDistance){
        return new struct coordinate(coordinate.row, coordinate.column);
    } else {
        int row = sin * maxDistance;
        int column = cos * maxDistance;
        cout << row << " " << column << endl;
        return new struct coordinate(row, column);
    }
}


bool RRT::coordinateIsOpen(coordinate coordinate) {
    return visited[coordinate.row][coordinate.column] == 0;
}

vector<coordinate> RRT::getPath(node * endNode) {

    vector<coordinate> path;
    node * tmp = endNode;
    while(tmp != nullptr){
        path.push_back(*tmp->coordinate);
        tmp = tmp->parent;
    }
    reverse(path.begin(), path.end());

    return path;
}

node *RRT::getNode(coordinate coordinate) {
    for(node * current : graph){
        if (*current->coordinate == coordinate){
            return current;
        }
    }
    return nullptr;
}
