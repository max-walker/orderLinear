#include <iostream>
#include<stdlib.h>
#include "shuzudeshunx.h"
using namespace std;


int main()
{
    cout << "应用开始\n";
    int ennn[] = { 46,50,23,89,90,100,20 };
    shuzu<int>* shu = new shuzu<int>(ennn,7);
    shu->Show();
    system("pause");
    return 0;
}