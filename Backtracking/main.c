/*

	Emrehan ILHAN
	13011021
	
	Algoritma Analizi 3. Odev
*/


#include <stdio.h>
#include <string.h>
int writeAll=0;

//matrisi ekrana basar
void printMatris(int A[][8], int n){
	int i,j;
	
	printf("   ");
	for(i=0; i<n; i++){
		printf("%d ",i);
	}
	printf("\n");
	for(i=0; i<n; i++){
		printf("%d ",i);
		for(j=0; j<n; j++){
			printf("|%d",A[i][j]);
			if(j==n-1)
				printf("|");
		}
		printf("\n");
	}
	printf("\n");
}

//Bir satiri saga kaydirir
//satirin numarasini alir.
void shiftRow(int row, int shifted[], int A[][8], int n){
	int i,j, tmp;
	
	tmp = A[row][n-1];
	for(i=n-1; i>0; i--){
		A[row][i]=A[row][i-1];
	}
	A[row][0]=tmp;
	shifted[row]++;
}

void backtrack(int row, int shifted[], int A[][8], int n){	
	if( row==(n-1) && allDiff(n-1,A,n)==1){ //En alt satirdayken tum satirlar farkliysa sonuc bulundu
		if(writeAll==1){
			printMatris(A,n);
			printf("Bakilan satir %d\n",row);
		}
		printf("A Row %d\n",row);
		printf("Basarili\n");
	}else if(row==0 && shifted[0]==n-1){  //ilk satir n-1 kez shift edildiyse sonuc bulunamiyor
		printf("Basarisiz\n");
		printf("B Row %d\n",row);
	}else if(row!=0 && shifted[row]==n-1){ // ilk satir haric diger herhangi bir satir, n-1 kez shift edildiyse ust satira doner
		printf("C Row %d\n",row);
		if(writeAll==1){
			printMatris(A,n);
			printf("Bakilan satir %d\n",row);
		}
		shiftRow(row-1,shifted,A,n);
		backtrack(row-1,shifted,A,n);
	}else if(row!=n-1 && allDiff(row,A,n)==1){ //en ust satir haric diger herhangi bir satirin, ustundeki satirlarin hepsi farkliysa bir alt satira gecilir
		printf("D Row %d\n",row);
		if(writeAll==1){
			printMatris(A,n);
			printf("Bakilan satir %d\n",row);
		}
		backtrack(row+1,shifted,A,n);
	}else{
		printf("E Row %d\n",row);
		if(writeAll==1){
			printMatris(A,n);
			printf("Bakilan satir %d\n",row);
		}
		shiftRow(row,shifted,A,n);
		backtrack(row,shifted,A,n);
	}
}

//Verilen satirin, ustundeki satirlarla ortak elemani var mi diye bakar

// 0 => 1 2 3
// 1 => 2 3 1
// 2 => 1 3 2
// Bu örnekte row=1'se sonuc 1, row=2'yse sonuc 0
int allDiff(int row, int A[][8], int n){
	int i,j;
	
	if(row==0)
		return 1;
	
	for(i=1; i<(row+1); i++){
  		for(j=0; j<n; j++){
	    	if(A[row][j]==A[row-i][j]){
	      		return 0;
			}
    	}
    	printf("\n");
	}
  	return 1;
}

void flush(int shifted[], int A[][8]){
	int i,j;
	for(i=0; i<8; i++){
		for(j=0; j<8; j++){
			A[i][j]=-1;
		}
		shifted[i]=0;
	}
}

//printf("sari=1, mavi=2, yesil=3, mor=4, beyaz=5, siyah=6, kirmizi=7, gri=8\n");
int changeColor(char color[]){
	int i;
	
	if(strcmp(color, "sari")==0){
		return 1;
	}else if(strcmp(color, "mavi")==0){
		return 2;
	}else if(strcmp(color, "yesil")==0){
		return 3;
	}else if(strcmp(color, "mor")==0){
		return 4;
	}else if(strcmp(color, "beyaz")==0){
		return 5;
	}else if(strcmp(color, "siyah")==0){
		return 6;
	}else if(strcmp(color, "kirmizi")==0){
		return 7;
	}else if(strcmp(color, "gri")==0){
		return 8;
	}
}

int main(){
	int n;	  	// N
	int i, j; 	//iterasyon
	int A[8][8];//Renk matrisi
	char color[10];
	
	int shifted[8]; //Her bir satirin kac kez shift edildigini tutan matris
	
	flush(shifted,A);
	
	while(1){
		do{
			printf("N giriniz [3,8]\n");
			scanf("%d",&n);
		}while(n<3 || n>8);
		//n okundu
		
		printf("sari=1, mavi=2, yesil=3, mor=4, beyaz=5, siyah=6, kirmizi=7, gri=8\n");
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				printf("A[%d][%d]=",i,j);
				scanf("%s",&color);
				A[i][j]=changeColor(color);
				printf("A[%d][%d]=> %d\n",i,j,A[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
		//Matris okundu
		
		printMatris(A,n);
		
		printf("Tum ara adimlar\nyazdirilsin mi? (1/0)\n");
		scanf("%d",&writeAll);
		
		//Ilk satiri atlayip 2. satirdan basliyoruz. 
		backtrack(1,shifted,A,n);
		
		printf("________________________________________ \n");
		printf("Sonuc ____________________________________\n\n");
		printMatris(A,n);
		
		printf("\nDevam etmek icin herhangi bir tusa basin\n");
		getch();
		flush(shifted,A);
		system("cls");
	}
	
	return 0;	
}
