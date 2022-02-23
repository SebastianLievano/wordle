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

    // return 0;

    // bestInput = bot.getBestInput();
    // cout << bot.getInputWord(bestInput);
    // for(int i = 0; i < 7; ++i){
    //     numAnsLast = numAns;
    //     numAns = bot.getNumRemainingAnswers();
    //     if(i == 0){
    //         bot.firstTurn();
    //         goto invalid;
    //     }
    //     bestInput = bot.getBestInput();
    //     ans = bot.getAnswers();
    //     if(bestInput == -1){
    //         bot.removeFirstAnswerOption();
    //         cout << "Best input is: " << bot.getAnswerWord(ans[0]) << endl;
    //     }
    //     else cout << "Best input is " << bot.getInputWord(bestInput) << endl;
    //     cout << numAns << " remaining potential answers" << endl;
    //     cout << "Potential Answers include: " << endl;
    //     for(int i = 0; i < ans.size(); ++i){
    //         cout << bot.getAnswerWord(ans[i]) << endl;
    //     }
    //     invalid:
    //     cout << "\nyour input: ";
    //     cin >> input;
    //     cout << "B for Gray/black, G for green, Y for yellow\nresult: ";
    //     cin >> result;
    //     if(result.length() != 5 || input.length() != 5) goto invalid;
    //     for(int i = 0; i < 5; ++i){
    //         if(result[i] != 'G' && result[i] != 'B' && result[i] != 'Y') goto invalid;
    //     }
    //     bot.updateAnswers(result, input);
    //     bot.updateMaps();
    // }
    // return 0;
}







