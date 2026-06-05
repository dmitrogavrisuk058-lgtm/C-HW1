#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <stdlib.h>

void* allocate(int a, size_t mySize) {
	void* arrStart = malloc(a * mySize);
	if (arrStart == NULL)
	{
		printf("Memory allocation error!\n");
		exit(1);
	}
	return arrStart;
}

int reallocate(char** inputString, int* capacity) {
	char transportArray[1000] = "";
	scanf_s("%999s", transportArray);
	
	int myLength = strlen(transportArray);
	
	if (myLength + 1 > *capacity)
	{
		*capacity = myLength + 50;
		char* addition = (char*)realloc(*inputString, *capacity * sizeof(char));
		if (addition != NULL) { 
			*inputString = addition; 
		}
	}
	strcpy_s(*inputString, transportArray, 1000);
	return myLength;
}

void deallocate(void* inputString) {
	free(inputString);
}

int main() 
{

	bool editorRuns = true;
	int length = 40;
	char* currentConsole = allocate(length, sizeof(char));;
	currentConsole[0] = '\0';
	// Початкове виділення пам'яті
	
	while (editorRuns)
	{
		int userInput;
		printf("Enter your option. You can choose from: 1-Append, 2-New line, 3-Save, 4-Load, 5-Print, 6-Insert, 7-Search, 8-Clear, 9-Exit  \n");
		scanf("%d", &userInput);
		switch (userInput) {
			case 1: {

				char* appendText = allocate(length, sizeof(char));
				printf("Enter text to append: \n");

				int myLength = reallocate(&appendText, &length);
				currentConsole = realloc(currentConsole, myLength * sizeof(char));

				strcat(currentConsole, appendText); 
				deallocate(appendText);
				break;
			}
			case 2: {
				printf("Start the new line: \n");
				strcat(currentConsole, "\n");
				break;
			}
			case 3: {
				char* nameSave = allocate(length, sizeof(char));
				printf("Enter the file name for saving: \n");
				scanf("%s", nameSave);

				FILE* file = fopen(nameSave, "w");

				if (file == NULL)
				{
					fputs(currentConsole, file);
					fclose(file);
					printf("Text have been saved successfully\n");
					editorRuns = false;
				}
				else{
					printf("Error with file opening occured(");}
				deallocate(nameSave);
				break;
			}
			case 4: {
				char* nameLoad = allocate(length, sizeof(char));
				printf("Enter the file name for loading: \n");
				scanf("%s", nameLoad);

				FILE* file = fopen(nameLoad, "r");
				char* mystring = allocate(length, sizeof(char));

				
				if (file == NULL)
				{
					printf("Error opening file. This file might not exist or is empty(\n");
					
				}
				else
				{
					char* copyConsole = allocate(1000, sizeof(char));
					strcpy(copyConsole, currentConsole);
					currentConsole[0] = '\0';
					while (fgets(mystring, 100, file) != NULL)
					{
						strcat(currentConsole, mystring);
					}
					strcat(currentConsole, copyConsole);
					fclose(file);
					printf("Text have been loaded successfully\n");
					deallocate(copyConsole);
				}
				deallocate(mystring); deallocate(nameLoad); 
				break;
			}
			case 5: {
				printf("Printing the current text console: %s\n", currentConsole);
				break;
			}
			
			case 6: {
				int line = 0;
				int index = 0;
				char* text = allocate(length, sizeof(char)); 

				printf("Insert the text by line and symbol index: \n");
				printf("Enter line number: \n");
				scanf("%i", &line);
				printf("Enter symbol index: \n");
				scanf("%i", &index);
				printf("Enter text to insert: \n");
				int myLength = reallocate(&text, &length);

				char searchConsole = (char)realloc(currentConsole, myLength * sizeof(char));
				// strncat(currentConsole, text, sizeof(currentConsole) - strlen(text) - 1);
			
				int allLines = 1;
				for (int i = 0; i<strlen(currentConsole); i++)
				{
					if (currentConsole[i] == '\n') {
						allLines += 1;}}
				if (line>=1 && line<=allLines && index>=0 && text!=NULL && index<=strlen(currentConsole))
				{
					for (int j = (int)strlen(currentConsole); j > index; j--)
					{
						currentConsole[j + strlen(text)] = currentConsole[j];
					}
					int textCounter = 0;
					for (int a = index; a < index+strlen(text); a++)
					{
						currentConsole[a] = text[textCounter];
						textCounter += 1;
					}
					printf("Text is successfully inserted.");
				}
				else
				{
					printf("Either there is no such a line or index in the text, or you wrote nothing as text.\n Please, try again!");
					break;
				}
				deallocate(text);
				break;
			}
			case 7: {
				int* positions = allocate(length, sizeof(int));
				int* exactLocations = allocate(length, sizeof(int));
				char* seekingText = allocate(length, sizeof(char));

				printf("Enter text to search: \n");

				int myLength = reallocate(&seekingText, &length);
				int index1 = 0;
				int myPosition = 0;

				char* searchArea = currentConsole;
				while ((searchArea = strstr(searchArea, seekingText)) != NULL) {
					index1 = searchArea - currentConsole;
					positions[myPosition] = index1;
					myPosition++;
					searchArea += strlen(seekingText);
					if (myPosition >= length) break;
				}

				int counter = 0; int line = 0; int positionIndex = 0; int exactIndex = 0;

				for (int i = 0; i < strlen(currentConsole); i++)
				{
					if (currentConsole[i] == '\n'){
						line++;
						counter = 0; 
						continue;
					}
					if (i == positions[positionIndex])
					{
						positionIndex++;
						exactLocations[exactIndex] = line; exactIndex++;
						exactLocations[exactIndex] = counter; exactIndex++;
					}
					if (positionIndex > 19)
					{
						break;
					}
					counter++;
				}
				//While strstr != Null шукаємо у певному рядку збіги за strstr. Якщо такий знайдений, то продовжуємо пошук з наступного індексу який вивів нам метод 
				// Тепер коли у нас є адреса входження ітеруємося до індексу, дивимося рахуємо через counter індекс і скидаємо його коли отримуємо входження \n
				printf("Text is present in the position/positions: \n");
				for (int b = 0; b < exactIndex; b+=2)
				{
					printf("Row:%i - Index:%i\n", exactLocations[b], exactLocations[b+1]);
				}
				deallocate(seekingText); deallocate(positions); deallocate(exactLocations); deallocate(myLength);
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
	deallocate(currentConsole);
	printf("Program is shutting down...");
	return 0;
}