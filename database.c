#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "database.h"


int writeDatabase(struct Book * dataPtr, size_t size, FILE * file)
{
   fwrite(&size, sizeof(size_t), 1, file);
   fwrite(dataPtr, sizeof(struct Book), size, file);
   return 0;
}

/*
 * Function allocates twice the needed memory so there is no
 * need for instant reallocation when adding new entries.
 */
int readDatabase(struct Book ** dataPtr, FILE * file)
{
   size_t numberOfEntries;
   fseek(file, 0, SEEK_SET);
   fread(&numberOfEntries, sizeof(size_t), 1, file);
   *dataPtr = calloc(2 * numberOfEntries, sizeof(struct Book));
   fread(*dataPtr, sizeof(struct Book), numberOfEntries, file);
   return numberOfEntries;
}

int addEntry(struct Book * books, int * total)
{
   //TODO: This function should only insert data into the array
   //separate function should get user input.
   printf("Title: ");
   scanf(" %[^\n]", (books+(*total))->title);
   printf("Author: ");
   scanf(" %[^\n]", (books+(*total))->author);
   printf("Pages: ");
   scanf(" %d", &((books+(*total))->pages));
   *total = *total + 1;
   return 0;
}

void populate(struct Book * books2)
{
   int pag[7] = {255, 120, 70,364,240,320,99};
   char auts[7][80] = { "Caio Carneiro", "Matheus A", "Robert Brynoza",
                        "Rainbow Rowell", "C.J Tudor", "Desconhecido",
                        "M.S. Fayes"};
   char titl[7][80] = { "Seja Foda", "Termodinamica", "A Garota no Gelo",
                        "Eleanor e Park", "O Homem de Giz", "O Acidente",
                        "Rainbow"};

   for(int i = 0; i < 7; i++){
      strcpy((books2+i)->title,titl[i]);
      strcpy((books2+i)->author,auts[i]);
      (books2+i)->pages = pag[i];
   }
}


FILE * initDatabase(char * filename)
{
   FILE * file;
   file = fopen(filename, "rb+");
   /*
    * TODO: Add initialization of an empty database file
    * if file does not exist. For now just create database
    * with example entries.
    */
   if(!file){
      file = fopen(filename, "ab+");
      struct Book * books = malloc(7*sizeof(struct Book));
      populate(books);
      writeDatabase(books, 7, file);
      free(books);
   }
   return file;
}

