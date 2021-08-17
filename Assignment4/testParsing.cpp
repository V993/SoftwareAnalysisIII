#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//outdated algorithm:

void SpellChecker(const string document_filename) {
    
    string input_line, input_word;
    ifstream input_stream(document_filename);
    size_t end;
    
    // parse through each line
    while(getline(input_stream, input_line)) {
        // parse through every word in the line
        while(input_line != "") { // if the line is not empty,
            if (input_line.find(" ") != std::string::npos) { // collect the first word, if there is a space.
                input_word = input_line.substr(0, input_line.find(" ")); // get the first word in the line
                input_line = input_line.substr(input_word.length()+1, input_line.size()); // get the remaining string
            }
            else { //if there is no space, this must be the last word. Collect it and exit the loop.
                input_word = input_line.substr(0, input_line.length());
                input_line = "";
            }
            cout << "->" + input_word + "<-" << endl;
        }        
    }
}

int main(int argc, char** argv) {
    cout << "testing parsing... " << endl;
    SpellChecker(argv[1]);
}