# Project Proposal

## Overview 
Implement a basic RRT Mapping algorithm. RRT (Rapidly Exploring Random Trees) is an algorithm that efficiently maps an unknown space by incrementally building a space filling tree. 

## Goals
* Implement basic RRT in an open space
* Bound/obstacle detection
* Graphics (visual representation at the end of algorithm)

### Other goals to extend the project if I have time
* Live Graphics (graphics updating as algorithm runs)
* RRT* (more advanced version that guarantees shortest path) 
* Run Dijkstra’s on the graph after it’s been built to find shorter path and compare to RRT’s path

## How my implementation of RRT will work
* First pick starting and ending coordinates
* Specify coordinates where bounds/obstacles exist 
* Specify a percentage of the time that the algorithm should try to approach the goal
* Specify a max travel distance
* Start RRT
  * Generate a random number between 1 and 100
  * If that number is between 1 and the percentage specified above, select the end node as the goal. Otherwise generate a random coordinate within the bounds and select that as the goal. 
  * Find the nearest node currently in the graph to the goal coordinate using Euclidian distances.
  * If the goal is less than the max travel distance from the closet node and the goal coordinates are not in an obstacle. Create a node with the goal coordinates and add it to the graph. Otherwise go the max travel distance from the closet node toward the goal coordinate, check that the desired coordinates are not in an obstacle, create a new node and add it to the graph and set the new node’s parent to the node it is connected to. 
  * If the Goal is within an obstacle add the node at the edge of the obstacle
  * If the Goal node was the end node then the mapping part of the algorithm is complete.
  * When mapping finishes trace the path from the end to the start using the parent pointers. Reverse the path.  

![alt text](https://github.com/jaseychanders/RRT/blob/main/IMG_0085.jpg)
