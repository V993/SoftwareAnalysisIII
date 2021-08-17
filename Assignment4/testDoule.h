

#include "quadratic_probing.h"  //Include quadratic_probing.h file to use IsPrime() and NextPrime() functions
#include <vector>
#include <algorithm>
#include <functional>

//***********************************************************Modified or Added*************************************************************

// Public:
//      size_t GetSize()                                    --> Returns size_t data member current_size_
//      size_t GetTableSize()                               --> Returns the size of vector array_ as size_t
//      int TotalCollisions()                               --> Returns private data member collisions
//      int ProbesForContains(const HashedObj & x)          --> Finds probes for each Contains operation to find HashedObj x
//      bool SetR(int R_val)                                --> Set R to R_val. Returns true if R is set to R_val. Otherwise, return false.
//      int GetR()                                          --> Returns private data member R
//      void MakeEmpty()                                    --> Modified to set collisions to 0

// Private:
//      mutable int collisions                              --> Mutable Int data member to hold the total number of collisions
//      int R                                               --> Int data member to hold the R value that will be used for second hash function
                                                                //default value set to 2 in MakeEmpty()
//      size_t InternalHash2(const HashedObj & x) const     --> Second hash function. Hash2=R-(key%R) where R is prime and not 0
//      size_t FindPos(const HashedObj & x) const           --> Modified to implement double hashing and count the number of collisions

//******************************************************************************************************************************************

// Double Hashing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  //Enum EntryType elements are ACTIVE,EMPTY,DELETED
  enum EntryType {ACTIVE, EMPTY, DELETED};

  //Constructor
  //Sets size_t size to 101. Sets the size of array_ to smallest prime number greater than size
  //Calls MakeEmpty() to innitialize the private data members
  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }
  
  //Takes parameter template object x
  //Returns true if x is found in the table. Returns false if x is not found
  //Calls IsActive on FindPos(x). If x is in the table, IsActive returns true. Otherwise returns false
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  //Removes template object x from the table
  //Returns true if item is successfully removed. Otherwise return false
  bool Remove(const HashedObj & x) {
    //Set current_pos to FindPos(x). FindPos(x) will use hash function to get the position of x
    size_t current_pos = FindPos(x);
    //If current_pos is not active, return false
    if (!IsActive(current_pos))
      return false;
    //Set the info_ of position of x to DELETED
    array_[current_pos].info_ = DELETED;
    //return true
    return true;
  }
  
  //Insert function for the address of template object x
  //Inserts objext x to the table
  bool Insert(const HashedObj & x) {
    // Insert x as active
    // Get the current_pos of x using FindPos(x)
    size_t current_pos = FindPos(x);
    // If current_pos is active, insert fails as x is already in the table
    if (IsActive(current_pos))
      return false;
    
    //Set element of index current_pos in array_ equal to x
    array_[current_pos].element_ = x;
    //Set info_ of index current_pos in array_ equal to ACTIVE
    array_[current_pos].info_ = ACTIVE;
    
    // Call Rehash() if the array starts getting full
    // Rehash() if current_size_ is more than half of the size of array_
    if (++current_size_ > array_.size() / 2){
      Rehash();   
    }
    // Return true
    return true;
  }

  //Insert function for the rvalue reference of template object x
  //Inserts objext x to the table
  bool Insert(HashedObj && x) {
    // Insert x as active
    // Get the current_pos of x using FindPos(x)
    size_t current_pos = FindPos(x);
    // If current_pos is active, insert fails as x is already in the table
    if (IsActive(current_pos))
      return false;
    
    //Set element of index current_pos in array_ equal to x
    array_[current_pos].element_ = x;
    //Set info_ of index current_pos in array_ equal to ACTIVE
    array_[current_pos].info_ = ACTIVE;
    
    // Call Rehash() if the array starts getting full
    // Rehash() if current_size_ is more than half of the size of array_
    if (++current_size_ > array_.size() / 2){
      Rehash();   
    }
    // Return true
    return true;
  }

