/*
 * Given a shuffled pick of 4 integers in range 0..9, and assuming random shuffle, provide a 2-digit number 
 * combination sum that is closest to the provided number.
 * Lets say the provided number is 100 and say a random shuffle picked deck of numbers 7 8 5 6 
 * one of the combination of sum is 78 + 56 = 134, which has a distance of 34 from 100
 * another combination from this shuffle would be 58 + 65 = 123, which has a distance of 23 and is closer to 100 
 * that the previous combination.
 *
 * Given such random shuffle of deck and the number find the two 2-digit numbers whose sum is closes to the 
 * provided number
 *
 */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

struct DistancePair {
	// Don't care about the encapsulation etc. atm
	unsigned int n1, n2;
	unsigned int distance;

	DistancePair(unsigned int x, unsigned int y, unsigned int compareTo)
		: n1(x), n2(y), distance(::abs(x + y - compareTo)) {
	}

	bool operator < (const DistancePair& other) const {
		return this->distance < other.distance;
	}
};

void printDeck(const vector<unsigned int>& deck) {
	cout << " Deck [";
	for (auto i = 0; i < deck.size(); ++i) {
		if (i) {
			cout << ", ";
		}
		cout << deck[i];

	}
	cout << "]" << endl;
}


vector<unsigned int> getShuffledDeck(int count, unsigned int min, unsigned int max) {
	static std::default_random_engine generator;
	std::uniform_int_distribution<unsigned int> distribution(min, max);
	auto boundGen = std::bind(distribution, generator);

	vector<unsigned int> shuffledDeck(count);
	for (auto i = 0; i < count; ++i) {
		shuffledDeck[i] = boundGen();
	}

	return shuffledDeck;
}

DistancePair minDistanceRecursive(vector<unsigned int>& deck, int index, unsigned int compareTo) {
	// Initialize with first combination
	DistancePair minDp(deck[0] * 10 + deck[1], deck[2] * 10 + deck[3], compareTo);

	for (auto i = index; i < deck.size(); ++i) {
		std::swap(deck[index], deck[i]);
		DistancePair tempDp = minDistanceRecursive(deck, i + 1, compareTo);
		printDeck(deck);
		if (tempDp < minDp) {
			minDp = tempDp;
			cout << "Dp [" << minDp.n1 << ", " << minDp.n2 << ", " << minDp.distance
				<< "] -> [" << tempDp.n1 << ", " << tempDp.n2 << ", " << tempDp.distance << "]" << endl;
		}

		std::swap(deck[index], deck[i]);
	}

	cout << "Returning MinDp [" << minDp.n1 << ", " << minDp.n2 << ", " << minDp.distance
		<< "] for [index: " << index << "]" << endl;
	return minDp;
}


int main() {
	unsigned int sampleCount  = 1;
	vector<unsigned int> shuffledDeck = getShuffledDeck(4, 0, 9);
	printDeck(getShuffledDeck(4, 0, 9));
	minDistanceRecursive(shuffledDeck, 0, 100);


	shuffledDeck = {7, 2, 9, 8};
	minDistanceRecursive(shuffledDeck, 0, 100);
	return 0;
}
