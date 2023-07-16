#include <bits/stdc++.h>
using namespace std;

/** Simple trie implementation. Values stored are -1 by default */
class trie {
  private:
    struct trie_node {
      trie_node *parent;
      vector<trie_node*> children;
      int val;
    } *cur;
    string s;
  public:
    trie() {
      cur = new trie_node{nullptr, vector<trie_node*>(26, nullptr), -1};
      s = "";
    }

    void update(int x) {
      cur->val = x;
    }

    int query() {
      return cur->val;
    }

    /** Does nothing if current node is root */
    void go_up() {
      if (cur->parent == nullptr) return;
      cur = cur->parent;
      s.pop_back();
    }

    void go_down(char c) {
      if (cur->children[c - 'a'] == nullptr) cur->children[c - 'a'] = new trie_node{cur, vector<trie_node*>(26, nullptr), -1};
      cur = cur->children[c - 'a'];
      s.push_back(c);
    }

    const char current_char() {
      if (cur->parent == nullptr) return '$';
      return s.back();
    }
};
