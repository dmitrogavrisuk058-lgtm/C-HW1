#include <stdio.h>
#include <stdbool.h> /*Треба підключати ззовні окрему бібліотеку для bool*/
int main() {
	char name[40];
	printf("Name: %s \n", name);
	int age;
	scanf("%d", &age);

	for (int i = 0; i < 4; i++) {
		//
	}
	/*Array з 7 елементів*/
	int* myArr;
	/* функція malloc - memory allocation */

	//void* -> int*
	int* myArr = malloc(20 * 4/*int N bytes*/);

	sizeof(myArr); /*Виділення певної кількості пам'яті*/
	return 0;
}