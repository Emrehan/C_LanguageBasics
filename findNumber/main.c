#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int isvalueinarray(int, int*, int);

// Verilen sayilarla verilen bir sayiya ulasilip ulasilamayacagini bulan program
int main(){
	
	srand(time(NULL));
	
	int numbers[8] = {1,3,5,7,9,11,13,15};
	int numbersCount = 8;
	
	int target = 30;
	
	int rands[3];
	int randsCount = 3;
	
	int maxIter = 1000000;
	int allowRepeatedRands = 0; 

	int a, sum , i, iter = 0;
	
	do{
		do {
			sum = 0;
			for(i=0; i<randsCount; i++){
				do{
					a = numbers[rand()%numbersCount];
				} while( isExist(a,rands,randsCount)!=(-1) && !allowRepeatedRands );
				rands[i] = a;
				
				sum += rands[i];
			}
		} while(sum!=target && (iter++)<maxIter);
		
		if(sum==target){
			printf("\n\nFound!\n");
		
			for(i=0; i<randsCount; i++){
				printf("%d ",rands[i]);
				i==(randsCount-1)?printf(" = "):printf(" + ");
			}
			printf("%d",sum);
		}else{
			printf("Maximum iteration reached.");
			printf("It's not possible to reach %d with %d of these numbers: ",target,numbersCount);
			for(i=0; i<numbersCount; i++){
				printf("%d ",numbers[i]);
			}
		}
		getchar();
	}while(1);
	
	return 0;
}

int isExist(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return i;
    }
    return -1;
}
