#include <bits/stdc++.h> 

/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);

    approach: sort the strings array. this is important step as we "abc" string to be processed after "a" and "ab" as our goal is to find the longest complete string. 

    insert the strings one by one: small modification in insert method: while going through char array, check whether if we flag = true at each char ending: if it is obeyed at
    characters, then we have our complete string. accept it as an answer if length is maximum
 */

class Node{
    public: Node *links[26];
    public: bool flag = false;

    bool containsKey(char ch){
        return this->links[ch-'a']!=NULL;
    }

    void put(char ch, Node* node){
        this->links[ch-'a'] = node;
    }

    Node* get(char ch){
        return this->links[ch-'a'];
    }

    void setEnd(){
        this->flag= true;
    }

    bool isEnd(){
        return this->flag;
    }
};
class Trie {

public:

    /** Initialize your data structure here. */
    Node* root;
    Trie() {
        root = new Node();
    }

    /** Inserts a word into the trie. */
    bool insert(string word) {
        Node* node = root;
        int n = word.size();
        bool isCompleteString = true;
        for(int i=0;i<n;i++){
            if(!node->containsKey(word[i])){
                node->put(word[i],new Node());
            }
            node = node->get(word[i]);
            if(i!=n-1 && !node->isEnd())isCompleteString = false;
        }

        node->setEnd();
        return isCompleteString;
    }

};
string completeString(int n, vector<string> &a){
    // Write your code here.
    sort(a.begin(),a.end());

    Trie *trie = new Trie();
    string ans="";int maxLen = 0;
    for(int i=0;i<n;i++){
        if(trie->insert(a[i])){
            int wordLen = a[i].size();
            if(wordLen> maxLen){
                maxLen = a[i].size();
                ans = a[i];
            }
        }
    }

    if(maxLen==0)return "None";
    return ans;
}
