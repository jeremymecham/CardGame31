#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::shuffle
#include <random>    // For random device, generates random numbers
using namespace std;

/* 
This is the Card class.This contains 3 values: a suit, a face, and a value.
The constructor will take values put into the card to generate each card object.
The toString function is a constant string return type that will return the values
of the card, which will never change among each card object
*/
class Card {
public:
    string suit;
    string face;
    int value;

    // Constructor
    Card(string s, string f, int v) : suit(s), face(f), value(v) {}

    // String representation
    string toString() const {
        return face + " of " + suit + ", value: " + to_string(value);
    }
};

/*
 -Private-
The DeckOfCards class has 5 different values that make up the deck.
The first value is the deck, which is a vector composed of Card objects.
The next 3 values are vectors that contain all the values and combinations
a card object could have, such as a suit, a face, and a value.
The final value is a playIdx, which is a size_t that will be used to iterate.
 -Public-
The class constructor builds the deck using a for loop that loops through each suit
in the suits vector. A nested for loop then loops through the size of the faces vector
to place each combination of values in the deck vector, which creates new card objects due
to the data type of deck being card.
*/
class DeckOfCards {
private:
    vector<Card> deck;
    vector<string> suits = { "Hearts", "Diamonds", "Spades", "Clubs" };
    vector<string> faces = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    vector<int> values = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
    size_t playIdx = 0;

public:
    DeckOfCards() {
        for (const string& suit : suits) {
            for (size_t i = 0; i < faces.size(); ++i) {
                deck.emplace_back(suit, faces[i], values[i]);
            }
        }
    }

    /*
    The shuffleDeck is used to shuffle the deck. The random_device rd is imported from the 
    random library. The random seed rd is then passed in as a parameter for the Mersenne Twister
    algorithm. The Mersenne Twister algorithm creates an object g, which uses the seed to generate
    a random number. The shuffle function is imported from the algorithm library. It takes the
    beginning and ending of the vector and uses the g random number to shuffle the deck.
    */
    void shuffleDeck() {
        random_device rd;
        mt19937 g(rd());
        shuffle(deck.begin(), deck.end(), g);
    }

    /*
    The printDeck function loops through each card in the deck and prints it off the deck.
    Used to check if shuffle was working
    */
    void printDeck() const {
        for (const Card& card : deck) {
            cout << card.face << " of " << card.suit << ", ";
        }
        cout << "---" << endl;
    }

    /*
    The getCard function is used to return the next card in the deck, which is tracked using the
    playIdx variable.
    */
    Card getCard() {
        return deck[playIdx++];
    }
};

/*
The calculateTotalValue takes in a vector and a string suit. The totalValue variable is set to 0.
The loop will go through each card in the cards vector, and checks if the card.suit is equal to the suit
passed through, the totalValue will add up the current card value. The totalValue is returned as an int.
*/
int calculateTotalValueSameSuit(const vector<Card>& cards, const string& suit) {
    int totalValue = 0;
    for (const Card& card : cards) {
        if (card.suit == suit) {
            totalValue += card.value;
        }
    }
    return totalValue;
}

/*
The calculateBestSuitValue takes in a vector hand as a parameter. A vector suits and maxValue are created.
A for loop loops through each suit in the suits vector and creates a variable that will store the 
totalValue from the calculateTotalValueSameSuit. Running the calculateTotalValueSameSuit with each
suit allows the program to keep track of the total value of each suit. The maxValue variable is set
to the max of the current maxValue value or the suitValue, which helps the program keep track of the
largest total value. The maxValue is returned as an int to the user
*/
int calculateBestSuitValue(const vector<Card>& hand) {
    vector<string> suits = { "Hearts", "Diamonds", "Spades", "Clubs" };
    int maxValue = 0;
    for (const string& suit : suits) {
        int suitValue = calculateTotalValueSameSuit(hand, suit);
        maxValue = max(maxValue, suitValue);
    }
    return maxValue;
}

/*
The checkSpecialConditions takes a vector hand as a parameter. A vector is created for the suits,
an array is created to keep track of suit totals, and a valueCount vector is created to keep track of
how many of a card there is (used for 30). 
*/
bool checkSpecialConditions(vector<Card>& hand) {
    vector<string> suits = { "Hearts", "Diamonds", "Spades", "Clubs" };
    int suitTotals[4] = { 0, 0, 0, 0 };
    vector<int> valueCount(13, 0);
    int aceCount = 0;

    // Adds up the suitTotals and has a ace tracker
    for (const Card& card : hand) {
        for (size_t i = 0; i < suits.size(); ++i) {
            if (card.suit == suits[i]) {
                suitTotals[i] += card.value;
            }
        }
        if (card.face == "Ace") aceCount++;
        valueCount[card.value]++;
    }

    // Adjust Ace values if there are exactly 2
    if (aceCount == 2) {
        for (Card& card : hand) {
            if (card.face == "Ace" && card.value == 11) {
                card.value = 1; // Change Ace value to 1
            }
        }
    }

    // Check for 31 in any suit
    for (int suitTotal : suitTotals) {
        if (suitTotal == 31) {
            cout << "Congratulations! You have 31 and win instantly!" << endl;
            return true;
        }
    }

    // Check for 30 with three cards of the same value
    for (int count : valueCount) {
        if (count == 3) {
            cout << "Congratulations! You have three cards of the same value totaling 30! You win!" << endl;
            return true;
        }
    }
    return false;
}

/*
The calculateBestSuitValue takes a hand vector as a parameter. It initialzes a vector with the
suits and an array of size 4 initialized with values of 0. The loop goes through each card in the
hand, and has another nested loop that loops through the size of the suit vector. It checks if the 
current card suit is equal to the current suit index in the vector, and if true, will add the
card value to the respective position in the suitTotals array. The return is the pointer of the
max_element in the suitTotals array. It has to be passed as a pointer because max_element defaults
by giving the address of the value instead of the value, so you need to dereference it.
*/
int calculateBestSuitValue(vector<Card>& hand) {
    vector<string> suits = { "Hearts", "Diamonds", "Spades", "Clubs" };
    int suitTotals[4] = { 0, 0, 0, 0 };
    for (const Card& card : hand) {
        for (size_t i = 0; i < suits.size(); ++i) {
            if (card.suit == suits[i]) {
                suitTotals[i] += card.value;
            }
        }
    }
    return *max_element(suitTotals, suitTotals + 4);
}
