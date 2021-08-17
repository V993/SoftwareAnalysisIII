#include <iostream>
#include <string>

using namespace std;

int main() {
    string word = "abacination";
    string word2 = "abacination";   // Case A
    string word3 = "abacination"; // Case B
    string word4 = "abacination";  // Case C

    hash<string> hf;
    cout << word << " --> " << hf(word) % 101 << endl;
    cout << word2 << " --> " << hf(word2) % 101 << endl;
    cout << word3 << " --> " << hf(word3) % 101 << endl;
    cout << word4 << " --> " << hf(word4) % 101 << endl;
}

                // // test all helper case functions
                // if (caseA(input_word) != vector<string>{}) {
                //     suggestion = caseA(input_word);
                //     suggestionCase = 0;
                // }
                // if (caseB(input_word) != vector<string>{}) {
                //     suggestion = caseB(input_word);
                //     suggestionCase = 1;
                // }
                // if (caseC(input_word) != vector<string>{}) {
                //     suggestion = caseC(input_word);
                //     suggestionCase = 2;
                // }

                    

                // cout << "*** " << input_word << " ->" <<  suggestion;

                // switch (suggestionCase) {
                //     case 0:
                //         cout << " *** case A" << endl;
                //         break;
                //     case 1:
                //         cout << " *** case B" << endl;
                //         break;
                //     case 2:
                //         cout << " *** case C" << endl;
                //         break;
                //     default:
                // }