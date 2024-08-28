#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class Trienode
{
    public:
        char data;
        Trienode *childern[26];
        bool isterminal;
        Trienode(char ch)
        {
            data = ch;
            for(int i=0; i<26; i++)
            {
                childern[i] = NULL;
            }

            isterminal = false;
        }
};

class Trie
{
    public:
        Trienode* root;
        Trie()
        {
            root = new Trienode('\0');
        }

        void insert_util(Trienode* root,string word)
        {
            if(word.length() == 0)
            {
                root->isterminal = true;
                return;
            }

            int index = word[0]-'A';
            Trienode *child;
            if(root->childern[index] != NULL)
            {
                child = root->childern[index];
            }
            else
            {
                child = new Trienode(word[0]);
                root->childern[index] = child;
            }

            insert_util(child,word.substr(1));
        }

        void insert(string word)
        {
            return insert_util(root,word);
        }

        bool search_util(Trienode* root, string word)
        {
            if(word.length() == 0)
            {
                return root->isterminal;
            }

            int index = word[0]-'A';
            Trienode *child;
            if(root->childern[index] != NULL)
            {
                child = root->childern[index];
            }
            else
            {
                return false;
            }

            return search_util(child,word.substr(1));
        }

        bool search(string word)
        {
            return search_util(root,word);
        }


        void remove_word(Trienode *root , string word)
        {
            if(word.length() == 0)
            {
                root->isterminal =  false;
                return;
            }

            int index = word[0]-'A';
            Trienode *child;
            if(root->childern[index] != NULL)
            {
                child = root->childern[index];
            }
            else
            {
                return ;
            }

            return remove_word(child,word.substr(1)); 
        }

        void remove(string word)
        {
            remove_word(root,word);
            return;
        }
};

int main()
{

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    Trie *t = new Trie();

    t->insert("ARM");
    t->insert("ARMED");
    t->insert("DOG");

    cout<<t->search("ARM")<<endl;
    cout<<t->search("ARMED")<<endl;
    cout<<t->search("DOG")<<endl;

    t->remove("ARM");
    cout<<t->search("ARM")<<endl;


}