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
	char transportArray[2000] = "";
	if (fgets(transportArray, (int)sizeof(transportArray), stdin) == NULL) {
		printf("You wrote nothing into console"); return 0;
	}
	fgets(transportArray, (int)sizeof(transportArray), stdin);
	transportArray[strcspn(transportArray, "\n")] = '\0';
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

int reallocDynamic(char** inputString, int* capacity) {
	int memoryIncrease = 100;
	*capacity += 100;
	char* addition = (char*)realloc(*inputString, *capacity * sizeof(char));
}

void deallocate(void* inputString) {
	free(inputString);
}

int main() {

	bool editorRuns = true;
	int length = 40;
	int maxSize = 2000;
	char* currentConsole = allocate(length, sizeof(char));;
	currentConsole[0] = '\0';
	int allLines = 1;
	char* copyBuffer = allocate(length, sizeof(char));

	while (editorRuns)
	{
		int userInput;
		printf("Enter your option. You can choose from: 1-Append, 2-New line, 3-Save, 4-Load, 5-Print, 6-Insert, 7-Search, 8-Clear,  \n");
		printf(" 9-Delete, 10-Undo, 11-Redo, 12-Cut, 13-Paste, 14-Copy, 15-Insert&Replace, 16-Exit, 17-Print copy.\n");
		scanf_s("%d", &userInput);
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
				allLines += 1;
				while (getchar() != '\n');
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
					char* copyConsole = allocate(maxSize, sizeof(char));
					strcpy_s(copyConsole, maxSize, currentConsole);
					currentConsole[0] = '\0';
					while (fgets(mystring, 100, file) != NULL)
					{
						strcat_s(currentConsole, maxSize, mystring);
					}
					strcat_s(currentConsole, maxSize, copyConsole);
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
			
				if (line>=0 && line <= allLines && index >= 0 && text != NULL && index <= strlen(currentConsole))
				{
					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') { currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;

					for (int j = (int)strlen(currentConsole); j >= consoleIndex; j--)
					{
						currentConsole[j + strlen(text)] = currentConsole[j];
					}
					
					int b = 0;
					for (int a = consoleIndex; a < consoleIndex+strlen(text); a++)
					{
						currentConsole[a] = text[b];
						b++;
					}
					printf("Text is successfully inserted.");
				}
				else
				{
					printf("Either there is no such a line or index in the text, or you wrote nothing as text.\n Please, try again!\n");
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
				printf("Text is present in the position/positions: \n");
				for (int b = 0; b < exactIndex; b+=2)
				{
					printf("Row:%i - Index:%i\n", exactLocations[b], exactLocations[b+1]);
				}
				deallocate(seekingText); deallocate(positions); deallocate(exactLocations); 
				break;
			}
			case 8: {
				printf("Clearing the console \n");
				currentConsole[0] = '\0';
				break;
			}
			case 9: {
				int line = 0;
				int index = 0;
				int lastDelElem = 0;

				printf("Delete text by line and symbol index: \n");
				printf("Enter line number: \n");
				scanf_s("%i", &line);
				printf("Enter first index: \n");
				scanf_s("%i", &index);
				printf("Enter last index: \n");
				scanf_s("%i", &lastDelElem);

				if (line >= 0 && line <= allLines && index >= 0 && index <= strlen(currentConsole))
				{
					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') {currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;
					int upperValue = consoleIndex + lastDelElem - index;

					for (int j = consoleIndex; j <= (int)strlen(currentConsole)-lastDelElem+index; j++){
						currentConsole[j] = currentConsole[upperValue];
						upperValue++;}
				
					printf("Text is successfully deleted.\n");
				}
				else{
					printf("Either there is no such a line or index in the text.\n Please, try again!\n");}
				break;
			}
			
			case 12: {
				int line = 0;
				int index = 0;
				int lastCutElem = 0;
				int localLength = length;

				printf("Cut text by line and symbol index: \n");
				printf("Enter line number: \n");
				scanf_s("%i", &line);
				printf("Enter first index: \n");
				scanf_s("%i", &index);
				printf("Enter last index: \n");
				scanf_s("%i", &lastCutElem);

				if (line >= 0 && line <= allLines && index >= 0 && index <= strlen(currentConsole))
				{
					if (copyBuffer != NULL) copyBuffer[0] = '\0';

					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') { currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;
					
					int bufferIndex = 0;
					int upperValue = consoleIndex + lastCutElem - index;
					for (int j = consoleIndex; j <= (int)strlen(currentConsole) - lastCutElem + index; j++)
					{
						if (bufferIndex >= localLength) {
							reallocDynamic(&copyBuffer, &localLength);
						}
						copyBuffer[bufferIndex] = currentConsole[j];
						currentConsole[j] = currentConsole[upperValue];
						upperValue++; bufferIndex++;
					}
					if (bufferIndex >= localLength) { reallocDynamic(&copyBuffer, &localLength); }
					copyBuffer[bufferIndex] = '\0';
					printf("Text is successfully cut.\n");
				}
				else { printf("Either there is no such a line or index in the text.\n Please, try again!\n"); }
				break;
			}
			case 13: {
				int line = 0;
				int index = 0;

				printf("Paste text by line and symbol index: \n");
				printf("Enter line number: \n");
				scanf_s("%i", &line);
				printf("Enter symbol index: \n");
				scanf_s("%i", &index);

				if (line >= 0 && line <= allLines && index >= 0 && index <= strlen(currentConsole))
				{
					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') { currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;

					for (int j = (int)strlen(currentConsole); j >= consoleIndex; j--){
						currentConsole[j + strlen(copyBuffer)] = currentConsole[j];}

					int b = 0;
					for (int a = consoleIndex; a < consoleIndex + strlen(copyBuffer); a++){
						currentConsole[a] = copyBuffer[b];
						b++;}
					printf("Text is successfully pasted.\n");
				}
				else{
					printf("Either there is no such a line or index in the text.\n Please, try again!\n");
				}
				break;
			}
			case 14: {
				int line = 0;
				int index = 0;
				int lastCopyElem = 0;
				int localLength = length;
		
				printf("Copy text by line and symbol index: \n");
				printf("Enter line number: \n");
				scanf_s("%i", &line);
				printf("Enter first index: \n");
				scanf_s("%i", &index);
				printf("Enter last index: \n");
				scanf_s("%i", &lastCopyElem);
				
				if (line >= 0 && line <= allLines && index >= 0 && lastCopyElem >= 0 && lastCopyElem > index && index <= strlen(currentConsole)){
					if (copyBuffer != NULL) copyBuffer[0] = '\n';

					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') { currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;

					int bufferIndex = 0;
					for (int j = consoleIndex; j <= consoleIndex + lastCopyElem + index; j++){
						if (bufferIndex >= localLength) {
							reallocDynamic(&copyBuffer, &localLength);
						}
						copyBuffer[bufferIndex] = currentConsole[j];
						bufferIndex++;
					}
					if (bufferIndex >= localLength) {reallocDynamic(&copyBuffer, &localLength);}
					copyBuffer[bufferIndex] = '\0';
					printf("Text is successfully copied.\n");
				}
				else{printf("Either there is no such a line or index in the text.\n Please, try again!\n");}
				break;
			}
			case 15: {
				int line = 0;
				int index = 0;
				char* text = allocate(length, sizeof(char));

				printf("Delete text by line and symbol index: \n");
				printf("Enter line number: \n");
				scanf_s("%i", &line);
				printf("Enter start index: \n");
				scanf_s("%i", &index);
				printf("Enter replacing text: \n");
				int myLength = reallocate(&text, &length);

				if (line >= 0 && line <= allLines && index >= 0 && index <= strlen(currentConsole))
				{
					int currentLine = 1;
					int consoleIndex = 0;
					while (currentConsole[consoleIndex] != '\0' && currentLine < line) {
						if (currentConsole[consoleIndex] == '\n') { currentLine++; }
						consoleIndex++;
					}
					consoleIndex += index;
					int upperValue = consoleIndex + strlen(text) - index; //index - індекс початку заміни

					int textInd = 0;
					for (int j = consoleIndex; j < upperValue ; j++) {
						currentConsole[j] = text[textInd];
						textInd++;
					}

					printf("Text is successfully replaced.\n");
				}
				else {
					printf("Either there is no such a line or index in the text.\n Please, try again!\n");}
				break;
			}
			case 16: {
				printf("Exiting editor.\n");
				editorRuns = false;
				break;
			}
			case 17: {
				printf("%s\n", copyBuffer);
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