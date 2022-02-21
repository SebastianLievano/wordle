#include "wordleBot.h"


int main(){
    int dummy, numAns, numAnsLast;
    wordleBot bot;
    string input, result;
    pair <double, int> bestInput;
    vector<ansId> ans;
    cout << "WORDLE HELPER" << endl;
    for(int i = 0; i < 7; ++i){
        numAnsLast = numAns;
        numAns = bot.getNumRemainingAnswers();
        if(i == 0){
            bot.firstTurn();
            goto skipped;
        }
        bestInput = bot.getBestInput();
        cout << "Done getting best input" << endl;
        cout << "Your best input is: " << bot.getInputWord(bestInput.second) << "  " << bestInput.first << endl;
        skipped:
        ans = bot.getAnswers();
        cout << "There are " << numAns << " remaining potential answers" << endl;
        cout << "This is " << numAns - numAnsLast << " than before this input" << endl;
        cout << "Potential Answers include: " << endl;
        for(int i = 0; i < ans.size(); ++i){
            cout << bot.getAnswerWord(ans[i]) << endl;
        }
        invalid:
        cout << "Please input the word you inputted: ";
        cin >> input;
        cout << "Please input the result (B for Gray/black, G for green, Y for yellow): ";
        cin >> result;
        if(result.length() != 5 || input.length() != 5) goto invalid;
        for(int i = 0; i < 5; ++i){
            if(result[i] != 'G' && result[i] != 'B' && result[i] != 'Y') goto invalid;
        }
        bot.updateAnswers(result, input);
        bot.updateMaps();
    }
    return 0;
}