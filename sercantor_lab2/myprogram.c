#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "file1.h"
  
int main()
{
  FILE *fptr = fopen("temp.txt", "r"); // open file in read mode
  search_file(fptr);
  store_and_free(fptr);
  
  FILE *ptrReport = fopen("report.txt", "w");
  if (!ptrReport) {
    fprintf(stderr, "Error opening the temp file");
    return -1;
    }
    
  /*time on search_file*/
  clock_t t;
  t = clock();
  search_file(fptr);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  fprintf(ptrReport,"search_file took %f seconds to execute\n", time_taken);
  
  /*time on store_and_free*/
  clock_t p;
  p = clock();
  store_and_free(fptr);
  p = clock() - t;
  double time_taken2 = ((double)p)/CLOCKS_PER_SEC;
  fprintf(ptrReport,"store_and_free took %f seconds to execute\n", time_taken2);
  
  
  fclose(fptr);
  return 0;
  
}
