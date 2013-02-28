#include <cassert>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

#define BUFFER_SIZE 1024
#define MIN_CHAR 'a'
#define MAX_CHAR 'z'

inline bool
alpha(char symbol)
{
	return (symbol == ' ') || isalpha(symbol);
}

typedef bool (*matcher)(char c);
typedef unordered_map<char, size_t> db_t;

bool
not_all_match(const string &s, matcher m)
{
	for (const char &c : s) {
		if (!m(c)) return true;
	}
	return false;
}

int main(void) {
	db_t letters;
	string token;
	stringstream stream;
	char buffer[BUFFER_SIZE];
	// Check the paramters
	assert(BUFFER_SIZE > 0 && islower(MIN_CHAR) && islower(MAX_CHAR));
	// Read line by line
	while (cin.getline(buffer, BUFFER_SIZE)) {
		token = string(buffer);
		if (not_all_match(token, &alpha)) break;
		// TODO map lambda (or tolower) onto buffer?
		stream << token;
		// Setup database
		for (char c = MIN_CHAR; c <= MAX_CHAR; ++c) letters[c] = 0;
		while (stream >> token) {
			if (token.empty()) continue;
			letters[token[0]] += 1;
		}
		// Print database
		bool first = true;
		for (const db_t::value_type &v : letters) {
			if (v.second > 0) {
				if (!first) cout << ", ";
				cout << v.first << "=" << v.second;
				first = false;
			}
		}
		cout << endl;
	}
	return (EXIT_SUCCESS);
}
