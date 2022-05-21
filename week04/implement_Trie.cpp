class Node {
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
class Trie {
    Node *root;
public:
    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node *curr = root;
        for(auto c:word) {
            int id = c - 'a';
            if(curr->next[id] == NULL)
                curr->next[id] = new Node();
            curr = curr->next[id];
        }
        curr->wordFlag = true;
    }

    bool search(string word) {
        Node *curr = root;
        for(auto c:word) {
            int id = c - 'a';
            if(curr->next[id] == NULL)
                return false;
            curr = curr->next[id];
        }
        return curr->wordFlag;
    }

    bool startsWith(string prefix) {
        Node *curr = root;
        for(auto c:prefix) {
            int id = c - 'a';
            if(curr->next[id] == NULL)
                return false;
            curr = curr->next[id];
        }
        return true;
    }

    /*
    bool search(string word, bool isPrefixSearch = false) {
        Node *curr = root;
        for(auto c:word) {
            int id = c - 'a';
            if(curr->next[id] == NULL)
                return false;
            curr = curr->next[id];
        }
        return curr->wordFlag || isPrefixSearch;
    }

    bool startsWith(string prefix) {
        return search(prefix, true);
    }
    */
};
