/** @author Leonardo Matone
 *  @brief linear probing implementation
 *  @date 4.12.21 */

#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

// Linear probing implementation
template <typename HashedObj>
class HashTableLinear {
    public:
        enum EntryType {ACTIVE, EMPTY, DELETED};

        explicit HashTableLinear(size_t size = 101) : array_(NextPrime(size))
            { MakeEmpty(); }

        /** Contains test
         *  @brief Returns result of IsActive member function and passes
         *  the position of HashedObj @param x for IsActive to test if
         *  that posiiton has EntryType == ACTIVE  
         *  @return true if the hash tbale contains, false if not. */
        bool Contains(const HashedObj & x) {
            return IsActive(FindPos(x));
        }
        
        // Destroy HashTable
        void MakeEmpty() {
            current_size_ = 0;
            for (auto &entry : array_)
                entry.info_ = EMPTY;
        }

        /** Insert implementation
         *  @brief Inserts a new HashedObj @param x into the hash table. 
         *  @return false if @param x is already inside of the hash table
         *  @return true if is not. Tests if the hash table is in need of 
         *  a rehash as well. */
        bool Insert(const HashedObj & x) {

            // Insert x as active
            size_t current_pos = FindPos(x);
            if (IsActive(current_pos))
                return false;
            
            array_[current_pos].element_ = x;
            array_[current_pos].info_ = ACTIVE;

            // Rehash; see Section 5.5
            if (++current_size_ > array_.size() / 2)
                Rehash();    
            return true;
        }

        /** Insert implementation for @param x r-value*/ 
        bool Insert(HashedObj && x) {

            // Insert x as active
            size_t current_pos = FindPos(x);
            if (IsActive(current_pos))
                return false;
            
            array_[current_pos] = std::move(x);
            array_[current_pos].info_ = ACTIVE;

            // Rehash; see Section 5.5
            if (++current_size_ > array_.size() / 2)
                Rehash();

            return true;
        }

        /** Remove implementaton
         *  @brief removes HashedObj @param x from the hash
         *  table, if it exists, by setting its EntryType to
         *  DELETED.
         *  @returns whether operation was successful (false
         *  if the element does not exist) */
        bool Remove(const HashedObj & x) {

            current_size_--;

            size_t current_pos = FindPos(x);
            if (!IsActive(current_pos))
                return false;

            array_[current_pos].info_ = DELETED;
            return true;
        }

        size_t getCurrentSize() {
            return current_size_;
        }

        int getTableSize() {
            return array_.size();
        }

        int getNumCollisions() {
            return numCollisions;
        }

        int getNumProbes() {
            return currentNumProbes;
        }

        void resetNumProbes() {
            currentNumProbes = 1;
        }

        // return array to test if valid
        std::vector<HashedObj> getArrayElements() {
            std::vector<HashedObj> objectArray;

            for (size_t i = 0; i < array_.size(); i++)
                objectArray.push_back(array_[i].element_);

            return objectArray;
        }
        
    private:
        struct HashEntry {
            HashedObj element_;
            EntryType info_;
            
            HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
            : element_{e}, info_{i} { }
            
            HashEntry(HashedObj && e, EntryType i = EMPTY)
            : element_{std::move(e)}, info_{ i } {}
        };
    
        std::vector<HashEntry> array_;
        size_t current_size_;
        int numCollisions = 0;
        int currentNumProbes = 1;

        bool IsActive(size_t current_pos) const
        { return array_[current_pos].info_ == ACTIVE; }

        /** @brief performs collision resolution. Helper function for 
         *  Insert, linear implementation.
         *  @param x will be inserted with a linear algorithm, so our
         *  offset will always be 1. */
        size_t FindPos(const HashedObj & x)  {
            size_t current_pos = InternalHash(x);
            
            while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
                current_pos++;  // Compute ith probe.
                numCollisions++; // Add to global variable for collision count
                currentNumProbes++;
                if (current_pos >= array_.size()) // wrap
                    current_pos -= array_.size();
            }
            return current_pos;
        }

        void Rehash() {
            std::vector<HashEntry> old_array = array_;

            // Create new double-sized, empty table.
            array_.resize(NextPrime(2 * old_array.size()));
            for (auto & entry : array_)
            entry.info_ = EMPTY;
            
            // Copy table over.
            current_size_ = 0;
            for (auto & entry :old_array)
            if (entry.info_ == ACTIVE)
            Insert(std::move(entry.element_));
        }
        
        size_t InternalHash(const HashedObj & x) const {
            static std::hash<HashedObj> hf;
            return hf(x) % array_.size( );
        }
};

#endif // LINEAR_PROBING