// Verilen biti 1 yapma ZCT

#include <stdio.h>

int bit_1le(int a,int x){
	int number = a;
	
	number&=~(1 << x); 
	
	return number;
}

int main(){
	
	// 5= 0 1 0 1
	
	printf("%d",bit_1le(5,2));
	
	return 0;
}
