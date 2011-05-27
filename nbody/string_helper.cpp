#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;
inline double convertToDouble(string const& s);

void split(const string& str, const string& delim, vector<string>& result) {
  size_t start_pos = 0;
  size_t match_pos;
  size_t substr_length;

  while((match_pos = str.find(delim, start_pos)) != string::npos) {
    substr_length = match_pos - start_pos;

    if (substr_length > 0) {
      result.push_back(str.substr(start_pos, substr_length));
    }

    start_pos = match_pos + delim.length();
  }

  substr_length = str.length() - start_pos;

  if (substr_length > 0) {
    result.push_back(str.substr(start_pos, substr_length));
  }
}

inline double convertToDouble(std::string const& s) {
   std::istringstream i(s);
   double x;
   i >> x;
   return x;
}
