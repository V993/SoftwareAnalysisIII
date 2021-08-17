/** @author Leonardo Matone
 *  @brief implementation of a hash testing algorithm
 *  @date 4.12.21 */

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/** Test Hash Table Implementation:
 *  @brief constructs a hash table based off an input words file, 
 *  outputs data from the newly established table, and checks words
 *  in a query file against the hash table to see if they are matched.
 *  @param words_filename, a dictionary file to base our hash table from
 *  @param query_filename, a file containing words to check against the 
 *  table.  */
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
    // cout << "TestFunctionForHashTables..." << endl;
    // cout << "Words filename: " << words_filename << endl;
    // cout << "Query filename: " << query_filename << endl;
    hash_table.MakeEmpty();  

    // add words from words_filename into our table:
    string current_word;
    ifstream words_stream(words_filename);

    while(words_stream >> current_word) {
        // each line contains only one word. 
        // no need to parse, just Insert:
        hash_table.Insert(current_word);
    }

    // Output contents of hash array_ member for tests:
    // vector<string> arrayWords = hash_table.getArrayElements();
    // /* Test array construction */
    // for (size_t i = 0; i < arrayWords.size(); i++) {
    //     if (arrayWords[i] == "out")
    //         cout << "\t\tit do be in here dog" << endl;
    //     // cout << i << ": " << arrayWords[i] << endl;
    // }
    
    // establish our variables to properly implement our expressions below 
    int N = hash_table.getCurrentSize();
    int T = hash_table.getTableSize();
    int C = hash_table.getNumCollisions();

    // Output results:
    cout << "number_of_elements: " << N << endl;
    cout << "size_of_table: " << T << endl;
    cout << "load_factor: " << (float)N / (float)T << endl;
    cout << "average_collisions: " << (float)C / (float)N << endl;
    cout << "total_collisions: " << C << endl;

    cout << '\n';

    // test each word to see if it's in the table:
    string input_word;
    ifstream input_stream(query_filename);

    hash_table.resetNumProbes();

    while(getline(input_stream, input_word)) {
        cout << input_word;
        if (hash_table.Contains(input_word))
            cout << " Found ";
        else
            cout << " Not_Found ";
        cout << hash_table.getNumProbes() << endl;
        hash_table.resetNumProbes();
    }
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 97;
    if (argument_count == 5) {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);   
    }

    if (param_flag == "linear") {
        // cout << "Linear:" << endl;
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                                query_filename);
    } else if (param_flag == "quadratic") {
        // cout << "Quadratic:" << endl;
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    } else if (param_flag == "double") {
        // cout << "Double:" << endl;
        cout << "r_value: " << R << endl;
        HashTableDouble<string> double_probing_table;
        double_probing_table.SetR(R);
        TestFunctionForHashTable(double_probing_table, words_filename,
                                query_filename);
    } else {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

/*
    Expected output format: 

        number_of_elements: <int>
        size_of_table: <int>
        load_factor: <float>
        average_collisions: <float>
        total_collisions: <int>
        <new line>
        <word1> Found <probes1>
        <word2> Not_Found <probes2>
        <word3> Found <probes3>
*/

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED