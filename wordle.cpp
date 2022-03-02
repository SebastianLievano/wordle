#include "wordleBot.h"

void testSuite(wordleBot& bot);

void wordleGame(wordleBot& bot); 




int main(){
    int dummy, numAns, numAnsLast, bestInput;
    wordleBot bot;
    string input, result;
    vector<ansId> ans;
    cout << "WORDLE HELPER" << endl;
    invalid1:
    cout << "Press 1 to play wordle, 2 to run test suite" << endl;
    cin >> dummy;
    if(dummy == 2) testSuite(bot);
    else if(dummy == 1) wordleGame(bot);
    else goto invalid1;
    return 0;
}







