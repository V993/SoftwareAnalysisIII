// Leonardo Matone
// Part 1: Sequence Map object class

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <sstream>

using namespace std;

class SequenceMap {
    public:

/**---------------------------------------------------------------------------------------**/
/**                                        BIG FIVE                                       **/
/**---------------------------------------------------------------------------------------**/

        /** Zero-paremeter constructor 
         * empty string, empty array initialization */
        SequenceMap() : recognition_sequence_{""}, enzyme_acyonyms_{} {}

        /** Copy constructor
         * @param copy the SequenceMap object to base our new object from */
        SequenceMap(const SequenceMap &copy) = default;

        /** Copy assignment operator
         * @param copy the SequenceMap object to base our new object from */
        SequenceMap& operator=(const SequenceMap &copy) = default;

        /** Move constructor
         * @param copy the SequenceMap object to base our new object from */ 
        SequenceMap(SequenceMap &&copy) = default;

        /** Move assignment operator
         * @param copy the SequenceMap object to base our new object from */
        SequenceMap& operator=(SequenceMap &&copy) = default;

        // Destructor
        ~SequenceMap() = default;

/**---------------------------------------------------------------------------------------**/
/**                              ADDITIONAL MEMBER FUNCTIONS                              **/
/**---------------------------------------------------------------------------------------**/

        /** Constructor
         * @param a_rec_seq a recognition sequence string in memory (address)
         * @param an_enz_acro an enzyme acronym string in memory (address)
         * @brief establishes a new SequenceMap object with the provided 
         * recognition string and pushes the provided enzyme acronym into 
         * the our enzyme acronym vector datamember. */
        SequenceMap(const string &a_rec_seq, const string &an_enz_acro) {
            recognition_sequence_ = a_rec_seq;
            enzyme_acyonyms_.push_back(an_enz_acro);
        }

        /** Single-Parementer Constructor
         * @param sequence a recognition sequence string
         * @brief creates a new SequenceMap object with an empty enzyme_acronyms
         * vector, for the purpose of comparisons between nodes and easier passing
         * between functions in later tests.
         * **/
        SequenceMap(string sequence) : recognition_sequence_{sequence}, enzyme_acyonyms_{} {}

        /** Basic getter functions getSequence/getEnzymeAcronyms */
        string getSequence() const {return recognition_sequence_;}
        vector<string> getEnzymeAcronyms() const {return enzyme_acyonyms_;}

        /** Bool Operator
         * @param rhs the rvalue of the < operator
         * @brief operates based on regular string comparison between the 
         * lvalue and rvalue recognition_sequence_ strings. */
        bool operator<(const SequenceMap &rhs) const {
            return (this->recognition_sequence_ < rhs.recognition_sequence_);
        }

        /** Overload << Operator */
        friend ostream &operator<<(ostream &out, const SequenceMap &some_sequence_map) {
            for (int i = 0; i < some_sequence_map.enzyme_acyonyms_.size(); i++){
                out << (some_sequence_map.enzyme_acyonyms_[i]) << " ";
            }
            return (out << endl);
        }

        /** Merge
         * @param other_sequence is the second sequence to be merged with the 
         * caller sequence. Assumes object's recognition_sequence_ and other
         * recognition_sequence_ are equal to each other.
         * @brief merges two sequences together into the caller sequence,
         * merging the caller's enzyme_acronym_ with the other sequence. */
        void Merge(const SequenceMap &other_sequence) {
            for (int i = 0; i < other_sequence.enzyme_acyonyms_.size(); i++) {
                // cout << "pushng: " << other_sequence.enzyme_acyonyms_[i] << " into caller." << endl;
                enzyme_acyonyms_.push_back(other_sequence.enzyme_acyonyms_[i]);
            }
        }

    private:
        string recognition_sequence_;
        vector<string> enzyme_acyonyms_;
};


/****** NONRECURSIVE VERSION*************************
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
*****************************************************/