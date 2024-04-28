#include <iostream>
#include <string>
#include <stack>
using namespace std;
#include <algorithm>
#include <random> // Included for random number generation
#include <vector>




// Define the Card class to represent individual cards
class Card {
public:
    Card(int value, string name, string suit, int Point_Name, int Point_Suit, int sortvalue) : value(value), name(name), suit(suit), Point_Name(Point_Name), Point_Suit(Point_Suit), sortvalue(sortvalue) {}

    // Getter methods for accessing card attributes
    int getValue() const { return value; }
    int getPoint_Name() const { return Point_Name;}
    int getPoint_Suit() const {return Point_Suit;}
    string getName() const { return name; }
    string getSuit() const { return suit; }
    int sortvalue;
    

private:
    int value;
    // the following two variables are used to evaluate the hands, they are numerical  
    // versions of the name and suit of the card to better handle the evaluation 
    int Point_Name;
    int Point_Suit;
    // string representations of the name and suit (i.e. “hearts”, “Ace”, “diamond”, etc.) 
    string name;
    string suit;
};


// Define the Deck class to represent a deck of cards using a stack
class Deck {
public:
    // Constructor to initialize the deck with standard 52 cards
    Deck() {
        initializeDeck();
    }

    // Function to initialize the deck with standard 52 cards
    void initializeDeck() {
        string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        string names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

        int f=1;
        for (int n = 0; n < 13; ++n) {
            for (int s = 0; s < 4; ++s) {
                Card card(n+2, names[n], suits[s], n+2, s, f); // Initialize card with value, name, and suit
                deck.push(card);
                f++;
            }
        }
    }
  
    // Function to print the entire deck
    void printDeck() {
        stack<Card> temp = deck; // Create a copy of the deck
        while (!temp.empty()) {
            Card card = temp.top();
            cout << card.getName() << " of " << card.getSuit() << "\t \t" << card.getPoint_Name() << " , " << card.getPoint_Suit() << endl;
            temp.pop();
        }
    }
  
    // Function to shuffle the deck
    void deck_shuffle() {
        vector<Card> temp; // Temporary vector to hold shuffled cards

        // Transfer cards from the stack to the vector
        while (!deck.empty()) {
            temp.push_back(deck.top());
            deck.pop();
        }
        random_device rd; //This is used for the Mersenne Twister algorithm.
        mt19937 generated_seed(rd()); //This is the Mersenne Twister algorithm, which is used for randomly shuffling the deck by generating a random seed.

        // Shuffle the temporary vector
        shuffle(temp.begin(), temp.end(), generated_seed);


        for (int i = 0; i < temp.size(); i++){
            deck.push(temp[i]);
        }
        
    }

    // Function to deal a card from the deck
    Card dealCard() {
        if (!deck.empty()) {
            Card dealtCard = deck.top();
            deck.pop();
            return dealtCard;
        } else {
            cerr << "Deck is empty!" << endl;
            exit(1);
        }
    }
    

private:
    stack<Card> deck;
};





class Deck_Hand {
public:
    Deck_Hand(Deck& deck) : deck(deck) {
        // Initialize hand with 5 cards
        for (int i = 0; i < 5; ++i) {
            Card dealtCard = deck.dealCard();
            Hand.push_back(dealtCard);
        }
    }

    void Sort_Hand(){//function to sort the hands.
        vector<Card> temp; //make temp function
        for (int i = 0; i < 5; ++i) {
            temp.push_back(Hand[i]); //put Hand in temp
        }
        for (int b = 0; b<5; ++b){ //Clear the hand
            Hand.pop_back();
        }
        for (int j = 0; j < 5; ++j) { //This is logic to sort temp.
            Card* temp_card;
            temp_card = &temp[0];
            Card* test_card;
            int del_idx = 0; 
            for (int x = 0; x < 5; ++x) {
                test_card = &temp[x];
                if (test_card->sortvalue < temp_card->sortvalue) {
                    temp_card = test_card;
                    del_idx = x; //This value will be "deleted" from the temp.
                }
            }
            Hand.push_back(*temp_card); //Put elements in temp back in Hand.
            temp[del_idx].sortvalue = 55; //This puts sort value higher than any other card, essentially removing it from the temp.
            }
    }


    

