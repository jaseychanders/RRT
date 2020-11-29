//
// Created by Jasey Chanders on 11/27/20.
//

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
        int maxDistance = 2;
        int size = 5;
        int obstacles[5][5] = {{0,0,0,0},{0,0,1,1,0}, {0,0,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0}};
        int visited[5][5] = {{0,0,0,0},{0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}};
        bool endNodeFound = false;
        vector<node*> graph;
        node * getNextNode(coordinate * coordinate);
        coordinate *coordinateForNewNode(node * closetNode, coordinate coordinate);
        node * getNearestNode(coordinate goalCoordinate);
        bool coordinateIsOpen(coordinate coordinate);
        coordinate getNextGoalCoordinate(coordinate * endCoordinate);
        vector<coordinate> getPath(node * endNode);
        node * getNode(coordinate coordinate);

    public:
    vector<coordinate> runRRT(int startRow, int startColumn, int endRow, int endColumn);


};


#endif //RRT_RRT_H
