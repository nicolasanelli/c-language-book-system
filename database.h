#ifndef DATABASE_H
#define DATABASE_H

typedef struct Book {
   char title[80];
   char author[80];
   int pages;
}Book;

FILE * initDatabase(char * filename);
int writeDatabase(struct Book * dataPtr, size_t size, FILE * file);
int readDatabase(struct Book ** dataPtr, FILE * file);
void populate(struct Book * books2);
int addEntry(struct Book * books, int * total);

#endif /* DATABASE_H */
