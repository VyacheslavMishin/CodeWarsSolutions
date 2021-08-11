#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <cstring>
#include <algorithm>

bool isRoyalFlush(const std::string &combination, bool the_same_suits)
{
  return the_same_suits && combination.back() == 'i';
}

bool isStraightFlush(const std::string &combination, bool the_same_suit)
{
  return the_same_suit && combination.front() - combination.back() == combination.size() - 1;
}

bool isFour_of_a_kind(std::string &combination)
{
  if(combination.back() == combination[1])
  {
    std::swap(combination.front(), combination.back());
    return true;
  }
  return combination.front() == combination[3]; 
}

bool isFull_house(std::string &combination)
{
  if (combination.front() == combination[1] && combination.back() == combination[2])
  {
    std::rotate(combination.begin(), combination.begin() + 2, combination.end());

    return true;
  }
  
  return combination.front() == combination[2] && combination.back() == combination[3];
}

bool isFlush(bool the_same_suit)
{
  return the_same_suit;
}

bool isStraight(const std::string &combination)
{
  if(combination == "mdcba") // Wheel combination checking
  {
    return true;
  }
  
  for (size_t i = 0; i < combination.size() - 1; i++)
  {
    if(combination[i] - combination[i + 1] == 1)
    {
      continue;
    }
    else
    {
      return false;
    }
    
  }
  return true;
  
}


bool isThree_of_a_kind(std::string &combination)
{
  if(combination.back() == combination[2])
  {
    std::rotate(combination.begin(), combination.begin() + 2, combination.end());
    return true;
  }
  if (combination[1] == combination[3])
  {
    std::swap(combination.front(), combination[3]);
    return true;
  }
  
  return combination.front() == combination[2];
}

int num_of_pairs(std::string &combination)
{
  std::vector<int> pairs_positions;
  std::string buff;

  for (size_t i = 0; i < combination.size() - 1; i++)
  {
    if(combination[i] == combination[i + 1])
    {
      pairs_positions.push_back(i);
      buff.push_back(combination[i]);
      buff.push_back(combination[i + 1]);
    }
  }

if (buff.size())
{
  for(int i = pairs_positions.size() - 1; i >= 0 ; i--)
  {
    combination.erase(pairs_positions[i], 2);
  }
  
  std::swap(combination, buff);
  combination += buff;
}
  
  return pairs_positions.size();
}

enum class Combinations
{
  high_card,
  pair,
  two_pairs,
  tree_of_a_kind,
  straight,
  flush,
  full_house,
  four_of_a_kind,
  straight_flush,
  royal_flush
};

struct PokerHand 
{
  bool the_same_suits;
  Combinations combination;
  std::map<char, char> translator{{'2', 'a'},
                                  {'3', 'b'},
                                  {'4', 'c'},
                                  {'5', 'd'},
                                  {'6', 'e'},
                                  {'7', 'f'},
                                  {'8', 'g'},
                                  {'9', 'h'},
                                  {'T', 'i'},
                                  {'J', 'j'},
                                  {'Q', 'k'},
                                  {'K', 'l'},
                                  {'A', 'm'}
                                 };
  std::string sorted_hand;
  
  PokerHand (const char* pokerhand) 
  {
    the_same_suits = true;
    
    for (size_t i = 0; i < strlen(pokerhand); i += 3)
    {
        the_same_suits &= (pokerhand[1] == pokerhand[i + 1]);
        sorted_hand += translator[pokerhand[i]]; 
    }

    std::sort(sorted_hand.rbegin(), sorted_hand.rend());

    if (isRoyalFlush(sorted_hand, the_same_suits))
    {
      combination = Combinations::royal_flush;
    }
    else if (isStraightFlush(sorted_hand, the_same_suits))
    {
      combination = Combinations::straight_flush;
    }
    else if (isFour_of_a_kind(sorted_hand))
    {
      combination = Combinations::four_of_a_kind;
    }
    else if (isFull_house(sorted_hand))
    {
      combination = Combinations::full_house;
    }
    else if (isFlush(the_same_suits))
    {
      combination = Combinations::flush;
    }
    else if (isStraight(sorted_hand))
    {
      combination = Combinations::straight;
    }
    else if (isThree_of_a_kind(sorted_hand))
    {
      combination = Combinations::tree_of_a_kind;
    }
    else
    {
      int pairs = num_of_pairs(sorted_hand);
      if (pairs == 2)
      {
        combination = Combinations::two_pairs;
      }
      else if (pairs == 1)
      {
        combination = Combinations::pair;
      }
      else
      {
        combination = Combinations::high_card;
      }
      
    }
    
  }
};

enum class Result { Win, Loss, Tie };

Result compare (const PokerHand &player, const PokerHand &opponent) 
{  
  if (player.combination > opponent.combination)
  {
    return Result::Win;
  }
  else if (player.combination < opponent.combination)
  {
    return Result::Loss;
  }
  else if (player.combination == Combinations::straight || player.combination == Combinations::straight_flush)
  {
    bool players_loss = (player.sorted_hand.front() == 'm') && (player.sorted_hand.back() == 'a');
    bool opponents_loss = (opponent.sorted_hand.front() == 'm') && (opponent.sorted_hand.back() == 'a');

    if (players_loss && !opponents_loss)
    {
      return Result::Loss;
    }
    else if (!players_loss && opponents_loss)
    {
      return Result::Win;
    }
    else if (players_loss && opponents_loss)
    {
      return Result::Tie;
    }
    
  }
  
  if (player.sorted_hand > opponent.sorted_hand)
  {
    return Result::Win;
  }
  else if (player.sorted_hand < opponent.sorted_hand)
  {
    return Result::Loss;
  }
  
  return Result::Tie;
  
}
