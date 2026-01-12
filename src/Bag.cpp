#include "../include/Bag.hpp"
#include <iostream>

/**
 * A Bag is a collection of Tokens (chips) that supports
 * functions that work by enumerating the contents.
 *
 * @author: Sam Xie
 */

Bag::Bag(int numTokens) : contents(numTokens) {}

void Bag::firstToken() const {
    if (!contents.empty())
        std::cout << contents[0].toString() << std::endl;
}

void Bag::allTokens() const {
    for (const auto& token : contents) {
        std::cout << token.toString() << std::endl;
    }
}

void Bag::allTokensWhile() const {
    size_t i = 0;
    while (i < this->contents.size()) {
        std::cout << contents[i].toString() << std::endl;
		++i;
    }
}

int Bag::addTokens() const {
	int total_value = 0;
	for (const auto& token : this->contents){
		total_value += token.getValue();
	}
    return total_value;
}

int Bag::highValueTokens() const {
    int high_count = 0;
	for (const auto& token : this->contents){
		high_count += token.isHighValue();
	}
    return high_count;	
}

int Bag::firstGreen() const {
    int index = -1;
	for (int i = 0; i < this->contents.size() && index == -1; ++i){
		if ((this->contents)[i].getColor() == std::string("Green")){
			index = i;
		}
	}
    return index;
}