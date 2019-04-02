#include <stdio.h>
#include <stdlib.h>

int main()
{
  //putting some stuff in the array
  int *ap;
  ap = malloc(9500000*sizeof(int));
  if(ap){
    printf("%zu, bytes allocated", 9500000*sizeof(int));
    for(int i = 0; i <= 9500000; i++){
      ap[i] = i+2;
    }
  }
  
  free(ap); //done with ap
  return 0;
}
