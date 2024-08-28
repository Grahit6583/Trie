#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class Trienode
{
    public:
        char data;
        bool isterminal;
        Trienode* children[26];
        Trienode(char data)
        {
            this->data = data;
            for(int i=0; i<26; i++)
            {
                children[i] = NULL;
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

        void insert_util(Trienode* root, string word)
        {
            if(word.length() == 0)
            {
                root->isterminal = true;
                return;
            }

            int index  = word[0] - 'a';
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

            insert_util(child,word.substr(1));
        }

        void insert(string word)
        {
            return insert_util(root,word);
        }

        void printsuggestions(Trienode* curr, vector<string> &temp, string prefix)
        {
            cout<<"next_entry  "<<curr->data<<endl;
            cout<<"prefix_entry   "<<prefix<<endl;
            if(curr->isterminal)
            {
                temp.push_back(prefix);
            }
            for(char ch = 'a'; ch<='z'; ch++)
            {
                Trienode* next = curr->children[ch-'a'];
                cout<<"next  "<<curr->data<<"  "<<ch<<endl;
                if(next != NULL)
                {
                    prefix.push_back(ch);
                    cout<<"push_pre   "<<prefix<<endl;
                    printsuggestions(next, temp, prefix);
                    prefix.pop_back();
                    cout<<"pop_pre   "<<prefix<<endl;
                }
            }
        }

        vector<vector<string>> getsuggestions(string str)
        {
            Trienode* prev = root;
            vector<vector<string>> output;
            string prefix = "";

            for(int i=0; i<str.length(); i++)
            {
                char lastch = str[i];
                prefix.push_back(lastch);
                Trienode* curr = prev->children[lastch - 'a'];
                cout<<curr->data<<"  "<<endl;
                if(curr == NULL)
                {
                    break;
                }

                vector<string> temp;
                printsuggestions(curr,temp,prefix);
                output.push_back(temp);
                temp.clear();
                prev = curr;
            }
            return output;
        }
};

vector<vector<string>> phone_Directory(vector<string>& contact, string &querystr)
{
    Trie* t = new Trie();
    for(int i=0; i<contact.size();i++)
    {
        string str = contact[i];
        t->insert(str);
    }

    return t->getsuggestions(querystr);
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    Trie *t = new Trie();

    vector<string> contact;
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        string temp;
        cin>>temp;
        contact.push_back(temp);
    }
    for(int i=0; i<n; i++)
    {
        cout<<contact[i]<<"   ";
    }
    string ans;
    cin>>ans;
    cout<<endl;
    vector<vector<string>> answ = phone_Directory(contact,ans);
    for (const auto& row : answ) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    // for(int i=0; i<answ.size(); i++)
    // {
    //     for(int j =0; j<answ[i].size(); i++)
    //     {
    //         cout<<answ[i][j]<<"  ";
    //     }
    // }
    return 0;
}