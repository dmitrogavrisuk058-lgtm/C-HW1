#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
int main() {

	bool editorRuns = true;
	char currentConsole[30] = ""; //LinkedList use
	char filenames[20] = "";
	int length = 1;

	if (filenames != "") {
		length = sizeof(filenames) / sizeof(filenames[0]);
	}

	while (editorRuns)
	{
		int userInput;
		printf("Enter your option: \n");
		scanf("%d", &userInput);
		switch (userInput) {
		case 1: {
			char appendText[30];
			printf("Enter text to append: \n");
			scanf("%s", &appendText);
			strcat(currentConsole, appendText, sizeof(appendText) - strlen(appendText) - 1);
			break;
		}
		case 2: {
			printf("Start the new line: \n");
			strcat(currentConsole, "\n", 2);
			break;
		}
		case 3: {
			char nameSave[10];

			printf("Enter the file name for saving: \n");
			scanf("%s", &nameSave);

			for (int i = 0; i<length; i++)
			{
				if (nameSave == filenames[i])
				{
					printf("This file already exists. Try another name! \n");
					break;
				}
			}
			//File save current info

			printf("Text have been saved successfully\n");
			editorRuns = false;
			break;
		}
		case 4: {
			bool isInList = false;
			char nameLoad[10];
			printf("Enter the file name for saving: \n");
			scanf("%s", &nameLoad);

			for(int i = 0; i<length; i++)
			{
				if (nameLoad == filenames[i])
				{
					isInList = true;
					//File load 

					printf("Text have been loaded successfully\n");
					break;
				}
			}

			printf("There is no such a file, try another one(");
			break;
		}
		case 5: {
			printf("Printing the current text console: %s\n", currentConsole);
			break;
		}
		
		case 6: {
			int line;
			int index;
			char text[10]; //Linked List or plain list insert in LList;

			printf("Insert the text by line and symbol index: \n");
			printf("Enter line number: \n");
			scanf("%i", &line);
			printf("Enter symbol index: \n");
			scanf("%i", &index);
			printf("Enter text to insert: \n");
			scanf("%s", text);
			break;
		}
		case 7: {
			char positions[10];
			char seekingText[30];
			printf("Enter text to search: \n");
			//Logic of seek
			printf("Text is present in the position/positions: %s\n", positions);
			break;
		}
		case 8: {
			printf("Clearing the console \n");
			currentConsole[0] = '\0';
			break;
		}
		default: {
			printf("There is no such an optin, try again! \n");
		}
	}
	printf("Program is shutting down...");

	return 0;
}