#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/**
 * is_prime - Check if a number is prime.
 * @num: The number to check for primality.
 *
 * Return: true if the number is prime, false otherwise.
 */
_Bool is_prime(mpz_t num)
{
	mpz_t i, mul_i;

	mpz_inits(i, mul_i, NULL);
	mpz_set_ui(i, 3);
	mpz_set(mul_i, i);
	mpz_mul(mul_i, mul_i, mul_i);
	if (mpz_divisible_ui_p(num, 2) != 0)
	{
		mpz_clears(i, mul_i, NULL);
		return (0);
	}
	while (mpz_cmp(mul_i, num) <= 0)
	{
		if (mpz_divisible_p(num, i) != 0)
		{
			mpz_clears(i, mul_i, NULL);
			return (0);
		}
		mpz_add_ui(i, i, 2);
		mpz_mul(mul_i, mul_i, mul_i);
	}
	mpz_clears(i, mul_i, NULL);
	return (1);
}

/**
 * factorize_to_primes - Factorize a number into two prime numbers.
 * @number: The number to be factorized.
 * @p: A pointer to store the first prime factor.
 * @q: A pointer to store the second prime factor.
 *
 * Return: true if factorization is successful, false otherwise.
 */
_Bool factorize_to_primes(mpz_t number, mpz_t p, mpz_t q)
{
	mpz_t idx, sqrt_number;
	mpz_inits(idx, sqrt_number, NULL);

	if (mpz_cmp_ui(number, 2) < 0)
	{
		mpz_set_ui(p, 1);
		mpz_set_ui(q, 1);
		mpz_clears(idx, sqrt_number, NULL);
		return 0;
	}

	mpz_sqrt(sqrt_number, number);

	if (mpz_divisible_ui_p(number, 2) != 0)
	{
		mpz_cdiv_q_ui(q, number, 2);
		mpz_set_ui(p, 2);
		if (mpz_probab_prime_p(q, 25) && mpz_probab_prime_p(p, 25))
		{
			mpz_clears(idx, sqrt_number, NULL);
			return 1;
		}
	} else {
		mpz_set_ui(idx, 3);
		while (mpz_cmp(idx, sqrt_number) <= 0)
		{
			if (mpz_divisible_p(number, idx) != 0)
			{
				mpz_cdiv_q(q, number, idx);
				mpz_set(p, idx);
				if (mpz_probab_prime_p(q, 25) && mpz_probab_prime_p(p, 25))
				{
					mpz_clears(idx, sqrt_number, NULL);
					return (1);
				}
			}
			mpz_add_ui(idx, idx, 2);
		}
	}

	mpz_clears(idx, sqrt_number, NULL);
	return (0);
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
			gmp_printf("%Zd=%Zd*%Zd\n", number, q, p);
	}

	if (line != NULL)
		free(line);

	mpz_clears(number, p, q, NULL);

	fclose(file);
	return (0);
}
