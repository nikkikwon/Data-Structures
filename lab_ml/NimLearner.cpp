/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true) 
{

  unsigned int size = startingTokens; 
  unsigned int vertex = (2*size)+2;
  int count = 1; 


  for (unsigned int i = 0; i < vertex; i++)
  {
    g_.insertVertex();
  }

  for (unsigned int i = 0; i <=size; i++)
  {
    string print = "p1-" + std::to_string(i);
    g_.setVertexLabel(i, print);
  }

  for (unsigned int i = size+1; i <= (2*size)+1; i++)
  {
    string print = "p2-" + std::to_string(i - size - 1);
    g_.setVertexLabel(i, print);
  }


  if (startingTokens >= 2 )
  { 
    for (unsigned int i = 2; i <=size; i++)
    {
      Edge temp;
      g_.insertEdge(i, size + (i-1));
      temp = g_.getEdge(i, size + (i-1));
      temp.weight = 0;

      g_.insertEdge(i, size + i );
      temp = g_.getEdge(i, size + i );
      temp.weight = 0;
    }

    for (unsigned int i = (size*2)+1 ; i >= size +3; i--)
    {
       Edge temp;
       g_.insertEdge(i, size - count );
       temp = g_.getEdge(i, size - count);
       temp.weight = 0;
       
       g_.insertEdge(i, size - count - 1);
       temp = g_.getEdge(i, size - count - 1);
       temp.weight = 0;
       count ++;
    }
  }

  Edge temp;
  g_.insertEdge(1,size+1);
  temp = g_.getEdge(1,size+1);
       temp.weight = 0;

  g_.insertEdge(size + 2, 0);
  temp = g_.getEdge(size + 2, 0);
       temp.weight = 0;

}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const 
{
  //unsigned long random;
  vector<Edge> path;
/*
  string label = g_.getVertexLabel(startingVertex_);

  while (label != "p1-0" || label != "p2-0" )
  {
    if (label[1] == 1)
    {
      random = rand() % 2;
      Vertex insert = g_.getVertexByLabel(label);
      path.push_back(g_.getEdge(insert, insert * 2 - random));
      label = g_.getVertexLabel(insert * 2 - random );
    }

    if (label[1] == 2)
    {
      random = rand() % 2;
      Vertex insert = g_.getVertexByLabel(label);
      path.push_back(g_.getEdge(insert, insert - startingVertex_ - 2 - random));
      label = g_.getVertexLabel(insert - startingVertex_ - 2 - random );
    }
   
  }*/

  return path;
}





/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {

}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
