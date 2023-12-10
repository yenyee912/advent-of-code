#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue> // so no need to write own queue

using namespace std;

// aho-corasick
// by build keyword trie, iterate the input based on trie pattern
// then find which pose in the input contains the word

const int ALPHABET_SIZE = 35; // including 26 alphabets and 1-9

struct TrieNode {
  TrieNode* children[ALPHABET_SIZE];
  TrieNode* fail;
  vector<int> output;  // Index of patterns that end at this node
    
  // constructor
  TrieNode() : fail(nullptr) {
    for (int i = 0; i < ALPHABET_SIZE; ++i){
      children[i] = nullptr;
    }
  }
};

class AhoCorasick{
  public:
      AhoCorasick() : root(new TrieNode()) {}

      void addPattern(const string& pattern, int index) {
        TrieNode* current = root;

        for (char c : pattern) {
            int index = getCharIndex(c);
            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }

        current->output.push_back(index);
        patterns.push_back(pattern);

    };

    void buildTrie() {
        queue<TrieNode*> q;
        
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != nullptr) {
            root->children[i]->fail = root;
            q.push(root->children[i]);
        }
    }

    while (!q.empty()) {
      TrieNode* current = q.front();
      q.pop();

      for (int i = 0; i < ALPHABET_SIZE; ++i){
        if (current->children[i] != nullptr){
          TrieNode* child = current->children[i];
          TrieNode* failNode = current->fail;

          while (failNode != nullptr && failNode->children[i] == nullptr){
            failNode = failNode->fail;
            }

          if (failNode != nullptr) {
            child->fail = failNode->children[i];
            } 
            
          else {
            child->fail = root;
            }

          // Merge output from fail link
          child->output.insert(child->output.end(), child->fail->output.begin(), child->fail->output.end());

          q.push(child);
          }
        }
      }
    };

    void searchPatterns(const string& text, vector<int> &result ){
      TrieNode* current = root;

      for (int i = 0; i < text.size(); ++i) {
        char c = text[i];
        int index = getCharIndex(c);

        while (current != nullptr && current->children[index] == nullptr) {
            current = current->fail;
        }

        if (current != nullptr) {
            current = current->children[index];

            // Process matches at current node
            for (int patternIndex : current->output) {
                //cout << "Pattern found at index " << i << ": " << patterns[patternIndex] << endl;
                result.push_back(patternIndex);
            }
        } 
        
        else {
            current = root;
        }
      }

    };

    private:
    TrieNode* root;
    vector<string> patterns; //Keep track of the patterns for display purposes
    int getCharIndex(char c) {
      int output= -1;
        if ('a' <= c && c <= 'z') {
            return c - 'a';  // Index for lowercase letters
        } else if ('1' <= c && c <= '9') {
            return c - '1' + 26;  // Index for numeric digits (starting from 26)
        } else {
            // Handle other characters if needed
            return -1;
        }

      return output;
      
    }

};

int matchResult(int index){
  switch(index){
    case 0:
    case 9:{
      return 1;
      break;
    }

    case 1:
    case 10:{
      return 2;
      break;
    }

    case 2:
    case 11:{
      return 3;
      break;
    }

    case 3:
    case 12:{
      return 4;
      break;
    }

    case 4:
    case 13:{
      return 5;
      break;
    }

    case 5:
    case 14:{
      return 6;
      break;
    } 

    case 6:
    case 15:{
      return 7;
      break;
    }

    case 7:
    case 16: {
      return 8;
      break;
    } 

    case 8:
    case 17:{
      return 9;
      break;
    }


    default:{
      return -1;
    }
  }
};

void doSearch(vector<string> &str1){
    AhoCorasick ac;
    string keyword[] = {"one", "two", "three", "four", "five",
                         "six", "seven", "eight", "nine", 
                         "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    // Add patterns to the Trie
    for (int i = 0; i < 18; i++) {
        ac.addPattern(keyword[i], i);
    }

    // Build the Aho-Corasick Trie
    ac.buildTrie();

    // Search for patterns in the strings


    int sum=0;
    for (const string& str : str1) {
      vector<int> result;
      //cout << "Searching patterns in: " << str << endl;
      ac.searchPatterns(str, result);
      //cout << result.size() << endl;

      int num1= matchResult(result[0]);
      int num2= matchResult(result[result.size()-1]);

      sum+= num1*10+ num2;

    }

    cout<< sum;
  
  //return sum;


}

int main(){
  fstream myFile; 
  myFile.open("day1.txt", ios::in);

  vector<string> str_arr;
  string cur_str="";

  while (!myFile.eof()){
    getline(myFile, cur_str);
    if (cur_str.length()>0){
      str_arr.push_back(cur_str);
    }
  }

  doSearch(str_arr);
}


