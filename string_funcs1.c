#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: Pointer to characters of a string.
 *
 * Return: The length of the character string.
*/
int _strlen(const char *s)
{
	int length;

	length = 0;

	if (s == NULL)
	{
		return (length);
	}
	while (*(s + length) != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *		terminating null byte, to the buffer pointed to by des.
 * @dest: Pointer to destination string
 * @src: Pointer to the src of the string
 *
 * Return: Pointer to dest.
*/
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strcat - Concantenates two strings.
* @dest: Pointer to destination string.
* @src: Pointer to source string.
*
* Return: Pointer to destination string.
*/
char *_strcat(char *dest, const char *src)
{
	int i;

	int dest_length = 0;
	int src_length = 0;

	while (dest[dest_length] != '\0')
	{
		dest_length++;
	}

	while (src[src_length] != '\0')
	{
		src_length++;
	}

	for (i = 0; i < src_length; i++)
	{
		dest[dest_length + i] = src[i];
	}
	return (dest);
}

/**
* _strncat - Concatenates two strings but this time using more bytes from n
* @dest: char argument
* @src: char argument
* @n: int argument
* Return: Return a pointer to the resulting string dest
*/
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int src_len = 0;
	int des_len = 0;

	while (dest[des_len] != '\0')
	{
		des_len++;
	}
	while (src[src_len] != '\0')
	{
		src_len++;
	}

	for (i = 0; i < n && src_len; i++)
	{
		dest[des_len + i] = src[i];
	}
	dest[des_len + i] = '\0';
	return (dest);
}
