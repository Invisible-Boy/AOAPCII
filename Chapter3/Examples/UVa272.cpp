#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    char c;
    int flag = 1;
    while((c = getchar()) != EOF)
    {
        if(c == '"')
        {
            printf("%s", flag ? "``" : "''");
            flag = !flag;
        }
        else
            printf("%c", c);
    }
    return 0;
}
