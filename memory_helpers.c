#include "shell.h"

/**
 * free_array - free an array of strings
 * @array: array to free
 */

void free_array(char **array)
{
	size_t i;

	for (i = 0; i<arr_size;i++)
	{
		array[i]='\0';
		free(array[i]);
	}

	free(array);

}
