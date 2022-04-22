#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int letters[26], indexes[26];						 // global declaration for the frequency and indexes array

void main()
{
	FILE* pFile = fopen("Names.txt", "r");
	char buffer[128];
	char* names[50];					 // sizeof names will be 50 * 4 bytes
	char** agenda[26];
	int index = 0;

	// initiating names
	for (int i = 0; i < 50; i++) {
		names[i] = NULL;
	}

	// initiating agenda
	for (int i = 0; i < 26; i++) {
		agenda[i] = NULL;
	}

	memset(names, NULL, sizeof(char*) * 50);	// same thing as the for does

	if (pFile) {
		fscanf(pFile, "%s", buffer);

		// char** [] implementation -> first we go through the entire file to compute the freq. array
		while (!feof(pFile)) {
			/*names[index] = (char*)malloc(strlen(buffer) + 1);  // malloc will always return a pointer to void 
																 // - that will be casted automatically to whatever type we need
			strcpy(names[index++], buffer);
			//int pos = *names[index];   // this is pos = names[index][0]
			//index++;*/				 // redundant because we incremented at the previous line

			letters[buffer[0] - 'A']++;	 // we increase the frequency array when we find a name starting with a certain letter
			
			fscanf(pFile, "%s", buffer); // reading the next name
		}
		rewind(pFile);					 // rewind the file in order to read it a second time

		// we allocate space for the names according to the frequency array
		for (int i = 0; i < 26; i++) {
			if (letters[i] != 0) {
				agenda[i] = (char**)malloc(sizeof(char**) * letters[i]);
			}
		}
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			agenda[buffer[0] - 'A'][indexes[buffer[0] - 'A']] = (char*)malloc(strlen(buffer) + 1);
			strcpy(agenda[buffer[0] - 'A'][indexes[buffer[0] - 'A']], buffer);
			indexes[buffer[0] - 'A']++;

			fscanf(pFile, "%s", buffer);
		}
	}

	// sorting the agenda
	for (int i = 0; i < 26; i++) {
		if (letters[i] != 0) {
			for (int j = 0; j < letters[i] - 1; j++) {
				for (int k = j + 1; k < letters[i]; k++) {
					if (strcmp(agenda[i][j], agenda[i][k]) > 0) {
						char* aux;
						aux = (char*)malloc(strlen(agenda[i][j]) + 1);
						strcpy(aux, agenda[i][j]);

						free(agenda[i][j]);
						agenda[i][j] = (char*)malloc(strlen(agenda[i][k]) + 1);
						strcpy(agenda[i][j], agenda[i][k]);

						free(agenda[i][k]);
						agenda[i][k] = (char*)malloc(strlen(aux) + 1);
						strcpy(agenda[i][k], aux);
					}

				}
			}
		}
	}

	// printing the agenda
	for (int i = 0; i < 26; i++) {
		if (letters[i] != 0) {
			printf("   Names that start with %c:\n", (char)i + 'A');
			for (int j = 0; j < letters[i]; j++) {
				printf("%s; ", agenda[i][j]);
			}
			printf("\n");
		}
	}

	// int a = 2;	// for testing
}

//			----------------- EXPLANATIONS -----------------
/*	//for storing a char
	char* name;		// on runtime,so we don't have to specify the number of bytes //heap 
					// stores the address of the first elemnent 

	// on compile
	char name[20];	// stores the address of the first elemnent
	char name[] = "Ionescu"; 

	// for storing a vector of chars
	 char* name[7]; // static array of 7 pointers to char; don't forget to initialize them with null
 
	 char** name;	// dynamic pointer to an array of pointers to chars
					// the disadvantage of this is that we need to resize it every time we want to add an element

	 char name[7][20]; // static			!!Jagged array bcs the names have different lenghts
	 in [20] is the size of the longest element(name)

	char** agenda[26] // to do as homework
*/
