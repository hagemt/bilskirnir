#include <iostream>
#include <cstdlib>
#include <queue>

template <class T>
void merge(std::queue<T>& q, std::queue<T>& a, std::queue<T>& b) {
	while (!a.empty() && !b.empty()) {
		T& t1 = a.front(), t2 = b.front();
		if (t1 < t2) { q.push(t1); a.pop(); }
		else { q.push(t2); b.pop(); }
	}
	while (!a.empty()) { q.push(a.front()); a.pop(); }
	while (!b.empty()) { q.push(b.front()); b.pop(); }
}

template <class T>
void sort(std::queue<T>& q) {
	if (q.size() < 2) { return; }
	typename std::queue<T>::size_type s = q.size() / 2; std::queue<T> a, b;
	while (a.size() < s) { a.push(q.front()); q.pop(); }
	while (!q.empty()) { b.push(q.front()); q.pop(); }
	sort(a); sort(b); merge(q, a, b);
}

template <class T>
std::ostream& operator<<(std::ostream& ostr, std::queue<T>& q) {
	ostr << "[";
	while (!q.empty()) { ostr << " " << q.front(); q.pop(); }
	return ostr << " ]";
}

int main(int argc, char** argv) {
	std::queue<int> q; while (--argc) { q.push(atoi(argv[argc])); }
	sort(q); std::cout << q << std::endl; return 0;
}
