#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class Trienode
{
    public:
        char data;
        Trienode *children[26];
        bool isTerminal;
        Trienode(char ch)
        {
            data = ch;
            for(int i=0; i<26; i++)
            {
                children[i] = NULL;
            }
            isTerminal = false;
        }
};

class Trie
{
    public:
        Trienode *root;
        Trie()
        {
            root = new Trienode('\0');
        }

        void insertutil(Trienode *root, string word)
        {
            if(word.length() == 0)
            {
                root->isTerminal = true;
                return;
            }

            int index = word[0]-'A';
            Trienode* child;
            if(root->children[index] != NULL)
            {
                child = root->children[index];
            }
            else
            {
                child = new Trienode(word[0]);
                root->children[index] = child;
            }

            insertutil(child,word.substr(1));
        }

        void insertWord(string word)
        {
            return insertutil(root,word);
        }

        bool searchutil(Trienode* root, string word)
        {
            if(word.length() == 0)
            {
                return root->isTerminal;
            }
            int index = word[0]-'A';
            Trienode *child;
            if(root->children[index] != NULL)
            {
                child = root->children[index];
            }
            else
            {
                return false;
            }

            return searchutil(child,word.substr(1));
        }

        bool searchword(string word)
        {
            return searchutil(root,word);
        }
};

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    Trie *t = new Trie();

    t->insertWord("ABCD");

    cout<<t->searchword("ABC")<<endl;
    return 0;
}