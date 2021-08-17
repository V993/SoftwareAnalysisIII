/** @author Leonardo Matone
 *  @brief implementation of a spell checking algorithm using double_hashing
 *  @date 4.12.21 */

#include "quadratic_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/** MakeDictionary implementation:
 *  @brief takes input of a dictionary filename, outputs hash 
 *  table containing contents of dictionary.
 *  @returns HashTable utilizing doublehashing containing 
 *  strings from dictionary file. */
HashTableDouble<string> MakeDictionary(const string dictionary) {

    // build a double hash table: 
    HashTableDouble<string> hash_table;
    hash_table.SetR(97); // already set by default, but setting again to be safe
    hash_table.MakeEmpty(); 

    // add words from dictionary to our table:  
    string current_word;
    ifstream words_stream(dictionary);

    while(words_stream >> current_word) {   
        // each line contains only one word.
        // no need to parse, just Insert: 
        hash_table.Insert(current_word);
    }

    // probes counts from our dictionary build should not be counted should we
    // need to count probes in the future
    hash_table.resetNumProbes();

    // Output hash array_
    vector<string> arrayWords = hash_table.getArrayElements();

    /* Test array construction */
    // for (size_t i = 0; i < arrayWords.size(); i++) {
    //     // if (arrayWords[i] == "out")
    //     //     cout << arrayWords[i] << " | found at loc: "<< i << endl;;
    //     cout << i << ": " << arrayWords[i] << endl;
    // }

    return hash_table;
}

/** Helper functions for cases A, B, C
 *  @brief each case takes input of a word and returns 
 *  a vector containing suggested words. */
vector<string> caseA(HashTableDouble<string> *dictionary, string word){ // Add one character in any possible position 
    // set up a vector with alphabet characters for testing:
    vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    string testWord;
    vector<string> recommendations; // set up a vector to add possible recommendations
    bool alreadyNoted; // to test if we have already added this string to the vector.

    for (size_t i = 0; i < word.length(); i++) { // loop through each character
        for (size_t j = 0; j < alphabet.size(); j++) { // loop through each letter in the alphabet
            testWord = word.substr(0,i) + alphabet[j] + word.substr(i,word.size()); // create a new string with the new char from the alpabet
            if (dictionary->Contains(testWord)) { // test to see if the dictionary contains our new word
                alreadyNoted = false;
                for (size_t k = 0; k < recommendations.size(); k++) //loop through our recommendations
                    if (recommendations[k] == testWord) // if we already have this recommendation, set noted to True
                        alreadyNoted = true;
                if (!alreadyNoted) // if our recommendations vector does not already contain this string, add it
                    recommendations.push_back(testWord);
            }
            // else {
            //     cout << "suggestion: " << testWord << endl;
            // }
        }
    }
    return recommendations;
}
vector<string> caseB(HashTableDouble<string> *dictionary, string word){ // Remove one character in any possible position
    vector<string> recommendations; // establish vector for our returns
    bool alreadyNoted;
    for (size_t i = 0; i < word.length(); i++) { // loop through each character in the word
        string testWord = "";
        for (size_t j = 0; j < word.length(); j++) { // loop through each character in the word
            if (i != j) // add every character except for the ith character to our new word
                testWord += word[j]; // this results in a word with all of the characters but one, in [i]
        }
        if (dictionary->Contains(testWord)) { // if the dictionary contains this word, add it
            alreadyNoted = false;
            for (size_t k = 0; k < recommendations.size(); k++) //loop through our recommendations
                if (recommendations[k] == testWord) // if we already have this recommendation, set noted to True
                    alreadyNoted = true;
            if (!alreadyNoted) // if our recommendations vector does not already contain this string, add it
                recommendations.push_back(testWord);
        }
        // else
        //     cout << "dictionary does not contain: " << testWord << endl;
    }
    return recommendations;
}
vector<string> caseC(HashTableDouble<string> *dictionary, string word) { // Swap any two adjacent characters 
    vector<string> recommendations;
    bool alreadyNoted;
    for (size_t i = 0; i < word.length()-1; i++) { // loop through each character except the last, as we go one ahead
        swap( word[i] , word[i+1] ); //swap the ith position with the i+1 position
        
        if (dictionary->Contains(word)) { // if the dictionary contains this word, add it
            alreadyNoted = false;
            for (size_t k = 0; k < recommendations.size(); k++) //loop through our recommendations
                if (recommendations[k] == word) // if we already have this recommendation, set noted to True
                    alreadyNoted = true;
            if (!alreadyNoted) // if our recommendations vector does not already contain this string, add it
                recommendations.push_back(word);
        }

        swap( word[i] , word[i+1] ); // swap the positions back
    }
    return recommendations;
}
// extra case added for kicks, very similar to caseA but REPLACES a character instead of adding. Unannoted.
vector<string> caseD(HashTableDouble<string> *dictionary, string word){ // Replace one character in any possible position
    vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    string testWord;
    vector<string> recommendations;

    for (size_t i = 0; i < word.length(); i++) {
        char currentChar = word[i];
        for (size_t j = 0; j < alphabet.size(); j++) {
            word[i] = alphabet[j];
            if (dictionary->Contains(word))
                recommendations.push_back(word);
        }
        word[i] = currentChar;
    }
    return recommendations;
}

