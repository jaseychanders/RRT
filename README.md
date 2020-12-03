# Project Summary
RRT is an algorithm used in robotics applications for mapping areas and finding paths from a given start point to a given end point in an unknown area. The process consists of building a tree of connected locations in the unknown field by generating random goal locations, finding the closest node in the tree to that location and then going a certain distance towards that goal and adding a new node to the graph. My version of RRT uses what is called Manhattan distance to find the nearest node which is the distance between two points only using straight lines and 90 degree turns. The result of RRT is a map of the area and a path (not necessarily the shortest) from the starting location to the ending location. For a more detailed description of RRT scroll down to my project proposal.

# Examples
## Full Map 
S represents the starting location, E represents  the ending location, ▢ represents an obstacle and * are nodes in the graph
<img src="https://github.com/jaseychanders/RRT/blob/main/RRT%20Full%20Map.png" width="600">

## Final Path
<img src="https://github.com/jaseychanders/RRT/blob/main/RRT%20Path.png" width="600">

## How to Run
If you are using VS code or a command line g++ complier use the following line to run the code, if you are using an IDE with built in compile functions simply run the code. 

g++ -std=c++11 main.cpp RandomGenerator.cpp RRT.cpp

## Dependencies/System Requirements
There are no dependencies for this code and should be no system requirements

## Team members
None

## Contributors
Thank you so much to Sam Feig for suggesting this algorithm and for the help in planning out this project and debugging it.

## Open Issues and Bugs
None that I am aware of however due to the randomization there are many edge cases that are hard to find/test for. If you find any please let me know.

## Changes from the initial proposal
* Switched to Manhattan distances from Euclidean distances to simplify obstacle avoidance
* Decided to use command line graphis instead of a graphics library due to complications of setting up graphics libraries
* Limited max distance to 1 unit for simplicity
* Did not implement RRT* or Dijkstra’s due to time constraints




#----------------------------------------------------------------------------------------------------------------

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
* Run Dijkstra’s on the tree after it’s been built to find shorter path and compare to RRT’s path

## How my implementation of RRT will work
* First pick starting and ending coordinates
* Specify coordinates where bounds/obstacles exist 
* Specify a percentage of the time that the algorithm should try to approach the goal
* Specify a max travel distance
* Start RRT
  * Generate a random number between 1 and 100
  * If that number is between 1 and the percentage specified above, select the end node as the goal. Otherwise generate a random coordinate within the bounds and select that as the goal. 
  * Find the nearest node currently in the tree to the goal coordinate using Euclidian distances.
  * If the goal is less than the max travel distance from the closet node and the goal coordinates are not in an obstacle. Create a node with the goal coordinates and add it to the tree. Otherwise go the max travel distance from the closet node toward the goal coordinate, check that the desired coordinates are not in an obstacle, create a new node and add it to the tree and set the new node’s parent to the node it is connected to. 
  * If the Goal is within an obstacle add the node at the edge of the obstacle
  * If the Goal node was the end node then the mapping part of the algorithm is complete.
  * When mapping finishes trace the path from the end to the start using the parent pointers. Reverse the path.  

![alt text](https://github.com/jaseychanders/RRT/blob/main/IMG_0085.jpg)
