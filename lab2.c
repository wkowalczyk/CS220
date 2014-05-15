
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  WORD_LENGTH  30
#define  INITIAL_ARRAY_MAX 50

int loadDictionary(char *inFileName, char ***array, int *count, int *capacity);
int menu(int *wordCount, char ***array);
void doubleArray(char **array, int *capacity);
int insertWord(char **array, int *count, char word[]);
void printArray(char **array, int count);
int removeWord(char **array, int *count, char word[]);
int searchWord(char **array, int *count, char word[]);
//int saveDictionary(char *outFileName, char **array);

int main(int argc, char* argv[]){
	
	char **dictionaryArray;

    int capacity = INITIAL_ARRAY_MAX;
    int wordCount = 0;

    if (argc != 3)
    {
        fprintf(stderr,"Usage: %s inputfile outputfile\n", argv[0]);
        return 1;
    }
  
	if (loadDictionary(argv[1], &dictionaryArray, &wordCount, &capacity) != 0)
    {
        fprintf(stderr,"    loadArray failed! Program terminating...\n");
        return 1;  /* don't need to call exit - we're in main! */
    }

    printf("\n  Finished loading %d words.\n", wordCount);

   printf("\n");
   int i;
   for (i = 0; i < wordCount; i++)
       printf("array[%d]: %s\n", i, dictionaryArray[i]);

	menu(&wordCount, &dictionaryArray);

	/* comment this out if using a big file!*/
    printArray(dictionaryArray, wordCount);

    return 0;

}


/*The array passed into the loadDictionary() function will open the input file, 
 *read in all the strings, and then close the input file.
 *Must als update the word count. As it reads in words from the file, it keeps
 *the dictionay in sorted(lexical) order at al times.*/
int loadDictionary(char *inFileName, char ***wordArray, int *count, int *capacity){
	
	FILE *inFile;
	char word[WORD_LENGTH]; //initializes an array for each word

	if ((inFile = fopen(inFileName, "r")) == NULL)
    {
	fprintf(stderr,"Error opening input file, %s\n", inFileName);
	return -1;
    }

    *wordArray = (char **)malloc(*capacity * sizeof(char*));
    if (*wordArray == NULL)
    {
	fprintf(stderr, "Malloc of array in loadArray failed!\n");
	return -1;
    }

	printf("Reading file %s (each . is 1000 words read)\n", inFileName);

    *count = 0;
    while (fscanf(inFile, "%s", word) == 1)
    {
	
		if (*count >= *capacity)
		{
		/* call a function that will double the size of the array and copy its contents */
			doubleArray(*wordArray, capacity);
		}

		if (insertWord(*wordArray, count, word) != 0)
		{
	    	fprintf(stderr,"    Insert returned an error!\n");
	    	fclose(inFile);
	    	return 1;
		}

		if (*count % 1000 == 0)
		{
		    printf(".");
		    fflush(stdout);  /* stdout is buffered, so have to force flush */
		}
	}

    fclose(inFile);

	return 0;
}

/*Makes a new array that is double the size of the older array,
 *and copies the older array to the new array.
 *It then frees the older array and points the array to the same address of temp.*/
void doubleArray(char **array, int *capacity){

	int newCapacity = (*capacity) * 2;

	char **temp;
	
	temp = (char **)malloc(newCapacity * sizeof(char*));

	int i;
	for(i = 0; i < (*capacity); i++){
		(*temp)[i] = (*array)[i];
	}

	*capacity = newCapacity;

	free(*array);

	array = temp;

}


/*This function offers the user a list of operations to interact
 *with the dictionary. The menu offers the user 5 options:
 * 'S'earch, 'I'nsert, 'R'emove, 'C'ount, and 'Q'uit*/