/** SpellChecker implementation:
 *  @brief compares a text document's words against an
 *  input dictionary. For each incorrect word, outputs
 *  a suggested change to make the word correct.  */
void SpellChecker(HashTableDouble<string> &dictionary, const string document_filename) {
    
    string input_line, input_word;
    ifstream input_stream(document_filename);
    
    // parse through each line
    while(getline(input_stream, input_line)) {
        stringstream line(input_line);
 
        // parse through each word in the line
        while (line >> input_word) {

            // if the selected portion of our line contains end punctuation, remove the punctuation:
            if ((input_word[input_word.size()-1] == '!') | (input_word[input_word.size()-1] == ':') | 
                (input_word[input_word.size()-1] == '.') | (input_word[input_word.size()-1] == '?') | 
                (input_word[input_word.size()-1] == ',') | (input_word[input_word.size()-1] == ';') )
                {
                    input_word = input_word.substr(0,input_word.size()-1);
                }

            // if the selected portion of our line is inside of quotes or brackets, remove them:
            if ((input_word[input_word.size()-1] == '[') | (input_word[input_word.size()-1] == ']') | 
                (input_word[input_word.size()-1] == '(') | (input_word[input_word.size()-1] == ')') |
                (input_word[input_word.size()-1] == '"') | (input_word[input_word.size()-1] == '"') |
                (input_word[input_word.size()-1] == '\'') | (input_word[input_word.size()-1] == '\'') )
                {
                    input_word = input_word.substr(1,input_word.size()-1);
                }

            // the conciseness of this line below may give away that it is not mine, I did some research
            // into quick lowercase methods in STL and found the following approach from: 
            // https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
            transform(input_word.begin(), input_word.end(), input_word.begin(), ::tolower);

            // OUTPUT 
            cout << input_word;

            if (dictionary.Contains(input_word)) // word is correct
                cout << " is CORRECT" << endl;
            else {  
                cout << " is INCORRECT" << endl;

                // test each case for suggestions, output accordingly:
                vector<string> suggestionA = caseA(&dictionary, input_word);
                for (size_t i = 0; i < suggestionA.size(); i++) {
                    cout << "*** " << input_word << " -> " << suggestionA[i] << " *** case A" << endl;
                }
                vector<string> suggestionB = caseB(&dictionary, input_word);
                for (size_t i = 0; i < suggestionB.size(); i++) {
                    cout << "*** " << input_word << " -> " << suggestionB[i] << " *** case B" << endl;
                }
                vector<string> suggestionC = caseC(&dictionary, input_word);
                for (size_t i = 0; i < suggestionC.size(); i++) {
                    cout << "*** " << input_word << " -> " << suggestionC[i] << " *** case C" << endl;
                }
            } // else
        } // while stringstream
    } // while ifstream
} // SpellChecker

/***/
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Create dictionary:
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);

    dictionary.SetR(97); // Set default value of R to 97 for efficiency

    // Check input document against the established dictionary table:
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    cout << endl;

    testSpellingWrapper(argc, argv);

    return 0;
}
