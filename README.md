**WORDLE BOT**

This bot calculates the optimal inputs to solve the popular game wordle.

Wordle Instructions: https://www.cnet.com/how-to/wordle-everything-you-need-to-know-about-the-viral-word-game/

USAGE INSTRUCTIONS:

Insert the word you inputted in LOWERCASE.

Then insert the result in UPPERCASE.
Gray/Black Tiles - 'B'
Yellow Tiles - 'Y'
Green Tiles - 'G'

The program will then calculate your best inputs and return the best one.

Repeat until you've completed your wordle.

Success is largerly based on the first word you select. Included below are the average stats for this bot using different
starting words (Using version 1.0 - Feb 21th) The best average per word comes from SLATE, but CRANE is the only starting word 
which guarantees completing all words.

Word    AVG.    Num Failed
slate   3.675   1
crane   3.731   0
crate   3.733   2
salet   3.747   6
tares   3.824   10
oater   3.872   7
realo   3.994   10
adieu   3.994   10

The bot also has the option to test different starting words and get the average results. FOR EXAMPLE:

Starting Word: Adieu
Duration: 160 seconds
Duration/Word: ~12 ms
1 guesses:   0
2 guesses:   ||34
3 guesses:   |||||||||||||||||||||||571
4 guesses:   |||||||||||||||||||||||||||||||||||||||||||||||1171
5 guesses:   |||||||||||||||||||463
6 guesses:   |||66
FAILURES: 10
Words Failed: caste paste petal shave state stave taste vocal waste whose 
Average Guesses to get Word = 3.99568

HOW DOES THIS BOT WORK?
NOTE: ∩ = intersection of sets (part of both)
      - = subtract all terms in this vector from first vector
The bot tracks and updates the list of potential answers based on user inputted result information.
All information is stored in a vector of <char, vector < wordID > > unordered maps. 
The index is the position, and indexes 5 and 6 are used to store all words with the letter and words with the letter duplicated respectively.
For Green tiles: CurrentPotentialAnswers ∩ ansMap[position][letter]
For Yellow tiles: (CurrentPotentialAnswers ∩ ansMap[ALL][letter]) - ansMap[position][letter]
For Gray tiles: CurrentPotentialAnswers - ansMap[ALL][letter]

Once the lists are updated, a score is calculated for every potential guess using the formula:

WordScore = Σ letterFreq[letter]

The current version of the bot does not account for duplicates. It will only add the frequency of a letter once.





