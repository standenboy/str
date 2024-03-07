#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
	char *bytes;
	int length;
} str;

typedef struct {
	str *strings;
	int count;
} strs;

str *initStr(char *STR, int length){ // creates a new string, if the length is -1 it is calculated from the STR input, otherwise an empty string is created with size length
	if (length == -1){
		char *tmpString = malloc(strlen(STR));
		strcpy(tmpString, STR); // force the str value onto the heap

		str *STRING = malloc(sizeof(str));
		STRING->length = strlen(STR);
		STRING->bytes = (char*)malloc(STRING->length+1); 
		STRING->bytes = tmpString;
		return STRING;
	}else{
		str *STRING = malloc(sizeof(str));
		STRING->length = length; 
		STRING->bytes = (char*)calloc(0, STRING->length+1);
		return STRING;
	}
}

strs *initArrayStr(int length, int count){ // creates an array that is count large of str's each one being size length 
	strs *STRING = malloc(sizeof(strs));
	STRING->strings = malloc(sizeof(str)*count);
	for (int i = 0; i < count; i++){
		STRING->strings[i].length = length; 
		STRING->strings[i].bytes = (char*)calloc(0, length+1);
	}
	STRING->count = count;
	return STRING;
}

void strconcat(str *string1, str *string2){ // concats two strings together storing the output in string1
	int newSize = string1->length + string2->length;
	char *tmpString = malloc(newSize);
	
	strcat(tmpString, string1->bytes);
	strcat(tmpString, string2->bytes);

	str *output = initStr(tmpString, -1);
	
	string1->bytes = output->bytes;
	string1->length= output->length; 
}

void strappend(str *string1, str *string2){ // appends a string to the start of another string, same as strconcat but backwards
	strconcat(string2, string1);
}

void strstrip(str *string, char toStrip){ // removes all instances of the char toStrip
	int occurrences = 0;
	for (int i = 0; i < string->length; i++){
		if (string->bytes[i] == toStrip){
			occurrences++;
		}
	}

	char *tmpString = malloc(string->length - occurrences);
	int charCounter = 0;
	for (int i = 0; i < string->length; i++){
		if (string->bytes[i] != toStrip){
			tmpString[charCounter] = string->bytes[i];	
			charCounter++;
		}
	}

	string->bytes = tmpString;
	string->length = string->length - occurrences;
}

strs *strsplit(str *string, char delim){ // takes a string, splits it into an array of stings, divided by the deliminer, deliminer is removed
	// 123..456...789
	// split at . should return [123, 456, 789]
	// number of elements = number of delims + 1
	// unless the delim is next to itself, in which case a block of delims should be counted as 1
	int delimCount = 0;	
	char prev; 
	for (int i = 0; i < string->length; i++){
		if (string->bytes[i] == delim){
			if (string->bytes[i] != prev){
				delimCount++;
			}
		}
	}

	delimCount++;
	strs *output = initArrayStr(string->length, delimCount);	

	int charCounter = 0;
	int currentStr = 0;
	for (int i = 0; i < string->length; i++){
		if (string->bytes[i] == delim){
			if (i != 0 && string->bytes[i] != string->bytes[i-1]){
				currentStr++;
				charCounter = 0;
			}
		}else{
			output->strings[currentStr].bytes[charCounter] = string->bytes[i];
			charCounter++;
		}
	}

	return output;
}

void freeStr(str *string){ // frees the memory alocated to a string !!!MUST BE DONE!!!
	free(string->bytes);
	free(string);
}

void freeArrayStr(strs *strings){ // frees the memory alocated to a string !!!MUST BE DONE!!!
	free(strings->strings);
	free(strings);
}

int main(){
	
	str *myString = initStr("", 10);
	scanf("%s", myString->bytes);
	strconcat(myString, myString);
	printf("%s\n", myString->bytes);
	exit(0);

	strs *myStrings = strsplit(myString, 'l');

	for (int i = 0; i < myStrings->count; i++){
		printf("%s\n", myStrings->strings[i].bytes); 
	}
	
	freeStr(myString);
	freeArrayStr(myStrings);
}
