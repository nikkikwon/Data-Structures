/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    vector< Point<3> > data;
    map<Point<3>, TileImage> Map;
    Point<3> val;
	HSLAPixel pixel;

    for (unsigned long i = 0; i < theTiles.size(); i ++)
    {
        pixel = theTiles[i].getAverageColor();
		val = Point<3>(pixel.h, pixel.s, pixel.l);
        Map[val] = theTiles[i];
        data.push_back(val);
    }
	
    KDTree<3> tree(data);
    
    for (int i = 0; i < theSource.getRows(); i++)
    {
        int j = 0;
        while(j < theSource.getColumns())
        {
            pixel = theSource.getRegionColor(i, j);
            val = Point<3>(pixel.h, pixel.s, pixel.l);
            val = tree.findNearestNeighbor(val);
            canvas->setTile(i, j, Map[val]);
            j++;
       }
    
    }
    return canvas;
}
