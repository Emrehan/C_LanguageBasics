// Emrehan ILHAN 13011021 - Algoritma Analizi 2. Ödev

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define TESTSIZE 95

#define HASHSIZE 267569
#define DICTIONARYSIZE 133780


#define CHANGE 2
#define DELETE 1
#define INSERT 1

#define HASHWORD 50
#define MINRESULT 4

#define TESTOUT "testout.txt"

#define DEBUG 0

struct HASH{
	char word[HASHWORD];
	int isEmpty; // 0&1
}HASH[HASHSIZE];

//Hash struct yapisini sifirlar.
void initHash(){
	int i;
	for(i=0; i<HASHSIZE; i++){
		HASH[i].isEmpty=1;
		strcpy(HASH[i].word,"");
	}
}

//Hash bellege alinmis mi kontrol eder
int hashIsSet(){
	int i;
	
	for(i=0; i<HASHSIZE; i++){
		if(HASH[i].isEmpty==0){
			return 1;
		}
	}	
	return 0;
}

//Olusan hash yapisini yazdirir.
void printHash(){
	int i;
	for(i=0; i<HASHSIZE; i++){
		if(HASH[i].isEmpty==1){
			printf("%d=> EMPTY", i);
		}else{
			printf("%d=> %s",i,HASH[i].word);
		}
		printf("\n");
	}
}

//Dosya adini okuyan fonksiyon, sureyi kisaltmak icin direk default degeri donduruyor
int readFile(char name[], char info[], char defaultName[]){
	strcpy(name,defaultName);
	return 0;
	int devam;
	printf("%s\n\n",info);
	printf("Dosya adi varsayilan (%s) olarak devam etmek ister misiniz?\n",name);
	printf("Evet = 1 / Hayir = 0\n");
	scanf("%d",&devam);
	if(devam==0) {
		printf("\nDosya adini giriniz. \n=");
		scanf("%s",name);
	}
	printf("Kullanilan dosya adi = |%s|\n\n",name);
}

int hashId(char word[]){
	int i, addr=0;
	for(i=0; i<strlen(word); i++){
		addr += word[i]*26*i;
	}
	addr = addr % HASHSIZE;
	return addr;
}

int calculateHashId(char word[]){
	int i;
	int addr=0;
	
	addr=hashId(word);
	
	//printf("Hash'e gelen kelime |%s|, ilk adres %d\n",word,addr);
	while(HASH[addr].isEmpty==0){
		addr++;
		addr = addr % HASHSIZE;
	}
	//printf("Hash'e gelen kelime |%s|, son adres %d\n",word,addr);
	
	return addr;
}

void toLowerCase(char word[]){
	int i;
	
	for(i=0; i<strlen(word); i++){
		if(word[i]>'A' && word[i]<'Z'){
			word[i]=word[i]+'a'-'A';
		}
	}
}

//dict.txt isimli dosyadan hash yapisini olusturur ve hash.txt yazar
int createHash(){
	char dictionaryName[50];
	char hashName[50];
	char tmp[50];
	int count=0;
	int i;
	int addr;
	
	readFile(dictionaryName,"Kelimelerin okunacagi sozlugun adresini giriniz","dict.txt");
	readFile(hashName,"Hash'in yazilacagi adresi giriniz","hash.txt");
	
	FILE *fpr=fopen(dictionaryName,"r");
	FILE *fpw=fopen(hashName,"w");
	if(!fpr || !fpw) {
		printf("Error!");
		return -1;
	}

	for(i=0; i<DICTIONARYSIZE; i++){
		fscanf(fpr,"%s",tmp);
		toLowerCase(tmp);
		strlwr(tmp);
		addr=calculateHashId(tmp);
		
		HASH[addr].isEmpty=0;
		strcpy(HASH[addr].word,tmp);
	
		printf("%s %d\n",tmp,strlen(tmp));
		count++;
	}
	fclose(fpr);
	
	for(i=0; i<HASHSIZE; i++){
		fprintf(fpw,"%s\n",(HASH[i].isEmpty==0)?HASH[i].word:"-");
	}
	fclose(fpw);
	
	printf("%d adet kelime hash tablosuna yerlestirildi ve %s isimli dosyaya yazildi. Devam etmek icin bir tusa basin.",count,hashName);
	getch();
	system("cls");
}

//createHash fonksiyonunun olusturdugu dosyadan hash yapisini okuyan fonksiyon.
int readHashFromFile(){
	char hashFileName[50];
	char tmp[50];
	int i;
	int addr;
	
	readFile(hashFileName,"Hash'in okunacagi dosyanin adresini giriniz","hash.txt");
	
	FILE *fp=fopen(hashFileName,"r");
	if(!fp) {
		printf("Error!");
		return -1;
	}

	for(i=0; i<HASHSIZE; i++){
		fscanf(fp,"%s",tmp);
		strlwr(tmp);
		toLowerCase(tmp);
		
		if(tmp[0]!='-'){
			HASH[i].isEmpty=0;
			strcpy(HASH[i].word,tmp);
			printf("%s\n",tmp);
		}
	}
	
	printf("%d adet kelime hash tablosuna yerlestirildi. Devam etmek icin bir tusa basin.",HASHSIZE);
	getch();
	system("cls");
	
	fclose(fp);
}

