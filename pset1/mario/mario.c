#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Initiate our variable height to prevent errors
    int height;

    // This block is responsable for acceptting only the valid *numbers* (> 1 and < 8)
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int horizontal_value = 1;
    int horizontal_blank_value = height - 1;

    // Each repeat of this block represents one line of our print
    for (int i = 0; i < height; i++)
    {
        // Left part of the tower
        // That first part is responsible to print the spaces (" "), needed to shape it correctly
        for (int z = 0; z < horizontal_blank_value; z++)
        {
            printf(" ");
        }
        // Then, simply print the necessary amount of hash's to make the left tower
        for (int y = 0; y < horizontal_value; y++)
        {
            printf("#");
        }


        // The 2 spaces between the towers
        printf("  ");


        // Right part of the tower
        for (int y = 0; y < horizontal_value; y++)
        {
            printf("#");
        }

        // Next line and updating our control variables
        printf("\n");
        horizontal_blank_value--;
        horizontal_value++;
    }
}
