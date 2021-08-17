// Homework 5
// Testing Sorting Algorithms
// Leonardo Matone

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.
void TestingTiming() {
  cout << "Testing Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();    
  cout << chrono::duration_cast<chrono::nanoseconds>(end 
                                      - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end 
                                      - begin).count() << "ms" << endl;

}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  // Use rand() to generate random integer
  vector<int> new_vector(size_of_vector);
  for (size_t i = 0; i < size_of_vector; i++) {
    int new_value = rand();
    new_vector[i] = new_value; // add the new value to our array
    // cout << "Position: " << i << " | " << new_value << endl;
  }

  return new_vector;
}

// Generate and returns sorted vector of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  vector<int> new_vector(size_of_vector);
  for (size_t i = 0; i < size_of_vector; i++) {
    int new_value = i;
    if (smaller_to_larger) // if we want smaller to larger, add as is.
      new_vector[i] = new_value; // add the value of our iterator to the array
    else // else, add from the end of the array backwards.
      new_vector[new_vector.size()-(i+1)] = i;
  }
  
  return new_vector;
}

// Verifies that a vector is sorted given a comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {

  for (size_t i = 0; i < input.size()-1; i++) { // for each item in the array
    // if the item is not comparator of ith and (i+1)th item and the items are not equivalent,
    if (!less_than( input[i], input[i+1]) && input[i] != input[i+1]) 
      return false;
  }

  return true;
}

// Computes duration given a start time and a stop time in nano seconds
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, 
                          chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time 
                                                - start_time).count();
                                        // return the difference
}

// Wrapper function to test the different sorting algorithms
int testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" 
                                    && input_type != "sorted_large_to_small") {
    cout << "Invalid input type. Types are: \n\t\"random\"\n\t\"sorted_small_to_large\"\n\t\"sorted_large_to_small\"" << endl;
    return 0;
  }
  if (input_size <= 0) {
    cout << "Invalid size. Size must be greater than zero." << endl;
    return 0;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type. Types are: \n\t\"less\"\n\t\"greater\"" << endl;
    return 0;
  }
  
  cout << "Running sorting algorithms: " << input_type << " " 
                      << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") {
    input_vector = GenerateRandomVector(input_size);
  } else { // Generate sorted vector
    if (input_type == "sorted_small_to_large")
      input_vector = GenerateSortedVector(input_size, true);
    else if (input_type == "sorted_large_to_small")
      input_vector = GenerateSortedVector(input_size, false);
    else
      cout << "Invalid input type. Types are: \n\t\"random\"\n\t\"sorted_small_to_large\"\n\t\"sorted_large_to_small\"" << endl;
  }


  /*****************************************************************************/
  /*                                DRIVER CODE:                               */
  /*****************************************************************************/


  // create copy of vector to reset ordered vector
  vector<int> inorderedVector = input_vector;

  // boolean to test if each algorithm functions properly
  bool success = false; 

  cout << endl;

  //   Call QuickSort / HeapSort / mergesort using appropriate input.

  /**********************************************************************/
  /*                             HEAPSORT                               */
  /**********************************************************************/

  cout << "HeapSort" << endl;

  cout << endl;

  auto begin = chrono::high_resolution_clock::now();
  if (comparison_type == "less") {
    HeapSort(input_vector, less<int>{});
    success = VerifyOrder(input_vector, less<int>{});
  }
  else {
    HeapSort(input_vector, greater<int>{});
    success = VerifyOrder(input_vector, greater<int>{});
  }
  auto end = chrono::high_resolution_clock::now();

  cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
  cout << "Verified: " << success << endl;
  
    cout << endl;
    input_vector = inorderedVector;

  /**********************************************************************/
  /*                             MERGESORT                              */
  /**********************************************************************/

  //output vector

  cout << "MergeSort" << endl;

  cout << endl;

  begin = chrono::high_resolution_clock::now();
  if (comparison_type == "less") {// if comparison type is "less" then call 
    MergeSort(input_vector, less<int>{});
    success = VerifyOrder(input_vector, less<int>{});
  }
  else {// otherwise call
    MergeSort(input_vector, greater<int>{});
    success = VerifyOrder(input_vector, greater<int>{});
  } 
  end = chrono::high_resolution_clock::now();

  cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
  cout << "Verified: " << success << endl;

  //output vector

    cout << endl;
    input_vector = inorderedVector;

  /**********************************************************************/
  /*                              QUICKSORT                             */
  /**********************************************************************/

  //output vector

  cout << "QuickSort" << endl;

  cout << endl;

  // Call QuickSort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // if comparison type is "less" then call 
  begin = chrono::high_resolution_clock::now();
  if (comparison_type == "less") {
    QuickSort(input_vector, less<int>{});
    success = VerifyOrder(input_vector, less<int>{});
  }
  else {// otherwise call
    QuickSort(input_vector, greater<int>{});
    success = VerifyOrder(input_vector, greater<int>{});
  }
  end = chrono::high_resolution_clock::now();

  cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
  cout << "Verified: " << success << endl;

    cout << endl;
    input_vector = inorderedVector;


  /**********************************************************************/
  /*                  QUICKSORT PIVOT IMPLEMENTATIONS:                  */
  /**********************************************************************/

  cout << "Testing Quicksort Pivot Implementations" << endl;

  cout << endl;


  /**********************************************************************/
              cout << "Median of Three" << endl << endl;
  /**********************************************************************/

  // Call QuickSort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // if comparison type is "less" then call 
  begin = chrono::high_resolution_clock::now();
  if (comparison_type == "less") {
    QuickSort(input_vector, less<int>{});
    success = VerifyOrder(input_vector, less<int>{});
  }
  else {// otherwise call
    QuickSort(input_vector, greater<int>{});
    success = VerifyOrder(input_vector, greater<int>{});
  }
  end = chrono::high_resolution_clock::now();

  cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
  cout << "Verified: " << success << endl;

    cout << endl;
    input_vector = inorderedVector;


  /**********************************************************************/
              cout << "Middle" << endl << endl;
  /**********************************************************************/

  // if comparison type is "less" then call 
  begin = chrono::high_resolution_clock::now();
  if (comparison_type == "less") {
    QuickSort2(input_vector, less<int>{});
    success = VerifyOrder(input_vector, less<int>{});
  }
  else {// otherwise call
    QuickSort2(input_vector, greater<int>{});
    success = VerifyOrder(input_vector, greater<int>{});
  }
  end = chrono::high_resolution_clock::now();

  cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
  cout << "Verified: " << success << endl;

    cout << endl;
    input_vector = inorderedVector;


  /**********************************************************************/
              cout << "First" << endl << endl;
  /**********************************************************************/

  // if comparison type is "less" then call 
  begin = chrono::high_resolution_clock::now();
  if (comparison_type == "less") {
    QuickSort3(input_vector, less<int>{});
    success = VerifyOrder(input_vector, less<int>{});
  }
  else {// otherwise call
    QuickSort3(input_vector, greater<int>{});
    success = VerifyOrder(input_vector, greater<int>{});
  }
  end = chrono::high_resolution_clock::now();

  cout << "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
  cout << "Verified: " << success << endl;

    cout << endl;
    input_vector = inorderedVector;

  return 0;
}

// Do not change anything below

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }
  
  testSortingWrapper(argc, argv);

  return 0;
}
