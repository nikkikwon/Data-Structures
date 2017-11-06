/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
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

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    KDTreehelper(0, points.size()-1, 0);
    
}

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


template<int Dim>
void KDTree<Dim>::KDTreehelper(int left, int right, int dimension)
{
    if (left >= right)
        return;
    quickselect(left, right, (left+right)/2, dimension);
    KDTreehelper(left, ((left+right)/2)-1, (dimension + 1) % Dim);
    KDTreehelper(((left+right)/2)+1, right, (dimension + 1) % Dim);
    
}


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




































