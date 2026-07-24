#include <algorithm>
#include <random> 
#include <iostream>


enum class Suit 
{ 
    heart, diamond, spade, club 
};

enum class Rank 
{ 
    two, three, four, five, six, seven, 
    eight, nine, ten, jack, queen, king, ace 
};

struct Card
{
    Suit suit;
    Rank rank;
};

class Deck
{
    friend std::ostream& operator<<(std::ostream& os, const Deck& d);
public:
    Deck()
    {
        using enum Suit;
        using enum Rank;

        deck.reserve(52);
        for(auto suit: {heart, diamond, spade, club}) {
            for(auto rank: {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace}) {
                deck.emplace_back(suit, rank);
            }
        }
    }

    void shuffle() 
    {
        std::shuffle(deck.begin(), deck.end(), gen);
    }

private:
    std::vector<Card> deck;
    std::mt19937 gen{std::random_device{}()};
};

std::string suit_to_string(Suit s)
{
    using enum Suit;
    switch (s) {
        case heart:   return "Hearts";
        case diamond: return "Diamonds";
        case spade:   return "Spades";
        case club:    return "Clubs";
    }
    return "?";   
}

std::string rank_to_string(Rank r)
{
    using enum Rank;
    switch (r) {
        case two:   return "2";
        case three: return "3";
        case four:  return "4";
        case five:  return "5";
        case six:   return "6";
        case seven: return "7";
        case eight: return "8";
        case nine:  return "9";
        case ten:   return "10";
        case jack:  return "Jack";
        case queen: return "Queen";
        case king:  return "King";
        case ace:   return "Ace";
    }
    return "?";
}

std::ostream& operator<<(std::ostream& os, const Deck& d)
{
    for(const auto& c: d.deck){
        os << rank_to_string(c.rank) << " of " << suit_to_string(c.suit) << '\n';
    }
    return os;
}

int main()
{
    Deck d;
    d.shuffle();
    std::cout << d;
}