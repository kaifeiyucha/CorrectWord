#include "query.h"
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "index.h"
#include "lexicon.h"
#include "cache.h"

using namespace std;

#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

Query::Query(const string &file)
    :cache_(1024),
     index_(file){

//     wordusr_ = word;//这个可以去掉
    open_lexicon(file);//打开词库
}


void Query::open_lexicon(const string &filename){//打开词库
    ifstream infile;
    infile.open(filename.c_str());
    if(!infile)
        ERR_EXIT("open file fail");
    read_from_lexicon(infile);//从词库中读取数据
    infile.close();
}

string Query::find_to_cache(const string &word){//在cache中寻找
   
    string word_right = cache_.get(word);//从cache中读取
    string str;

   if(!word_right.empty()){//不为空，代表cache中有这个单词
        str = word_right + string("\r\n");
        cout << "find in cache" << endl;
        return str;
   }else{
        cout << "cache isn't exit the word" << endl;
        return string();//返回空对象
   }
}



string Query::find_to_index(const string &word){//在index中寻找
    set<string>  tempset = index_.run_index(word);//返回查询词的所有候选索引
    set<string>::const_iterator loc = tempset.find(word);
    if(loc != tempset.end()){//在索引中找到了
        cache_.set(word, *loc);//放在cache中

        string final = word+"\r\n";

        cout << "find in index" << endl;
        return final;
    }else{
        return string();
    }
}

string Query::final_word(const string &word){//根据最小编辑距离 词频 纠错
    
    priority_queue<pqueue> que;
    string str;
    map<string, int>::const_iterator it = words_.begin();
    for( ; it != words_.end(); ++it){
        int mini = mini_distance(word, it->first, word.size()-1, (it->first).size()-1);
        if(mini < 3){
               add_priority(it->first,mini, it->second , que);
        }else{
            continue;
        }

    }
   str =  printf_result(que);

   cache_.get(str);
   return str;
    
}


string Query::run_query(const string &word){//入口程序，查询
    
    string word_right = find_to_cache(word);//先从cache中查询
    if(!word_right.empty())
        return word_right;
 
    word_right = find_to_index(word);
    if(!word_right.empty())//此时，词库中有这个词，直接输出
        return word_right;

    else
        return final_word(word);//最后根据最小编辑距离和词频，寻找恰当的词
    
    
}

void Query::read_from_lexicon(ifstream &infile){//从词库中读取数据
            
    string line;
    while(getline(infile, line)){
         char buf[100];
         int frequence;
         sscanf(line.c_str() ,"%s %d", buf, &frequence);
         words_[string(buf)] = frequence;
    }
}



void Query::add_priority(const string &word_old, int mini, int frequence,priority_queue<pqueue>  &que){
        
    pqueue q;

    q.word_ = word_old;
    q.mini_distance_ = mini;
    q.frequency_ = frequence;

    que.push(q);
}


int Query::mini_distance(const string &word1, const string &word2, int i, int j){
    if(i == -1 && j == -1)      // apple  apple
        return 0;
    else if(i == -1)//   null apple
        return j+1;
    else if(j == -1)//    apple null
        return i+1;

      
 if(word1[i-1] == word2[j-1]){
        return mini_distance(word1, word2, i-1, j-1);
    }else{
        int t1 = mini_distance(word1, word2, i, j-1)+1;//add
        int t2 = mini_distance(word1, word2, i-1, j)+1;//delete
        int t3 = mini_distance(word1, word2, i-1, j-1)+1;//update
        return MinInt(t1, t2, t3);    
    }


}

int Query::MinInt(int t1, int t2, int t3){
    
    int min_int;
    min_int = t1>t2 ? t2 : t1;
    min_int = t3>min_int ? min_int : t3;
    return min_int;

}



string Query::printf_result(priority_queue<pqueue>  que){
  
    string str;
    str = que.top().word_;
    return str;
}
