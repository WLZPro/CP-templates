#include "math/modint.hpp"
#include <bits/stdc++.h>
using namespace std;

// Copied from tourist

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

string to_string(const string &s) {
  return '"' + s + '"';
}

string to_string(const char *s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

template <typename T1, typename T2>
string to_string(pair<T1, T2> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template<typename T>
string to_string(const priority_queue<T> &pq) {
  priority_queue<T> tmp = pq;
  string ans = "{";
  bool first = true;
  while (!tmp.empty()) {
    if (!first) ans += ", ";
    first = false;
    ans += to_string(tmp.top());
    tmp.pop();
  }
  ans += '}';
  return ans;
}

template<typename T>
string to_string(const stack<T> &st) {
  stack<T> tmp = st;
  string ans = "{";
  bool first = true;
  while (!tmp.empty()) {
    if (!first) ans += ", ";
    first = false;
    ans += to_string(tmp.top());
    tmp.pop();
  }
  ans += '}';
  return ans;
}

template<typename T>
string to_string(const queue<T> &q) {
  queue<T> tmp = q;
  string ans = "{";
  bool first = true;
  while (!tmp.empty()) {
    if (!first) ans += ", ";
    first = false;
    ans += to_string(tmp.top());
    tmp.pop();
  }
  ans += '}';
  return ans;
}

template<const int MOD>
string to_string(const modint<MOD> &x) {
    return to_string(x.val());
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string ans = "{";
  for (const auto &x : v) {
    if (!first) ans += ", ";
    first = false;
    ans += to_string(x);
  }
  ans += "}";
  return ans;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}
