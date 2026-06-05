#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <stdlib.h>

void* allocate(int a, size_t mySize) {
	void* arrStart = malloc(a * mySize);
	if (arrStart == NULL)
	{
		printf("Memory allocation error!\n");exit(-1);
	}
	return arrStart;
}

int reallocate(char** inputString, int* capacity) {
	char transportArray[1000] = "";
	scanf_s("%999s", transportArray, (unsigned int)sizeof(transportArray));
	
	int myLength = (int)strlen(transportArray);
	
	if (myLength + 1 > *capacity)
	{
		int preSize = *capacity;
		*capacity = myLength + preSize;
		char* addition = (char*)realloc(*inputString, *capacity * sizeof(char));
		if (addition != NULL) { 
			*inputString = addition; 
		}
	}
	strcpy_s(*inputString, *capacity, transportArray);

	return myLength;
}

void deallocate(void* inputString) {
	free(inputString);
}

int main() {

	bool editorRuns = true;
	int length = 40;
	char* currentConsole = allocate(length, sizeof(char));;
	currentConsole[0] = '\0';
	// Початкове виділення пам'яті

	while (editorRuns)
	{
		int userInput;
		printf("Enter your option. You can choose from: 1-Append, 2-New line, 3-Save, 4-Load, 5-Print, 6-Insert, 7-Search, 8-Clear, 9-Exit  \n");
		scanf_s("%d", &userInput);
		//while (getchar() != '\n');
		switch (userInput) {
			case 1: {

				char* appendText = allocate(length, sizeof(char));
				printf("Enter text to append: \n");

				int myLength = reallocate(&appendText, &length);
				int newSize = myLength + 6 + (int)strlen(currentConsole);
				char* caseAppend1 = realloc(currentConsole, newSize * sizeof(char));
				if (caseAppend1 == NULL) {
					printf("Memory allocation error\n");exit(-1);
				}

				currentConsole = caseAppend1;
				strcat_s(currentConsole, newSize, appendText); 
				deallocate(appendText);
				break;
			}
			case 2: {
				printf("Start the new line: \n");
				int newSize = (int)strlen(currentConsole) + 5;
				char* myLength = realloc(currentConsole, newSize * sizeof(char));
				if (myLength == NULL) {
					printf("Memory allocation error\n"); exit(-1);}

				currentConsole = myLength;
				strcat_s(currentConsole, newSize, "\n");
				break;
			}
			case 3: {
				char* nameSave = allocate(length, sizeof(char));
				printf("Enter the file name for saving: \n");
				scanf_s("%s", nameSave, length);
				FILE* file = NULL;
				fopen_s(&file, nameSave, "w");

				if (file != NULL)
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
				scanf_s("%s", nameLoad, length);

				FILE* file = fopen(nameLoad, "r");
				char* mystring = allocate(length, sizeof(char));

				
				if (file == NULL)
				{
					printf("Error opening file. This file might not exist or is empty(\n");
					
				}
				else
				{
					char* copyConsole = allocate(1000, sizeof(char));
					strcpy_s(copyConsole, 1000, currentConsole);
					currentConsole[0] = '\0';
					while (fgets(mystring, 100, file) != NULL)
					{
						strcat_s(currentConsole, 1000, mystring);
					}
					strcat_s(currentConsole, 1000, copyConsole);
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
				scanf_s("%i", &line);
				printf("Enter symbol index: \n");
				scanf_s("%i", &index);
				printf("Enter text to insert: \n");
				int myLength = reallocate(&text, &length);

				int newSize = myLength + 6 + (int)strlen(currentConsole);
				char* searchConsole = (char*)realloc(currentConsole, newSize * sizeof(char));
				if (searchConsole == NULL){
					printf("Memory allocation error\n");exit(-1);
				}
				currentConsole = searchConsole;
			
				int allLines = 1;
				for (int i = 0; i<strlen(currentConsole); i++)
				{
					if (currentConsole[i] == '\n') {
						allLines += 1;}}
				if (line>=1 && line<=allLines && index>=0 && text!=NULL && index<=strlen(currentConsole))
				{
					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') { currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;

					for (int j = (int)strlen(currentConsole); j > index; j--)
					{
						currentConsole[j + strlen(text)] = currentConsole[j];
					}
					
					for (int a = index; a < index+strlen(text); a++)
					{
						currentConsole[consoleIndex + a] = text[a];
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

				int preSize = (int)strlen(currentConsole);
				int myLength = reallocate(&seekingText, &preSize);
				int index1 = 0;
				int myPosition = 0;

				char* searchArea = currentConsole;
				while ((searchArea = strstr(searchArea, seekingText)) != NULL) {
					index1 = (int)(searchArea - currentConsole);
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
				deallocate(seekingText); deallocate(positions); deallocate(exactLocations); //deallocate(myLength);
				break;
			}
			case 8: {
				printf("Clearing the console \n");
				currentConsole[0] = '\0';
				break;
			}
			case 9: {
				printf("Exiting editor.\n");
				editorRuns = false;
				//deallocate(currentConsole);
				break;
			}
			default: {
				printf("There is no such an option, try again! \n");
			}
		}
	}
	deallocate(currentConsole);
	printf("Program is shutting down...");
	return 0;
}