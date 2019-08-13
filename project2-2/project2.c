/*******************************
*
* Assignment: Project 2
* This program contains methods which encrypt a message using a One Time Pad, Tiling, and Chaining
* Date: 02/17/17
* Authors: Aaron Riegel and Dillon Dotson
*
********************************/

#include <stdio.h>
#define DELIMITER 255 //define the DELIMITER as the ASCII value 255

// Prototypes for each function in the program
int messageInput(unsigned char message[]);
int keyInput(unsigned char key[]);
void output(unsigned char out[], int length);
void combine(unsigned char message[], unsigned char key[], int length);
unsigned char rotate(unsigned char character, int count);
int bits(unsigned char character);
void tiling(unsigned char key[], int length, int keyLength);
void chaining(unsigned char key[], int keyLength);


int main()
{
	
    unsigned char message[2048]; //unsigned char array to hold the message
    unsigned char key[2048];	//unsigned char array to hold the key
    int length = messageInput(message); //read in the message and determine the length
    int keyLength = keyInput(key); //read in the key and determine the length
	if (keyLength < length){ //if the key length is less than the length of the message, exectue tiling
		tiling(key, length, keyLength);
		keyLength = length;
	}
	chaining(key, length); //exectue chaining 
    combine(message, key, length); //XOR the files together
    output(message, length);
	
 	return 0;
}

int messageInput(unsigned char message[]) { //this method gets all of the characters from the message file and puts them in an array, returns the length
    int i;
    int c = 0;
	int count = 0;
	
    for(i = 0; (c = getchar()) != DELIMITER; ++i) //read in characters until the delimiter is reached
		if (i < 2048) { //only read in characters while i is less than 2048
			message[i] = c;
			count++;
		}
    return count; // return the length of the message
}

int keyInput(unsigned char key[]) { //read in characters until the End of File is reached
    int i;
    int c = 0;
	int count = 0;
	
    for(i = 0; (c = getchar()) != EOF; ++i)
		if (i < 2048) {	//only read in characters while i is less than 2048
			key[i] = c;
			count++;
		}
    return count; //return the length of the key
}

void output(unsigned char out[], int length){ //write the encrypted message to a file
   
    int i;
    for(i = 0; i < length; ++i) //loop through the text, outputting each character
        putchar(out[i]);
   
}

void combine(unsigned char message[], unsigned char key[], int length){    //This method XORs the message and key together
    int i;
    
    for(i = 0; i < length; ++i) {
    	message[i] = message[i] ^ key[i];
		
    }
   
}


unsigned char rotate(unsigned char character, int count){ //rotates its 7 least significant digits to the right by count steps
	int i;
	for (i = 0; i < count; i++) //count through the bits in a character
	{
		if (character%2==0){ //if the character is even, right shift by 1 bit position
			character=character >> 1;
		}
		else{ //right shift by 1 bit position and then OR with 64
			character = (character >> 1)|64;
		}
	}
	return character;
	
}
 
int bits(unsigned char character){ //counts the number of 1 bits in the binary representation of the value of character
	int count = 0;
	while (character){ //while the character is not equal to 0, mod the character by 2 and add it to count
		count += character % 2; 
		character >>= 1; //shift character by 1 bit position
	}
	return count; //return the count

}
void tiling(unsigned char key[], int length, int keyLength){ //if the key is shorter than the message, the key needs to be repeated to continue encrypting
	int i;
	for(i = keyLength; i < length; ++i) //go through the key and repeat it until it is the same length as the message
		key[i] = key[i-keyLength]; 
}


void chaining(unsigned char key[], int keyLength){ //take a key composed of a short repeating phrase and turn it into a full-length pseudorandom key 
    int i;
    int sum = key[keyLength-1] % keyLength; //initialize sum
	key[0] = rotate(key[0]^key[sum], bits(key[keyLength-1])); //initialize first index in key array
	sum += key[0]; //increase sum
    sum %= keyLength; //mod sum by keylength and set it equal to sum
    for(i = 1 ; i < keyLength; ++i) { //cycle through the key array and complete Vigenere Cipher
        key[i] = rotate(key[i]^key[sum], bits(key[i-1]));
        sum += key[i];
        sum %= keyLength;
    }
}