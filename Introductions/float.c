#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float price = get_float("What's the price of your product?\n");
    printf("You need to pay %.2f \n", price * 1.0625);
}