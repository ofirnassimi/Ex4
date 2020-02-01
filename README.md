# Shortest Path - Milestone 2
This program gets a Graph, finds the shortest path from an initial state to a goal state and prints this path (by directions - up, down, left, right) and the cost of it
# Collaborators
Inbar Horesh and Ofir Nassimi
# Installation
clone this repository
git clone https://github.com/ofirnassimi/Ex4.git
# Input
Our problem is a graph, and in this case, a matrix of numbers. The matrix will be add line by line, where every number in this line represents the cost f geting to this place in the matrix.
Under the matrix, there will be another 3 lines. The first one will represent the initial state - the place in the matrix where we start our path.
Then we have the place of the goal state and in the last line we have the word "end" to confirm we end add the matrix.
# Output
The client will get the shortest path from the initial state to the goal state. First it shows the direction and then, in brackets, the cost of getting to this new position.
# How to run
First open the command line.
Then write: g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
# Link to GitHub
https://github.com/ofirnassimi/Ex4
