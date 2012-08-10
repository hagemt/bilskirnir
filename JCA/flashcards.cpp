#include <fstream>
#include <iostream>
#include <string>
#define SEPARATOR '%'
using namespace std;

// A very simple container class that facilitates Evan's JCA format
class flashcard
{
public:
  flashcard() { };
  flashcard(const string& front, const string& back) :
    m_front(front), m_back(back) { };
  explicit flashcard(const flashcard& f) :
    m_front(f.m_front), m_back(f.m_back) { };
  friend istream& operator>>(istream& istr, flashcard& f);
  friend ostream& operator<<(ostream& ostr, const flashcard& f);
private:
  string m_front, m_back;
};

istream&
operator>>(istream& istr, flashcard& f)
{
  string front, back;
  getline(istr, front, SEPARATOR);
  getline(istr, back);
  f.m_front = front;
  f.m_back = back;
  return istr;
}

ostream&
operator<<(ostream& ostr, const flashcard& f)
{
  ostr << "\\begin{flashcard}[Yomifuda]{" << f.m_front << "}" << endl;
  ostr << f.m_back << endl;
  return ostr << "\\end{flashcard}" << endl;
}

int
main(int argc, char ** argv)
{
  // Sanitize inputs
  if (argc < 3) {
    cerr << "USAGE: " << argv[0] << " in_file out_file [options...]" << endl;
    return 1;
  }
  ifstream input(argv[1]);
  if (!input) {
    cerr << "Unable to read from: '" << argv[1] << "'" << endl;
    return 1;
  }
  ofstream output(argv[2]);
  if (!output) {
    cerr << "Unable to write to: '" << argv[2] << "'" << endl;
    return 1;
  }

  flashcard f;
  // Join the options
  string options;
  for (int i = 3; i < argc; ++i) {
    if (i > 3) { options.append(1, ','); }
    options.append(argv[i]);
  }
  // Print a header
  output << "\\documentclass";
  if (!options.empty()) {
    output << '[' << options << ']';
  }
  output << "{flashcards}" << endl;
  output << "\\cardfrontstyle{headings}" << endl;
  output << "\\cardfrontfoot{Karuta Cards, RPI JCA 2012}" << endl;
  output << "\\usepackage{amssymb}" << endl;
  output << "\\begin{document}" << endl;
  // Print the cards
  for (int i = 1; input >> f; ++i) {
    #ifndef NDEBUG
    output << "%% Card " << i << endl;
    #endif
    output << f << endl;
  }
  // Print a footer
  output << "\\end{document}" << endl;
  return 0;
}

