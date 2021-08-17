// Leonardo Matone
// Main file for Part 2.3 of Homework 3.

#include "avl_tree_mod.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

namespace {

// @dbx_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &dbx_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part 2.2

/* ------------------------------------------------------------------------------------------------------------------------ */
/*                                    SAME AS HWK2                                                                          */
/* ------------------------------------------------------------------------------------------------------------------------ */
  string db_line;
  ifstream db_stream(dbx_filename);

  // Disregard the header
  for (int i = 0; i < 9; i++) {
    getline(db_stream, db_line);  
  }

  // Iterate through important data lines:
  while(getline(db_stream, db_line))
  {
    // PARSING STRING:
    // | UcoMSI/GAGCTCNNNNN'NN/'NNNNNNNGAGCTC//   <--- example for tests

    // | UcoMSI
    string an_enz_acro = db_line.substr(0, db_line.find('/'));
    // | GAGCTCNNNNN'NN/'NNNNNNNGAGCTC//
    string recognitionSequences = db_line.substr(db_line.find('/')+1, db_line.size());
    // | GAGCTCNNNNN'NN
    string a_reco_seq = recognitionSequences.substr(0, recognitionSequences.find('/'));;
    // | /'NNNNNNNGAGCTC//
    string remainingString = recognitionSequences.substr(a_reco_seq.size(), recognitionSequences.size());

    // loop through and get the other remaining strings, stop when we hit "", i.e. between '//'
    while (a_reco_seq != ""){
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro); // add new sequence (value from outside of loop initially)
      a_tree.insert(new_sequence_map);
      remainingString = remainingString.substr(1, remainingString.size());
      a_reco_seq = remainingString.substr(0, remainingString.find('/'));
      remainingString = remainingString.substr(a_reco_seq.size(), remainingString.size());// find next sequence 
    } // end second while
  } // end first while

/* ------------------------------------------------------------------------------------------------------------------------ */
/*                              HWK3 ADDITIONS:                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------ */
  
  // get number of nodes from getter function
  int N = a_tree.getNumNodes();
  cout << "2: " << N << endl;

  // calculate depth with avgDepth function
  float avgDepth = a_tree.getAvgDepth();
  cout << "3a: " << avgDepth << endl;

  // calculate avdDepth/log2(N) and output
  float ratio = avgDepth / (float)(log2 (N));
  cout << "3b: " << ratio << endl;

    //establish a newSequence string for each line in input
  string newSequence;
  ifstream input_stream(seq_filename);

  // vector for sequenceMaps and vector for input strings for further use
  vector<SequenceMap> matched;
  // vector<string> listSequences;

  // go through the input and add sequences to string vecto 
  while(getline(input_stream, newSequence)) {
    // instantiate a new sequenceMap with single parameter constructor 
    SequenceMap sequence(newSequence);

    // add new sequence SequenceMap vector
    matched.push_back(sequence);
  }

  // initial value of numCalls needs to be zero
  int numCalls = 0;
  // call find function with sequencemap vector, returns the number of calls
  numCalls = a_tree.find(matched);

  // get number of queries from getter function getNumQueries
  cout << "4a: " << a_tree.getNumQueries() << endl;

  // calculate the avgCalls from numCalls / numQueries
  float avgCalls =  (float)numCalls / (float)a_tree.getNumQueries();
  cout << "4b: " << avgCalls << endl;

  // call remove function with sequencemap vector
  a_tree.removeBySequence(matched);

  // get number of recursion calls
  cout << "5a: " << a_tree.getNumSuccessfulRemoves() << endl;
  cout << "5b: " << (float)a_tree.getNumRecursiveCalls() / (float)a_tree.getNumSuccessfulRemoves() << endl;

  // update values after remove:
  N = a_tree.getNumNodes();
  avgDepth = a_tree.getAvgDepth();
  ratio = avgDepth / (float)(log2 (N));
  cout << "6a: " << N << endl;
  cout << "6b: " << avgDepth << endl;
  cout << "6c: " << ratio << endl;
} // TestTree
}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  const string seq_filename(argv[2]);
  cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;
  AvlTree<SequenceMap> a_tree;
  TestTree(dbx_filename, seq_filename, a_tree);

  return 0;
}
