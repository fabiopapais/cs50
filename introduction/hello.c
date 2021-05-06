#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("teste\n");
    printf("hello, %s\n", answer);
}