#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layout.h"
#include "database.h"


void printHeader(int total);
void printMenu();
int  addNewBook(Book books[], int *total);
void showAllBooks(Book books[], int total);

int main() {

   char * filename = "database.dat";
   FILE * database = initDatabase(filename);
	int op = 0;
	int total;
   int retCode = 0;
   Book * books2 = NULL;
   total = readDatabase(&books2,database);

	do{
		printMenu(total);
		printf("\nOption: ");
		scanf("%i", &op);

		switch(op){
		case 1:
			retCode = addNewBook(books2, &total);
         if(retCode){
            printf("Memory allocation failed\n");
            exit(1);
         }
			break;
		case 2:
			showAllBooks(books2, total);
			break;
		case 99:
		default:
			cls();
         /*
          * TODO: Do something with unsupported options
          */
         op = 99;
		}

	} while (op != 99);

   //Save to file at exit.
   //TODO: Check if data changed to see if rewriting the
   //database is needed.

   freopen(filename, "wb", database);
   writeDatabase(books2, (size_t)total, database);
   fclose(database);
   free(books2);
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
   int i;
	cls();
	printHeader(total);
	printLine("Main menu", 'L');
	printStarLine();
	printLine("", 'L');
	printLine("1. Add new book", 'L');
	printLine("", 'L');
	printLine("2. Show all books", 'L');
   for(i = 0; i < 8; i++){
      printLine("", 'L');
   }
	printLine("99 - Exit", 'R');
	printStarLine();
}


int addNewBook(Book * books, int *total) {

	int op = 50;
	char *title;
	char *author;
	int *pages;
	char txt_title[80];
	char txt_author[80];
	char txt_pages[80];
   int i;

	title = (char*)calloc(80,1);
	author = (char*)calloc(80,1);
	pages = (int*)calloc(1,sizeof(int));
   if( !(title && author && pages)){
      return 1;
   }
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
		for(i =0; i < 4; i++){
         printLine("", 'L');
      }
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
			strcpy((books+(*total))->title, title);
			strcpy((books+(*total))->author, author);
         (books+(*total))->pages = *pages;

			*total += 1;
			op = 50;
			break;
		case 50:
		default:
			printf("\nOption: ");
			scanf(" %d", &op);
			break;
		}

	} while (op != 99);
         free(title);
         free(author);
         free(pages);
   return 0;
}
void showAllBooks(struct Book * books, int total) {

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
			sprintf(txt_book, "%d - %s by %s - %d pages", index,
                 (books+index)->title, (books+index)->author,
                 (books+index)->pages);

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
			printf("\nOption: ");
			scanf("%d", &op);
			break;
		}
	} while (op != 99);
}
