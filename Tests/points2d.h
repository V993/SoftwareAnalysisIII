// Nancy Jennifer Ng
// Few comments describing the class Points2D
//Points 2D class represents a graph, where there are x coordinates and y coordinates to plot on a 2D plane
//object sequence is the 2 points on the graph, and the size would be the size of the sequence

#ifndef CSCI335_HOMEWORK2_POINTS2D_H_
#define CSCI335_HOMEWORK2_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
// Place comments that provide a brief explanation of this class,
// and its sample usage.
template<typename Object>
  class Points2D {
    public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation for it.

    // Zero-parameter constructor. 
    // Set size to 0.
    Points2D(){
      size_= 0; //initilaized size_ to 0 
      sequence_= nullptr;  //must initialize pointer to nullptr
    }
    // Copy-constructor.
    Points2D(const Points2D &rhs){
      // std::cout<<"went here to copy constructors func"<<std::endl; 
      size_= rhs.size(); //making the size_ in rhs.size()
      
      //line 37 referred in textbook on page 35
      sequence_ = new std::array<Object,2>[size_]; //making a new array
      // std::cout<<"size "<<size_<<std::endl; 
      
      for (size_t x =0 ; x<rhs.size(); x++){
        sequence_[x]= rhs.sequence_[x]; //copying whatever is in rhs sequence into sequence_
      }
     
    }

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    Points2D& operator=(const Points2D &rhs){
       Points2D copy = rhs; 
       std::swap(*this, copy);
       return *this;
    }

    // Move-constructor. 
    Points2D(Points2D &&rhs){//R value reference here. means we can do whatever we want with this temporary object
      size_ = rhs.size_;//moving rhs.size to size_
      rhs.size_ =0;//must initialize this back to 0, since there is nothing here now
      sequence_= rhs.sequence_;//moving rhs.sequence_ to sequence_
      rhs.sequence_= nullptr; //nullptr to prevent from this pointer from being deleted 
    }

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs){
      //we must swap both sequences and the sizes for move to work 
      
      //refered to page 35 on the textbook on line 69
      std::swap(sequence_,rhs.sequence_);//swaps the rhs.sequence_ into sequence_ 
      std::swap(size_, rhs.size_); //swaps the rhs.sequence_ size into sequence_ size
      return *this;
    }


    ~Points2D(){
      sequence_ = nullptr;
      size_ = 0;
      delete[] sequence_;//deletes entire array
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
      size_=1; //size is initialized to 1 
      // std::cout<<"prog went here to parameter constructor"<<std::endl; 
      sequence_= new std::array<Object, 2>{item}; //making a new array with item for our object.
      
    }

    // Read a chain from standard input.
    void ReadPoints2D() {
      // std::cout<<"went here to read"<<std::endl;
      // Part of code included (without error checking).
      std::string input_line; 

      std::getline(std::cin, input_line); 
      //reads in our input object

      
      std::stringstream input_stream(input_line);
      if (input_line.empty()){
        return; //don't read anything if it's empty
      }
      // Read size of sequence (an integer).

      //dynamically allocated array
      // Allocate space for sequence.
      int size_of_sequence; 
      input_stream >> size_of_sequence; //reads through the size of sequence
      sequence_ = new std::array<Object,2>[size_of_sequence]; 
      size_= size_of_sequence;//initializing size_ to size_of_sequence
      // std::cout<<"now in readpoints2D Function"<<std::endl; 
      // std::cout<<"the size of the sequence is"<<size_of_sequence<<std::endl; 

      Object token;
      for (size_t i = 0 ;input_stream >> token; ++i) {
        sequence_[i][0] = token;//putting x element into sequence
        input_stream>>token; //this reads the token from above
        sequence_[i][1] = token;//putting y element into sequence
        
        
        // std::cout<<"helloooo i tehre"<<std::endl; 
      
        // Fill sequence_ here.
      }
    
    }

    size_t size() const {
      return size_; //returns the size
    }

    // @location: an index to a location in the given sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const { 
      
      if(location>size_){// checking to see if location is within range by checking the size
        abort(); //if out of bounds, abort
      }
      else{ //this shows where the location is in the sequence
        return sequence_[location]; 
      }
      
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    //c1 = 3 2.1 20.3 11.11 12.45 13.1 14.2
    // c2  = 2 1.1 100.0 20.1 30.2
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
      
      Points2D<Object>new_array; //declared a new object for our new array

      //when there are two sequences, and they are the same size. return value of the sum of the first and second sequences
      // + is a move operator and this adds up elements in our sequence, and if the size are not equal the remaining 
      //numbers are appended aka not added

      
      if (c1.size() > c2.size()){ //checking sizes for c1 and c2 
        new_array=c1;//if c1 is greater than c2, the remaining elements are appended and not added
      }
      else{
        new_array=c2;//else, return c2
      }
      

      //now checking for the smallest sizes for our for loop
      double smallest = 0; 
      if (c1.size_ <c2.size_){
        smallest = c1.size_; //c1 is the smallest if size for c1 is smaller than c2 
      }
      else{ 
        smallest = c2.size_;//else smallest is c2
      }//getting the smallest elements so that we know which seqeunce we have to append
      
      for(size_t index = 0 ; index<smallest; index++){
        new_array.sequence_[index][0] = c1.sequence_[index][0]+ c2.sequence_[index][0]; //adding x elements in new array
        new_array.sequence_[index][1]= c1.sequence_[index][1]+c2.sequence_[index][1];//adding y elements in new array
      }

      return new_array; 

    }

    // Overloading the << operator.
    //output stream
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2d) {
      // want to get the points of the object
      //dereference sequence pointer 
      
      if(some_points2d.size() ==0){//checks if the size is empty
        out<<"()";//just output parenthesis if it is empty

      }
     
      // std::cout<<"we're in overload operators now"<<std::endl; 
      // std::cout<<"size of some_points 2d is"<<some_points2d.sequence_->size()<<std::endl; 
      else{//if the some_points object does not have a size of 0
        for(size_t x =0 ; x<some_points2d.size(); ++x){
          out<<"("<<some_points2d.sequence_[x][0]<<","<<some_points2d.sequence_[x][1]<<")"<<" ";//prints out each seq coordinate at x and y 
        }   
      }
      
      return out; 
    }
  
    private:
    // Sequence of points. 
      std::array<Object, 2> *sequence_;
      // Size of the sequence.
      size_t size_;

  };

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK2_POINTS2D_H_
