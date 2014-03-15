#include <iostream>
#include <algorithm>
#include "Map.h"

Map soundex = Create_map("ao")("eiu")("bfpv")("cgjkqsxz")("dt")("mn");

cost_type insertion_cost(std::string::value_type);
cost_type removal_cost(std::string::value_type);
cost_type update_cost(std::string::value_type, std::string::value_type);
double similarity(std::string const& from, std::string const& to);

int main() {
	std::string s, t;
	double coef;
	
	std::cout << "Enter two strings (or enter for exit):\n";
	while (true) {
		std::cout << "string 1: ";
		getline(std::cin, s);
		if (s == "") break;
		std::cout << "string 2: ";
		getline(std::cin, t);
		if (t == "") break;
		coef = similarity(s, t);
		std::cout << "Similarity coefficient: " << coef * 100 << "%\n\n";
		std::cout << "Enter another two strings (or enter for exit):\n";
	}

	std::cout << "Bye!\n";
	return 0;
}

cost_type insertion_cost(std::string::value_type ch) {
	return max_cost;
}

cost_type removal_cost(std::string::value_type ch) {
	return max_cost;
}

cost_type update_cost(std::string::value_type lhs, std::string::value_type rhs) {
	if (lhs == rhs) return l0_cost;
	if (tolower(lhs) == tolower(rhs)) return l1_cost;
	if (soundex[lhs] == soundex[rhs]) return l2_cost;
	if (soundex[tolower(lhs)] == soundex[tolower(rhs)]) return l3_cost;

	return max_cost;
}

double similarity(std::string const& from, std::string const& to) {
	Matrix costTable(2, Line(to.length() + 1));

	costTable[0][0] = 0;

	for (std::size_t j = 0; j != to.length(); ++j) {
		costTable[0][j + 1] = costTable[0][j] + insertion_cost(to[j]);
	}

	for (std::size_t i = 0; i != from.length(); ++i) {
		costTable[1][0] = costTable[0][0] + removal_cost(from[i]);

		for (std::size_t j = 0; j != to.length(); ++j) {
			costTable[1][j + 1] = std::min(std::min(
				costTable[1][j] + insertion_cost(to[j]),
				costTable[0][j + 1] + removal_cost(from[i])),
				costTable[0][j] + update_cost(from[i], to[j]));
		}

		costTable.erase(costTable.begin());
		costTable.push_back(Line(to.length() + 1));
	}

	int max_len = from.length() > to.length() ? from.length() : to.length();

	return ( max_len - costTable[0][to.length()] / max_cost ) / max_len;
}