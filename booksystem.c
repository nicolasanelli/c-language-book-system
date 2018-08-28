#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layout.h"

typedef struct Book {
	char title[80];
	char author[80];
	int pages;
} Book;

void printHeader(int total);
void printMenu();
void addNewBook(Book books[], int *total);
void showAllBooks(Book books[], int total);
void populateBooks(Book books[]);

int main() {

	int op = 0;
	int total = 6;
	Book books[20];

	populateBooks(books);

	do{
		printMenu(total);
		printf("\nOption: ");
		scanf("%i", &op);

		switch(op){
		case 1:
			addNewBook(books, &total);
			break;
		case 2:
			showAllBooks(books, total);
			break;
		case 99:
		default:
			cls();
		}

	} while (op != 99);

	return 0;
}

void printHeader(int total) {

	char txt_total_books[25];
	sprintf(txt_total_books, "Total books: %d", total);

	printf("\n");
	printStarLine();
	printLine("", 'L');
	printLine("TechBooks Control System", 'C');
	printLine(txt_total_books, 'R');
	printStarLine();
}
void printMenu(int total) {
	cls();
	printHeader(total);
	printLine("Main menu", 'L');
	printStarLine();
	printLine("", 'L');
	printLine("1. Add new book", 'L');
	printLine("", 'L');
	printLine("2. Show all books", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("", 'L');
	printLine("99 - Exit", 'R');
	printStarLine();
}
void addNewBook(Book books[], int *total) {

	int op = 50;
	char *title;
	char *author;
	int *pages;
	char txt_title[100];
	char txt_author[100];
	char txt_pages[100];


	title = (char*)malloc(80);
	author = (char*)malloc(80);
	pages = (int*)malloc(sizeof(int));

	do{
		sprintf(txt_title, "1. Title: %s", title);
		sprintf(txt_author, "2. Author: %s", author);
		sprintf(txt_pages, "3. Pages: %d", *pages);

		cls();
		printHeader(*total);
		printLine("Add new book", 'L');
		printStarLine();
		printLine("", 'L');
		printLine(txt_title, 'L');
		printLine("", 'L');
		printLine(txt_author, 'L');
		printLine("", 'L');
		printLine(txt_pages, 'L');
		printLine("", 'L');
		printLine("", 'L');
		printLine("", 'L');
		printLine("", 'L');
		printLine("0 - Save", 'L');
		printLine("", 'L');
		printLine("99 - Back to menu", 'R');
		printStarLine();

		switch(op) {
		case 1:
			printf("Title: ");
			scanf(" %[^\n]", title);
			op = 50;
			break;
		case 2:
			printf("Author: ");
			scanf(" %[^\n]", author);
			op = 50;
			break;
		case 3:
			printf("Pages: ");
			scanf("%d", pages);
			op = 50;
			break;
		case 0:
			strcpy(books[*total].title, title);
			strcpy(books[*total].author, author);
			books[*total].pages = (int)*pages;

			title = (char*)malloc(80);
			author = (char*)malloc(80);
			pages = (int*)malloc(sizeof(int));

			printf("Title: %s \n", books[*total].title);
			printf("Author: %s \n", books[*total].author);
			printf("Pages: %d \n", books[*total].pages);

			*total += 1;

			op = 50;
			break;
		case 50:
		default:
			printf("Option: ");
			scanf(" %d", &op);
			break;
		}

	} while (op != 99);
}
void showAllBooks(Book books[], int total) {

	int op = 50;
	int offset = 0;
	int step = 5;
	int i, j, k;
	int index;
	int pags;
	char txt_book[60];

	do {
		cls();
		printHeader(total);
		printLine("Show all books", 'L');
		printStarLine();
		if (total > (offset + step)){
			j = step;
		} else {
			if(total <= step)
				j = total;
			else
				j = total - offset;
		}
		k = 0;
		for(i = 0; i < j; i++, k++) {
			index = offset + i;
			sprintf(txt_book, "%d - %s by %s - %d pages", index, books[index].title, books[index].author, books[index].pages);

			printLine("", 'L');
			printLine(txt_book, 'L');
		}
		for(i = step; i > k; i--) {
			printLine("", 'L');
			printLine("", 'L');
		}

		printLine(" ", 'L');
		printLine("0 - First | 1 - Back || Next - 2 | Last - 3", 'C');
		printLine("99 - Back to menu", 'R');
		printStarLine();

		switch(op) {
		case 0:
			// First
			offset = 0;
			op = 50;
			break;
		case 1:
			if(offset >= step)
				offset -= step;
			op = 50;
			break;
		case 2:
			if(total > (offset + step)){
				offset += step;
			} else {
				pags = total % step;
				if(total > step)
					offset = total-pags;
				else
					offset = 0;
			}
			op = 50;
			break;
		case 3:
			// Last
			pags = total % step;
			if(total > step)
				offset = total-pags;
			else
				offset = 0;
			op = 50;
			printf("%d", pags);
			break;
		case 50:
		default:
			printf("Option: ");
			scanf("%d", &op);
			break;
		}
	} while (op != 99);
}
void populateBooks(Book books[]){

	strcpy(books[0].title,  "Seja Foda");
	strcpy(books[0].author, "Caio Carneiro");
	books[0].pages = 255;

	strcpy(books[1].title, "Termodinamica");
	strcpy(books[1].author, "Matheus A");
	books[1].pages = 120;

	strcpy(books[2].title, "A Garota no Gelo");
	strcpy(books[2].author, "Robert Brynoza");
	books[2].pages = 70;

	strcpy(books[3].title, "Eleanor e Park");
	strcpy(books[3].author, "Rainbow Rowell");
	books[3].pages = 364;

	strcpy(books[4].title, "O Homem de Giz");
	strcpy(books[4].author, "C.J. Tudor");
	books[4].pages = 240;

	strcpy(books[5].title, "O Acidente");
	strcpy(books[5].author, "Desconhecido");
	books[5].pages = 320;

	strcpy(books[6].title, "Rainbow");
	strcpy(books[6].author, "M.S. Fayes");
	books[6].pages = 99;
}

