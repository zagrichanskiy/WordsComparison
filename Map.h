#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <map>
#include <vector>
#include <cctype>

enum { l0_cost, l1_cost, l2_cost, l3_cost, max_cost };
typedef double cost_type;
typedef std::vector<cost_type> Line;
typedef std::vector<Line> Matrix;
typedef std::map<std::string::value_type, int> Map;

class Create_map {
private:
	Map new_map;
	int value;
public:
	Create_map(const std::string let) : value(1) {
		for (std::size_t i = 0; i < let.length(); ++i) {
			new_map[let[i]] = value;
			new_map[toupper(let[i])] = -value;
		}
	}
	Create_map & operator()(const std::string let) {
		value++;
		for (std::size_t i = 0; i < let.length(); ++i) {
			new_map[let[i]] = value;
			new_map[toupper(let[i])] = -value;
		}
		return *this;
	}
	operator Map() {
		return new_map;
	}
};

#endif