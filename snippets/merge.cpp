#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#define MIN_SIZE 1 << 15
#define MAX_SIZE 1 << 30
using namespace std;

template <typename T>
void merge(const vector<T>& left, const vector<T>& right, vector<T>& v) {
  typename vector<T>::size_type i, j, k, m, n;

  assert(left.size() + right.size() == v.size());

  i = j = k = 0;
  m = left.size();
  n = right.size();
  while (i < m && j < n) {
    if (left[i] < right[j]) {
      v[k] = left[i];
      ++i;
    } else {
      v[k] = right[j];
      ++j;
    }
    ++k;
  }

  while (i < m) {
    v[k] = left[i];
    ++i;
    ++k;
  }

  while (j < n) {
    v[k] = right[j];
    ++j;
    ++k;
  }
}

template <typename T>
void merge_sort(vector<T>& v, typename vector<T>::size_type i, typename vector<T>::size_type n) {
  vector<T> left, right;
  typename vector<T>::size_type m;

  if (i + 1 < n) {
    m = (i + n) / 2;

    left.resize(m - i);
    right.resize(n - m);
    copy(v.begin() + i, v.begin() + m, left.begin());
    copy(v.begin() + m, v.begin() + n, right.begin());

    merge_sort(left, 0, m - i);
    merge_sort(right, 0, n - m);

    merge(left, right, v);
  }
}

#ifndef NDEBUG
template <typename T>
ostream& operator<<(ostream& ostr, vector<T>& v) {
  typename vector<T>::size_type i, n = v.size();

  ostr << "[ ";
  for (i = 0; i < n; ++i) {
    ostr << v[i] << " ";
  }
  return ostr << "]";
}
#endif

template <typename T>
void randomize(vector<T>& v) {
  typename vector<T>::size_type i, r, n = v.size();

  for (i = 0; i < n; ++i) {
    v[i] = i;
  }

  for (i = 0; i < n; ++i) {
    r = i + rand() % (n - i);
    iter_swap(v.begin() + i, v.begin() + r);
  }
}

template <typename T>
void sort(vector<T>& v) {
  merge_sort(v, 0, v.size());
}

template <typename T>
void check(vector<T>& v) {
  typename vector<T>::size_type i, n = v.size();
  for (i = 1; i < n; ++i) {
    assert(!(v[i] < v[i-1]));
  }
}


int main(void) {
  vector<int> v;
  vector<int>::size_type n;
  time_t start, finish;

  srand(static_cast<unsigned int>(time(NULL)));

  for (n = MIN_SIZE; n <= MAX_SIZE; n <<= 1) {
    v.resize(n);
    randomize(v);
    #ifndef NDEBUG
    cout << v << endl;
    #endif
    time(&start);
    sort(v);
    time(&finish);
    #ifndef NDEBUG
    check(v);
    cout << v << endl;
    #endif
    cout << "Sorted " << n << " elements in " << finish - start << " second(s)" << endl;
  }

  return 0;
}
