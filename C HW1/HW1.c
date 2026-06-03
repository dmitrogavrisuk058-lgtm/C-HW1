#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

char** allocateChar(int a) {
	char** arrStart = malloc(a * sizeof(char*));
	return arrStart;
}

void** allocate(int a, size_t mySize) {
	void** arrStart = malloc(a * mySize);
	return arrStart;
}

int reallocate(char** inputString, int capacity) {
	char transportArray[2000] = "";
	scanf("%s", transportArray);
	
	/*while (length + 1 < capacity) {
		length += 50;
	}*/
	int myLength = strlen(transportArray);
	char* temp = 'a';
	if (transportArray != NULL && myLength-2 > capacity)
	{
		temp = (char*)realloc(inputString, myLength * sizeof(char*));
	}
	else if (transportArray == NULL)
	{
		printf("Something went wrong( You wrote nothing or exceeded limit.\n");
	}

	free(transportArray);
	return myLength;
}

void deallocate(char** inputString) {
	free(inputString);
}

int main() {

	bool editorRuns = true;
	char* currentConsole = ""; //LinkedList use
	int length = 35;// Початкове виділення пам'яті

	 // sizeof is as good as strlen
	
	while (editorRuns)
	{
		int userInput;
		printf("Enter your option: \n");
		scanf("%d", userInput);
		switch (userInput) {
		case 1: {
			char** appendText = allocate(length, sizeof(char));
			printf("Enter text to append: \n");

			int myLength = reallocate(appendText, length);
			char/**/ appendConsole = (char)realloc(currentConsole, myLength * sizeof(char));

			strncat(currentConsole, appendText, sizeof(currentConsole) - strlen(appendText) - 1); //sizeof optional , sizeof(currentConsole) - strlen(appendText) - 1
			deallocate(appendText);
			break;
		}
		case 2: {
			printf("Start the new line: \n");
			strcat(currentConsole, "\n");
			break;
		}
		case 3: {
			char** nameSave = allocate(length, sizeof(char));
			printf("Enter the file name for saving: \n");
			scanf("%s", nameSave);

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
			char** nameLoad = allocate(length, sizeof(char));
			printf("Enter the file name for loading: \n");
			scanf("%s", nameLoad);

			FILE* file;
			bool loadingFile = true;
			char** mystring[] = allocate(length, sizeof(char));
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
						printf("%s\n", mystring);
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
			char** text = allocate(length, sizeof(char)); //Linked List or plain list insert in LList;


			printf("Insert the text by line and symbol index: \n");
			printf("Enter line number: \n");
			scanf("%i", line);
			printf("Enter symbol index: \n");
			scanf("%i", index);
			printf("Enter text to insert: \n");
			int myLength = reallocate(text, length);

			char** searchConsole = (char)realloc(currentConsole, myLength * sizeof(char));
			// strncat(currentConsole, text, sizeof(currentConsole) - strlen(text) - 1);
			
			int allLines = 1;
			for (int i = 0; i<strlen(currentConsole); i++)
			{
				if (currentConsole[i] == '\n') {
					allLines += 1;}}
			if (line>=1 && line<=allLines && line!=NULL && index!=NULL && text!=NULL && index>=0)
			{
				for (int j = strlen(currentConsole); j > index; j--)
				{
					currentConsole[j + strlen(text)] = currentConsole[j];
				}
				int textCounter = 0;
				for (int a = index; a < index+strlen(text); a++)
				{
					currentConsole[a] = text[textCounter];
					textCounter += 1;
				}
			}
			else
			{
				printf("Either there is no such a line or index in the text, or you wrote nothing as text.\n Please, try again!");
				break;
			}
			deallocate(text);
			printf("Text is successfully inserted.");
			break;
		}
		case 7: {
			int** positions = allocate(length, sizeof(int));
			char** seekingText = allocate(length, sizeof(char));
			printf("Enter text to search: \n");
			int myLength = reallocate(seekingText, length);
			int index = 0;
			int myPosition = 0;

			while (strstr(&currentConsole[index], seekingText) != NULL) {
				char* location = strstr(&currentConsole, seekingText);
				index = location - currentConsole;
				positions[myPosition] = index;
				myPosition++;
			}
			//While strstr != Null шукаємо у певному рядку збіги за strstr. Якщо такий знайдений, то продовжуємо пошук з наступного індексу який вивів нам метод 
			// Тепер коли у нас є адреса входження ітеруємося до індексу, дивимося рахуємо через counter індукс і скидаємо його коли отримуємо входження \n
			printf("Text is present in the position/positions: %s\n", positions);
			deallocate(seekingText);
			break;
		}
		case 8: {
			printf("Clearing the console \n");
			deallocate(currentConsole);
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