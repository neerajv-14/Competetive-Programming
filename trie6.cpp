/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
 */

class Node{
    public: Node *links[2];
    //public: bool flag = false;

    bool containsKey(int ch){
        return this->links[ch]!=NULL;
    }

    void put(int ch, Node* node){
        this->links[ch] = node;
    }

    Node* get(int ch){
        return this->links[ch];
    }

    // void setEnd(){
    //     this->flag= true;
    // }

    // bool isEnd(){
    //     return this->flag;
    // }
};
class Trie {

public:

    /** Initialize your data structure here. */
    Node* root;
    Trie() {
        root = new Node();
    }

    /** Inserts a word into the trie. */
    void insert(int element) {
        Node* node = root;
        
        for(int i=31;i>=0;i--){
            int val = (element & (1<<i)) ? 1 : 0;

            if(!node->containsKey(val)){
                node->put(val,new Node());
            }
            node = node->get(val);
        }

        //node->setEnd();
    }

    int process(int element){
        Node* node = root;
        int ans=0;
        for(int i=31;i>=0;i--){
            int val = (element & (1<<i)) ? 0 : 1;

            if(node->containsKey(val)){
                ans+= (1<<i);
                node = node->get(val);
            }
            else{
                node = node->get(!val);
            }
            
        }

        return ans;
    }


};


int maxXOR(int n, int m, vector<int> &arr1, vector<int> &arr2) 
{
    // Write your code here.  

    Trie *trie = new Trie();

    for(int i=0;i<n;i++){
        trie->insert(arr1[i]);
    } 

    int ans=0;

    for(int i=0;i<m;i++){
        ans = max(ans, trie->process(arr2[i]));
    }

    return ans;
}
