//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"

using namespace std;

int main(){
    RRT rrt;


    rrt.inputObjects("2,4;2,5;3,4;3,5;4,4;4,5;5,4;5,5;6,1;6,2;7,1;7,2;8,1;8,2;");

    vector<coordinate> path = rrt.runRRT(0,0,9,9);
    for(coordinate coordinate : path){
        cout << "{" << coordinate.column << ", " << coordinate.row << "} ";
    }
    cout << endl;
}