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

    vector<int> dir{-1,0,1,0,-1};

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

    void dfs(int x, int y, vector<vector<char>> &board, Node *curr, vector<string> &wordsOnBoard) {
        char ch = board[x][y];
        if(ch == '#' || (curr && curr->next[ch - 'a'] == NULL)) return;
        curr = curr->next[ch - 'a'];
        if(curr && curr->word.size() > 0) {
            wordsOnBoard.push_back(curr->word);
            curr->word.clear();
        }
        board[x][y] = '#';
        for(int i=0; i<4; i++) {
            int X = x + dir[i];
            int Y = y + dir[i+1];
            if(X < 0 || Y < 0 || X >= board.size() || Y >= board[0].size() || board[X][Y] == '#') continue;
            dfs(X,Y,board,curr,wordsOnBoard);
        }
        board[x][y] = ch;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Node *root = generateTrie(words);
        vector<string> wordsOnBoard;
        int n = board.size();
        int m = board[0].size();
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                dfs(i, j, board, root, wordsOnBoard);
            }
        }
        return wordsOnBoard;
    }
};
