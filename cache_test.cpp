#include "cache.h"
#include <iostream>

using namespace std;

int main(int argc, const char **argv)
{
    LRUCache s(2) ;
    s.set("gool", "google") ;
    s.set("bai", "baidu") ;
    cout << s.get("gool") << endl;
    s.set("qui", "quit") ;
    cout << s.get("qui") << endl;
   cout << s.get("bai") << endl;
    return 0 ;
}
