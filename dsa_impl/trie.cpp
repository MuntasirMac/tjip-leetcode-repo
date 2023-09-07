#include <bits/stdc++.h>
using namespace std;

#define CHAR_SIZE 26

class TrieNode
{
public:
    bool isEnd;
    int cnt;
    TrieNode* next[CHAR_SIZE];

    TrieNode()
    {
        isEnd = false;
        cnt = 0;
        for (int i = 0; i < CHAR_SIZE; i++)
        {
            next[i] = nullptr;
        }
    }

    bool hasChildren()
    {
        for (int i = 0; i < CHAR_SIZE; i++)
        {
            if (next[i]) return true;
        }
        return false;
    }
};

class Trie
{
public:
    TrieNode* root;
    Trie()
    {
        root = new TrieNode();
    }
    Trie(vector<string> words)
    {
        root = new TrieNode();
        for (auto &wd : words)
        {
            insert(wd);
        }
    }
    bool search(string word);
    bool insert(string word);
    bool insertAll(vector<string> words);
    bool remove(TrieNode* u, string &word, int pos);
    bool remove(string word);
    void clear();
    void clear_tree(TrieNode* u);
    void fetch(TrieNode* u, int level);
    void print();
};

bool Trie::search(string word)
{
    if (root == nullptr) return false;
    auto curr = root;
    for (auto c : word)
    {
        int id = c - 'a';
        if (curr -> next[id] == nullptr)
        {
            return false;
        }
        curr = curr -> next[id];
    }
    return curr -> isEnd;
}

bool Trie::insert(string word)
{
    if (search(word)) return false;
    auto curr = root;
    for (auto c : word)
    {
        int id = c - 'a';
        curr -> cnt++;
        if (curr -> next[id] == nullptr)
        {
            curr -> next[id] = new TrieNode();
        }
        curr = curr -> next[id];
    }
    curr -> cnt++;
    return curr -> isEnd = true;
}

bool Trie::insertAll(vector<string> words)
{
    if (root == nullptr) return false;
    for (auto &wd : words)
    {
        insert(wd);
    }
    return true;
}

bool Trie::remove(TrieNode* u, string &word, int pos)
{
    if (u == nullptr) return false;
    u -> cnt--;
    if (word.size() == pos)
    {
        if (u -> isEnd) u -> isEnd = false;
        return true;
    }
    bool status = remove(u -> next[word[pos] - 'a'], word, pos + 1);
    if (u -> next[word[pos] - 'a'] -> hasChildren() == false && u -> next[word[pos] - 'a'] -> cnt == 0)
    {
        delete u -> next[word[pos] - 'a'];
        u -> next[word[pos] - 'a'] = nullptr;
    }
    return status;
}

bool Trie::remove(string word)
{
    if (!search(word)) return false;
    return remove(root, word, 0);
}

void Trie::fetch(TrieNode* u, int level)
{
    if (u == nullptr) return;
    if (level == 0) printf("root (%d), ", u -> cnt);
    else
    {
        if (u -> isEnd)
            printf("(*%d), ", u -> cnt);
        else
            printf("(%d), ", u -> cnt);
    }
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (u -> next[i])
        {
            printf("%c ", (char)(i + 'a'));
            fetch(u -> next[i], level + 1);
        }
    }
}

void Trie::print()
{
    fetch(root, 0);
    puts("");
}

void Trie::clear_tree(TrieNode* u)
{
    if (u == nullptr) return;
    u -> cnt = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (u -> next[i])
        {
            clear_tree(u -> next[i]);
            if (u -> next[i] -> hasChildren() == false && u -> next[i] -> cnt == 0)
            {
                delete u -> next[i];
                u -> next[i] = nullptr;
            }
        }
    }
}

void Trie::clear()
{
    clear_tree(root);
}

int main()
{
    Trie* trie = new Trie();
    trie -> insertAll({"abb", "abbc", "abbd"});
    return 0;
}
