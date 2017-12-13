/* Your code here! */

#ifndef MAZE_H
#define MAZE_H

#include <stack>
#include <map>
#include <queue>
#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"

using namespace cs225;


class SquareMaze
{
	public:
        //no parameter default constructor
        SquareMaze(); 
        
		//makes a new square maze of the given height and width
		void makeMaze(int width, int height);

        //This uses your representation of the maze to determine
        // whether it is possible to travel in the given direction from the square at coordinates (x,y).
		bool canTravel(int x, int y, int dir) const;

		//Sets whether or not the specified wall exists
		void setWall(int x, int y, int dir, bool exists);

		//Solves this SquareMaze
		vector<int> solveMaze();

		//Draws the maze without the solution
		PNG * drawMaze() const;

        //This function calls drawMaze, then solveMaze; 
        //it modifies the PNG from drawMaze to show the solution vector and the exit.
        PNG * drawMazeWithSolution();
        
    private: 
        int width;
        int height;
        int size;

        vector<bool> downwall;
        vector<bool> rightwall;

};


#endif 









