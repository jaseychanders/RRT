//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"

using namespace std;

int main(){
    RRT rrt;
    vector<coordinate> path = rrt.runRRT(0,0,4,4);
    for(coordinate coordinate : path){
        cout << "{" << coordinate.row << ", " << coordinate.column << "} ";
    }
    cout << endl;
}