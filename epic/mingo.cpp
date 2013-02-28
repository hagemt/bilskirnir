#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
using namespace std;

#ifdef USE_BITSET
#include <bitset>
typedef bitset bits_t;

inline bool
all(const bitset &bits)
{
	return bitset.all();
}
#else
typedef vector<bool> bits_t;

inline bool
all(const vector<bool> &bits)
{
	vector<bool>::size_type i, n = bits.size();
	for (i = 0; i < n; ++i) {
		if (!bits[i]) {
			return false;
		}
	}
	return true;
}
#endif

inline void
mark(bits_t &bits, size_t index)
{
	bits[index] = true;
}

// For convenience, some structs:
typedef size_t num_t;
typedef pair<num_t, num_t> loc_t;

// For the arguments, some types:
typedef vector<num_t> row_t;
typedef vector<row_t> tab_t;
typedef list<num_t> list_t;

// Use a hash map, if it's available
#if __cplusplus > 199711L
#include <unordered_map>
typedef unordered_map<num_t, loc_t> tableau_t;
#else
#include <map>
typedef map<num_t, loc_t> tableau_t;
#endif

void
mingo(const tab_t &board, const list_t &calls)
{
	tab_t::size_type m = 1, n = board.size();
	// Create database of taken squares
	vector<bits_t> taken_by_row(n, bits_t(n, false));
	vector<bits_t> taken_by_col(n, bits_t(n, false));
	bits_t diagonal(n, false), skew(n, false);
	// Create location lookup table
	tableau_t location;
	for (tab_t::size_type i = 0; i < n; ++i) {
		for (row_t::size_type j = 0; j < n; ++j) {
			location[board[i][j]] = make_pair(i, j);
		}
	}
	// Perform calls, in order
	bool any_mingo = false;
	list_t::const_iterator it, itend = calls.end();
	for (it = calls.begin(); it != itend; ++it, ++m) {
		loc_t loc = location[*it];
		// Mark this location multiple ways
		mark(taken_by_row[loc.first], loc.second);
		mark(taken_by_col[loc.second], loc.first);
		if (loc.first == loc.second) {
			mark(diagonal, loc.second);
		}
		if (loc.first + loc.second == n) {
			mark(skew, loc.second);
		}
		// Check for mingos (each O(1), using bitset)
		bool mingo = all(taken_by_row[loc.first]) || all(taken_by_col[loc.second]);
		if (loc.first == loc.second) {
			mingo = mingo || all(diagonal);
		}
		if (loc.first + loc.second == n) {
			mingo = mingo || all(skew);
		}
		if (mingo) {
			cout << "You got a Mingo on call: " << m << endl;
			any_mingo = true;
		}
	}
	// Any mingo overall?
	if (!any_mingo) {
		cout << "Sorry! No Mingo for you!" << endl;
	}
}

void
play(size_t n)
{
	// Set up a sample table (increasing grid)
	tab_t t(n, row_t(n, 0));
	for (tab_t::size_type i = 0; i < n; ++i) {
		for (row_t::size_type j = 0; j < n; ++j) {
			t[i][j] = i * n + j;
		}
	}
	// Set up a sample call list (increasing numbers)
	list_t c;
	for (num_t i = 0; i < n * n; ++i) {
		c.push_back(i);
	}
	// Play!
	mingo(t, c);
}

int
main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i) {
		play(atoi(argv[i]));
	}
}
