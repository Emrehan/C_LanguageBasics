#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

void delay(double sec)
{
    clock_t start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < sec);       
}

int main(){
	int h,m,s;

	h=23;
	m=59;
	s=55;
	
	while(1==1){
		m += s/60;
		s%=60;
		
		h += m/60;
		m%=60;
		
		h%=24;
		
		printf("%d:%d:%d\n",h,m,s);
		delay(1);
		
		s++;
	}	
	
	return 0;
}
