#include<iostream>
#include<direct.h>
#include<fstream>
#include<unordered_map>
#include<vector>
using namespace std;
//convert string to lower case
void tolower(string &str){
    for(auto& ch:str){
        ch=tolower(ch);
    }
}

class SpellChecker{
public:
    unordered_map<string,string> wordDict;
    void checkFile(const string& filename){
        //open input file
        ifstream fin;
        fin.open(filename);
        if(fin.is_open()){
            string word;
            //extraction operator to read word by word until eof
            while(fin>>word){
                tolower(word);
                //for each word ,we have three possibilities
                //1. found in dictionary so assume correct
                //2. not found,but no suggestions
                //3. not found, but we find suggestion
                cout<<word;
                if(wordDict.find(word)!=wordDict.end()){
                    //case 1:found
                    cout<<": ok"<<endl;
                }else{
                    //look for alternative spellings of word
                    vector<string> altWordList=createWordList_SwapAdjChars(word);
                    if(altWordList.empty()){
                        //case 2: not found,no suggestion
                        cout<<": misspelled? no suggesstions"<<endl;

                    }else{
                        //case 3: not found,we have suggestions
                        cout<<": mispelled? suggestions-> ";
                        for(auto altWord : altWordList){
                            cout<< altWord <<",";
                        }
                        cout<<endl;
                    }
                }
            }
        }
        else{
            cout<<"Error Opening File: "<<filename<<endl;
        }
    }
    vector<string> createWordList_SwapAdjChars(const string& word){
        //result list of possible corrections
        vector<string>result;
        //try to find some alternative spellings for each pos in word up to 2nd last
        for(int i=0;i<word.size()-1;++i){
            //create copy of word
            string newWord= word;
            //swap adjacent letters at i and i+1
            swap(newWord[i],newWord[i+1]);
            //if new word is in dictionary, then add it to the list of possible corrections
            if(wordDict.find(newWord)!=wordDict.end()){
                result.push_back(newWord);
            }
        }
        return result;
    }
    void readDictionaryFile(const string& filename){
        //open input file
        ifstream fin;
        fin.open(filename,ios::in);
        if(fin.is_open()){
            string word;
            //extraction operator to read word by word until eof
            while(fin>>word){
                tolower(word);
                wordDict.emplace(word,word);
            }
        }
        else{
            cout<<"Error Opening File: "<<filename<<endl;
        }
    }
};

int main(){
    cout<<"Working Directory: "<< _getcwd(NULL,0)<<endl;
    SpellChecker spellChecker;
    string textFile= "textFile.txt";
    string dictFile="knuth_words.txt";
    spellChecker.readDictionaryFile(dictFile);
    spellChecker.checkFile(textFile);
    return 0;
}