int menu(int *count, char*** array){

	char userInput;
	
	char newWord[WORD_LENGTH];
	
	printf("Choose: 'S'earch, 'I'nsert, 'R'emove, 'C'ount, 'Q'uit: ");
	scanf("%c", &userInput);
	
	/*Sees what the user input and calls that function*/
	/*search word: prints whether or not the word was found*/
	if(userInput == 'S' || userInput == 's'){
		//prompts for a word and passes it to the search function
		printf("Enter a word to search for: ");
		scanf("%s", &newWord);
		if(searchWord(*array, count, newWord) == 1){
			printf("Word has been found");
		}else{
			printf("Word has not been found");
		}
	}
	/*insert word: inserts word into the array*/
	else if(userInput == 'I' || userInput == 'i'){
		printf("Enter a word to insert into the dictionary: ");
		scanf("%s", &newWord);
		insertWord(*array, count, newWord);
	}
	/*remove word*/
	else if(userInput == 'R' || userInput == 'r'){
		printf("Enter a word to remove from the dictionary: ");
		scanf("%s", &newWord);
		removeWord(*array, count, newWord);
	}
	/*print the count*/
	else if(userInput == 'C' || userInput == 'c'){
		printf("The word count is: %d", *count);
	}
	/*quit program*/
	else if(userInput == 'Q' || userInput == 'q'){
		printf("Program is ending and the dictionary will be sent to the output file specified on the command line");
		/*call saveDictionary(); to save the contents of the dictionary to the output file
		 *saveDictionary(&outFileName, *array);*/
	}else{
		fprintf(stderr, "Invalid user input");
	}

}

/*mallocs space for the word and if the word is in the array, returns 1*/
int searchWord(char **array, int *count, char word[])
{
	char *wordPtr;

    wordPtr = (char *)malloc((strlen(word) + 1) * sizeof(char));
    if (wordPtr == NULL)
    {
	fprintf(stderr,"    Malloc of array[%d] failed!\n", *count);
	return -1;
    }

	strcpy(wordPtr, word);

	int i;
	for(i = 0; i < *count; i++){
		if(strcmp(array[i], wordPtr) == 0){
			return 1;
		}
	}

}

/*removes word from array, subtracts one from count*/
void removeWord(char **array, int *count, char word[]){

    char *wordPtr;

    wordPtr = (char *)malloc((strlen(word) + 1) * sizeof(char));
    if (wordPtr == NULL)
    {
	fprintf(stderr,"    Malloc of array[%d] failed!\n", *count);
	return -1;
    }

	strcpy(wordPtr, word);
	
	/*iterate through the array to find the word, if found remove it*/
	int i;
	for(i = 0; i < *count; i++){

		/*Uses strncmp to find the word in the array*/
		while(strcmp((array)[i], wordPtr) == 0){
			/*move all the other words down by one index*/
			int j;
			for(j = i; j < (*count -1); j++){	
					(array)[j] = (array)[j+1];
			}
			
		}
	}
	(*count)--;
}

/*inserts word into the array in lexical order*/
int insertWord(char **array, int *count, char word[])
{
    char *wordPtr;

    wordPtr = (char *)malloc((strlen(word) + 1) * sizeof(char));
    if (wordPtr == NULL)
    {
	fprintf(stderr,"    Malloc of array[%d] failed!\n", *count);
	return -1;
    }

	strcpy(wordPtr, word);
	
	/* Memory for this word has been allocated, so copy characters
     *  and insert into array */

	/*if the array is null, put the word into the first position*/
	if(array[0] == NULL){ 
    	array[*count] = wordPtr;
	}
	/*if the array is not null, iterate through the array until you find a word bigger
	 *than the word you want to insert.*/
	else{
		int i;
		for(i = 0; i < *count; i++){
			/*iterate until you found the word that is bigger than the word you want to insert*/
			if(strcmp((array)[i], wordPtr) > 0){
				/*move the words after the ith space to the next index*/
				int j;
				for(j = (*count - 1); j >= i; j--){	
					array[j+1] = array[j];
				}
				array[i] = wordPtr;
				i = *count;
			}
			/*if the word you want to insert is the biggest, append it to the index
			 *after all the other words*/
			else{
				array[*count] = wordPtr;
			}
		}
	}
	
    (*count)++;

    return 0;
}

/*int saveDictionary(char *outFileName, char **array){
	
	//save array to output file
	FILE *outFile;

}*/

void printArray(char **array, int count)
{
   int i;

   printf("\n");
   for (i = 0; i < count; i++)
       printf("array[%d]: %s\n", i, array[i]);
}
