#include <iostream>
#include <string>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include <vector>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
void gotoxy(int x,int y)
 {
     COORD c;
     c.X=x;
     c.Y=y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
 }

class TrieNode {

	public :

	char data;
	TrieNode **children;
	bool isTerminal;

	TrieNode(char data) {

		this -> data = data;
		children = new TrieNode*[26];

		for(int i = 0; i < 26; i++)
		{
			children[i] = NULL;
		}

		isTerminal = false;
	}
};

class Trie {

	TrieNode *root;

	public :

	int count;

	Trie() {

		this->count = 0;
		root = new TrieNode('\0');
	}

	bool insertWord(TrieNode *root, string word) {

		if(word.size() == 0)
		{
			if (!root->isTerminal)
			{
				root -> isTerminal = true;
				return true;
			}
			else
			{
				return false;
			}
		}

		int index = word[0] - 'a';
		TrieNode *child;

		if(root -> children[index] != NULL)
		{
			child = root -> children[index];
		}
		else
		{
			child = new TrieNode(word[0]);
			root -> children[index] = child;
		}

		return insertWord(child, word.substr(1));
	}

	void insertWord(string word) {
		if (insertWord(root, word))
		{
			this->count++;
		}
	}

    void possibleWord(TrieNode *root, string ans, string pattern){

        if(!pattern.size() && root->isTerminal==true)
        {
            cout<< ans<<endl;
        }

        if(pattern.size())
        {
            int index = pattern[0] - 'a';
            if(root -> children[index] == NULL)
            {
                return;
            }
            else
            {
                ans +=pattern[0];
                possibleWord(root -> children[index], ans, pattern.substr(1));
            }
        }
        else
        {
            for(int i = 0; i < 26; i++)
            {
                if(root -> children[i] != NULL)
                {
                    string smallAns = ans;
                    smallAns += root -> children[i] -> data;
                    possibleWord(root -> children[i], smallAns, pattern);
                }
            }
        }
    }


    TrieNode* findWord(TrieNode *root, string pattern){

        if(pattern.size()==0)
        {
            return root;
        }

        int index=pattern[0]-'a';
        TrieNode *child;

		if(root->children[index]!=NULL)
        {
            child=root->children[index];
            return findWord(child,pattern.substr(1));
        }
        else
        {
            return NULL;
        }
    }


    void autoComplete(vector<string> input, string pattern) {

        for(int i = 0; i < input.size(); i++)
		{
            insertWord(input[i]);
        }

        string ans = "";

        possibleWord(root, ans, pattern);
    }
};


int main() {
Trie t;
/*	Trie t;
    int N;
    cin>>N;
    string pattern;
    vector<string> vect;
    for (int i=0; i < N; i++)
	{
        string word;
        cin >> word;
        vect.push_back(word);
    }

	cin >> pattern;
	string pattern;
    string word;
    t.autoComplete(vect, pattern);*/
    string word;
    string word1;
    string pattern;
    vector<string> vect;
    int k;
    while(1)
    {
        system("cls");
        gotoxy(90,20);
    cout<<"1.Enter new words"<<endl;
    gotoxy(90,21);
    cout<<"2.Autosuggestion tab"<<endl;
    gotoxy(90,22);
    cout<<"3.Exit"<<endl;
    gotoxy(90,23);
    cout<<"Enter your Choice";
    cin>>k;
    switch(k)
    {
    case 1:
    {
        system("cls");
        gotoxy(90,20);
    ofstream ofile;
    ofile.open("words.txt",ios::app);
    int N;
    cout<<"Enter number of words you want to enter";
    cin>>N;
    for (int i=0; i < N; i++)
	{
	    gotoxy(90,20+i+1);
	    cin>>word;
        ofile<<word<<endl;
    }
        gotoxy(90,20+N+1);
        cout<<"Words Entered Successfully";
        gotoxy(90,20+N+2);
        cout<<"Press Any Key To Continue";
        _getch();
        ofile.close();
        break;
    }
    case 2:
       {
        system("cls");
        ifstream ifile;
        ifile.open("words.txt",ios::in);
        cout<<"Enter Pattern";
        cin>>pattern;
        while(ifile>>word1)
        {
            vect.push_back(word1);
        }
        ifile.close();

        t.autoComplete(vect,pattern);
        cout<<"Press any key to continue";
        _getch();
        break;
       }
    case 3:
        exit(0);
        break;
    default:
        gotoxy(90,24);
        cout<<"Invalid choice";
    }
    }
}
