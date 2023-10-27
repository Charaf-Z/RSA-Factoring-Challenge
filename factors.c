#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/**
 * main - Entry point.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	long number = 0, p = 0, q = 0;
	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("File not found!\n");
		return (1);
	}
	while ((read = getline(&line, &len, file)) != -1)
	{
		number = atoll(line);
		p = 2;
		q = number;
		while (p < q)
		{
			if (q % p == 0)
			{
				q /= p;
				printf("%ld=%ld*%ld\n", number, q, p);
				break;
			}
			++p;
		}
	}
	if (line != NULL)
		free(line);
	fclose(file);
	return (0);
}
