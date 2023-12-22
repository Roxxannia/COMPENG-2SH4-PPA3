#include <stdio.h>
#include <stdlib.h>

#include "myStringLib.h"

// [COPY AND PASTE] Copy and Paste your Lab 3 Q1 Solution Below

//  This is then your very first reusable custom C library 


int my_strlen(const char * const str1)
{
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character
	int size = 0; 
	int j;
	// char *i = str1; 
	// for (size = 0; *(i) != '\0'; i++)
	// {
	// 	size++;
	// }
	for (j = 0; *(str1+j) != '\0'; j++)
	{
		size++;
	}
	return size;
	
}

int my_strcmp(const char * const str1, const char * const str2)
{
	// Return 0 if the two strings are not identical.  Return 1 otherwise.
	
	// Criteria 1: Check their lenghts.  If not the same length, not equal

	// Criteria 2: Check their contents char-by-char.  If mismatch found, not equal

	// if passing the two criteria, strings equal

	int flg;
	int i;
	int size1 = my_strlen(str1);
	int size2 = my_strlen(str2);

	if (size1 == size2 && size1>0)
	{
		for(i = 0; i<size1;i++)
		{
			if (*(str1 + i) == *(str2 + i))
			{
				flg = 1;
			}
			else
			{
				flg = 0; 
				break;
			}
		}
	}
	else if (size1 == size2 && size1 == 0)
	{
		flg = 1;
	}
	else 
	{
		flg = 0;
	}
	return flg;

}


int my_strcmpOrder(const char * const str1, const char * const str2)
{
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/

	// if two strings are completely identical in order, return -1.

	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII character
	int flg;
	int i;
	int size1 = my_strlen(str1);
	// printf("%d\n", size1);
	int size2 = my_strlen(str2);
	// printf("%d\n", size2);

	if (size1 == size2)
	{
		for(i = 0; i<size1;i++)
		{
			if (*(str1 + i) == *(str2 + i))
			{
				flg = -1;
			}
			else if (*(str1 + i) > *(str2 + i))
			{
				flg = 1; 
				break;
			}
			else if (*(str1 + i) < *(str2 + i))
			{
				flg = 0; 
				break;
			}

		}
	}
	else if (size1 < size2)
	{
		for(i = 0; i<size1;i++)
		{
			if (*(str1 + i) > *(str2 + i))
			{
				flg = 1; 
				break;
			}
			else if (*(str1 + i) < *(str2 + i))
			{
				flg = 0; 
				break;
			}
			else if (*(str1 + i) == *(str2 + i))
			{
				flg = -1;
			}

		}
		if (flg == -1)
		{
			flg = 0;
		}
	}
	else if (size1 > size2)
	{
		for(i = 0; i<size2;i++)
		{
			if (*(str1 + i) > *(str2 + i))
			{
				flg = 1; 
				break;
			}
			else if (*(str1 + i) < *(str2 + i))
			{
				flg = 0; 
				break;
			}
			else if (*(str1 + i) == *(str2 + i))
			{
				flg = -1;
			}

		}
		if (flg == -1)
		{
			flg = 1;
		}
	}



	return flg;
	
}


char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;

	int size1 = my_strlen(str1);
	int size2 = my_strlen(str2);
	int n = size1 + size2+1;
	z = (char*)malloc(n*sizeof(char));

	int i, j;
	
	for ( i = 0; *(str1+i); i++)
	{
		// printf("%c", *(str1+i));
		z[i] = *(str1+i);
	}

	for (j = 0; *(str2+j); j++)
	{
		// printf("%c", *(str2+j));
		// printf("%c", *(str1+i));
		z[size1+j] = *(str2+j);
	}

	z[size1+size2] = '\0';
	return z;
	

	// IMPORTANT!!  Where did the newly allocated memory being released?
	// THINK ABOUT MEMORY MANAGEMENT
	
}	