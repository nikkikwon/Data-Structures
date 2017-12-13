/* Your code here! */
#include <sys/time.h>
#include "maze.h"
using namespace cs225;
using namespace std;

/**
*  No-parameter default constructor. It creates an empty maze by initializing private variables.
**/
SquareMaze::SquareMaze()
{
  width = 0;
  height = 0;  
  size = 0;
}

/**
*  Makes a new SquareMaze of the given height and width. It only needs to store right and down walls 
* in order to make the entire maze. Briefly, it randomly selects right or down wall and remove it to create a maze. 
**/
void SquareMaze::makeMaze(int width, int height)
{
    DisjointSets dset;

    this->height = height;
    this->width = width;
    this -> size = width * height;

    for(int i = 0; i < size; i++)
    {
        downwall.push_back(true);
        rightwall.push_back(true);
    }

    dset.addelements(size);

    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec);

    for (int i = 0; i < size - 1;)
    {
        int removex = rand() % width;
        int removey = rand() % height;

        if(rand() % 2)
        {
            if (removex < width - 1)
            {
                if (dset.find(removey * width + removex) != dset.find(removey * width + removex + 1))
                {
                    rightwall[removey * width + removex] = false;
                    dset.setunion(removey * width + removex, removey * width + (removex + 1));
                    i++;
                }

            }   
        }
        else if (removey < height - 1)
        {   
            if (dset.find(removey * width + removex) != dset.find((removey + 1) * width + removex))
            {
                downwall[removey * width + removex] = false;
                dset.setunion(removey * width + removex, (removey + 1) * width + removex);
                i++;
            }
        } 
    }
}

/**
*  This uses the maze to determine whether it is possible to travel 
*in the given direction from the square at coordinates (x,y).
**/
bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if(dir == 0 && x != width-1)
    {
        if (rightwall [y * width + x] == false)
            return true;
        return false;
    }
	
    if(dir == 1 && y != height-1)
    {
        if (downwall[y*width + x] == false)
            return true;
        return false;
    }

    if(dir == 2 && x != 0)
    {
        if (rightwall[y*width + x-1] == false)
            return true;
        return false;
    }

	if(dir == 3 && y != 0)
    {
        if (downwall[(y-1)*width + x] == false)
            return true;
        return false;
    } 
	return false;
}
/**
 * Determine whether or not the specified wall exists with parameter int dir.
 **/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{

    if (dir == 0)
    {
        rightwall[y * width + x] = exists;
    }
    
    else if (dir == 1)
    {
        downwall[y * width + x] = exists;
    }
}

/**
 * Solves this SquareMaze using BFS**/
vector<int> SquareMaze::solveMaze()
{
    vector<int> ret;
    vector<int> data;
    vector<int> visited;
    queue<int> q;
    map<int, int> parent;
    int v;

    for(int i = 0; i < size; i++)
    {
        visited.push_back(0);
    }   

    visited[0] = 1;
    q.push(0);

    while(!q.empty())
    {
        v  = q.front();
        q.pop();

        if(v / width == height - 1)
        {
            data.push_back(v % width);
        }

        int x = v % width;
        int y = v / width;
        
        if(canTravel(x, y, 0) && visited[v + 1] == 0)
        {
            q.push(v + 1);
            visited[v + 1] = 1;
            parent.insert( pair <int,int> (v + 1, v));

        }
        
        if(canTravel(x, y, 1) && visited[v + width] == 0)
        {
            q.push(v + width);
            visited[v + width] = 1;
            parent.insert( pair <int,int> (v + width, v));
        }
        
        if(canTravel(x, y, 2) && visited[v - 1] == 0)
        {
            q.push(v - 1);
            visited[v - 1] = 1;
            parent.insert(pair <int,int> (v - 1, v));
        }
        
        if(canTravel(x, y, 3) && visited[v - width] == 0)
        {
            q.push(v - width);
            visited[v - width] = 1;
            parent.insert(pair <int,int> (v - width, v));
        }
    }

    vector<int> temp;
    int path = width * (height - 1) + data[width - 1];

    while(path)
    {
        int temp2 = parent[path];

        if (path - 1 == temp2)
        {
            temp.push_back(0);
        }

        else if(path - temp2 == width)
        {
            temp.push_back(1);
        }

        else if (path + 1 == temp2)
        {
            temp.push_back(2);
        }

        else 
        {
        temp.push_back(3);
        }

        path = temp2;
    }

    while (!temp.empty())
    {
        ret.push_back(temp.back());
        temp.pop_back();
    }
  
    return ret;
}

/**
 * Draws the maze without the solution. An empty maze with entrance not colored black
 **/
