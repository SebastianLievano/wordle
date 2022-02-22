#include "wordleBot.h"

string calculateResult(string answerWord, string inputWord){
    unordered_map<char, int> ansLets;
    unordered_map<char, int> inpLets;
    string ansResult;
    char c;
    ansResult.resize(5);
    for(int i = 0; i < 5; ++i){
        ansLets[answerWord[i]]++;
    }
    for(int i = 0; i < 5; ++i){
        if(answerWord[i] == inputWord[i]){
            ansResult[i] = 'G';
            ansLets[inputWord[i]]--;
        }
    }
    for(int i = 0; i < 5; ++i){
        c = inputWord[i];
        if(ansResult[i] == 'G') continue;
        if(ansLets[c]){
            ansResult[i] = 'Y';
            ansLets[c]--;
        }
        else ansResult[i] = 'B';
    }
    return ansResult;
}


void testSuite(wordleBot& bot){
    string correctAnswer, input, result;
    string startingWord = "crate";
    double average;
    unordered_map <int, vector<string> > guesses;
    vector<int> ans;
    int inp;
    bool guessed;
    for(int i = 0; i < 2315; ++i){
        bot.reset();
        correctAnswer = bot.getAnswerWord(i);
        result = calculateResult(correctAnswer, startingWord);
        if(correctAnswer == startingWord){
            guesses[1].push_back(startingWord);
            // cout << "Guessed slate in 1 turn" << endl;
            continue;
        }
        bot.updateAnswers(result, startingWord);
        bot.updateMaps();
        guessed = false;
        for(int turn = 2; turn < 7; ++turn){
            inp = bot.getBestInput();
            if(inp == -1){
                ans = bot.getAnswers();
                if(ans.size() == 0){
                    cout << correctAnswer << endl;
                    break;
                }
                input = bot.getAnswerWord(bot.getAnswers().at(0));
                bot.removeFirstAnswerOption();
            }
            else input = bot.getInputWord(inp);
            if(input == correctAnswer){
                guesses[turn].push_back(correctAnswer);
                // cout << "Guessed " << correctAnswer << " in " << turn << "s" << endl;
                guessed = true;
                break;
            }
            result = calculateResult(correctAnswer, input);
            bot.updateAnswers(result, input);
            bot.updateMaps();
        }
        if(!guessed){
            guesses[0].push_back(correctAnswer);
            cout << "FAILED to guess " << correctAnswer << endl;
        }
    }
    for(int i = 1; i < 7; ++i){
        cout << i << " guesses: " << guesses[i].size() << endl;
        average += (guesses[i].size()*i);
    }
    cout << "FAILURES: ";
    for(int i = 0; i < guesses[0].size(); ++i)cout << guesses[0][i] << " ";
    average += (guesses[0].size()*7);
    average = average/2314;
    cout << "\nAverage numGuesses = " << average << endl;
}



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
    bestInput = bot.getBestInput();
    cout << bot.getInputWord(bestInput);
    for(int i = 0; i < 7; ++i){
        numAnsLast = numAns;
        numAns = bot.getNumRemainingAnswers();
        if(i == 0){
            bot.firstTurn();
            goto invalid;
        }
        bestInput = bot.getBestInput();
        ans = bot.getAnswers();
        if(bestInput == -1){
            bot.removeFirstAnswerOption();
            cout << "Best input is: " << bot.getAnswerWord(ans[0]) << endl;
        }
        else cout << "Best input is " << bot.getInputWord(bestInput) << endl;
        cout << numAns << " remaining potential answers" << endl;
        cout << "Potential Answers include: " << endl;
        for(int i = 0; i < ans.size(); ++i){
            cout << bot.getAnswerWord(ans[i]) << endl;
        }
        invalid:
        cout << "\nyour input: ";
        cin >> input;
        cout << "B for Gray/black, G for green, Y for yellow\nresult: ";
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