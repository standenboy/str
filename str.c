#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
	char *bytes;
	int length;
} str;

str *initStr(char *STR, int length){ // creates a new string, if the length is -1 it is calculated from the STR input, otherwise an empty string is created with size length
	if (length == -1){
		char *tmpString = malloc(strlen(STR));
		strcpy(tmpString, STR); // force the str value onto the heap

		str *STRING = malloc(sizeof(str));
		STRING->length = strlen(STR);
		STRING->bytes = (char*)malloc(STRING->length+1); 
		STRING->bytes = tmpString;
		return STRING;
	}
	else{
		str *STRING = malloc(sizeof(str));
		STRING->length = length; 
		STRING->bytes = (char*)calloc(0, STRING->length+1);
		return STRING;
	}

}

void strconcat(str *string1, str *string2){ // concats two strings together storing the output in string1
	int newSize = string1->length + string2->length;
	char *tmpString = malloc(newSize);
	
	strcat(tmpString, string1->bytes);
	strcat(tmpString, string2->bytes);

	str *output = initStr(tmpString, -1);
	
	string1->bytes = output->bytes;
	string1->length = output->length;

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

void freeStr(str *string){ // frees the memory alocated to a string !!!MUST BE DONE!!!
	free(string->bytes);
	free(string);
}

int main(){
	str *myString = initStr("hello", -1);
	str *myOtherString = initStr("There", -1);
	strconcat(myString, myOtherString);
	freeStr(myOtherString);
	strstrip(myString, 'h');
	printf("%s\n", myString->bytes);
	freeStr(myString);
}
