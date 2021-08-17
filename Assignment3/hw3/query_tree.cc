// Leonardo Matone
// Main file for Part 2.1 of Homework 3.

#include "avl_tree.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

namespace {
// @dbx_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be empty.
template <typename TreeType>
void QueryTree(const string &dbx_filename, TreeType &a_tree) {
  // Code for running Part 2.1

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

  // Print entire tree:
  // a_tree.printTree();
} // QueryTree
} // namespace

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string dbx_filename(argv[1]);
  cout << "Input filename is " << dbx_filename << endl << endl;
  AvlTree<SequenceMap> a_tree;
  QueryTree(dbx_filename, a_tree);

  string input_line;
  getline(cin, input_line);
  stringstream input_stream(input_line);

  while (!input_line.empty()) {
    string sequence = input_line;
    vector<string> acronyms = a_tree.findAcronym(sequence);
    if (acronyms == vector<string>()) 
      cout << "Not Found";
    for (int i = 0; i < acronyms.size(); i++)
      cout << acronyms[i] << " ";
    cout << endl;
    getline(cin, input_line);
  }

  return 0;
}
