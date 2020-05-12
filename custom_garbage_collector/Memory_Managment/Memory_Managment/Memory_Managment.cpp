// Memory_Managment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>

int main()
{
    int i, n;
    char* buffer;

    printf("How long do you want the string? ");
    scanf_s("%d", &i);

    buffer = (char*)malloc(i + 1);
    if (buffer == NULL) exit(1);

    for (n = 0; n < i; n++)
        buffer[n] = rand() % 26 + 'a';
    buffer[i] = '\0';

    printf("Random string: %s\n", buffer);
    free(buffer);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
