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
    int y;
    int x;
    coordinate(int x, int y){
        this->y = y;
        this->x = x;
    }

    bool operator == (const coordinate& coordinate){
        return this->y == coordinate.y && this->x == coordinate.x;
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

const int maxDistance = 1;
const int sideSize = 25;

class RRT {
    private:

        int obstacles[sideSize][sideSize]{};
        int visited[sideSize][sideSize]{};
        bool endNodeFound = false;
        vector<node*> graph;
        node * getNextNode(coordinate * coordinate);
        coordinate *coordinateForNewNodeManhattan(node * closetNode, coordinate goalCoordinate);
        int getManhattanDist(double x1, double y1, double x2, double y2);
        node * getNearestNode(coordinate goalCoordinate);
        bool coordinateIsOpen(int x, int y);
        coordinate getNextGoalCoordinate(coordinate * endCoordinate);
        vector<coordinate> printPath(node * endNode, int startX, int startY, int endX, int endY);
        node * getNode(coordinate coordinate);
        bool areStillOpenSpaces();


public:
    RRT();
    ~RRT();
    vector<coordinate> runRRT(int startX, int startY, int endX, int endY);
    void inputObstacles(string csvOfObstacles);
    void display(int startX, int startY, int endX, int endY);


};


#endif //RRT_RRT_H
