#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number = get_int("Por favor insira um número\n");
    printf("Seu número vezes 25 é igual a %i \n", number * 25);
}