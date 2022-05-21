class Solution {
public:
    class Node{
    public:
        string word;
        Node *next[26];
        Node() {
            word = "";
            for(int i=0; i<26; i++) {
                next[i] = NULL;
            }
        }
    };

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
            curr->word = wd;
        }
        return root;
    }

    void dfs(Node *u, vector<string> &words) {
        if(u == NULL || words.size() == 3) return;
        if(u->word.size() > 0 && words.size()<3)
            words.push_back(u->word);
        for(int i=0; i<26; i++) {
            dfs(u->next[i], words);
        }
    }

    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> suggestion;
        Node *root = generateTrie(products);
        for(auto c:searchWord) {
            root = root && root->next[c-'a'] ? root->next[c - 'a'] : NULL;
            vector<string> words;
            dfs(root, words);
            suggestion.push_back(words);
        }
        return suggestion;
    }
};
