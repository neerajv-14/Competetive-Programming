/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
 */

// idea: 
/*
    maintain pair<Node*,int> links. links[a]-> gives next reference linked to character 'a' and frequency
    of char 'a'.

    flagEndings: gives no. of endings that happened at that node. 

    INSERT: 
     after you do the node link, increment frequency of curr element using incrementFrequency.

     setEnd(): will increment the counter instead of setting simple bool

    COUNT NO OF EXACT WORDS: 

     if at any point , there is no link then return 0. to check if there is link, we should check frequency
     as well. reason: insert a word, remove the same word immediately. here the link is still present, but
     frequency will be decreased during our erase() method , so we need to check if frequency is >0.

     at end: no. of endings is our answer. 

    ERASE: 

     we are assured that the deleted word is already present in trie. so, go node by node: decrement curr 
     character's frequency. at the end, decrement flagEndings by one as the word is no longer present 

    COUNT NO OF WORDS WITH PREFIX: 

        keep a mini initialized by INT_MAX.  go node by node, if at some point , there is no key: return 0, 
        otherwise do mini = min(mini, node-> getFrequency(curr character));
        at the end : directly return mini.


    STRIVER approach : Node{ Node* , int countEndings, int countPrefixEndings}
*/
class Node{
    public: pair<Node*,int> links[26];
    public: int flagEndings = 0;

    public: Node(){
        for(int i=0;i<26;i++){
            links[i].second =0;
        }
    }

    bool containsKey(char ch){
        return this->links[ch-'a'].first!=NULL && this->links[ch-'a'].second!=0;
    }

    void put(char ch, Node* node){
        this->links[ch-'a'].first = node;
    }

    Node* get(char ch){
        return this->links[ch-'a'].first;
    }

    void setEnd(){
        this->flagEndings++;
    }

    void removeEnd(){
        this->flagEndings--;
    }

    bool isEnd(){
        return this->flagEndings>0;
    }

    int noOfEndings(){
        return this->flagEndings;
    }

    void decrementFrequency(char ch){
        this->links[ch-'a'].second--;
    }

    void incrementFrequency(char ch){
        this->links[ch-'a'].second++;
    }

    int getFrequency(char ch){
        return this->links[ch-'a'].second;
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
            node->incrementFrequency(word[i]);
            node = node->get(word[i]);
        }

        node->setEnd();
    }
    int countWordsEqualTo(string &word){
        int n=word.size();
        Node* node =root;
        for(int i=0;i<n;i++){
            if(!node->containsKey(word[i])){
                return 0;
            }
            node = node->get(word[i]);
        }
        if(!node->isEnd())return 0;
        return node->noOfEndings();
    }      
    int countWordsStartingWith(string &word){
        int mini = INT_MAX,n=word.size();
        Node* node =root;
        for(int i=0;i<n;i++){
            if(!node->containsKey(word[i])){
                mini = 0;
                break;
            }
            mini = min(mini,node->getFrequency(word[i]));
            node = node->get(word[i]);
        }
        return mini;
    }    

    void erase(string &word){
        int n = word.size();
        Node* node = root;

        for(int i=0;i<n;i++){
            node->decrementFrequency(word[i]);
            
            node = node->get(word[i]);
        }

        node->removeEnd();

    }

   
};
