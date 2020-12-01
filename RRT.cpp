//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"
#include <math.h>
#include <sstream>
#include <iostream>

using namespace std;

vector<coordinate> RRT::runRRT(int startRow, int startColumn, int endRow, int endColumn) {

    srand(time(nullptr));
    node * startNode = new node(nullptr, nullptr);
    startNode->coordinate = new coordinate(startRow, startColumn);
    displayMatrix[startRow*2+1][startColumn*2+1] = 6;
    displayMatrix[endRow*2+1][endColumn*2+1] = 7;

    display();

    graph.push_back(startNode);
    visited[0][0] = 1;

    coordinate * endCoordinate = new coordinate(endRow, endColumn);

    while(!endNodeFound){
        node * nextNode = getNextNode(endCoordinate);
        if(nextNode->coordinate != nullptr){
            if(nextNode->coordinate->row == endCoordinate->row && nextNode->coordinate->column == endCoordinate->column){
                endNodeFound = true;
            }

            if(nextNode->coordinate != nullptr){
                graph.push_back(nextNode);
               // cout << nextNode->coordinate->column << " " << nextNode->coordinate->row << " parent " << nextNode->parent->coordinate->column << " " << nextNode->parent->coordinate->row << endl;
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

            }
        }
        display();

    }

    return printPath(getNode(*endCoordinate));
}

node * RRT::getNextNode(coordinate * endCoordinate) {
    coordinate goalCoordinate = getNextGoalCoordinate(endCoordinate);
    node * nearestNode = getNearestNode(goalCoordinate);
    coordinate * newCoordinate = coordinateForNewNodeManhattan(nearestNode, goalCoordinate);
    node * newNode = new node (nullptr, nullptr);
    if(coordinateIsOpen(*newCoordinate)){
        newNode->parent = nearestNode;
        newNode->coordinate = newCoordinate;
    }
    return newNode;
}

coordinate RRT::getNextGoalCoordinate(coordinate * endCoordinate) {
    double goToGoal = rand() & 100;

    int row;
    int column;

    if(goToGoal <= 2){
        row = endCoordinate->row;
        column = endCoordinate->column;
    } else {
        row = rand() % size;
        column = rand() % size;
    }

    return coordinate(row, column);
}

node *RRT::getNearestNode(coordinate goalCoordinate) {
    node * nearestNode = nullptr;
    double nearest = INT_MAX;
    for(node * current : graph){
        int manhattanDistToGoal = getManhattanDist(current->coordinate->column, current->coordinate->row, goalCoordinate.column, goalCoordinate.row);
        int rowDif = goalCoordinate.row - current->coordinate->row;
        int columnDif = goalCoordinate.column - current->coordinate->column;
        bool notBlocked = true;
        if(columnDif >=0){
            for(int i = 1; i <= columnDif; i++){
                if (obstacles[current->coordinate->row][current->coordinate->column+ i] != 0){
                    notBlocked = false;
                }
            }
        } else {
            for(int i = -1; i >= columnDif; i--){
                if (obstacles[current->coordinate->row][current->coordinate->column+ i] != 0){
                    notBlocked = false;
                }
            }
        }

        if(rowDif >=0){
            for(int i = 1; i <= rowDif; i++){
                if (obstacles[current->coordinate->row +i][goalCoordinate.column] != 0){
                    notBlocked = false;
                }
            }
        } else {
            for(int i = -1; i >= rowDif; i--){
                if (obstacles[current->coordinate->row +i][goalCoordinate.column] != 0){
                    notBlocked = false;
                }
            }
        }


        if(nearestNode == nullptr){
            nearestNode = current;
            nearest = manhattanDistToGoal;
        } else {
            if(notBlocked && manhattanDistToGoal < nearest){
                nearestNode = current;
                nearest = manhattanDistToGoal;
            }
        }
    }

    return nearestNode;
}

