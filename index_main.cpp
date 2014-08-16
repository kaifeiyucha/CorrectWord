#include "index.h"
#include <iostream>
#include <string>
#include <set>
#include <iterator>


using namespace std;

int main(int argc, const char *argv[])
{
    Index I("c.txt");
     I.printall();
    string  word;
    cin >> word; 
     set<string> set_index = I.run_index(word);
     set<string>::iterator it = set_index.begin();
     set<string>::iterator itend = set_index.end();
     cout << "main_iteartor" << endl;
     for(;it != itend; ++it)
     { cout << "end" << endl;
         cout << (*it) << endl;
         cout <<"endd" << endl;
     }
    return 0;
}