PNG * SquareMaze::drawMaze() const
{
    PNG * ret = new PNG(width * 10 + 1 , height * 10 + 1);

    for (int i = 0; i < width * 10 + 1; i++ )
    {
        (*ret).getPixel(i, 0) -> h = 0;
        (*ret).getPixel(i, 0) -> s = 0;
        (*ret).getPixel(i, 0) -> l = 0;
        (*ret).getPixel(i, 0) -> a = 1;
    }

    for (int i = 0; i < width * 10 + 1; i++)
    {
        (*ret).getPixel (0, i) -> h = 0;
        (*ret).getPixel (0, i) -> s = 0;
        (*ret).getPixel (0, i) -> l = 0;
        (*ret).getPixel (0, i) -> a = 1;
    }

     for (int i = 0; i < width * 10 + 1; i++)
    {
        (*ret).getPixel (width * 10, i) -> h = 0;
        (*ret).getPixel (width * 10, i) -> s = 0;
        (*ret).getPixel (width * 10, i) -> l = 0;
        (*ret).getPixel (width * 10, i) -> a = 1;
    }
    
    for (int i = 1; i < 10; i++)
    {
        (*ret).getPixel(i, 0) -> h = 0;
        (*ret).getPixel(i, 0) -> s = 0;
        (*ret).getPixel(i, 0) -> l = 1;
        (*ret).getPixel(i, 0) -> a = 1;
    }

    for (int i = 0; i < size; i++)
    {
        int x = i % width;
        int y = i / width;

        if (rightwall[i])
        {
            for (int j = 0; j <= 10; j++)
            {
                (*ret).getPixel ((x + 1) * 10, y * 10 + j) -> h = 0;
                (*ret).getPixel ((x + 1) * 10, y * 10 + j) -> s = 0;
                (*ret).getPixel ((x + 1) * 10, y * 10 + j) -> l = 0;
                (*ret).getPixel ((x + 1) * 10, y * 10 + j) -> a = 1;
            }
        }
        if (downwall[i])
        {
            for (int j = 0; j <= 10; j++)
            {
                (*ret).getPixel (x * 10 + j, (y + 1) * 10) -> h = 0;
                (*ret).getPixel (x * 10 + j, (y + 1) * 10) -> s = 0;
                (*ret).getPixel (x * 10 + j, (y + 1) * 10) -> l = 0;
                (*ret).getPixel (x * 10 + j, (y + 1) * 10) -> a = 1;  
            }
                
        }
    }
    return ret;
}

/**
 * This function calls drawMaze, then solveMaze, with those information
 * it modifies the PNG from drawMaze to show the solution vector and the exit.
 **/
PNG * SquareMaze::drawMazeWithSolution()
{
    PNG* ret = drawMaze();
    vector<int> path = solveMaze();
    int x = 5;
    int y = 5;

    for (size_t i = 0; i < path.size(); i++)
    {
        if (path[i] == 0)
        {
            for (int j = 0; j <11; j++)
            {
                (*ret).getPixel(x + j, y) -> h = 0;
                (*ret).getPixel(x + j, y) -> s = 1;
                (*ret).getPixel(x + j, y) -> l = 0.5;
                (*ret).getPixel(x + j, y) -> a = 1;    
            }
            x = x + 10;
        }
        else if (path[i] == 1)
        {
            for (int j = 0; j < 11; j++)
            {
                (*ret).getPixel(x, y + j) -> h = 0;
                (*ret).getPixel(x, y + j) -> s = 1;
                (*ret).getPixel(x, y + j) -> l = 0.5;
                (*ret).getPixel(x, y + j) -> a = 1;    
            }
            y = y + 10;
        }
        else if (path[i] == 2)
        {
            for (int j = 0; j <11; j++)
            {
                (*ret).getPixel(x - j, y) -> h = 0;
                (*ret).getPixel(x - j, y) -> s = 1;
                (*ret).getPixel(x - j, y) -> l = 0.5;
                (*ret).getPixel(x - j, y) -> a = 1;    
            }
            x = x - 10;

        }
        else 
        {
            for (int j = 0; j < 11; j++)
            {
                (*ret).getPixel(x, y - j) -> h = 0;
                (*ret).getPixel(x, y - j) -> s = 1;
                (*ret).getPixel(x, y - j) -> l = 0.5;
                (*ret).getPixel(x, y - j) -> a = 1;    
            }
            y = y - 10;
        }
    }

    for (int i = 1; i < 10; i++)
    {
        (*ret).getPixel(x / 10 * 10 + i, (height - 1 + 1) * 10) -> h = 0;
        (*ret).getPixel(x / 10 * 10 + i, (height - 1 + 1) * 10) -> s = 0;
        (*ret).getPixel(x / 10 * 10 + i, (height - 1 + 1) * 10) -> l = 1;
        (*ret).getPixel(x / 10 * 10 + i, (height - 1 + 1) * 10) -> a = 1;     
    }

  return ret;
}













