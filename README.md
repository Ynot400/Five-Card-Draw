# Five-Card-Draw
Project Report: Tampa Five Card Draw in C++ 

Created by Joshua-Luke Lacsamana, Josiah Varghese, and Isaac Powell 

Abstract/Overview 

Tampa Five Card Draw is our variant of the classic card game Poker, in which players are given a hand of five cards instead of getting a pair of cards. Tampa Five Card Draw has the same functionality as poker when it comes to betting chips, folding your cards, or checking, just with the difference that there are no “common cards,” and the winner is based on who has the better hand. Our variant has some unique rules: Aces are always high, suit values only matter in royal flushes, straights can’t be broken, and, in the case of a hand-rank tie (for example, both players have a pair of 2’s), a tie is given instead of determining follow-up high cards. This game has been executed by us in c++, and more info about how the game works can be found through this link. https://www.wikihow.com/Play-Five-Card-Draw 

Details of the Implementation 

Introduction 

The Project is created through C++. We have several classes and functions that make our code sequence into modular blocks.  

Classes and Functions 

Class Card 

First, we define the properties of a card object. The card has the following private variables: 

int value; 

// the following two variables are used to evaluate the hands, they are numerical  

// versions of the name and suit of the card to better handle the evaluation 

int Point_Name; 

int Point_Suit; 

// string representations of the name and suit (i.e. “hearts”, “Ace”, “diamond”, etc.) 

string name; 

string suit; 

Class Card Functions 
We have quick public functions that allow us to access these values, such as getName(), getSuit(), etc. 

 

 

Class Deck 

This class will allow us to store our card objects into a stack, which is how real-life decks work. Whenever a deck is called, it calls the initializeDeck() function that will initialize 52 cards akin to a deck. The Deck class comes with a variety of functions to deal with our cards in the deck stack. 

 

Void initializeDeck() 

Gets activated upon initialization of a deck object variable. Creates the standard deck of 52 cards and pushes them into a stack. Note that the deck is in order during this process, and it will be shuffled later for randomized gameplay. 

 

Void printDeck() 

Although this function is not used in the final logic, it is used for debugging and printing out all the cards in our stack by name, and suit, and its respective “points” which are used for the “weight” of our card. 

 

Void deck_shuffle() 

As the name suggests, this function works to shuffle the deck, so that it can be properly dealt to the players. In order to shuffle the deck, randomization must be introduced. In the <random> library for c++, we can achieve random number generation to be able to shuffle the deck. By calling on the Mersene Twister algorithm for psuedo-random number generation, we are able to generate a randomized “seed” that we can use in combination with the shuffle function from the library <algorithm>. This allows the deck to be shuffled differently each time, allowing proper card game play. 

 

Card dealCard() 

This function returns a dealt card by grabbing the .top() of the stack (deck) and returning it. This function is used in conjunction with our hand class, which will initialize a hand that uses dealCard() to grab 5 cards.  

 

Class Deck_Hand() 

This class contains a vector<> that will store 5 Card objects, called a hand. When created, a hand will be initialized, grabbing five cards from the shuffled deck.  

Void Sort_Hand() 

This function sorts the hand of the player in increasing order, first by number value then by suit rank. It does this by making a temporary vector of the cards, emptying the hand, then taking the card with minimum value from the temporary vector and pushing it into the hand in order. The minimum is “removed” from this temporary vector, this process of pushing the minimum value card is repeated until the hand is full and in order. 

 

Void displayHand() 

This function creates and displays the user interface of the player's hand. This is done by an assortment of for-loops that create the borders and correctly print the cards suit and rank. Below is an example image of a hand of 5 cards. 

 

Void discardCard() 

Before we talk about this function, heres a quick rundown of how this function pertains to the actual rules of the game: 

In five card draw, the key game feature is the ability to discard none or all your cards in the hand and replace them with new ones from the deck. If someone needed a certain card for their hand, they could take a chance and discard a card in their hand for a better ranking score. 

