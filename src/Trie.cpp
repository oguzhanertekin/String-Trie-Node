#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <vector>
#define R 26
using namespace std;

struct Node {
public:
    string value;
    Node* next[R];
    bool isEnd;
    string key2;
};

class Trie{
public:
    Node* root=getNode();
    Trie(){}
    ~Trie(){}


    Node *getNode()
    {
        Node *pNode =  new Node;
        pNode->isEnd = false;
        for (int i = 0; i < R; i++)
            pNode->next[i] = NULL;

        return pNode;
    }

    void insert(string key,string val)
    {
        Node *head= this->root;
        head->key2=".";
        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';

            if (!head->next[index]){
                head->next[index] = getNode();
                }
            head = head->next[index];
            head->key2=key[i];
        }

        head->value=val;
        head->isEnd = true;
    }

    bool isEmpty(Node* root)
    {
        for (int i = 0; i < R; i++)
            if (root->next[i])
                return false;
        return true;
    }
    string search(string key)
    {
        Node *pNode = this->root;
        int check=0;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'a';
            if(i==0 && !pNode->next[index]){
                string result="no record";
                return '"'+result+'"'+"\n";

            }
            if (pNode->next[index]) {
                check++;
            }
            if(pNode->next[index]){
                pNode = pNode->next[index];
            }
        }

        if(check<key.size()){
            string result="incorrect Dothraki word";
            return '"'+result+'"'+"\n";
        }

        if(check==key.size() && pNode->value==""){
            if(pNode->value==""){
                string result="not enough Dothraki word";
                return '"'+result+'"'+"\n";
            }
        }

        string result="The English equivalent is ";
        result+=pNode->value;
        return '"'+result+'"'+"\n";
    }
    Node *deleteNode(Node* root, string key, int depth = 0){

        if (!root)
            return NULL;

        if (depth == key.size()) {

            if (root->isEnd)
                root->isEnd = false;

            if (isEmpty(root)) {
                delete(root);
                root = NULL;
            }
            return root;
        }

        int index = key[depth] - 'a';
        root->next[index] =deleteNode(root->next[index], key, depth + 1);

        if (isEmpty(root) && root->isEnd == false) {
            delete (root);
            root = NULL;
        }

        return root;
    }
    int childNumber(Node* root){
        Node *pNode = root;
        int number=0;
        for (int i = 0; i < R; i++){
            if(pNode->next[i]){
                number++;
            }
        }
        return number;
    }
    void list(Node* root, char str[], int depth,ofstream *output)
    {
        if (childNumber(root)==0)
        {
            str[depth] = '\0';
            *output<<"-"<<str<<"("<<root->value<<")"<< endl;
        }

        for (int i = 0; i < R; i++)
        {
            if (root->next[i])
            {
                str[depth] = i + 'a';
                list(root->next[i], str, depth + 1,output);
            }
        }
    }

};





