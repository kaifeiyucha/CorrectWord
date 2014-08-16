#include "index.h"
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace std;

#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

/*Index::Index(const string &filename){
    open_file(filename);
}*/

void Index::open_file(const string &filename){
    ifstream infile;
    infile.open(filename.c_str());
    if(!infile)
        ERR_EXIT("open file b.txt fail");
    
    store_file(infile);
    build_map();
    build_index();

    infile.close();
}
/*
void Index::printall() const {
    for(auto &item: words_text_){
        cout << item << endl;    
    }
    for(auto &item: word_map_){
        cout << item.first << " ";
            for(auto &item2: item.second){
                   cout << item2 << " ";
            }
        cout << endl;
    }
}*/


void Index::store_file(ifstream &infile){
   string line;
   string word;
   while(getline(infile, line)){
       char buf[100];
       sscanf(line.c_str(), "%s",buf);
       word = buf;
       words_text_.push_back(word);
   }
}


void Index::build_index(){
    for(line_no num = 0; num < words_text_.size(); num++){
         string temp = words_text_[num];
         for(size_t i = 0; i < temp.size(); i++){
            word_map_[ temp[i] ].insert(temp);
      }
    }
}

 void Index::build_map(){
    for(int i = 0; i < 26;i++){
        word_map_[i+97] = set<string>();
    }
}

set<string> Index::run_index(const string &query_word){
      map<char, set<string> >::iterator MapIter;
      string::const_iterator StringIter;
      set<string> Union;
      for(StringIter = query_word.begin(); StringIter!=query_word.end(); StringIter++ ){
      MapIter = word_map_.find(*StringIter);
      vector<string>  temp;
      set_union(MapIter->second.begin(), MapIter->second.end(), Union.begin(), Union.end(), back_inserter(temp));
     
      Union = set<string>(temp.begin(), temp.end());
      }
      return Union;
  
}
 /*可以写成交集，但是没有成功！！！！
  * map<char, set<string> >::iterator MapIter;
      set<string> Intersection;
      set<string>::iterator IntersecIter;
      IntersecIter = word_map_.find(query_word[0]);
     
      for(int i = 1; i<query_word.size(); i++){
        
          MapIter = word_map_.find(query_word[i]);
          vector<string>  temp;
          set_intersection(MapIter->second.begin(), MapIter->second.end(), IntersecIter->second.begin(), IntersecIter->second.end(), back_inserter(temp));

          Intersection = set<string>(temp.begin(), temp.end());
      }

      return Intersection;
*/