//Bir kelimeyi bir dosyanin sonuna yazmayi saglayan fonksiyon
int appendFile( char text[]){
	FILE *fp=fopen(TESTOUT,"a");
	if(!fp){
			printf("Error append file\n");
			return -1;
		}

	fprintf(fp,"%s",text);
	
	fclose(fp);
	return 0;
}

//Verilen kelimeyi sozlukteki tum kelimelerle karsilastirir, distance sonucunu bir threshold degeriyle kontrol eder.
void findWord(char manuel[], int useManuel, char fileName[]){
	char target[20];
	int addr;
	int devam=1;
	int i;
	
	while(devam==1){
		char string[50];
		int step=0;
		if(useManuel==0){
			printf("Aranan kelimeyi giriniz\n");
			scanf("%s",target);
		}else{
			strcpy(target,manuel);
		}
		
		addr = hashId(target);
		step++;
		
		if(strcmp(HASH[addr].word,target)==0){
			if(DEBUG==1) printf("<%s> OK  (%d.adreste, %d adimda)\n",HASH[addr].word,addr,step);
			sprintf(string,"<%s> OK\n",HASH[addr].word);
			printf("<%s> OK\n",HASH[addr].word);
			if(useManuel==1) appendFile(string);
		}else if(HASH[addr].isEmpty==0){
			while(HASH[addr].isEmpty==0 && strcmp(HASH[addr].word,target)!=0 && (step-1)<HASHSIZE){
				addr++;
				addr%=HASHSIZE;
				step++;
			}
			if(strcmp(HASH[addr].word,target)==0){
				sprintf(string,"<%s> OK\n",HASH[addr].word);
				printf("<%s> OK\n",HASH[addr].word);
				if(useManuel==1) appendFile(string);
				
				//printf("<%s> OK  (%d.adreste, %d adimda)\n",HASH[addr].word,addr,step);
			}
		}
		if(strcmp(HASH[addr].word,target)!=0){
			int min=100,result=-1, minI=-1;
			for(i=0; i<HASHSIZE; i++){
				if(HASH[i].isEmpty==0){
					if(DEBUG==1) printf("HASH <%s> ve <%s> gonderildi\n",target,HASH[i].word);
					result=levenshtein_distance(target,HASH[i].word,0,"",0);
					if(DEBUG==1) printf("%s sonuc=>%d\n",HASH[i].word,result);
					if(result<min){
						if(DEBUG==1) printf("result(%d)<min(%d) yeni minI %d\n",result,min,i);
						min=result;
						minI=i;
					}
				}
			}
			if(DEBUG==1) printf("fordan cikti\n");
			if(DEBUG==1) printf("min %d minresult %d\n",min,MINRESULT);
			if(min<MINRESULT){
				if(DEBUG==1) printf("min<MINRESUlT\n",min);
				if(DEBUG==1) printf("%s tekrar minI=%d\n",HASH[minI].word,minI);
				levenshtein_distance(target,HASH[minI].word,1,fileName,1);
			}else{
				sprintf(string,"<%s> NONE\n",target);
				if(useManuel==1){
					appendFile(string);
				} 
			}
			printf("%s",string);
		}
		
		if(useManuel==0){
			printf("Devam(1) / Bitir(0)\n");
			scanf("%d",&devam);
			system("cls");
		}else{
			devam=0;
		}
	}
}

//distance matrisini sifirlayan fonksiyon
void initDistance(int matrix[][HASHWORD]){
	int i,j;
	for(i=0; i<HASHWORD; i++){
		for(j=0; j<HASHWORD; j++){
			matrix[i][j]=0;
		}
	}
	
	for(i=0; i<HASHWORD; i++){
		matrix[0][i]=i;	
	}
	for(i=0; i<HASHWORD; i++){
		matrix[i][0]=i;	
	}
}

int min3(int a, int b, int c){
	return (a<b)?((a<c)?a:c):((b<c)?b:c);
}

//Backtrack eksik
void backtrack(int distance[][HASHWORD],char wrong[], char right[], int isBest,char fileName[], int useManuel){
	char result[50];
	
	if(isBest==1){
		sprintf(result,"<%s>  <%s> \n",wrong,right);
		if(useManuel==1) appendFile(result);
		printf("%s",result);
	}
}

//distance matrisini olusturan fonksiyon
//Eger isBest==1 ise ayrica backtrack yapar
int levenshtein_distance(char w1[], char w2[], int isBest, char fileName[], int useManuel){
	if(DEBUG==1) printf("leven w1 w2 isbest filename usemanuel\n%s %s %d %s %d\n",w1,w2,isBest,fileName,useManuel);
	int distance[HASHWORD][HASHWORD];
	int i,j;
	initDistance(distance);
	
	for(i=1; i<strlen(w2)+1;i++){
		for(j=1; j<strlen(w1)+1; j++){
			if(w1[j-1]==w2[i-1]){
				distance[i][j]=distance[i-1][j-1];
			}else{
				distance[i][j]=(min3(
										distance[i-1][j]+DELETE,
										distance[i][j-1]+INSERT,
										distance[i-1][j-1]+CHANGE
									)
								);
			}
		}
	}
	
	if(isBest==1){
		backtrack(distance,w1,w2,isBest,fileName,useManuel);	
	}
	
	if(DEBUG==1) printf("leven kelime %s %s sonuc %d\n",w1,w2,distance[strlen(w2)][strlen(w1)]);
	return distance[strlen(w2)][strlen(w1)];
}