    // Function to display the hand
    void displayHand() {
    int width = 12; // specify the width of each card
    int height = 9; // specify the height of each card
    int numCards = 5; // specify the number of cards in the hand, in this case 5
    Card *card; // pointer to a card object in order to grab the details of the card

    // Top border
    for (int i = 0; i < numCards; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << "*";
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    // Middle part
    for (int i = 0; i < height - 2; ++i) {
        for (int k = 0; k < numCards; ++k) {
            std::cout << "*";
            card = &Hand[k];
            string num = card->getName();
            string suit = card->getSuit();
            for (int j = 0; j < width - 2; ++j) {
                if (j == 1 && i == 0) {
                    std::cout << num;
                    j += num.length() - 1;
                } 
                else if (i == 6 && j < suit.length()) {
                    std::cout << suit[j];
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
    

    // Bottom border
    for (int i = 0; i < numCards; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << "*";
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    }

    // Function to discard a card from the hand
    void discardCard() {
        vector<int> discardCards; // Vector to store the indices of cards to discard
        for (int i = 0; i < 5; ++i) {
            int cardIndex;
            std::cout << "Enter the number of a card to remove from 1-5, or -1 to stop: ";
            std::cin >> cardIndex;
                if (cardIndex == -1) {
                    break;
                }
            discardCards.push_back(cardIndex);
            }
        // Sort the indices in descending order so that the indices of the cards to remove are valid
        std::sort(discardCards.begin(), discardCards.end(), std::greater<int>());
        // Remove the cards from the hand
        for (int cardIndex : discardCards) {
            Hand.erase(Hand.begin() + cardIndex - 1);
        }
        for (int i = 0; i < discardCards.size(); ++i) {
            Card dealtCard = deck.dealCard();
            Hand.push_back(dealtCard);
        }

    }

    float evaluateHand(){
        Card *card;
        float points; //This will be used to rank the hands; it's their point value
        int z;
        int num[5];
        int suit[5];
        for(z=0; z<5; z++){
            card = &Hand[z];
            num[z] = card->getPoint_Name(); //making an array of the card values
            suit[z] = card->getPoint_Suit(); //make an array of the cards' suites
        }

        bool straight;
        if (num[4]-4 == num[3]-3 == num[2]-2 == num[1]-1 == num[0]){
            straight = true; //If the cards are all unbroken and in order (above), this is true.
        }

        bool samesuit;

        if(suit[0]==suit[1] && suit[0]==suit[2] && suit[0]==suit[3] && suit[0]==suit[4]){ //Compares if all cards are the same suit
            samesuit = true; 
        }

        int i;
        int j;
        int maxCard=0; //Card type of the highest pair/trio/quad
        int maxCount=0; //How many of each card type
        int secondMaxCard; //Card type for pairs
        int secondMax; //Second highest value for pairs
        int highest_card = 0; //Highest individual card in the hand
        int second_highest_card = 0; //Second highest card value (individual)
        int count[16] = {-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Implement similar to countSort to count how many of each type of card
        for(i=0; i<5; i++){
            j=num[i];
            count[j] +=1;  
        } 
        for(i=2; i<15; i++){
            if(maxCount <= count[i]){ //If there is a new highest count of card type in the array.secondMax = maxCount;
                secondMaxCard = maxCard;
                maxCount=count[i];
                maxCard=i;
            }
            if(count[i]!=0 && count[i]!=-1){ //If there is a card of that type
                second_highest_card = highest_card;
                highest_card = i;
            }
        }
        if (maxCount == 4){ //If 4 of a kind
            points = 7 + maxCard*.01;
            return points;
        }

        if (maxCount == 3 && secondMax == 2){//If Full House
            points = 6 + maxCard*.01 + secondMaxCard*.0001;
            return points;
        }
        

        if (maxCount == 3 && secondMax != 2){ //If 3 of a kind
            points = 3 + maxCard*.01;
            return points;
        }
        
        if(maxCount == 2 && secondMax==2){// 2 pair
            points = 2 + maxCard*.01 + secondMaxCard*.0001;
            return points;
        }

        if(maxCount==2 && secondMax!=2){//pair
            points = 1 + maxCard*.01;
            return points;
        }
        


        if(num[0]==10 && straight && samesuit){ //Royal Flush
            points=9;
        }
        else if(straight && samesuit){//Straight Flush   
            points=8 + num[4]*.01;
        }else if(samesuit){//Flush
            points=5 + num[4]*.01;
        }else if(straight){//Straight
            points=4 + num[4]*.01;
        }

        else{//No special rank; just by high card and second highest card (in case of tie)
            points = 0 + .01*highest_card +.0001*second_highest_card;
        }
        
        return points;

    }
    

private:
    vector<Card> Hand;
    Deck& deck;
};

pair<int,int> play_game(Deck& deck, int P1_chips, int P2_chips) {
    /* A quick overview of the logic for this game: Two players will receive randomized hands of 5 cards each. When it is player 1 or player 2s turn, they can either check, which will allow the game to continue, fold, which will end the game and the other player will win, or bet, which will require the other player to match the bet or fold. After the first round of betting is done, the players will have the option to discard cards and draw new ones. Another round of betting ensues, and then finally,the hands will then be evaluated to determine the winner. 
    */
    deck.deck_shuffle();
    // Players pay a blind fee of 5 chips to play
    P1_chips -= 5; 
    P2_chips -= 5; 
    // Initialize hands for two players
    int P1_bet = 0;
    int P2_bet = 0;
    // Initialize hands for two players
    Deck_Hand P1_hand(deck);
    P1_hand.Sort_Hand();
    Deck_Hand P2_hand(deck);
    P2_hand.Sort_Hand();
    cin.get();
    // Reveal hands to both  players
    cout << "Tampa Five Card Draw has started! 5 chips have been automatically deducted from both chip stacks due to blind fee." << endl;
    cout <<"Press enter to reveal Player 1's hand..." << endl;
    cin.get();
    cout << "Player 1's hand:" << endl;
    P1_hand.displayHand();
    cout << endl;
    cout << "Press enter to reveal Player 2's hand..." << endl;
    cin.get();
    cout << "Player 2's hand:" << endl;
    P2_hand.displayHand();
    cout << endl;
    // Player 1's turn to bet, check, or fold
    while(true){
        int choice;
        int P1_game_bet;
    
        cout << "Player 1, what would you like to do? Current amount of chips: " << P1_chips - P1_bet << endl;
        cout << "Enter the number corresponding to your play:" << endl;
        cout << "1. Check   2. Fold   3. Bet   4. Display Cards" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "Player 1 checks." << endl;
            break;
        } else if (choice == 2) {
            cout << "Player 1 folds." << endl;
            cout << "Player 2 wins!" << endl;
            return pair<int,int>(P1_chips - P1_bet, P2_chips + P1_bet + 10); 
        } else if (choice == 3) {
           if (P1_chips < 0) {
               cout << "You don't have any chips to bet!" << endl;
               continue;
           }
           cout << "How much would you like to bet? You currently have " << P1_chips - P1_bet << " chips" << endl;
           cin >> P1_game_bet;
           if (P1_game_bet + P1_bet > P1_chips) {
                cout << "You don't have enough chips! Please enter a different amount." << endl;
            } else {
                P1_bet += P1_game_bet;
                break;
            }
        } else if (choice == 4) {
            cout << "Player 1's hand:" << endl;
            P1_hand.displayHand();
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    // Executes if player 1 bets
    if (P1_bet > 0){
        int P2_game_bet;

        while (P1_bet != P2_bet) {
            cout << "Player 1 has " << P1_bet << " chips on the table. Player 2, you must match this bet to continue, or fold your cards by typing -1." << endl;
            cout << "Type " << P1_bet - P2_bet << " to match the bet: Your current amount of chips: " << P2_chips - P2_bet<< endl;
            cin >> P2_game_bet;
            if (P2_game_bet == -1) {
                cout << "Player 2 folds." << endl;
                cout << "Player 1 wins!" << endl;
                return pair<int,int>(P1_chips + P2_bet + 10, P2_chips - P2_bet);
            }
            P2_bet += P2_game_bet;
            if (P2_chips - P2_bet < 0) {
                cout << "Player 2 is out of chips!" << endl;
                break;
            }
           
            }
        }
    // Player 2's turn to bet, check, or fold
    while(true){
        int choice;     
        int P2_game_bet;   
        cout << "Player 2, what would you like to do? Current amount of chips: " << P2_chips - P2_bet << endl;        cout << "Enter the number corresponding to your play:" << endl;
        cout << "1. Check   2. Fold   3. Bet   4. Display Cards" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "Player 2 checks." << endl;
            break;
        } else if (choice == 2) {
            cout << "Player 2 folds." << endl;
            cout << "Player 1 wins!" << endl;
            return pair<int,int>(P1_chips + P2_bet + 10, P2_chips - P2_bet); 
        } else if (choice == 3) {
            if (P2_chips < 0) {
                cout << "You dont have any chips to bet!" << endl;
                continue;
            }
            if (P1_chips < 0) {
               cout << "You don't have any chips to bet!" << endl;
               continue;
           }
           cout << "How much would you like to bet? You currently have " << P2_chips - P2_bet << " chips" << endl;
           cin >> P2_game_bet;
           if (P2_game_bet + P2_bet > P2_chips) {
                cout << "You don't have enough chips! Please enter a different amount." << endl;
            } else {
                P2_bet += P2_game_bet;
                break;
            }
        } else if (choice == 4) {
            cout << "Player 2's hand:" << endl;
            P2_hand.displayHand();
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    // Executes if player 2 bets
    if (P2_bet > P1_bet) {
        int P1_game_bet;
        while(P2_bet != P1_bet) {
            cout << "Player 2 has " << P2_bet << " chips on the table. Player 1, you must match this bet to continue, or type -1 to fold." << endl;
            cout << "Type " << P2_bet - P1_bet << " to match the bet: Your current amount of chips: " << P1_chips - P1_bet << endl;
            cin >> P1_game_bet;
            if (P1_game_bet == -1) {
                cout << "Player 1 folds." << endl;
                cout << "Player 2 wins!" << endl;
                return pair<int,int>(P1_chips - P1_bet, P2_chips + P1_bet + 10);
            }
            P1_bet += P1_game_bet;
            if (P1_chips - P1_bet < 0) {
                cout << "Player 1 is out of chips!" << endl;
            }
            break;
        
        }
    }
    // Discard cards for both players
    cin.get();
    cout << "Press enter when Player 1 is ready to discard their cards." << endl;
    cin.get();
    cout << "Player 1's turn to discard cards:" << endl;
    P1_hand.displayHand();
    P1_hand.discardCard();
    cout << "Press enter when Player 2 is ready to discard their cards." << endl;
    cin.ignore();
    cin.get();
    cout << "Player 2's turn to discard cards:" << endl;
    P2_hand.displayHand();
    P2_hand.discardCard();

    P1_hand.Sort_Hand();
    P2_hand.Sort_Hand();

    cin.get();
    // Display hands for two players after discarding cards
    cout << "Press enter to display Player 1's hand after discarding cards:" << endl;
    cin.get();
    P1_hand.displayHand();
    cout << endl;
    cout << "Press enter to display Player 2's hand after discarding cards:" << endl;
    cin.get();
    P2_hand.displayHand();

    // Player 1's turn to bet, check, or fold
    while(true){
        int choice;
        cout << "Player 1, what would you like to do? Current amount of chips: " << P1_chips - P1_bet << endl;        cout << "Enter the number corresponding to your play:" << endl;
        cout << "1. Check   2. Fold   3. Bet   4. Display Cards" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "Player 1 checks." << endl;
            break;
        } else if (choice == 2) {
            cout << "Player 1 folds." << endl;
            cout << "Player 2 wins!" << endl;
            return pair<int,int>(P1_chips - P1_bet, P2_chips + P1_bet + 10); 
        } else if (choice == 3) {
            if (P1_chips < 0) {
                cout << "You don't have any chips to bet!" << endl;
                continue;
            }
            cout << "How much would you like to bet? You currently have " << P1_chips - P1_bet << " chips" << endl;
            int P1_game_bet;
            cin >> P1_game_bet;
            if (P1_bet + P1_game_bet > P1_chips) {
                cout << "You don't have enough chips! Please enter a different amount." << endl;
            } else {
                P1_bet += P1_game_bet;
                break;
            }
        } else if (choice == 4) {
            cout << "Player 1's hand:" << endl;
            P1_hand.displayHand();
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    
    }

    // Executes if player 1 bets
    if (P1_bet > P2_bet) {
        int P2_game_bet;
            while (P1_bet != P2_bet) {
                cout << "Player 1 has " << P1_bet << " chips on the table. Player 2, you must match this bet to continue, or type -1 to fold." << endl;
                cout << "Type " << P1_bet - P2_bet << " to match the bet: Your current amount of chips: " << P2_chips - P2_bet << endl;
                cin >> P2_game_bet;
                if (P2_bet == -1) {
                    cout << "Player 2 folds." << endl;
                    cout << "Player 1 wins!" << endl;
                    return pair<int,int>(P1_chips + P2_bet + 10, P2_chips - P2_bet);
                }
                P2_bet += P2_game_bet;
                if (P2_chips - P2_bet < 0) {
                    cout << "Player 2 is out of chips!" << endl;
                }
                break;
                
            }
        }
    
    // Player 2's turn to bet, check, or fold
    while(true){
        int choice;
        int P2_game_bet;

        cout << "Player 2, what would you like to do? Current amount of chips: " << P2_chips - P2_bet << endl;        cout << "Enter the number corresponding to your play:" << endl;
        cout << "1. Check   2. Fold   3. Bet   4. Display Cards" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << "Player 2 checks." << endl;
            break;
        } else if (choice == 2) {
            cout << "Player 2 folds." << endl;
            cout << "Player 1 wins!" << endl;
            return pair<int,int>(P1_chips + P2_bet + 10, P2_chips - P2_bet); 
        } else if (choice == 3) {
            if (P2_chips < 0) {
                cout << "You dont have any chips to bet!" << endl;
                continue;
            }
           cout << "How much would you like to bet? You currently have " << P2_chips - P2_bet << " chips" << endl;
           cin >> P2_game_bet;
           if (P2_game_bet + P2_bet > P2_chips) {
                cout << "You don't have enough chips! Please enter a different amount." << endl;
            } else {
                P2_bet += P2_game_bet;
                break;
            }
        } else if (choice == 4) {
            cout << "Player 2's hand:" << endl;
            P2_hand.displayHand();
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    // Executes if player 2 bets
    if (P2_bet > P1_bet) {
        int P1_game_bet;
        while(P2_bet != P1_bet) {
            cout << "Player 2 has bet " << P2_bet << ". Player 1, you must match this bet to continue." << endl;
            cout << "Type " << P2_bet - P1_bet << " to match the bet: Your current amount of chips: " << P1_chips - P1_bet << endl;
            cin >> P1_game_bet;
            if (P1_game_bet == -1) {
                cout << "Player 1 folds." << endl;
                cout << "Player 2 wins!" << endl;
                return pair<int,int>(P1_chips - P1_bet, P2_chips + P1_bet + 10);
            }
            P1_bet += P1_game_bet;
            if (P1_chips - P1_bet < 0) {
                cout << "Player 1 is out of chips!" << endl;
            }
            break;
        
        }
    }

    // Reveal hands to both players
    cout << "Now, we will reveal Player 1 and Player 2's cards" << endl;
    cout << "Player 1's hand:" << endl;
    P1_hand.displayHand();
    cout << "Player 2's hand:" << endl;
    P2_hand.displayHand();
    

    // Determine the winner of the game
    float P1_score = P1_hand.evaluateHand();
    float P2_score = P2_hand.evaluateHand();



    // grab a string of the hand type to place in the winners text
    string P1_hand_type;
    string P2_hand_type;
    // Convert the scores to integers for comparison
    int P1_score_for_string = int(P1_score);
    int P2_score_for_string = int(P2_score);

    // Determine the type of hand for each player based on the score received
    P1_hand_type = P1_score_for_string == 9 ? "Royal Flush" : P1_score_for_string == 8 ? "Straight Flush" : P1_score_for_string == 7 ? "Four of a Kind" : P1_score_for_string == 6 ? "Full House" : P1_score_for_string == 5 ? "Flush" : P1_score_for_string == 4 ? "Straight" : P1_score_for_string == 3 ? "Three of a Kind" : P1_score_for_string == 2 ? "Two Pair" : P1_score_for_string == 1 ? "One Pair" : "High Card";

    P2_hand_type = P2_score_for_string == 9 ? "Royal Flush" : P2_score_for_string == 8 ? "Straight Flush" : P2_score_for_string == 7 ? "Four of a Kind" : P2_score_for_string == 6 ? "Full House" : P2_score_for_string == 5 ? "Flush" : P2_score_for_string == 4 ? "Straight" : P2_score_for_string == 3 ? "Three of a Kind" : P2_score_for_string == 2 ? "Two Pair" : P2_score_for_string == 1 ? "One Pair" : "High Card";
    
    if (P1_score > P2_score) {
        cout << "Player 1 wins this round with a " << P1_hand_type << "!" << endl;
        return pair<int,int>(P1_chips + P2_bet + 10, P2_chips - P2_bet);
    } else if (P1_score < P2_score) {
        cout << "Player 2 wins this round with a " << P2_hand_type << "!" << endl;
        return pair<int,int>(P1_chips - P1_bet, P2_chips + P1_bet + 10);
    } else {
        cout << "It's a tie!" << endl;
        return pair<int,int>(P1_chips + 5, P2_chips + 5);
    }
}
    


int main() {

    int choice;
    int P1_chips = 100;
    int P2_chips = 100;
    cout << "Welcome to Five Card Draw Poker!" << endl;
    while (true){
        Deck deck;
        cout << "Press 1 to start a new game with two players or 2 to exit: ";
        cin >> choice;
        if (choice == 1) {
        cout << "Starting a new game..." << endl;
        pair<int,int> chips = play_game(deck, P1_chips, P2_chips);
        P1_chips = chips.first;
        P2_chips = chips.second;
        cout << "Player 1's chips: " << P1_chips << endl;
        cout << "Player 2's chips: " << P2_chips << endl;
        if (P1_chips <= 0) {
            cout << "Player 1 is out of chips! Player 2 wins!" << endl;
            break;
        } else if (P2_chips <= 0) {
            cout << "Player 2 is out of chips! Player 1 wins!" << endl;
            break;
        }
        } 
        else if (choice == 2) {
            return 0;
        } 
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

}
