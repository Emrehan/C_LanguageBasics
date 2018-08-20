#include <stdio.h>

int main () {
	int i,j,a=0,option=0;

	printf("1) CHAR -> ASCII\n2) ASCII -> CHAR\n");
	option=getch();
	
	if (option == '1') {
		while (a != 27) {
		printf("CHAR -> ASCII\n");
			a=getch();
	  		printf("%c   ====   %d\n",(char*)a,a);
	  		if(a==27) {
	  			printf("Exit");
			  }
		}
	} else if (option == '2') {
		printf("ASCII -> CHAR\n");
		while (a != 27) {
			a=getch();
	  		printf("%d   ====   %c\n",(int*)a,(char*)a);
	  		if(a==27) {
	  			printf("Exit");
			  }
		}
	}
		
	
	
	return 0;
}