coordinate *RRT::coordinateForNewNodeManhattan(node *closetNode, coordinate coordinate) {
    double manhattanDistance = getManhattanDist((closetNode->coordinate->column), (closetNode->coordinate->row), coordinate.column,  coordinate.row);

    if (manhattanDistance <= maxDistance){
        return new struct coordinate(coordinate.row, coordinate.column);
    } else {
        struct coordinate * bestCoordinate = new struct coordinate(0,0);
        int shortestManhattanDist = INT_MAX;
        //Square above
        int topSquareDist = getManhattanDist((closetNode->coordinate->column), (closetNode->coordinate->row + maxDistance), coordinate.column,coordinate.row);
        int rightSquareDist = getManhattanDist((closetNode->coordinate->column + maxDistance), (closetNode->coordinate->row), coordinate.column, coordinate.row);
        int bottomSquareDist = getManhattanDist((closetNode->coordinate->column), (closetNode->coordinate->row-maxDistance), coordinate.column, coordinate.row);
        int leftSquareDist = getManhattanDist((closetNode->coordinate->column -maxDistance), (closetNode->coordinate->row), coordinate.column, coordinate.row);

        if(topSquareDist < shortestManhattanDist){
            shortestManhattanDist = topSquareDist;
            bestCoordinate->column = closetNode->coordinate->column;
            bestCoordinate->row = closetNode->coordinate->row + maxDistance;
        } else if (rightSquareDist < shortestManhattanDist){
        //Square to the right
            shortestManhattanDist = rightSquareDist;
            bestCoordinate->column = closetNode->coordinate->column + maxDistance;
            bestCoordinate->row = closetNode->coordinate->row;
        } else if (bottomSquareDist < shortestManhattanDist){
        //Square below
            shortestManhattanDist = bottomSquareDist;
            bestCoordinate->column = closetNode->coordinate->column;
            bestCoordinate->row = closetNode->coordinate->row - maxDistance;
        } else if ( leftSquareDist < shortestManhattanDist){
        //Square to the left
            shortestManhattanDist = leftSquareDist;
            bestCoordinate->column = closetNode->coordinate->column - maxDistance;
            bestCoordinate->row = closetNode->coordinate->row;
        }

        return bestCoordinate;
    }
}

int RRT::getManhattanDist(double column1, double row1, double column2, double row2){
    return (abs(column2 - column1) + abs(row2 - row1));
}



bool RRT::coordinateIsOpen(coordinate coordinate) {
    bool hasBeenVisited = visited[coordinate.row][coordinate.column] == 0;
    bool isOpen = obstacles[coordinate.row][coordinate.column] != 1;
    return hasBeenVisited && isOpen;
}

vector<coordinate> RRT::printPath(node * endNode) {
    resetDisplayMatrixPathOnly();
    vector<coordinate> path;
    node * tmp = endNode;
    while(tmp != nullptr){
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

node *RRT::getNode(coordinate coordinate) {
    for(node * current : graph){
        if (*current->coordinate == coordinate){
            return current;
        }
    }
    return nullptr;
}

//The string to be passed in is formatted (x1,y1;x2,y2;)
void RRT::inputObjects(string csvOfObstacles){
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
        displayMatrix[row*2+1][column*2 +1] = 9;
    }

}

void RRT::display(){
    for(int i = size*2; i >= 0; i --){
        for(int j = 0; j < (size*2)+1; j ++){
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

void RRT::resetDisplayMatrix(){
    for(int i = 0; i < size*2+1; i ++){
        for(int j = 0; j < size*2+1; j ++){
           displayMatrix[i][j] = emptyDisplayMatrix[i][j];
        }
    }
}

void RRT::resetDisplayMatrixPathOnly(){
    for(int i = 0; i < size*2+1; i ++){
        for(int j = 0; j < size*2+1; j ++){
            if(displayMatrix[i][j] != 9 && displayMatrix[i][j] != 6 && displayMatrix[i][j] != 7){
                displayMatrix[i][j] = emptyDisplayMatrix[i][j];
            }
        }
    }
}