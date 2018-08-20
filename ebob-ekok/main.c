#include <stdio.h>

int ebob(int a, int b){
	if(a<b){
		ebob(b,a);
	}
	if(a%b==0){
		return b;
	}
	ebob(b,a%b);
}

int ekok(int a, int b){
	return (a*b)/ebob(a,b);
}

int main(){
	printf("EBOB = %d\n",ebob(3,4));
	printf("EKOK = %d\n",ekok(3,4));
	
	return 0;
}
