// FinalProjectCS1410
// Jeremy Mecham

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "FinalProjectHeader.h"
using namespace std;

int main() {
    char userInput = 'y';
    cout << "Welcome to 31. The goal is to get the closest to 31 and beat your opponent!" << endl;

    DeckOfCards deck;
    deck.shuffleDeck();
    vector<Card> playerHand;
    vector<Card> computerHand;

    /*
    This for loop loops through 3 times to give the player and the computer a card.
    Each card is pushed to each respective using the getCard function as a parameter.
    */
    for (int i = 0; i < 3; ++i) {
        playerHand.push_back(deck.getCard());
        computerHand.push_back(deck.getCard());
    }

    if (checkSpecialConditions(playerHand)) return 0; 

    /*
    This is the main loop. It starts by showing your hand by looping through each card in your hand.
    It moves on to the players choice, which asks the user if they want to knock or draw.
    If you choose to knock, the game will end and will check the scores to determine who wins.
    If you choose to take a card, the game will get a new card from the deck and push it to your
    vector. It will show your hand with the 4 cards and ask the user to discard 1 card 1-4.
    The card you choose is discarded and your hand is reshown.
    */
    while (userInput == 'y') {
        cout << "\nYour hand:" << endl;
        for (size_t i = 0; i < playerHand.size(); ++i) {
            cout << i + 1 << ": " << playerHand[i].toString() << endl;
        }

        int turnChoice;
        cout << "\nDo you want to knock (1) or draw (2) a new card? ";
        cin >> turnChoice;

        if (turnChoice == 1) { // User Choice knock
            cout << "You knocked! The game will now end." << endl;
            break;
        }
        else if (turnChoice == 2) { // User Choice take card
            Card newCard = deck.getCard();
            cout << "You drew: " << newCard.toString() << endl;
            playerHand.push_back(newCard);
            cout << "Your hand:" << endl;
            for (size_t i = 0; i < playerHand.size(); ++i) {
                cout << i + 1 << ": " << playerHand[i].toString() << endl;
            }
            cout << "Choose a card to discard (1-" << playerHand.size() << "): ";
            int discardIndex;
            cin >> discardIndex;
            if (discardIndex > 0 && discardIndex <= playerHand.size()) { // Choose card to discard
                playerHand.erase(playerHand.begin() + (discardIndex - 1));
                cout << "Card discarded. Your hand:" << endl;
                for (const Card& card : playerHand) {
                    cout << card.toString() << endl;
                }
            }
            else {
                cout << "Invalid choice. No card discarded." << endl;
            }
        }
        else {
            cout << "Invalid choice. Please enter 1 or 2." << endl;
            continue;
        }

        // Check for special conditions
        if (checkSpecialConditions(playerHand)) return 0;

        /*
        This portion is the computer logic. It has similar logic to the player, but will
        make a decision when it has a hand greater to or equal to 20. When the computer
        has 4 cards the minIt will determine which card in the computer's hand is the smallest.
        The lambda function allows the object cards  to be compared and returned as the value, which
        allows the min_element to function properly. The lowest card is then erased from the vector.
        */
        cout << "\nComputer's turn..." << endl;
        if (checkSpecialConditions(computerHand)) return 0;
        int computerBestValue = calculateBestSuitValue(computerHand);
        if (computerBestValue <= 20) { // Threshold for the computer to draw a card
            Card newCard = deck.getCard();
            computerHand.push_back(newCard);
            auto minIt = min_element(computerHand.begin(), computerHand.end(), [](const Card& a, const Card& b) { return a.value < b.value; });
            computerHand.erase(minIt);
            cout << "The computer drew a card and discarded one." << endl;
            if (checkSpecialConditions(computerHand)) return 0;
        }
        else {
            cout << "The computer chose not to draw a card." << endl;
            break;
        }

        // Check scores
        cout << "\nEnd of turn." << endl;
        cout << "Your best suit total: " << calculateBestSuitValue(playerHand) << endl;
        cout << "Computer's best suit total: " << calculateBestSuitValue(computerHand) << endl;
    }

    /*
    This final portion of the main code will determine who is the winner.
    It will take the best values of each player by running each hand through
    the calculateBestSuitValue, which will return the highest total value for
    each player. The if statements will determine who wins.
    */
    int playerBestValue = calculateBestSuitValue(playerHand);
    int computerBestValue = calculateBestSuitValue(computerHand);
    cout << "\nGame over!" << endl;
    cout << "Your best suit total: " << playerBestValue << endl;
    cout << "Computer's best suit total: " << computerBestValue << endl;

    if (playerBestValue > computerBestValue) {
        cout << "Congratulations! You win!" << endl;
    }
    else if (playerBestValue < computerBestValue) {
        cout << "The computer wins. Better luck next time!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}



/* TO DO
1) Create a card class that has the attributes of a card
2) Create a deck class that contains the information regarding the deck,
Have a way to randomize the deck(s)
3) Maybe have a class for the player
4) Give 3 cards each player
5) Create logic for 31
*/

/*
while userinput is y
run shuffle deck
tell players you are playing black jack
give players each 3 cards
ask player if they will take a card or knock
if they knock, deal a card to them and have them choose which of the four cards to throw down
do the same for the computer
add logic for computer to stop at a certain number(s)
add logic to determine winner
ask if they want to play again
*/

/* STILL TO DO
1) Fix the logic so 30 doesn't end the game
2) Create a loop to continue to play the game
3) Have a score counter. When someone reaches 5 "Marks" they lose
4) Fix computer logic with the special conditions
5) Clean up how the game appears in the console
6) Create a pile where cards go so someone can pick up a card in the pile if they know what it is
7) Give the person a final turn after someone has knocked instead of ending the game
8) Struct for each player
*/
