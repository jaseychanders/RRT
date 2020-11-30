//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"

using namespace std;

int main(){
    RRT rrt;
    vector<coordinate> path = rrt.runRRT(0,0,9,9);
    for(coordinate coordinate : path){
        cout << "{" << coordinate.column << ", " << coordinate.row << "} ";
    }
    cout << endl;
}