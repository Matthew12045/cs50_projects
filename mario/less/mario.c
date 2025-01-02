#include <cs50.h>
#include <stdio.h>

void print_row(int height, int space);

int main(void)
{
    // prompt the user for Height
    int height;
    int spaces;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);
    spaces = height - 1;

    // print the pyramid
    for (int i = 0; i < height; i++)
    {
        print_row(i + 1, spaces);
        spaces--;
    }
}

void print_row(int height, int space)
{
    for (int i = 0; i < space; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    printf("\n");
}
