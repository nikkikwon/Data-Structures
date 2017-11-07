/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

/**
 * This function takes two templatized parameters and return boolean value which indicates whether the first points is smaller than the second value specified.
 * depending on the comparison, operator '<' is used to distinguish between ties
 **/

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim])
        return first < second;
    else 
        return first[curDim] < second[curDim];
}

/**
 * This function takes three templated parameters, and it returns boolean value indicating whether the 
 * potential value is closer to the target value than the currentBest value. In case there is a tie, similarly to the previous function,
 * it determines by using the operator '<'. The distance is determined by the Euclidean distance and getd helper function is used to calculate that value.
 **/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int d1= getd(potential, target);
    int d2= getd(currentBest, target); 

    if (d1 == d2)
        return potential < currentBest;
    
    else 
        return d1 < d2;
}

/**
* This takes in one parameter which is a reference to a vector<Point<Dim>>. This builds a tree by calling several helper functions in the helper function itself.
**/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    KDTreehelper(0, points.size()-1, 0);
    
}

/**
*  This function takes one parameter as well and returns a Point which is closest to the parameter given in the tree. 
* Again, Euclidean distance is used to determine the closeness and in case of a tie '<' operator is being used. It calls several helper function
* to achieve its functionality in building tree. 
**/
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    Point<Dim> currentBest;
    bool isFirst = true;
    findNNHelper(0, points.size() - 1, 0, 0, isFirst, query, currentBest);

    return currentBest;
}

/**
 * This is a helper function to calculate the Euclidean distance by accepting two points and returning the Euclidean distance between those two points 
 **/
template<int Dim>
int KDTree<Dim>::getd(const Point<Dim> & point1, const Point<Dim> & point2) const
{
    int d = 0;
    for(int i = 0; i < Dim; i++)
    {
        d = d + (point2[i]-point1[i]) * (point2[i]-point1[i]);
    }
    return d;
}

/**
 * This is a helper function of the constructor. It is used to build a tree structure by providing the adaquate parameter values to various helper functions. 
 **/

template<int Dim>
void KDTree<Dim>::KDTreehelper(int left, int right, int dimension)
{
    if (left >= right)
        return;
    quickselect(left, right, (left+right)/2, dimension);
    KDTreehelper(left, ((left+right)/2)-1, (dimension + 1) % Dim);
    KDTreehelper(((left+right)/2)+1, right, (dimension + 1) % Dim);
    
}

/**
 * This function implements a quickselect algorithm provided by the link from the course webpage. It uses recursion to achieve the functionality
 **/
template<int Dim>
void KDTree<Dim>::quickselect(int left, int right, int midindex, int dimension)
{
    if (left >= right)
        return;
    int pivotval = partition (left, right, midindex, dimension);
    if (midindex == pivotval)
        return;
    else if (midindex < pivotval)
    {
        quickselect(left, pivotval-1, midindex, dimension);
    }
    else if (midindex > pivotval)
    {
            quickselect(pivotval +1, right, midindex, dimension);
    }

}

/**
 * used in quickselect this function is done in linear time and it groups a list into two parts. One with less than and one with more than specified element
 **/
template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dimension)
{
    Point<Dim> pivotValue = points[pivotIndex];
    Point<Dim> temp = points[right];
    points[right] = points[pivotIndex];
    points[pivotIndex] = temp;

    int storeIndex = left;
    for(int i = left; i < right; i++)
    {
        if(smallerDimVal(points[i], pivotValue, dimension))
        {
            Point<Dim> temp = points[i];
            points[i] = points[storeIndex];
            points[storeIndex] = temp;
            storeIndex++;
        }
    }
    Point<Dim> temp2 = points[storeIndex];
    points[storeIndex] = points[right];
    points[right] = temp2;

    return storeIndex;
}

/**
 * Helper function called from  the nearest neighbor. As already mentioned from description of the FindNearestNeighbor function
 * the Euclidean distance is used to determine and fine the nearest neighbor. This function recursively build up solution**/
template<int Dim>
void KDTree<Dim>::findNNHelper(int left, int right, int dimension, int min, bool &isFirst, const Point<Dim> & query, Point<Dim> & currentBest) const
{
    int mid = (left + right)/2;

    if(left >= right)
    {
        if(isFirst)
        {
            isFirst = false;
            currentBest = points[right];
        }
        else if (shouldReplace(query, currentBest, points[left]))
        {
                currentBest = points[left];
        }
        return;
    } 

     if(smallerDimVal(query, points[mid], dimension))
    {
        findNNHelper(left, mid - 1, (dimension + 1) % Dim, min, isFirst, query, currentBest);

        min = getd(currentBest, query);

        if((query[dimension] - points[mid][dimension]) * (query[dimension] - points[mid][dimension]) <= min)
            findNNHelper(mid + 1, right, (dimension + 1) % Dim, min, isFirst, query, currentBest);

        if(shouldReplace(query, currentBest, points[mid]))
            currentBest = points[mid];
    }

    else
    {
        findNNHelper(mid + 1, right, (dimension + 1) % Dim, min, isFirst, query, currentBest);

        min = getd(currentBest, query);

        if((query[dimension] - points[mid][dimension]) * (query[dimension] - points[mid][dimension]) <= min)
            findNNHelper(left, mid - 1, (dimension + 1) % Dim, min, isFirst, query, currentBest); 

        if(shouldReplace(query, currentBest, points[mid]))
            currentBest = points[mid];  
    }
    return;
}




































