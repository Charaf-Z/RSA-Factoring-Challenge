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
	mpz_t number, p, q;
	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("File not found!\n");
		return (1);
	}

	mpz_inits(number, p, q, NULL);
	while ((read = getline(&line, &len, file)) != -1)
	{
		mpz_set_str(number, line, 10);
		mpz_set_ui(p, 2);
		mpz_set(q, number);
		while (mpz_cmp(p, q) < 0)
		{
			if (mpz_divisible_p(q, p) != 0)
			{
				mpz_cdiv_q(q, q, p);
				gmp_printf("%Zd=%Zd*%Zd\n", number, q, p);
				break;
			}
			mpz_add_ui(p, p, 1);
		}
	}
	if (line != NULL)
		free(line);
	mpz_clears(number, p, q, NULL);
	fclose(file);
	return (0);
}
