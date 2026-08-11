/*
    Your Trie object will be instantiated and called as such:
    Trie* obj = new Trie();
    obj->insert(word);
    bool check2 = obj->search(word);
    bool check3 = obj->startsWith(prefix);
 */

class Node{
    public: pair<Node*,int> links[2];
    //public: bool flag = false;
    Node(){
        links[0].second = 2e9;
        links[1].second = 2e9;
    }
    bool containsKey(int ch){
        return this->links[ch].first!=NULL;
    }

    void put(int ch, Node* node,int element){
        this->links[ch] = make_pair(node,element);
    }

    void updateMinimum(int ch,int element){
        this->links[ch].second = min(this->links[ch].second,element);
    }

    pair<Node*,int> get(int ch){
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
                node->put(val,new Node(),element);
            }
            node->updateMinimum(val,element);
            node = node->get(val).first;
        }

        //node->setEnd();
    }

    int process(int element,int limit){
        Node* node = root;
        int ans=0;
        for(int i=31;i>=0;i--){
            int val = (element & (1<<i)) ? 0 : 1;
            
            if(node->containsKey(val) && node->get(val).second<=limit){
                ans+= (1<<i);
                node = node->get(val).first;
            }
            else{
                node = node->get(!val).first;
            }
            
        }

        return ans;
    }


};

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries){
	Trie *trie = new Trie();

	int n= arr.size(),m=queries.size();
    int mini=2e9;
	for(int i=0;i<n;i++){
        mini = min(mini,arr[i]);
		trie->insert(arr[i]);
	}

	vector<int> ans(m);

	for(int i=0;i<m;i++){
        if(queries[i][1]<mini)ans[i] = -1;
        else{
            ans[i] = trie->process(queries[i][0],queries[i][1]);
        }
	}

    return ans;
}
