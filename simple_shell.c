#include "shell.h"

/**
 * main - prints out the sum and product of numbers
 * @argc: counts number of arguments
 * @argv: array containing numbers
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	int j, sum = 0, product = 1;
	char operation;

	printf("Do you want to perform '+' or '*' operation ?\n");
	operation = getchar();

	if (argc > 1)
	{
		for (j = 1; j < argc; j++)
		{
			sum += atoi(argv[j]);
			product *= atoi(argv[j]);
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
