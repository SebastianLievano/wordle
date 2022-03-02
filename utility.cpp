#include "wordleBot.h"

string calculateResult(string answerWord, string inputWord);

int simulateWord(string word, string startWord, wordleBot& bot);

bool simulateTurn(string word, wordleBot &bot);

void printResults(unordered_map < int, vector<string> > guesses);

bool playTurn(wordleBot& bot, int mode);

void wordleGame(wordleBot& bot){
    int mode;
    bool done = false;
    string firstWord, result;
    restart:
    cout << "WORDLE GAME" << endl;
    cout << "Modes:\n0) Choose your own words\n1) Bot assumes you inputted its recommended move\n";
    cin >> mode;
    if(mode != 0 && mode != 1) goto restart;
    bot.firstTurn();
    cout << "Please input the word you inputted: ";
    cin >> firstWord;
    cout << "Please input the result: ";
    cin >> result;
    bot.updateAnswers(result, firstWord);
    bot.updateMaps();
    while(!done){
        done = playTurn(bot, mode);
    }
}

void testSuite(wordleBot& bot){
    unordered_map < int, vector<string> > guesses;
    string startWord;
    int turnsTaken;
    invalidStartWord:
    cout << "Please insert starting word: ";
    cin >> startWord;
    if(startWord.length() != 5) goto invalidStartWord;
    for(int i = 0; i < 2315; ++i){
        turnsTaken = simulateWord(bot.getAnswerWord(i), startWord, bot);
        if(turnsTaken < 7) guesses[turnsTaken].push_back(bot.getAnswerWord(i));
        else guesses[0].push_back(bot.getAnswerWord(i));
    }
    cout << "Starting Word: " << startWord << endl;
    printResults(guesses);
}

string calculateResult(string answer, string input){
    unordered_map<char, int> ansLets;
    string ansResult;
    ansResult.resize(5);    //making empty 5-length string
    //Getting answer letters frequency
    for(int i = 0; i < 5; ++i) ansLets[answer[i]]++;
    //Going through greens first
    //This is because greens ALWAYS behave the same, even in duplicate situations
    for(int i = 0; i < 5; ++i){
        if(answer[i] == input[i]){
            ansResult[i] = 'G';
            ansLets[input[i]]--;    //Lowering answer frequency of letter
        }
    }
    for(int i = 0; i < 5; ++i){
        if(ansResult[i] == 'G') continue;   //skipping greens
        if(ansLets[input[i]]){         //If the letter exists, 
            ansResult[i] = 'Y'; //That result is a yellow
            ansLets[input[i]]--;       //Lowering answer Frequency
        }
        else ansResult[i] = 'B';    //else letter not in answer so gray
    }
    return ansResult;
}

bool playTurn(wordleBot &bot, int mode){
    string bestInput, result;
    inpId id = bot.getBestInput();
    vector<int> ans = bot.getAnswers();
    if(ans.size() == 0) cout << "No Potential Answers" << endl;
    if(ans.size() == 1){
        cout << "ONE REMAINING POTENTIAL ANSWER: " << bot.getAnswerWord(ans[0]) << endl;
        return true;
    }
    if(id == -1){
        bestInput = bot.getAnswerWord(ans[0]);
        if(mode == 1){
            cout << "Removing inputted answer: " << bot.getAnswerWord(ans[0]) << endl;
            bot.removeFirstAnswerOption();
        }
    }
    else bestInput = bot.getInputWord(id);
    invalid:
    cout << "Your best input is " << bestInput << endl;
    if(!mode){
        cout << "Your input: " << endl;
        cin >> bestInput;
    }
    cout << "B for Gray/black, G for green, Y for yellow\nresult: " << endl;
  
  
    cin >> result;
    if(result.length() != 5 || bestInput.length() != 5) goto invalid;
    for(int i = 0; i < 5; ++i){
        if(result[i] != 'B' && result[i] != 'G' && result[i] != 'Y') goto invalid;
    }
    cout << "Valid Input!" << endl;
    bot.updateAnswers(result, bestInput);
    cout << "Updated Answers!" << endl;
    bot.updateMaps();
    return false;
}   

int simulateWord(string word, string startWord, wordleBot& bot){
    string result;
    int turn = 1;
    bool guessed;
    bot.reset();
    if(startWord == word) return 1;
    result = calculateResult(word, startWord);
    bot.updateAnswers(result, startWord);
    bot.updateMaps();
    while(!guessed){
        guessed = simulateTurn(word, bot);
        turn++;
    }
    return turn;
}

bool simulateTurn(string word, wordleBot &bot){
    string input, result;
    inpId id = bot.getBestInput();
    if(id == -1){
        vector<ansId> ans = bot.getAnswers();
        input = bot.getAnswerWord(bot.getAnswers().at(0));
        bot.removeFirstAnswerOption();
    }
    else input = bot.getInputWord(id);
    if(input == word){
        return true;
    }
    result = calculateResult(word, input);
    bot.updateAnswers(result, input);
    bot.updateMaps();
    return false;
}


void printResults(unordered_map < int, vector<string> > guesses){
    double average;
    int graphing, numWords;
    cout << "Guesses required:\n";
    for(int i = i; i < 7; ++i){
        numWords = guesses[i].size();
        cout << i << "guesses:  ";
        graphing = floor(numWords/25);
        if(numWords) cout << "|";
        for(int i = 0; i < graphing; ++i) cout << "|";
        cout << " " << numWords << endl;
        average += (numWords*i);
    }
    cout << guesses[0].size() << " FAILURES: ";
    for(int i = 0; i < guesses[0].size(); ++i){
        cout << guesses[0][i] << " ";
    }
    average = average/2315;
    cout << "\nAverage Guesses to get Word = " << average << endl;
}