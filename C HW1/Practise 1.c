//#include <stdio.h>
//#include <stdlib.h> // Необхідно для malloc, realloc, free та exit
//#include <stdbool.h> 
//#include <string.h>
//
//void* allocate(int a, size_t mySize) {
//	void* arrStart = malloc(a * mySize);
//	if (arrStart == NULL)
//	{
//		printf("Memory allocation error!\n");
//		exit(1);
//	}
//	return arrStart;
//}
//
//// ВИПРАВЛЕНО: Функція приймає подвійний вказівник, щоб успішно змінювати адресу в main
//int reallocate(char** inputString, int* capacity) {
//	char transportArray[1000] = "";
//	// ВИПРАВЛЕНО: Прибрали & та scanf_s (для стандартного C краще scanf або fgets)
//	scanf("%999s", transportArray);
//
//	int myLength = strlen(transportArray);
//
//	if (myLength + 1 > *capacity)
//	{
//		*capacity = myLength + 50; // Збільшуємо місткість із запасом
//		char* temp = (char*)realloc(*inputString, *capacity * sizeof(char));
//		if (temp != NULL) {
//			*inputString = temp; // Оновлюємо оригінальний вказівник у main
//		}
//	}
//
//	strcpy(*inputString, transportArray); // Копіюємо введений текст у виділену пам'ять
//
//	// ВИПРАВЛЕНО: free(transportArray) ПРИБРАНО, бо це статичний масив на стекі!
//	return myLength;
//}
//
//void deallocate(void* inputString) {
//	free(inputString);
//}
//
//int main() {
//	bool editorRuns = true;
//	int length = 40;
//
//	// Початкове виділення пам'яті під головну консоль (зробимо більше для злиття рядків)
//	int consoleCapacity = 2000;
//	char* currentConsole = allocate(consoleCapacity, sizeof(char));
//	currentConsole[0] = '\0';
//
//	while (editorRuns)
//	{
//		int userInput;
//		printf("\nEnter your option (1-Append, 2-New line, 3-Save, 4-Load, 5-Print, 6-Insert, 7-Search, 8-Clear, 9-Exit): \n> ");
//		if (scanf("%d", &userInput) != 1) break;
//
//		switch (userInput) {
//		case 1: {
//			char* appendText = allocate(length, sizeof(char));
//			printf("Enter text to append: \n");
//
//			// ВИПРАВЛЕНО: Передаємо адресу вказівника &appendText та &length
//			int myLength = reallocate(&appendText, &length);
//
//			// Перевіряємо, чи влізе новий текст у велику консоль
//			if (strlen(currentConsole) + myLength + 1 > consoleCapacity) {
//				consoleCapacity += myLength + 50;
//				currentConsole = realloc(currentConsole, consoleCapacity * sizeof(char));
//			}
//
//			strcat(currentConsole, appendText);
//			deallocate(appendText);
//			break;
//		}
//		case 2: {
//			printf("Start the new line: \n");
//			strcat(currentConsole, "\n");
//			break;
//		}
//		case 3: {
//			char* nameSave = allocate(length, sizeof(char));
//			printf("Enter the file name for saving: \n");
//			scanf("%s", nameSave); // ВИПРАВЛЕНО: Прибрали &
//
//			FILE* file = fopen(nameSave, "w");
//			if (file != NULL)
//			{
//				fputs(currentConsole, file);
//				fclose(file);
//				printf("Text have been saved successfully\n");
//			}
//			else {
//				printf("Error opening file!\n");
//			}
//			deallocate(nameSave);
//			break;
//		}
//		case 4: {
//			char* nameLoad = allocate(length, sizeof(char));
//			printf("Enter the file name for loading: \n");
//			scanf("%s", nameLoad); // ВИПРАВЛЕНО: Прибрали &
//
//			FILE* file = fopen(nameLoad, "r");
//			char* mystring = allocate(length, sizeof(char));
//
//			if (file == NULL)
//			{
//				printf("Error opening file. This file might not exist or is empty(\n");
//			}
//			else
//			{
//				// ВИПРАВЛЕНО: Зберігаємо копію тексту у новий тимчасовий буфер, а не просто дублюємо адресу
//				char* copyConsole = allocate(consoleCapacity, sizeof(char));
//				strcpy(copyConsole, currentConsole);
//
//				currentConsole[0] = '\0'; // Очищаємо консоль для завантаження нових даних
//
//				while (fgets(mystring, length - 1, file) != NULL)
//				{
//					strcat(currentConsole, mystring);
//				}
//				strcat(currentConsole, copyConsole); // Додаємо старий текст назад
//				fclose(file);
//				printf("Text have been loaded successfully\n");
//				deallocate(copyConsole); // Тепер це безпечно виділена пам'ять
//			}
//			deallocate(mystring);
//			deallocate(nameLoad);
//			break;
//		}
//		case 5: {
//			printf("Printing the current text console: \n%s\n", currentConsole);
//			break;
//		}
//		case 6: {
//			int line = 0;
//			int index = 0;
//			char* text = allocate(length, sizeof(char));
//
//			printf("Insert the text by line and symbol index: \n");
//			printf("Enter line number: \n");
//			scanf("%d", &line);
//			printf("Enter symbol index: \n");
//			scanf("%d", &index);
//			printf("Enter text to insert: \n");
//
//			int myLength = reallocate(&text, &length);
//
//			int allLines = 1;
//			for (int i = 0; i < strlen(currentConsole); i++)
//			{
//				if (currentConsole[i] == '\n') {
//					allLines += 1;
//				}
//			}
//
//			if (line >= 1 && line <= allLines && index >= 0 && index <= strlen(currentConsole))
//			{
//				// Розраховуємо глобальний індекс зсуву по рядках
//				int currentLine = 1;
//				int globalIndex = 0;
//				while (currentConsole[globalIndex] != '\0' && currentLine < line) {
//					if (currentConsole[globalIndex] == '\n') currentLine++;
//					globalIndex++;
//				}
//				globalIndex += index;
//
//				// Зсуваємо пам'ять вправо під новий текст
//				int textLen = strlen(text);
//				for (int j = (int)strlen(currentConsole); j >= globalIndex; j--)
//				{
//					currentConsole[j + textLen] = currentConsole[j];
//				}
//				// Вставляємо текст
//				for (int a = 0; a < textLen; a++)
//				{
//					currentConsole[globalIndex + a] = text[a];
//				}
//				printf("Text is successfully inserted.\n");
//			}
//			else
//			{
//				printf("Either there is no such a line or index in the text.\n Please, try again!\n");
//			}
//			deallocate(text);
//			break;
//		}
//		case 7: {
//			int* positions = allocate(length, sizeof(int));
//			int* exactLocations = allocate(length, sizeof(int));
//			char* seekingText = allocate(length, sizeof(char));
//
//			printf("Enter text to search: \n");
//			int myLength = reallocate(&seekingText, &length);
//
//			int index1 = 0;
//			int myPosition = 0;
//
//			char* searchArea = currentConsole;
//			// ВИПРАВЛЕНО: Додано круглі дужки для пріоритету операцій
//			while ((searchArea = strstr(searchArea, seekingText)) != NULL) {
//				index1 = searchArea - currentConsole;
//				positions[myPosition] = index1;
//				myPosition++;
//				searchArea += strlen(seekingText);
//				if (myPosition >= length) break;
//			}
//
//			int counter = 0; int line = 0; int positionIndex = 0; int exactIndex = 0;
//
//			for (int i = 0; i < strlen(currentConsole); i++)
//			{
//				if (currentConsole[i] == '\n') {
//					line++;
//					counter = 0;
//					continue;
//				}
//				if (positionIndex < myPosition && i == positions[positionIndex])
//				{
//					positionIndex++;
//					exactLocations[exactIndex] = line; exactIndex++;
//					exactLocations[exactIndex] = counter; exactIndex++;
//				}
//				counter++;
//			}
//
//			printf("Text is present in the position/positions: \n");
//			for (int b = 0; b < exactIndex; b += 2)
//			{
//				printf("Row:%d - Index:%d\n", exactLocations[b], exactLocations[b + 1]);
//			}
//			deallocate(seekingText);
//			deallocate(positions);
//			deallocate(exactLocations);
//			break;
//		}
//		case 8: {
//			printf("Clearing the console \n");
//			currentConsole[0] = '\0';
//			break;
//		}
//		case 9: { // Додано явний пункт для виходу з програми
//			editorRuns = false;
//			break;
//		}
//		default: {
//			printf("There is no such an option, try again! \n");
//		}
//		}
//	}
//
//	// ВИПРАВЛЕНО: Винесли очищення пам'яті ЗА межі циклу while
//	deallocate(currentConsole);
//	printf("Program is shutting down...\n");
//	return 0;
//}