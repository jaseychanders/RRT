//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"

using namespace std;

int main(){
    RRT rrt;


    rrt.resetDisplayMatrix();
    rrt.inputObjects("2,3;2,4;3,3;3,4;");

    vector<coordinate> path = rrt.runRRT(0,0,7,9);
//    for(coordinate coordinate : path){
//     //   cout << "{" << coordinate.column << ", " << coordinate.row << "} ";
//    }
    cout << endl;
}