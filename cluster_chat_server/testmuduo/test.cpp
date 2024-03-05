#include <iostream>
#include <map>
#include <string>
using namespace std;


int main()
{
    map<int,string> myMap{{1,"ab"},{3,"cd"},{2,"bc"}};

    cout << myMap[2] << endl;

    return 0;
}