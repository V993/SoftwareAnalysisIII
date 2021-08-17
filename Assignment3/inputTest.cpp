#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void QueryTree(const string &dbx_filename) {
  // Code for running Part 2.1
  // You can use public functions of TreeType. For example:

  string db_line;
  ifstream db_stream(dbx_filename);

  // Disregard the header
  for (int i = 0; i < 9; i++) {
    getline(db_stream, db_line);
  }

  while(getline(db_stream, db_line))
  {
    // PARSING STRING:
    // | UcoMSI/GAGCTCNNNNN'NN/'NNNNNNNGAGCTC//   <--- example for tests
    string an_enz_acro = db_line.substr(0, db_line.find('/'));
    // | GAGCTCNNNNN'NN/'NNNNNNNGAGCTC//
    string recognitionSequences = db_line.substr(db_line.find('/')+1, db_line.size());
    // | GAGCTCNNNNN'NN
    string a_reco_seq = recognitionSequences.substr(0, recognitionSequences.find('/'));;
    // | /'NNNNNNNGAGCTC//
    string remainingString = recognitionSequences.substr(a_reco_seq.size(), recognitionSequences.size());

    // loop through and get the other remaining strings, stop when we hit "", i.e. between '//'
    while (a_reco_seq != ""){
      // SequenceMap new_sequence_map(a_reco_seq, an_enz_acro); // add new sequence
      a_reco_seq = remainingString.substr(1, remainingString.find('/'));
      remainingString = remainingString.substr(a_reco_seq.size(), remainingString.size());// find next sequence 
    } // end second while
  } // end first while
} //end Query Tree

int main(int argc, char **argv) {
    cout << "running!" << endl;
    if (argc != 2) {
      cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
      return 0;
    }
    const string dbx_filename(argv[1]);
    cout << "Input filename is " << dbx_filename << endl;
    // Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
    QueryTree(dbx_filename);

    return 0;
}

/**
             NON-RELATED TO PROJECT, SEPERATE FUNCTION.
    test current node, if the value is the sequence, return it. 
    if the current node has no element, return nullptr.
    If the value is not the sequence, make two recursive calls 
    to right and left and recursively test the entire tree.
    if the current node has no children, do not make recursive calls.

Comparable* alreadyInSequence(string sequence, AvlNode * & t) {    
    if (t == nullptr)
        return nullptr;

    // the SequenceMap of the node we are currently in (not root)
    Comparable testSequence = (t->element);
    // cout << "currently testing: \n\t" << testSequence.getSequence() << "\n\t" << sequence << endl;
    if (testSequence.getSequence() == sequence) { // sequence
        cout << "this sequence has a duplicate! Duplicates:\n" << 
              "\t\t" << sequence << " = " << testSequence.getSequence() << endl;
        return &(t->element);
    }
    else {
        // cout << "this particular sequence is not the same. Testing children: " << endl;
        if (t->left != nullptr) {
            Comparable *leftSequenceResult = alreadyInSequence(sequence, t->left);
            if (leftSequenceResult != nullptr) return leftSequenceResult;
        }
        if (t->right != nullptr) {
            Comparable *rightSequenceResult = alreadyInSequence(sequence, t->right);
            if (rightSequenceResult != nullptr) return rightSequenceResult;
        }
    }
    // cout << "this sequence has no duplicates... yet. hehe" << endl;
    return nullptr;
}
**/