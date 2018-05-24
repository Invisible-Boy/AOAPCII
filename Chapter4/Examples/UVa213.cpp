#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
using namespace std;
#define Nmax 256
int main()
{
    freopen("input.txt", "r", stdin);
    char code[Nmax] = {'\0'}, temp;
    int i = 1, j = 0;
    while((temp = getchar()) != EOF)
    {
        if(temp != '\n')
        {
            int location = (int)floor(pow(2, i) + 0.5) - i - 1 + j;
            code[location] = temp;
            j++;
            if(j == (int)floor(pow(2, i) + 0.5) - 1)
            {
                j = 0;
                i++;
            }
        }
        else
        {
            while(1)
            {
                int weishu = 0, k = 0;
                while(k < 3 && (temp = getchar()) != EOF)
                {
                    if(!isdigit(temp))
                        continue;
                    k++;
                    weishu = weishu * 2 + temp - '0';
                }
                if(weishu == 0)
                {
                    printf("\n");
                    i = 1;
                    j = 0;
                    getchar();
                    break;
                }
                else
                {
                    while(1)
                    {
                        k = 0;
                        int location = 0;
                        while(k < weishu && (temp = getchar()) != EOF)
                        {
                            if(!isdigit(temp))
                                continue;
                            k++;
                            location = location * 2 + temp - '0';
                        }
                        if(location == (int)floor(pow(2, weishu) + 0.5) - 1)
                            break;
                        else
                            printf("%c", code[location + (int)floor(pow(2, weishu) + 0.5) -weishu - 1]);
                    }
                }
            }
        }
    }
    return 0;
}
