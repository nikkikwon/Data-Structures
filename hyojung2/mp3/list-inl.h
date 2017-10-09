#include <iostream>

/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1

	ListNode * HEAD = head_;
	ListNode * temp = NULL;

	while (HEAD != NULL)
	{
		temp = HEAD;
		HEAD = HEAD->next;
	 	delete temp;	
	}
	
	length_ = 0;
	temp = NULL;
	HEAD = NULL;
  tail_= NULL;
	}
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1

	ListNode * newnode = new ListNode(ndata);

   if(empty())
	{
		newnode -> prev = NULL;
		newnode -> next = NULL;
		head_ = newnode;
		tail_ = newnode;
	}
	else
	{
		newnode -> next = head_;
		newnode -> prev = NULL;
		head_ -> prev = newnode;
		head_ = newnode;
	}

	length_ = length_ +1;
	newnode = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
	
	ListNode * newnode = new ListNode(ndata);
	
	if (empty())
	{
    newnode -> prev = NULL;
		newnode -> next = NULL;
		head_ = newnode;
		tail_ = newnode;
	}
	else 
	{
		tail_-> next = newnode;
		newnode -> prev = tail_;
		newnode -> next = NULL;
    tail_ = newnode;
	}

	length_ = length_ + 1;
	newnode = NULL; 
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
	/// @todo Graded in MP3.1

	if (empty())
		return;

	if (startPoint == NULL || endPoint == NULL)
		return;

	ListNode * sp = startPoint;
  ListNode * startprev = startPoint -> prev;
	ListNode * endnext = endPoint -> next;

	if (startprev != NULL)
		startprev -> next = endPoint; 
	if (endnext != NULL)
		endnext -> prev = startPoint;

	while (startPoint != endPoint)
	{
		ListNode * temp = startPoint -> prev;
		startPoint -> prev = startPoint -> next;
		startPoint -> next = temp;
		startPoint = startPoint -> prev; 
	}

	ListNode * second = startPoint -> prev;
	startPoint -> next = second;
	startPoint -> prev = startprev;

	if (startprev == NULL) 
		head_ = startPoint;

  endPoint = sp;
	endPoint -> next = endnext;
	
	if (endnext == NULL)
		tail_ = endPoint;

	sp = NULL;
	second = NULL;
	startprev = NULL;
	endnext = NULL; 
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1

	if (empty() || n <= 1 || head_ == NULL || tail_ == NULL)
		return;	

	if (n >= length_)
	{
		reverse();
		return;
	}
		ListNode * start = head_;
		ListNode * end = head_;

		while(end -> next != NULL)
		{
			end = start;
			for(int i = 1; i < n; i++)
			{
				if(end->next != NULL)		
				end = end->next;
			}
			reverse(start, end);
			start = end->next;
		}
	start = NULL;
	end = NULL;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

	if (head_== NULL || head_ -> next == tail_)		
		return;
	if (head_ -> next == NULL)
		return;
	if(length_ < 3)
    return;

  ListNode* temp = head_;
  ListNode* curr = temp -> next;

	while (curr -> next != NULL && curr != tail_ && curr != NULL)
	{
		curr -> prev = tail_;
		tail_ = curr;
		temp -> next = curr -> next;
		curr -> next -> prev = temp;
		curr -> next = curr -> prev->next;
		curr -> prev -> next = curr;
		curr = temp -> next -> next; 
		temp = temp -> next;
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2

		if (empty() || start == NULL)
			return NULL;

		if(splitPoint == 0)
			return start;

		ListNode* newhead = head_;
			
		for(int i = 0; i < splitPoint; i++)
		{
			newhead = newhead -> next;
		}

		newhead -> prev -> next = NULL;
		newhead -> prev = NULL;

		return newhead;	
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (first == NULL && second == NULL)
	 return NULL;

	if (first == NULL)
		return second;

	if (second == NULL)
		return first;

	if (first == second)
		return first;

	ListNode * HEAD = NULL;
	ListNode * one = first;
	ListNode * two = second;
	ListNode * result = NULL;
  
  //set the head	
	if (one -> data < two -> data )
	{
		HEAD = one;
		result = HEAD;
		one = one -> next;	
	}
	else
	{
		HEAD = two;
		result = HEAD;
		two = two -> next;
	}

	while(one != NULL && two != NULL)
	{
		if(one -> data < two -> data)
		{
			result -> next = one;
			result = result -> next;
			one -> prev = result;
			one = one -> next;
		}
		else
		{
			result -> next = two;
			result = result -> next;
			two ->prev = result;
			two = two -> next;
		}
	}

	if(one == NULL)
	{
		result -> next = two;
		two -> prev = result; 
	}
	if (two == NULL)
	{
		result -> next = one;
		one -> prev = result; 
	}

	one = NULL;
	two = NULL;
	result = NULL;

	return HEAD;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2

		 	if (chainLength == 1)
				return start;
		else
		{
			ListNode * second = start;
			int mid = chainLength/2;
			int count = mid;

			while(count != 0)
			{
				second = second -> next;
				count--;
			}

			second->prev->next = NULL;
			second->prev = NULL;	

			start = mergesort(start, mid);
			second = mergesort(second, chainLength-mid);

			start = merge(start, second);
		}
		return start;
}




