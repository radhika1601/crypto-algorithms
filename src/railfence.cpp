#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/railfence.h"

typedef struct row_details
{

	int current_idx;
	char *row;
	int size;

	row_details(int given_size)
	{
		size = given_size;
		row = new char[size];
		current_idx = 0;
	}

} row_details;

std::string *railfence_cipher::encrypt(std::string plaintext)
{

	std::string *encrypted_str = new std::string();

	row_details **rows_array = new row_details *[key];

	for (size_t i = 0; i < key; ++i)
	{

		rows_array[i] = new row_details(plaintext.length());
	}

	// Store the plaintext characters in a zig-zag fashion in a 2D array.
	// The row_details struct makes the algorithm O(plaintextLength)
	uint8_t up = 0;
	int current_row = 0;
	for (size_t i = 0; i < plaintext.length(); ++i)
	{

		char c = plaintext[i];

		row_details *r = rows_array[current_row];

		r->row[r->current_idx] = c;

		r->current_idx++;

		(up == 0) ? (++current_row) : (--current_row);

		if ((current_row) % key == 0 || (current_row + 1) % key == 0)
		{

			up ^= 1;
		}
	}

	// Append all the row_detail structs that we have
	for (size_t i = 0; i < this->key; ++i)
	{

		row_details *r = rows_array[i];
		encrypted_str->append(r->row);

		delete r;
	}

	return encrypted_str;
}

std::string *railfence_cipher::decrypt(std::string *enc_str)
{

	std::string *decrypted_str = new std::string();

	size_t string_len = enc_str->length();

	char railfence[this->key][string_len];

	for (size_t i = 0; i < this->key; ++i)
	{

		memset(railfence[i], 0x0, string_len);
	}

	uint8_t up = 0;
	int current_row = 0;
	int current_column = 0;

	// For every column, there is only one row which is filled.
	for (size_t i = 0; i < string_len; ++i)
	{

		railfence[current_row][current_column] = '\xff';

		(up == 0) ? (++current_row) : (--current_row);

		if ((current_row) % key == 0 || (current_row + 1) % key == 0)
		{
			up ^= 1;
		}

		current_column++;
	}

	size_t idx = 0;

	for (size_t i = 0; i < this->key; ++i)
	{

		for (size_t j = 0; j < string_len; ++j)
		{
			if (railfence[i][j] == '\xff')
			{
				railfence[i][j] = (*enc_str)[idx];
				idx++;
			}
		}
	}

	up = 0;
	current_row = 0;
	current_column = 0;

	for (size_t i = 0; i < string_len; ++i)
	{

		decrypted_str->append(1, railfence[current_row][current_column]);

		(up == 0) ? (++current_row) : (--current_row);

		if ((current_row) % key == 0 || (current_row + 1) % key == 0)
		{
			up ^= 1;
		}

		current_column++;
	}

	return decrypted_str;
}