//*********************************************************Added or Modified Public Functions***************************************************
  
  //Returns private size_t data member current_size_
  size_t GetSize(){
    return current_size_;
  }

  //Returns size_t size of array_
  size_t GetTableSize(){
    return array_.size();
  }

  //Returns the private integer data member collisions
  int TotalCollisions(){
    return collisions;
  }

  //Modified version of the FindPos() function 
  //Returns int value of probes used to find an item x in the table using double hashing
  int ProbesForContains(const HashedObj & x){
    //Innitialize current_pos to InternalHash(x) which will give the approx location of the item
    size_t current_pos = InternalHash(x);
    //Int variable total_probes is innitialized equal to 1 to count the innitial probe
    int total_probes=1;
    //While loop runs if the current_pos index of array_ is not EMPTY and it is not equal to the item x
    while (array_[current_pos].info_ != EMPTY &&array_[current_pos].element_ != x) {
      //Call std::abort() if second key is equal to 0 
      if(InternalHash2(x)==0){
        std::abort();
      }
      //Increment total probes by 1 for every unsuccessful attempt to find item x
      total_probes++;
      //Increment current_pos by InternalHash2(x)
      current_pos +=InternalHash2(x);
      //If current_pos is greater than the size of array_, decrement current_pos by the size of array_
      if (current_pos >= array_.size()){
        current_pos -= array_.size();
      }
    }
    //Return total_probes 
    return total_probes;
  }
  
  //Set R to R_val 
  //Return false if parameter int R_val is 0 or not a prime number or greater than the table size
  //Return true if R is set equal to R_val
  bool SetR(int R_val){
    //Return false if R_val is 0 or not prime or greater than the size of array_
    if((R_val==0) or (IsPrime(size_t(R_val))==false) or (size_t(R_val)>array_.size())){
      return false;
    }
    //Set private data member R equal to R_val
    R=R_val;
    //Return true if R is equal to R_val. Otherwise return false
    return R==R_val;
  }

  //Returns private int data member R
  int GetR(){
    return R;
  }

  //Sets collisions and current_size_ to 0. Sets info_ of all entry in array_ to Empty.
  //Modified to set collisions to 0 and R to 2 when MakeEmpty() is called
  void MakeEmpty() {
    //Set current_size_ equal to 0
    current_size_ = 0;
    //Set collisions equal to 0
    collisions=0;
    //Set the info_ of all entry in array_ equal to EMPTY
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

//***************************************************************************************************************************************
 
 private:        
  //Struct HashEntry holds information about items inserted
  struct HashEntry {
    //Template class HashedObj element_
    HashedObj element_;
    //info_ can be ACTIVE, DELETED or EMPTY
    EntryType info_;
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };

  //array_ is a vector of struct HashEntry  
  std::vector<HashEntry> array_;
  //data member current_size_ to hold the number of items in the table
  size_t current_size_;

  //Returns true if info_ of item in current_pos is ACTIVE
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  //
  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array){
      if (entry.info_ == ACTIVE){
        Insert(std::move(entry.element_));
      }
    }
  }
  
  //Hash function used to assign position to parameter template HashedObj x
  //Returns the position of x based on hash function (key% size of array)
  size_t InternalHash(const HashedObj & x) const {
    //Call std::hash<HashedObj> to create hf
    static std::hash<HashedObj> hf;
    //Get key using hf(x) and return newly calculated position for x based on (key%size)
    return hf(x) % array_.size( );
  }

  //*************************************************Modified Private Functions*************************************************************
  
  //Private mutable integer data member to hold the total number of collisions
  //Mutable to allow increments within const functions
  mutable int collisions=0;

  //R value for second hash
  int R=2;

  //Find the position of item x on the hash table
  //If x is not on the table, assign a new position
  //Returns size_t value
  size_t FindPos(const HashedObj & x) const {
    //Innitialize current_pos to InternalHash(x) which will give the approx location of the item
    size_t current_pos = InternalHash(x);
    //While loop runs if the current_pos index of array_ is not EMPTY and it is not equal to the item x
    while (array_[current_pos].info_ != EMPTY &&array_[current_pos].element_ != x) {
      //Call std::abort() if second key is equal to 0
      if(InternalHash2(x)==0){
        std::abort();
      }
      //If there is a collision, increment private data member collisions
      collisions++;
      //Increment current_pos by InternalHash2(x)
      current_pos +=InternalHash2(x);
      //If current_pos is greater than the size of array_, decrement current_pos by the size of array_
      if (current_pos >= array_.size()){
        current_pos -= array_.size();
      }
    }
    //Return total_probes 
    return current_pos; 
  }
  //Second hash function for double hash
  //Returns R-(key%R) 
  //R is a prime number less than table size and it is not 0
  size_t InternalHash2(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return (R-(hf(x) % R));
  }
  //****************************************************************************************************************************************
};

#endif  // DOUBLE_HASHING_H