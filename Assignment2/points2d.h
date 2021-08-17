// --> Leonardo Matone
// This class works with arrays of points. Each point is composed of two numbers of type Object,
// allowing for flexible use of the class with int, float, double, etc. values. Points are stored
// in objects containing multiple points, with an array for each point contianing each number of
// the point.

#ifndef CSCI335_HOMEWORK2_POINTS2D_H_
#define CSCI335_HOMEWORK2_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
  // This class saves and stores arrays of points, composed of two numbers.
  // These points are saved as Objects, allowing them to be a variety of numerical
  // datatypes. The class below is defined for various uses, and overloads operators
  // to ensure that points can be properly output and utilized as needed. 
  template<typename Object>
  class Points2D {
    public:

      // Zero-parameter constructor. 
      // sets size to zero, sequence pointer points to null.
      Points2D() : sequence_{nullptr}, size_{0} {}

      // Copy-constructor. Takes default values from givem Points2D
      // @param rhs is the points which we base our new object from
      Points2D(const Points2D &rhs) {
        //copy sequence from input Points2D
        sequence_ = rhs.sequence_;
        //copy size from input Points2D
        size_ = rhs.size_;
      }

      // Copy-assignment.
      // @param rhs is the points which we base our new object from
      Points2D& operator=(const Points2D &rhs) {
        // establish copy of parameter Points2D
        Points2D copy = rhs;
        // using std swap, swap this keyword with Points2D copy
        std::swap(*this, copy);
        // return result
        return *this;
      }

      // Move-constructor. 
      // @param rhs is the points we use to establish our new object. This will be erased.
      Points2D(Points2D &&rhs) {
        // copy the size of paremeter Points2D 
        size_ = rhs.size();
        // set parameter Points2D to zero
        rhs.size_ = 0;
        // copy the sequence of Points2D
        sequence_ = rhs.sequence_;
        // set the sequence of Points2D to null 
        rhs.sequence_ = nullptr;
      }

      // Move-assignment.
      // Just use std::swap() for all variables.
      Points2D& operator=(Points2D &&rhs){
        // Used swap as instructed.
        std::swap(sequence_, rhs.sequence_);
        std::swap(size_, rhs.size_);

        //returns result
        return *this;
      }

      // Destructor
      ~Points2D() {
        sequence_ = nullptr;
        size_ = 0;
        delete[] sequence_;
      };

      // End of big-five.

      // One parameter constructor.
      // @param array item to be added as a sequence
      Points2D(const std::array<Object, 2>& item) {
        // set size to 1
        size_ = 1;
        // save item as sequence
        sequence_ = new std::array<Object,2>{item};
      }

      // returns size
      size_t size() const {
        return size_;
      }

      // Read a chain from standard input.
      void ReadPoints2D() {
        // Part of code included (without error checking).
        std::string input_line;
        std::getline(std::cin, input_line); 
        std::stringstream input_stream(input_line);
        if (input_line.empty()) return;
        // Read size of sequence (an integer).
        int size_of_sequence;
        input_stream >> size_of_sequence;
        // Allocate space for sequence.
        // Add code here.
        
        // initialize our sequence and size values.
        sequence_ = new std::array<Object, 2>[size_of_sequence];
        size_ = size_of_sequence;

        Object token;
        // loop through each number and add the pairs as points.
        for (int i = 0 ; input_stream >> token; ++i) {
          sequence_[i][0] = token;
          //take next digit
          input_stream >> token;
          sequence_[i][1] = token;
        }
      }

      // Overloading the << operator.
      friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2d) {
        
        // default, if the size is empty.
        if (some_points2d.size() == 0)
          return out << "()\n";

        // for each point, format output as specified
        for (size_t i = 0; i < some_points2d.size(); i++) {
          out << "(" << (some_points2d.sequence_[i][0]) << ", " << (some_points2d.sequence_[i][1]) << ") ";
        }

        // add endl character at the end for aesthetics
        out << "\n";

        return out;
      }
      
      //  @c1: A sequence.
      //  @c2: A second sequence.
      //  @return their sum. If the sequences are not of the same size, append the
      //  result with the remaining part of the larger sequence.
      friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        size_t larger, smaller;
        Points2D result, largest;

        // determine which is larger and smaller in the parameter sequences
        if (c1.size() > c2.size()) {
          smaller = c2.size();
          larger = c1.size();
          largest = c1;
        }
        else {
          smaller = c1.size();
          larger = c2.size();
          largest = c2;
        }
        // initialize a sequence we will modify with the added and appended values from
        // the parameter sequences.
        auto *sequence_ = new std::array<Object,2>[larger];

        // loop through and add each point to the new sequence. Add each value before 
        // adding to the sequence.
        for (size_t i = 0; i < smaller; i++) {
          sequence_[i][0] = c1[i][0] + c2[i][0];
          sequence_[i][1] = c1[i][0] + c2[i][1];
        }

        // append the remaining points, if there are any
        for (size_t j = smaller; j < larger; j++) {
          sequence_[j][0] = largest[j][0];
          sequence_[j][1] = largest[j][1];
        }

        // save the sequence and size into our Points2D object and return.
        result.sequence_ = sequence_; 
        result.size_ = larger;

        return result;
      }

      // @location: an index to a location in the given sequence.
      // @returns the point at @location.
      // const version.
      // abort() if out-of-range.
      const std::array<Object, 2>& operator[](size_t location) const { 
        if (location >= size_)
          abort();

        return sequence_[location];
      }


    private:
      // Sequence of points. 
      std::array<Object, 2> *sequence_;
      // Size of the sequence.
      size_t size_;

    };

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK2_POINTS2D_H_
