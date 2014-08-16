#include "query.h"
#include "QueryServer.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    QueryServer server(InetAddress(8989), "b.txt");
    server.start();
    return 0;
}
