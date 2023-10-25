#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gmp.h>

/**
 * is_prime - Check if a number is prime.
 * @num: The number to check for primality.
 *
 * Return: true if the number is prime, false otherwise.
 */
bool is_prime(mpz_t num)
{
	if (mpz_cmp_ui(num, 1) <= 0)
		return (false);

	mpz_t sqrt_num;
	mpz_t i;

	mpz_init(sqrt_num);
	mpz_sqrt(sqrt_num, num);
	for (; mpz_cmp(i, sqrt_num) <= 0; mpz_add_ui(i, i, 1))
	{
		if (mpz_divisible_p(num, i) != 0)
		{
			mpz_clear(sqrt_num);
			return (false);
		}
	}
	mpz_clear(sqrt_num);
	return (true);
}

/**
 * factorize_to_primes - Factorize a number into two prime numbers.
 * @number: The number to be factorized.
 * @p: A pointer to store the first prime factor.
 * @q: A pointer to store the second prime factor.
 *
 * Return: true if factorization is successful, false otherwise.
 */
bool factorize_to_primes(mpz_t number, mpz_t p, mpz_t q)
{
	mpz_t temp;
	mpz_t temp2;

	mpz_init(temp);
	mpz_init(temp2);

	mpz_set_ui(p, 0);
	mpz_set_ui(q, 0);

	for (mpz_init_set_ui(temp, 2);
			mpz_cmp(temp, number) <= 0;
			mpz_add_ui(temp, temp, 1))
	{
		if (is_prime(temp))
		{
			mpz_init_set(temp2, number);
			mpz_fdiv_qr(q, temp2, temp2, temp);
			if (mpz_cmp_ui(temp2, 0) == 0)
			{
				mpz_set(p, temp);
				if (is_prime(q))
				{
					mpz_clear(temp);
					mpz_clear(temp2);
					return (true);
				}
			}
			mpz_clear(temp2);
		}
	}

	mpz_clear(temp);
	return (false);
}

/**
 * main - Entry point for the prime factorization program.
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

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("File not found!\n");
		return (1);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	mpz_t number, p, q;

	mpz_inits(number, p, q, NULL);

	while ((read = getline(&line, &len, file)) != -1)
	{
		mpz_set_str(number, line, 10);
		if (factorize_to_primes(number, p, q))
			gmp_printf("%Zd=%Zd*%Zd\n", number, p, q);
	}

	if (line != NULL)
		free(line);

	mpz_clears(number, p, q, NULL);

	fclose(file);
	return (0);
}
