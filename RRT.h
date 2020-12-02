//
// Created by Jasey Chanders on 11/27/20.
//
#pragma
#ifndef RRT_RRT_H
#define RRT_RRT_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct coordinate{
    int row;
    int column;
    coordinate(int row, int column){
        this->row = row;
        this->column = column;
    }
    bool operator < (const coordinate& coordinate){
        int thisHypotenuse = sqrt((this->row * this->row) + (this->column * this->column));
        int coordinateHypotenuse = sqrt((coordinate.row * coordinate.row) + (coordinate.column * coordinate.column));
        return thisHypotenuse < coordinateHypotenuse;
    }
    bool operator == (const coordinate& coordinate){
        return this->row == coordinate.row && this->column == coordinate.column;
    }
};


struct node{
    node * parent = nullptr;
    coordinate * coordinate = nullptr;
    node(node * parent, struct coordinate * coordinate){
        this->parent = parent;
        this->coordinate = coordinate;
    }
};


class RRT {
    private:
        int maxDistance = 1;
        int size = 10;
        int obstacles[10][10]{};
        int visited[10][10]{};
        int emptyDisplayMatrix[21][21] = {{2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}, {2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2,0,2},
                                          {2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}};
        int displayMatrix[21][21]{};
        bool endNodeFound = false;
        bool goalUnreachable = false;
        vector<node*> graph;
        node * getNextNode(coordinate * coordinate);
        coordinate *coordinateForNewNodeManhattan(node * closetNode, coordinate coordinate);
        int getManhattanDist(double column1, double row1, double column2, double row2);
        node * getNearestNode(coordinate goalCoordinate);
        bool coordinateIsOpen(coordinate coordinate);
        coordinate getNextGoalCoordinate(coordinate * endCoordinate);
        vector<coordinate> printPath(node * endNode);
        node * getNode(coordinate coordinate);
        void resetDisplayMatrixPathOnly();



public:
    vector<coordinate> runRRT(int startRow, int startColumn, int endRow, int endColumn);
    void inputObjects(string csvOfObstacles);
    void display();
    void resetDisplayMatrix();
    int * getObstacles();


};


#endif //RRT_RRT_H
