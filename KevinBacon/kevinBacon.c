//Kevin_Bacon
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


#define BUFF_SIZE 20000
#define NAME_SIZE 70
#define MOVIE_ARRAY_SIZE 4530
#define DETAIL_SIZE 1500
#define HASH_SIZE 244003
#define QUEUE_SIZE 250000

typedef struct Actor {
	char name[NAME_SIZE];
	int hashCode;
	int lenght;
	int isVisited;
	int parent;
} Actor;

typedef struct Movie {
	char name[NAME_SIZE];
	int actors[DETAIL_SIZE];
	int actor_size;
	int isVisited;
	int parent;
} Movie;

struct Actor hashArray[HASH_SIZE];
struct Movie movie[MOVIE_ARRAY_SIZE];

void createHash() {
	int i;
	for(i=0; i<HASH_SIZE; i++) {
		hashArray[i].hashCode=-1;
		hashArray[i].isVisited=-1;
		hashArray[i].lenght=-1;
		hashArray[i].name[0]='\0';
		hashArray[i].parent=-1;
	}
}

int hashingCode(int x) {
	return (x)%HASH_SIZE;
}

int cmpString(char n1[], int s1, char n2[], int s2){
	int i;
	if(s1!=s2){
		return -1;
	}
	for(i=0; i<s1; i++){
		if(n1[i]!=n2[i]){
			return 1;
		}
	}
	return 0;
}

int search(char name[], int hashCode, int lenght) {
	int i=hashingCode(hashCode);
	while(hashArray[i].lenght!=-1) {
		if(/*strcmp(hashArray[i].name,name)==0*/ cmpString(hashArray[i].name,hashArray[i].lenght,name,lenght)==0 ) {
			return i;
		}
		i++;
		i%=HASH_SIZE;
	}
	return -1;
}

int insert(char name[], int lenght, int hashCode) {
	int i=hashingCode(hashCode);
	while(hashArray[i].lenght!=-1) {
		i++;
		i%=HASH_SIZE;
	}
	hashArray[i].hashCode=hashCode;
	hashArray[i].isVisited=0;
	hashArray[i].parent=-1;
	hashArray[i].lenght=lenght;
	strcpy(hashArray[i].name,name);
	return i;
}

void display() {
	int i = 0;

	for(i = 0; i<HASH_SIZE; i++) {

		if(hashArray[i].name != NULL){
			printf("%d=>",i);
			puts(hashArray[i].name);
		}else{
			printf(" ~~ ");
		}	
	}

	printf("\n");
}

int harfSay(char name[], int n) {
	int i,toplam;
	for(i=0; i<n; i++) {
		toplam*=name[i];
	}
	return toplam;
}

/*
int intArray[QUEUE_SIZE];
int front = 0;
int rear = -1;
int itemCount = 0;

bool isEmpty() {
	return itemCount == 0;
}

void enQ(int data) {
	if(rear == QUEUE_SIZE-1) {
		rear = -1;
	}

	intArray[++rear] = data;
	itemCount++;
}

int deQ() {
	int data = intArray[front++];

	if(front == QUEUE_SIZE) {
		front = 0;
	}

	itemCount--;
	return data;
}

void bfs(int movieCounter,int actorCounter) {
	int i,onTmp;

}*/

void flushString(char string[], int n, char x) {
	int i;
	for(i=0; i<n; i++) {
		string[i]=x;
	}
}
void dosya_adi(char name[]){
	int devam;
	strcpy(name,"cast.rated.txt");
	printf("Dosya adi = %s\n",name);
	printf("Devam = 1 / Degistir = 0\n");
	scanf("%d",&devam);
	if(devam==0){
		printf("\nDosya adi? \n=");
		scanf("%s",name);
	}
}

int fileRead(int *movieCounter, int *actorCounter) {
	int i=0, aC=0, mC=0,j=0,code,searchResult,aCWo=0;
	char fileName[150];
	dosya_adi(fileName);
	FILE *fp=fopen(fileName,"r");
	if(!fp) {
		printf("Error!");
		return -1;
	}

	char buff[BUFF_SIZE];
	char tmpName[NAME_SIZE];

	for(i=0; i<MOVIE_ARRAY_SIZE; i++) {
		for(j=0; j<DETAIL_SIZE; j++) {
			movie[i].actors[j]=-1;
		}
	}

	flushString(tmpName,NAME_SIZE,'\0');
	while(!feof(fp)) {
		flushString(buff,BUFF_SIZE,'\0');

		fgets(buff, BUFF_SIZE, fp);
		//film adi basla
		//printf("------------------");
		i=0;
		while(buff[i]!='/') {
			movie[mC].name[i]=buff[i];
			//printf("%c",movie[mC].name[i]);

			i++;
		}
		i++;
		//printf("------------------\n");
		//film adi bitis
		//oyuncu basla
		while(buff[i]!='\0') {
			if(buff[i]!='/') {
				tmpName[j++]=buff[i++];
			} else {				
				movie[mC].actor_size++;
				aCWo++;
				//puts(tmp->name);
				//printf("\nUzunlugu=%d,HarfToplam=%d\n",tmp->lenght,tmp->harfToplam);
				code=harfSay(tmpName,j);
				searchResult=search(tmpName, code, j);
				if(searchResult==-1) {
					//printf("HASH EKLENDI(NO:%d) => ",aC);
					//puts(tmpName);
					//printf("\n");
					movie[mC].actors[ (movie[mC].actor_size)-1]=insert(tmpName,j,code);
					aC++;
				} else {
					movie[mC].actors[ (movie[mC].actor_size)-1]=searchResult;
				}
				flushString(tmpName,NAME_SIZE,'\0');
				j=0;
				i++;
			}

		}

		/*BIR EKSIK VERI
		*/
		movie[mC].actor_size++;
		aCWo++;
		if(search(tmpName, harfSay(tmpName,j), j)==-1) {
			//printf("HASH EKLENDI(NO:%d) => ",aC);
			//puts(tmpName);
			//printf("\n");
			insert(tmpName,j,harfSay(tmpName,j));
			aC++;
		}
		mC++;
	}
	close(fp);

	printf("Hashsiz oyuncu sayisi = %d\n",aCWo);

	*actorCounter=aC;
	*movieCounter=mC;

	return 0;
}

int main(int argc, char *argv[]) {
	createHash();
	//hashArray=(struct actor*) malloc (HASH_SIZE * sizeof(struct actor));
	int movieCounter=0;
	int actorCounter=0;
	int i;

	fileRead(&movieCounter,&actorCounter);

	
	printf("Actor sayisi = %d\n",actorCounter);
	printf("Movie sayisi = %d\n",movieCounter);
	

	return 0;
}