//test.txt dosyasindan kelime okuyup sözlükte arayip, sonucu testout.txt yazan fonksiyon
int findWordFromFile(){
	char rfileName[50]="test.txt";
	char wfileName[50]="testout.txt";
	int i;
	
	FILE *fpr=fopen(rfileName,"r");
	if(!fpr) {
		printf("Error!");
		return -1;
	}

	for(i=0; i<TESTSIZE; i++){
		char tmp[50];
		fscanf(fpr,"%s",tmp);
		toLowerCase(tmp);
		strlwr(tmp);
		
		findWord(tmp,1,"testout.txt");
	}
	fclose(fpr);
}

//Edit distance'i ayri bir fonksiyon olarak denemek icin
void editDistance(){
	char w1[50], w2[50];
	int i,j;
	
	printf("Birinci kelimeyi girin\n");
	scanf("%s",w1);
	
	printf("Ikinci kelimeyi girin\n");
	scanf("%s",w2);
	
	int distance[HASHWORD][HASHWORD];
	initDistance(distance);
	
	for(i=1; i<strlen(w2)+1;i++){
		for(j=1; j<strlen(w1)+1; j++){
			//printf("Bakilan %c ve %c  => ",w1[j-1],w2[i-1]);
			if(w1[j-1]==w2[i-1]){
				distance[i][j]=distance[i-1][j-1];
				//printf("ayni d[%d][%d]<=%d\n",i,j,distance[i-1][j-1]);
			}else{
				distance[i][j]=(min3(distance[i-1][j],distance[i][j-1],distance[i-1][j-1])+1);
				//printf("farkli d[%d][%d]<=%d\n",i,j,(min3(distance[i-1][j],distance[i][j-1],distance[i-1][j-1])+1));
			}
		}
	}
	
	printf("\nSonuc = %d\n\nSonuc matrisi\n",distance[strlen(w2)][strlen(w1)]);
	
	for(i=0; i<strlen(w2)+1; i++){
		for(j=0; j<strlen(w1)+1; j++){
			printf("%d ",distance[i][j]);
		}
		printf("\n");
	}
	
	printf("Devam etmek icin bir tusa basin.",HASHSIZE);
	getch();
	system("cls");
	
	
}

//Menu isleri icin kullanilan fonksiyon
int menu(){
	int menu=0;
	char c;
	int maxMenu=5;
	int devam=1;
	char space[]= "                              ";
	while(devam==1){
		printf("%s",space);printf("Did You Mean???\n\n");
		
		printf("%s",space);printf("W/S, E for Enter\n");
		printf("%s",space);if(hashIsSet()==1)printf("Hash mevcut\n\n");else printf("Hash mevcut degil\n\n");
		printf("%s",space);if(menu==0)printf("=>");else printf("  "); printf("Hash Olustur\n");
		printf("%s",space);if(menu==1)printf("=>");else printf("  "); printf("Dosyadan Hash Oku\n");
		printf("%s",space);if(menu==2)printf("=>");else printf("  "); if(hashIsSet()==1) printf("Hash Tablosu\n"); else printf("Hash Tablosu(Once Hashleme gerekiyor)\n");
		printf("%s",space);if(menu==3)printf("=>");else printf("  "); if(hashIsSet()==1) printf("Dosyadan Kelime Bul\n"); else printf("Dosyadan Kelime Bul(Once Hashleme gerekiyor)\n");
		printf("%s",space);if(menu==4)printf("=>");else printf("  "); if(hashIsSet()==1) printf("Kelime Bul\n"); else printf("Kelime Bul(Once Hashleme gerekiyor)\n");
		printf("%s",space);if(menu==5)printf("=>");else printf("  "); printf("Edit Distance(Demo)\n");
		printf("%s",space);if(menu==6)printf("=>");else printf("  "); printf("Cikis\n");
		c=getch();
		
		system("cls");
		
		if(c=='w' || c==72){
			menu--;
			menu=menu<0?maxMenu:menu;
		}else if(c=='s' || c==80){
			menu++;
			menu=menu>maxMenu?0:menu;
		}
		
		if(c=='e'){
			return menu;
		}
	}
}

int main(){
	initHash();
	int menuDonen;
	
	do {
		menuDonen = menu();
	
		if(menuDonen==0) createHash();
		if(menuDonen==1) readHashFromFile();
		if(menuDonen==2) printHash();
		if(menuDonen==3) findWordFromFile();
		if(menuDonen==4) findWord("",0,"");
		if(menuDonen==5) editDistance();
	} while(menuDonen!=6);
	printf("Cikis yaptiniz.");
	
	return 0;
}
