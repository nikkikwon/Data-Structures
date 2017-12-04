/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */

    unsigned long count = 0;
    vector <Vertex> v = graph.getVertices();
    vector <Edge> e = graph.getEdges();

    Vertex init = graph.getStartingVertex();
    graph.setVertexLabel(init, "VISITED");	

    int MinWeight = graph.getEdgeWeight(init, (graph.getAdjacent(init))[0]);

    Vertex one, two;
    queue <Vertex> q;
    q.push(init);
  

    while (count != v.size())
    {
        graph.setVertexLabel(v[count], "UNEXPLORED");  
        count++;
    }
    count = 0;
    while(count != e.size())
    {
        graph.setEdgeLabel(e[count].source, e[count].dest, "UNEXPLORED");
        count++;
    }

	while(!q.empty())
	{
        Vertex ver = q.front();
        vector <Vertex> a = graph.getAdjacent(ver);
		q.pop();
		
        count = 0;
        while(count < a.size())
        {
            Vertex w = a[count];
            if(graph.getEdgeWeight(ver, w) <= MinWeight)
            {
                MinWeight = graph.getEdgeWeight(ver,w);
                one = ver;
                two = w;
            }

            if (graph.getVertexLabel(w).compare("UNEXPLORED") == 0)
            {
                graph.setEdgeLabel(ver, w, "DISCOVERY");
                graph.setVertexLabel(w, "VISITED");
                q.push(w);

            } 
            else if (graph.getEdgeLabel(ver, w).compare("UNEXPLORED") == 0)
            {
                 graph.setEdgeLabel(ver, w, "CROSS");
            }
            count++;
        }
	}
    graph.setEdgeLabel(one, two, "MIN");
    return MinWeight;
}
    

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    unsigned long count = 0;
    queue<Vertex> q;
    q.push(start);
	unordered_map<Vertex, Vertex> map; 
	map.insert(make_pair(start, start));
    Vertex v, v2;
    
	while(!q.empty())
	{
        v2 = q.front();
        vector<Vertex> a = graph.getAdjacent(v2);
        q.pop();

        count = 0;
        while(count < a.size())
        {
            if (v2 == end)
                v = v2;

			if(graph.getVertexLabel(a[count]) != "VISITED")
			{
				q.push(a[count]);
				graph.setVertexLabel(a[count], "VISITED");
				map.insert(make_pair(a[count], v2));
            }
            count++;
        }
    }

    for (count = 0; v != map[v]; count++)
    {
        v2 = map[v];
		graph.setEdgeLabel(v2, v, "MINPATH");
		v = v2; 
    }

    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector< Vertex > v = graph.getVertices();
    vector<Edge> e = graph.getEdges();
    DisjointSets dsets;
    unsigned long count = 0;

    sort(e.begin(), e.end());

    while (count < v.size())
    {
        dsets.addelements(v[count]);
        count++;
    }
    count = 0;

	for(count = 0; count < e.size(); count++)
	{
		if(dsets.find(e[count].source) != dsets.find(e[count].dest))
		{
			dsets.setunion(e[count].source, e[count].dest);
			graph.setEdgeLabel(e[count].source, e[count].dest, "MST"); 
		}
	}
}








