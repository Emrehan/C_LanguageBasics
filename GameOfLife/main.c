#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


void delay(double sec) { // Delay fonksiyonunu kullanmak için gereken fonksiyon
	clock_t start = clock();
	while ((clock() - start) / CLOCKS_PER_SEC < sec);
}

void count(int n) {
	int i,j=n;
	for(i=0; i<n; i++) {
		printf("%d ",j--);
		delay(1);
	}
	printf("\n");
	system("cls");
}

void life_print(char life[][15]){
	int i,j;
	
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			printf("| %c ",life[i][j]);
		}
		printf("|\n");
	}
}

void create_life(char life[][15],int number_of_living){
	int i,j,x,y;
	
	for(i=0; i<number_of_living; i++){
		x=rand()%13+1;
		y=rand()%13+1;
		while(life[x][y]!='-'){
			x=rand()%13+1;
			y=rand()%13+1;
		}
		life[x][y]='x';
	}
}

int komsu_sayisi(char life[][15], int x, int y){
	int i,j,komsu_sayisi=0;
	
	if(life[x-1][y-1]=='x') komsu_sayisi++;
	if(life[x-1][y]=='x') komsu_sayisi++;
	if(life[x-1][y+1]=='x') komsu_sayisi++;
	
	if(life[x+1][y-1]=='x') komsu_sayisi++;
	if(life[x+1][y]=='x') komsu_sayisi++;
	if(life[x+1][y+1]=='x') komsu_sayisi++;
	
	if(life[x][y-1]=='x') komsu_sayisi++;
	if(life[x][y+1]=='x') komsu_sayisi++;
	
	return komsu_sayisi;
}

int live(char life[][15], char prev[][15]){
	int komsu, yasam=0;
	int i,j;
	
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			prev[i][j]=life[i][j];	
		}
	}
	
	for(i=1; i<14; i++){
		for(j=1; j<14; j++){
			if(prev[i][j]=='x'){
				komsu=komsu_sayisi(prev,i,j);
				if(komsu==0 || komsu==1 || komsu>3){
					life[i][j]='o';
					yasam--;
				}
			}else if(prev[i][j]=='o'){
				life[i][j]='-';
			}else if(prev[i][j]=='-'){
				komsu=komsu_sayisi(prev,i,j);
				if(komsu==3){
					life[i][j]='x';
					yasam++;
				}
			}
		}
	}
	return yasam;
}

int degisim(char life[][15], char prev[][15]){
	int i,j;
	
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			if(life[i][j]!=prev[i][j]){
				return 1;	
			}
		}
	}
	return 0;
}

int main(){
	srand(time(NULL));
	
	char life[15][15];
	char prev[15][15];
	int i,j,start_living,day=0,number_of_living=0,max_day,degisti=1,number_of_living_yesterday=0;
	
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			life[i][j]='-';
			prev[i][j]='-';
		}
	}
	
	do{
		printf("Baslangicta kac yasayan canli olsun?(Max 169 , Min 1)\n");
		scanf("%d",&start_living);
	}while(start_living>169 || start_living<=0);
	number_of_living+=start_living;
	
	printf("Maximum gun sayisi?\n");
	scanf("%d",&max_day);
	
	create_life(life,start_living);
	life_print(life);
	
	
	while(number_of_living!=0 && degisti==1 && day<=max_day){
		count(3);
		printf("%d. Gun - Yasayan sayisi = %d\n-------------------------------------\n",day+1,number_of_living);
		life_print(life);
		
		printf("Dunku durum - Dun Yasayan sayisi %d\n",number_of_living_yesterday);
		life_print(prev);
		
		number_of_living_yesterday = number_of_living;
		number_of_living+=live(life,prev);
		day++;
		
		degisti=degisim(life,prev);
	}
	
	count(3);
	life_print(life);
	
	if(number_of_living==0){
		printf("Yasayan canli kalmadi. ");
	}else if(day>=max_day){
		printf("Maximum gun sayisi gecti. ");
	}else{
		printf("Canlilar artik degismiyor. Yasayan sayisi = %d",number_of_living);
	}
	printf("Gun = %d\n",day);
	
	return 0;
}
