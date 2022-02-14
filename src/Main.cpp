#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include "Trie.cpp"
#include <map>

#define R 26
using namespace std;

vector<string> readFile(string fileName){   // Reading file function
    ifstream new_file;
    vector<string> str;
    new_file.open(fileName, ios::in);
    string line;
    if(!new_file) {
        cout<<"No such file";
    }
    else {
        while (getline(new_file, line)) {
            str.push_back(line);
        }
        new_file.close();
    }
    return str;
}

vector<string> split (string str, string delimiter) {  // Splitting the strings that in input file by delimeter
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> splitArray;

    while ((pos_end = str.find (delimiter, pos_start)) != string::npos) {
        token = str.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        splitArray.push_back (token);
    }
    splitArray.push_back (str.substr (pos_start));
    return splitArray;
}



int main(int argc, char *argv[]) {

    ofstream output;
    output.open(argv[2],ios::out);
    if(!output)
    {cout<<"File creation failed";
    }
    Trie trie;
    char charList[R];
    map<string,string> keys;
    map<string,string>::iterator i;
    vector<string> inputArray= readFile(argv[1]);
    for(string str:inputArray){
        if(str!="list"){
            string key;
            string val;
            string command=split(str,"(")[0];
            string word= split(str,"(")[1];
            word.pop_back();
            if(command=="insert"){
                key= split(word,",")[0];
                val= split(word,",")[1];
                i=keys.find(key);
                if(i==keys.end()){
                    trie.insert(key,val);
                    keys.insert(pair<string,string>(key,val));
                    output<<'"'<<key<<'"'<< " was added\n";
                }
                else{
                    if(keys.at(key)==val){
                        output<<'"'<<key<<'"'<< " already exist\n";
                    }
                    else if(keys.at(key)!=val){
                        keys.erase(key);
                        keys.insert(pair<string,string>(key,val));
                        output<<'"'<<key<<'"'<< " was updated\n";
                        trie.insert(key,val);
                    }
                }
            }
            if(command=="search"){
                output<<trie.search(word);
            }
            if(command=="delete"){
                if(split(trie.search(word)," ").size()==5){

                    if(keys.at(word)==""){
                        string s="not enough Dothraki word";
                        output<<'"'<<s<<'"'<<"\n";

                    }
                    else{
                        trie.deleteNode(trie.root,word);
                        keys.erase(word);
                        keys.insert(pair<string,string>(word,""));
                        output<<'"'<<word<<'"'<<" deletion is successful\n";
                    }

                }
                else{
                    output<<trie.search(word);
                }
            }

        }
        else if(str=="list"){

            trie.list(trie.root,charList,0,&output);
        }
    }

    output.close();
    return 0;
}