DiscardCard() is ran for player 1 and player 2’s hand. It creates a vector called discardCards that will store the user output of selected indices for the cards they wish to remove from their deck. These numbers get sorted in descending order to ensure that removing the cards from the hand will be correct and not mess up the card index values for removal. Lastly, it will check the discardCards.size(), and push_back the appropriate amount of removed cards back into the hand. 

Float evaluateHand() 

This function gives the player’s hand a point value based on Poker rankings. Since the cards will be sorted by this point, it is easier to compare. All rankings determined by straights or flushes compare each card using integer values. All rankings determined by matching are found through a counting array that keeps track of index as the individual card numbers/values (similar to how a compare sort functions). The point value is returned dependent on the rank achieved and card values for that rank and given a tie the person with the highest value card of that rank-rule, would have the higher point. The point ranking system that is followed is shown below, with the Royal Flush having the most points. 

 

Function pair<int,int> play_game(Deck& deck, int P1_chips, int P2_chips) 

This function contains the logic behind five card draw. This function will keep being activated in the main function until either the two players quit or lose all their chips. We pass our deck, and the two players chips so that they are updated appropriately with each succeeding session. The function implements most of the game running functions in our Hand and Deck classes. It takes turns between player one and player two, where during a turn, players can either check, fold, bet, or display their cards. The flow of the logic changes if players bet, as there will be logic checks that will ensure the other player either matches the bet or folds their hand, which makes them lose. Chips are dispersed appropriately, and the winner of the game is decided when a player loses all their chips. 

 

 

 

Challenges Faced and Learnings 

Our team found it difficult to find common time to work on this large of a project between three people with varying schedules. So, our work was condensed into large time blocks on the days that we met to work on this project.  

One of our largest challenges throughout this coding process was attaining functionality from the evaluateHand() function. To rank all the hands possible in poker to compare against each other, multiple of our team members had to collaborate in brainstorming and implementing systems. We settled on assigning a point value to each hand based on the displayed rankings in the chart. To further this, we added secondary values based on card values and/or suits. The end implementation was fully functional for our version of poker, Tampa Five Card Draw. 

Another issue that we were running into was problems with the hand sorting. Despite being condensed in terms of lines of code, the scope and consistency of certain variables made the implementation of the hand sorting difficult. This section of code caused many problems throughout our coding progression and ended up being edited multiple times. To fix it, we had many moments of troubleshooting and shadow printing to assess and resolve the issues. 

The biggest issues faced in the project was the logic of the game in the play_game() function. There were many key variables that could've been overlooked, so lots of game testing was done to ensure the accuracies of the chips and overall text in the game. 

Contributions 

Josiah Varghese 

I created the idea and plan of creating a card game, and worked out which game would best function to display our creative prowess. 

I created most of the evaluteHand() function and created the logic for each rank rule set by the poker rules. 

I created printDeck() which was only used for testing the contents of a deck both after initializing and after shuffling 

I created the initializeDeck() function which creates a deck which creates the stack full of Cards, while also assigning required card details such as the name and suit, which are used for display, Point_Name and Point_Suit, which is the numerical value of the name and suit (used for integer comparison), and the sortvalue. 

Isaac Powell 

I helped to complete the evaluateHand() function. This function was pivotal for our project completion, and it posed one of the biggest threats with the initial complexity, so Josiah and I worked together to brainstorm and implement this function.  

Also, I completed the deck_shuffle() function to ensure that the game would be properly randomized.  

Another main point that I completed and maintained throughout the development of the code was the Sort_Hand() function.  

I also helped create the Card class and the Deck class, where the cards are used. 

Joshua Lacsamana 

I created the displayHand() and discardCard() functions in the Deck_Hand.  

The entirety of the play_game() function was created by me as well, as it was crucial that I understood the innerworkings of the logic to the game throughout the whole function.  

I wrote the main function to appropriately set up the logic of the game with the chips and deck 

 
