//
// Created by Jasey Chanders on 11/27/20.
//

#include "RRT.h"

using namespace std;

int main(){
    RRT rrt;

    rrt.display();

    rrt.inputObjects("2,4;2,5;3,4;3,5;");

    vector<coordinate> path = rrt.runRRT(0,0,4,4);
    for(coordinate coordinate : path){
        cout << "{" << coordinate.column << ", " << coordinate.row << "} ";
    }
    cout << endl;

}