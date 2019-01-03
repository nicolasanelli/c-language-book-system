/*
 * layout.h
 *
 *  Created on: 18 de ago de 2018
 *      Author: nicolas
 */

#ifndef BOOKSYSTEM_LAYOUT_H_
#define BOOKSYSTEM_LAYOUT_H_

#define SIZE 60

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printStarLine();
void printLine(char *content, char align);
void cls();
void error(char *content);


void printStarLine() {
	printf("\t");
	for (int i = 0; i<SIZE; i++){
		printf("*");
	}
	printf("\n");
}
void printLine(char *content, char align) {
	int size;
	int rest = SIZE - 1;
	int writed = 0;
	int aux = 0;
	int i;
	size = strlen(content);

	printf("\t");
	switch (align) {
		case 'L':
			printf("*  ");
			writed += 3;
			printf("%s", content);
			writed += size;
			rest -= writed;
			for (i = 0; i < rest; i++) {
				printf(" ");
			}
			printf("*");
			break;
		case 'R':
			printf("*  ");
			writed += 3;
			aux = (SIZE - 3) - (size + 2);
			for (i = 0; i < aux; i++) {
				printf(" ");
			}
			writed += aux;
			printf("%s", content);
			writed += size;
			rest -= writed;
			for (i = 0; i < rest; i++) {
				printf(" ");
			}
			printf("*");
			break;
		case 'C':
			printf("*  ");
			writed += 3;
			aux = ((SIZE/2) - 3) - size/2;
			for (i = 0; i < aux; i++) {
				printf(" ");
			}
			writed += aux;
			printf("%s", content);
			writed += size;
			rest -= writed;
			for (i = 0; i < rest; i++) {
				printf(" ");
			}
			printf("*");
			break;
		default:
			error("Align type not exists");
	}
	printf("\n");
}
void cls() {
	printf("\e[1;1H\e[2J");
}
void error(char *content) {
	cls();
	printf("There is an error: %s \n\nProgram exit \n\n", content);
	exit(0);
}

#endif /* BOOKSYSTEM_LAYOUT_H_ */
