class Solution {
public:
    class Node{
    public:
        bool wordFlag;
        Node *next[26];
        Node() {
            wordFlag = false;
            for(int i=0; i<26; i++) {
                next[i] = NULL;
            }
        }
    };

    vector<bool> visited;

    Node* generateTrie(vector<string> &products) {
        Node *root = new Node();
        for(auto &wd:products) {
            Node *curr = root;
            for(auto &c:wd) {
                int id = c - 'a';
                if(curr->next[id] == NULL)
                    curr->next[id] = new Node();
                curr = curr->next[id];
            }
            curr->wordFlag = true;
        }
        return root;
    }

    void search(string word, int start, int n, Node *root) {
        Node* temp = root;
        for(int i=start; i<n; i++){
            int index = word[i]-'a';
            if(temp->next[index] == NULL){
                return;
            }
            temp = temp->next[index];
            if(temp->wordFlag)
                visited[i+1] = true;
        }
        if(temp->wordFlag)
            visited[n] = true;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        visited.assign(n+1,false);
        Node *root = generateTrie(wordDict);
        visited[0] = true;
        for(int i=0; i<n; i++) {
            if(visited[i])
                search(s,i,n, root);
        }
        return visited[n];
    }
};
