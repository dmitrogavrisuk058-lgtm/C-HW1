#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

char allocate(int a) {
	char arrLength = malloc(a * sizeof(char));
}

void reallocate(char inputString, int capacity) {
	char transportArray[2000] = "";
	scanf("%s", &transportArray);
	
	/*while (length + 1 < capacity) {
		length += 50;
	}*/
	int myLength = strlen(transportArray);
	if (transportArray != NULL && myLength-2 > capacity)
	{
		char temp = (char)realloc(inputString, myLength * sizeof(char));
	}
	else if (transportArray == NULL)
	{
		printf("Something went wrong( You wrote nothing or exceeded limit.\n");
	}
}

void deallocate(char inputString) {
	free(inputString);
}

int main() {

	bool editorRuns = true;
	char currentConsole[] = ""; //LinkedList use
	int length = 35;// Початкове виділення пам'яті

	 // sizeof is as good as strlen
	
	while (editorRuns)
	{
		int userInput;
		printf("Enter your option: \n");
		scanf("%d", &userInput);
		switch (userInput) {
		case 1: {
			char appendText[] = allocate(length);
			printf("Enter text to append: \n");
			reallocate(appendText, length);
			
			strcat(currentConsole, appendText); //sizeof optional , sizeof(currentConsole) - strlen(appendText) - 1
			deallocate(appendText);
			break;
		}
		case 2: {
			printf("Start the new line: \n");
			strcat(currentConsole, "\n");
			break;
		}
		case 3: {
			char nameSave[] = allocate(length);
			printf("Enter the file name for saving: \n");
			scanf("%s", &nameSave);

			FILE* file;
			file = fopen(nameSave, "w");

			if (file != NULL)
			{
				printf("Creating new file");
				fputs("Hello, files world!", file);
			}

			fputs(currentConsole, file);
			fclose(file);
			printf("Text have been saved successfully\n");
			editorRuns = false;
			deallocate(nameSave);
			break;
		}
		case 4: {
			char nameLoad[] = allocate(length);
			printf("Enter the file name for loading: \n");
			scanf("%s", &nameLoad);

			FILE* file;
			bool loadingFile = true;
			char mystring[] = allocate(length);
			file = fopen(nameLoad, "r");

			while (loadingFile) {
				if (file == NULL)
				{
					printf("Error opening file. This file might not exist or is empty(");
					break;
				}
				else
				{
					if (fgets(mystring, 10, file) != NULL)
					{
						fgets(mystring, 100, file);
						printf("%s", mystring);
						mystring[0] = '\0';
					}
					else
					{
						loadingFile = false;
					}
				}
			}
			fclose(file); 
			deallocate(mystring);
			printf("Text have been loaded successfully\n");
			break;
		}
		case 5: {
			printf("Printing the current text console: %s\n", currentConsole);
			break;
		}
		
		case 6: {
			int line;
			int index;
			char text[] = allocate(length); //Linked List or plain list insert in LList;


			printf("Insert the text by line and symbol index: \n");
			printf("Enter line number: \n");
			scanf("%i", &line);
			printf("Enter symbol index: \n");
			scanf("%i", &index);
			printf("Enter text to insert: \n");
			reallocate(text, length);
			// Logic of inserting
			deallocate(text);
			break;
		}
		case 7: {
			char positions[] = allocate(length);
			char seekingText[] = allocate(length);
			printf("Enter text to search: \n");
			reallocate(seekingText, length);
			//Logic of seek
			printf("Text is present in the position/positions: %s\n", positions);
			deallocate(seekingText);
			break;
		}
		case 8: {
			printf("Clearing the console \n");
			currentConsole[0] = '\0';
			break;
		}
		default: {
			printf("There is no such an option, try again! \n");
		}
	}
	printf("Program is shutting down...");

	return 0;
}

// should implement logic of freeing arrays for each case