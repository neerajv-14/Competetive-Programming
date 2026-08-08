/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
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
    void insert(string word) {
        Node* node = root;
        int n = word.size();

        for(int i=0;i<n;i++){
            if(!node->containsKey(word[i])){
                node->put(word[i],new Node());
            }
            node = node->get(word[i]);
        }

        node->setEnd();
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* node = root;
        int n = word.size();

        for(int i=0;i<n;i++){
            if(!node->containsKey(word[i]))return false;
            node = node->get(word[i]);
        }

        return node->isEnd();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* node = root;
        int n = prefix.size();

        for(int i=0;i<n;i++){
            if(!node->containsKey(prefix[i]))return false;
            node = node->get(prefix[i]);
        }
        return true;
    }
};
