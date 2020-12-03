//
// Created by Jasey Chanders on 11/27/20.
// CSCI 2275 Final Project
//

//This file runs the RRT (randomly exploring random trees) algorithm

#pragma
#ifndef RRT_RRT_H
#define RRT_RRT_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

//Stores and x,y coordinate
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

//Stores a node in the tree
struct node{
    node * parent = nullptr;
    coordinate * coordinate = nullptr;
    node(node * parent, struct coordinate * coordinate){
        this->parent = parent;
        this->coordinate = coordinate;
    }
};

const int maxDistance = 1; //Max distance you can go in one iteration, can not be changed
const int sideSize = 25; // Length of a side of the field, can be changed

class RRT {
    private:
        int obstacles[sideSize][sideSize]{}; //Stores the obstacles on the field
        int visited[sideSize][sideSize]{}; //Stores the locations that have a node in them
        bool endNodeFound = false;
        vector<node*> tree; //Stores the nodes that have been added to the tree
        node * getNextNode(coordinate * coordinate); //Returns the next node to add to the tree
        coordinate getNextGoalCoordinate(coordinate * endCoordinate);//Returns an x,y point that is the goal for this iteration
        node * getNearestNode(coordinate goalCoordinate); // Returns the nearest node to the goal coordinate
        coordinate *coordinateForNewNode(node * closetNode, coordinate goalCoordinate);//Returns the coordinate for the next node to be added
        int getManhattanDist(double x1, double y1, double x2, double y2);//Returns the distance between two x,y points using strait lines and 90 degree angles
        bool coordinateIsOpen(int x, int y); // Checks if a coordinate does not have an obstacles and has not already been added to the tree
        void printPath(node * endNode, int startX, int startY, int endX, int endY); //Prints the final path
        node * getNode(coordinate coordinate);//Returns a node in the tree from it's x,y coordinate
        void display(int startX, int startY, int endX, int endY);//Prints the field
public:
    RRT();
    ~RRT();
    void runRRT(int startX, int startY, int endX, int endY); //main function
    void inputObstacles(string csvOfObstacles);//adds obstacles to the graph
};


#endif //RRT_RRT_H
