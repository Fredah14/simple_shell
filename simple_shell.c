#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - prints out the sum and product of numbers
 * @argc : counts number of arguments
 * @argv : array containing numbers
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	int i, sum = 0, product = 1;
	char operation;

	printf("Do you want to perform '+' or '*' operation ?\n");
	operation = getchar();

	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			sum += atoi(argv[i]);
			product *= atoi(argv[i]);
		}

		if (operation == '+')
		{
			printf("The sum is: %d\n", sum);
		}
		else
		{
			printf("The product is: %d\n", product);
		}
	}
	return (0);
}
