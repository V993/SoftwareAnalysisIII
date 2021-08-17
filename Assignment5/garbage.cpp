
// Original HEAPSORT:

/**
 * Internal method for HeapSort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable>
void percDown(vector<Comparable> &a, int i, int n)
{
    int child;
    Comparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[i] = std::move(a[child]);
        else
            break;
    }
    a[i] = std::move(tmp);
}

/** 
 * Standard HeapSort.
 */
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable> &a, Comparator less_than)
{
    for (int i = a.size() / 2 - 1; i >= 0; --i) /* buildHeap */
        percDown(a, i, a.size());
    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]); /* deleteMax */
        percDown(a, 0, j);
    }
}

// Original MERGE():

template <typename Comparable>
void merge(vector<Comparable> &a, vector<Comparable> &tmpArray,
           int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (a[leftPos] <= a[rightPos])
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd) // Copy rest of first half
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd) // Copy rest of right half
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}


// Original QUICKSORT:

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * @param a is an array of Comparable items.
 * @param left is the left-most index of the subarray.
 * @param right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable> &a, int left, int right, less_than)
{
    if (left + 10 <= right)
    {
        const Comparable &pivot = median3(a, left, right);

        // Begin partitioning
        int i = left, j = right - 1;
        for (;;)
        {
            while (a[++i] < pivot)
            {
            }
            while (pivot < a[--j])
            {
            }
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]); // Restore pivot

        quicksort(a, left, i - 1);  // Sort small elements
        quicksort(a, i + 1, right); // Sort large elements
    }
    else // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}



// original INSERTIONSORT

template <typename Comparable>
void insertionSort(vector<Comparable> &a, int left, int right)
{
    for (int p = left + 1; p <= right; ++p)
    {
        Comparable tmp = std::move(a[p]);
        int j;

        for (j = p; j > left && tmp < a[j - 1]; --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}


// Original VERIFYORDER

for (int i = 0; i < input.size()-1; i++) {
    Comparable a = input[i];
    Comparable b = input[i+1];
    if (!less_than(a, b))
      return false;
  }
  return true;

template <typename Comparable, typename Comparator>
void quicksort2( vector<Comparable> & a, int left, int right, Comparator compare)
{
    // Using cutoff of 10
    if( left + 10 <= right )
    {
        // Swap a[right] with a[(right+left)/2](which is equivalent to middle element)
        std::swap(a[right],a[(right+left)/2]);
        // Set pivot to a[right] which now contains the innitial middle element
        const Comparable & pivot = a[right];
        // Begin partitioning
        // i holds the index of left partition, j holds index of right partition
        int i = left-1, j = right;
        for( ; ; )
        {
            // Partition left of pivot
            while( compare(a[ ++i ] , pivot )) { }
            // Partition right of pivot
            while( compare(pivot , a[ --j ] )) { }
            // Swap a[i] and a[j] if i<j
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        // Restore pivot to a[i] from a[right]
        std::swap( a[ i ], a[right] ); 

        // Sort elements left side of pivot by calling quicksort recursively
        quicksort( a, left, i - 1, compare); 
        // Sort elements right side of pivot by calling quicksort recursively    
        quicksort( a, i + 1, right, compare);    
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, compare);
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses first element as pivot and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * Modified: Takes comparator to make comparisons
 */
template <typename Comparable, typename Comparator>
void quicksort3( vector<Comparable> & a, int left, int right, Comparator compare)
{
    // Using cutoff of 10
    if( left + 10 <= right )
    {
        // Swap a[right] with a[left] 
        //std::swap(a[right],a[left]);
        // Set pivot to a[right] which now has innitial first element
        const Comparable & pivot = a[left];
        // Begin partitioning
        // i holds the index of left partition, j holds index of right partition
        int i = left, j = right+1;
        for( ; ; )
        {
            // Partition left of pivot
            while( compare(a[ ++i ] , pivot )) { }
            // Partition right of pivot
            while( compare(pivot , a[ --j ] )) { }
            // Swap a[i] and a[j] if i<j
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        // Restore pivot to a[i] from a[right]
        std::swap( a[ j], a[left] ); 

        // Sort elements left side of pivot by calling quicksort recursively
        quicksort( a, left, j - 1, compare);    
        // Sort elements right side of pivot by calling quicksort recursively
        quicksort( a, j + 1, right, compare);   
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right, compare);
}