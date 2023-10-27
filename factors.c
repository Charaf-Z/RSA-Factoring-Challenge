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
	mpz_t number, p, q, flag, __flag;
	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("File not found!\n");
		return (1);
	}
	mpz_inits(number, p, q, flag, __flag, NULL);
	while ((read = getline(&line, &len, file)) != -1)
	{
		mpz_set_str(number, line, 10);
		mpz_set(q, number);
		if (mpz_divisible_ui_p(q, 2) != 0)
		{
			mpz_cdiv_q_ui(q, q, 2);
			gmp_printf("%Zd=%Zd*%d\n", number, q, 2);
		}
		else
		{
			mpz_sqrt(flag, number);
			mpz_add_ui(flag, flag, 1);
			mpz_set(__flag, flag);
			for (mpz_set_ui(p, 3); mpz_cmp(p, flag) <= 0; mpz_add_ui(p, p, 2))
			{
				if (mpz_divisible_p(q, p) != 0)
				{
					mpz_cdiv_q(q, q, p);
					gmp_printf("%Zd=%Zd*%Zd\n", number, q, p);
					break;
				}
				mpz_add(__flag, flag, p);
				if (mpz_divisible_p(q, __flag) != 0)
				{
					mpz_cdiv_q(q, q, __flag);
					mpz_add(p, p, flag);
					gmp_printf("%Zd=%Zd*%Zd\n", number, q, p);
					break;
				}
				mpz_sub(__flag, flag, p);
				if (mpz_divisible_p(q, __flag) != 0)
				{
					mpz_cdiv_q(q, q, __flag);
					mpz_sub(p, flag, p);
					gmp_printf("%Zd=%Zd*%Zd\n", number, q, p);
					break;
				}
			}
		}
	}
	if (line != NULL)
		free(line);
	mpz_clears(number, p, q, flag, __flag, NULL);
	fclose(file);
	return (0);
}
