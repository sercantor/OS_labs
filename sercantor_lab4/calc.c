#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {

 if(argc !=4){
   printf("Not a suitable number of program parameters\n");
   return(1);
 } 

    int result =0;

    switch(argv[2][0]){
    case '+':
	result = atoi(argv[1]) + atoi(argv[3]);
    break;
    
    case '-':
	result = atoi(argv[1]) - atoi(argv[3]);
    break;

    case 'x':
	result = atoi(argv[1]) * atoi(argv[3]);
    break;

    case '/':
	if(atoi(argv[3])!=0){
		result = atoi(argv[1]) / atoi(argv[3]);
	}
    break;
    
    default:
     printf("Wrong operation selected\n");
     return(1);
    }
    
    printf("%s %s %s is %d\n", argv[1], argv[2], argv[3], result);

    return 0;
}
