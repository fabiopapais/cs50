#include <stdio.h>
#include <cs50.h>

void cough(int n);

int main(void)
{
    int answer = get_int("How many times do you wanna cough?\n");
    cough(answer);
}


void cough(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("cough!\n");
    }
}