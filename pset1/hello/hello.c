#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get the name of the person
    string name = get_string("Please write your name here:\n");

    //Print that name based on string variable assigned before
    printf("hello, %s\n", name);
}