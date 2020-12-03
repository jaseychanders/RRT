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
    int y;
    int x;
    coordinate(int x, int y){
        this->y = y;
        this->x = x;
    }
//    bool operator < (const coordinate& coordinate){
//        int thisHypotenuse = sqrt((this->y * this->y) + (this->x * this->x));
//        int coordinateHypotenuse = sqrt((coordinate.y * coordinate.y) + (coordinate.x * coordinate.x));
//        return thisHypotenuse < coordinateHypotenuse;
//    }
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


class RRT {
    private:
        int maxDistance;
        int sideSize;
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
        vector<node*> graph;
        node * getNextNode(coordinate * coordinate);
        coordinate *coordinateForNewNodeManhattan(node * closetNode, coordinate goalCoordinate);
        int getManhattanDist(double x1, double y1, double x2, double y2);
        node * getNearestNode(coordinate goalCoordinate);
        bool coordinateIsOpen(int x, int y);
        coordinate getNextGoalCoordinate(coordinate * endCoordinate);
        vector<coordinate> printPath(node * endNode);
        node * getNode(coordinate coordinate);
        void resetDisplayMatrixPathOnly();
        bool areStillOpenSpaces();


public:
    RRT();
    ~RRT();
    vector<coordinate> runRRT(int startX, int startY, int endX, int endY);
    void inputObstacles(string csvOfObstacles);
    void display();
    void resetDisplayMatrix();
   // void updateObstacles();


};


#endif //RRT_RRT_H
