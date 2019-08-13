/*
*
*Assignment: Project 3
*Date: 3/3/2017
*Authors: Aaron Riegel and Isaac Axtmann
*
*/



#include "stddef.h"

#ifndef NEW_STRING_H
#define NEW_STRING_H


char* new_strcpy(char* destination, const char* source){ //Copies the characters from source into destination.

	int i;
	
	for(i = 0; source[i]; i++) //while the current location in source is not equal to the NULL character, set the location in destination equal to the location in source
		destination[i] = source[i];
		
	destination[i] = '\0'; //set the last character in the desination string equal to the NULL character
	
	return destination;
}

char* new_strncpy(char* destination, const char* source, size_t n){ //Copies the first n characters from source into destination. If the function hits a null character in source before it has copied n characters, the remaining characters are filled with null characters.
	
	int i;
	
	for(i = 0; i < n && source[i]; i++) //while i is less than n and the current location in source is not equal to the null character, copy the current location in destination equal to the location in source
		destination[i] = source[i];
		
	destination[i] = '\0'; //set the last location in destination equal to the NULL character
	
	for(; i < n ; i++) //fill the rest of the string to n with NULL characters
		destination[i] = '\0';
	
	return destination;
}

int new_strcmp(const char* string1, const char* string2){ //Compares two strings. The return value is positive if string1 comes after string2 alphabetically, negative if string1 comes before string2 alphabetically, and 0 if the two strings are equal.
	
	int i;
	
	for(i = 0; string1[i] == string2[i] && string1[i] && string2[i]; i++); //while the character at location in string1 and string2 are the same and the location in string1 and string2 are not the NULL character
	
	return string1[i] - string2[i]; //return the difference between the location in string1 and string2. If they are different, it will return the difference in the characters at location i.
	
	
}

int new_strncmp(const char* string1, const char* string2, size_t n){ //Compares two strings exactly like new_strcmp(), except comparing at most the first n characters.
	
	int i;
	
	for(i = 0; i < n && string1[i] == string2[i] && string1[i] && string2[i]; i++); //while the character at location in string1 and string2 are the same and the location in string1 and string2 are not the NULL character and i is not equal to n
	
	return string1[i] - string2[i]; //return the difference in the current location of string1 and string2. If they are differenct, it will return the difference in the characters at the location i.

}

char* new_strcat(char* destination, const char* source){ //Adds the string contained in source to the end of the string contained in destination. The values in destination are modified, but a pointer to destination is also returned.

	int i;
	int j;
	
	for(i = 0; destination[i]; i++); //find the end of destination
	
	for(j = 0; source[j]; j++, i++) 
		destination[i] = source[j]; //copy the location in source and add it to the end of destination
	
	destination[i] = '\0'; //set the last location in destination equal to the NULL character
	
	return destination;
	

}

char* new_strncat(char* destination, const char* source, size_t n){ //Adds the string contained in source to the end of the string contained in destination, but adding a maximum of n characters.
	
	int i;
	int j;
	
	for(i = 0; destination[i]; i++); //find the end of destination
	
	for(j = 0; source[j] && j < n; j++, i++) //while the location in source is not the NULL character and j is less than n
		destination[i] = source[j];	//set the location at destination equal to the current location in source
	
	destination[i] = '\0'; //set the last location in destination equal to the NULL character
	
	return destination;
	
}

size_t new_strlen(const char* string){ //Returns the number of characters in string before the null character.
	
	int i;
	
	for(i = 0; string[i]; i++); //find the length of the string by searching until finding the NULL character
	
	return i; 
	
}

char* new_strchr(const char* string, int character){ //Returns a pointer to the first occurrence of character (converted to a char) in string or a NULL pointer if character cannot be found.
	
	int i;
	
	for(i = 0; string[i] && string[i] != (char)character; i++); //while the location in string is not the NULL character and is also no the character currently being searched for, loop through string
	
	if(!string[i]) //if the character was not found, return NULL pointer
		return NULL;
		
	return (char*)&string[i]; //return the pointer to the character
					
}

char* new_strstr(const char* haystack, const char* needle){ //Returns a pointer to the first occurrence of the string contained in needle in haystack or a NULL pointer if needle cannot be found.
	
	int i;
	int j;
	int temp;
	if(!haystack[0]) //if there is nothing in the string, return a pointer to the first location (same behavior as string.h)
		return &haystack[0];
	
	for(i = 0; haystack[i]; i++){ //search through the haystack while the location is not the NULL character
		temp = i;
		for(j = 0; haystack[temp] == needle[j] && haystack[temp] && needle[j]; j++, temp++); //while the temporary variable is equal to the location in needle and the locations in haystack and needle are not equal to the NULL character, increment j and temp
		
		if(!needle[j]) //if the location in needle is NULL, return a pointer to the location in Haystack where needle is
			return (char*)&haystack[i];
	}
	
	return NULL; //return NULL pointer if needle cannot be found
		
}


#endif
