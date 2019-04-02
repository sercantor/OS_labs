#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file1.h"
#define MAXCHARS 500
#define MAXLINES 1000

int search_file(FILE *fptr)
{
  const char* command = "sudo find / -iname 'manjaro' | tee temp.txt"; // stores output in temp
  system(command); // exec the command
 /*if file doesn't exist, quit*/
  if (!fptr) {
    fprintf(stderr, "Error opening the temp file");
    return -1;
    }
  return 0;
}

void store_and_free(FILE *fptr)
{
  /*pointer that points to the line count*/  
  char *lptr;
  char content[MAXCHARS];
  char *lineptr[MAXLINES];

  unsigned len = 0;
  int nlines = 0;

  while((fgets(content,MAXCHARS,fptr)) != NULL) {
    len = strlen(content);
    /*setting the end char to null, if you don't do this, 
    the last character will be randomly allocated*/
    content[len-1] = '\0';
    /*allocating for the line pointer, and strcpying it to content, so that it gets stored*/
    lptr = (char*) malloc(len*sizeof(char));
    strcpy(lptr, content);
    lineptr[nlines++] = lptr;
  }
  
  printf("-----------------------------------------\n");

    //printing the stored lines.
    for(int i = 0; i<nlines; i++)
      printf("%s\n", lineptr[i]);

    //freeing the memory that we allocated.
    for(int i = 0; i < nlines; i++)
      free(lineptr[i]);

}
