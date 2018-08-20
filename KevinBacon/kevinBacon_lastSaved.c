//Kevin_Bacon
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define BUFF_SIZE 20000
#define NAME_SIZE 200
#define MOVIE_ARRAY_SIZE 5000
#define ACTOR_ARRAY_SIZE 220000
#define DETAIL_SIZE 1500
#define HASH_SIZE 244003

struct actor {
	char name[150];
	int harfToplam;
	int lenght;
} actor;

struct mov {
	char name[NAME_SIZE];
	int actors[DETAIL_SIZE];
	int isVisited;
} movie[MOVIE_ARRAY_SIZE];

struct actor *hashArray[HASH_SIZE];
struct actor *tmp;

int hashCode(struct actor x) {
	return (x.harfToplam)%HASH_SIZE;
}

struct actor *search(struct actor *x) {
	int i=hashCode(*x);
	while(hashArray[i]!=NULL) {
		if( strcmp(hashArray[i]->name,x->name)==0 ) {
			return hashArray[i];
		}
		i++;
		i%=HASH_SIZE;
	}
	return NULL;
}

void insert(struct actor *x) {
	int i=hashCode(*x);
	while(hashArray[i]!=NULL) {
		i++;
		i%=HASH_SIZE;
	}
	hashArray[i]=x;
}

void display() {
	int i = 0;

	for(i = 0; i<HASH_SIZE; i++) {

		if(hashArray[i] != NULL)
			puts(hashArray[i]->name);
		else
			printf(" ~~ ");
	}

	printf("\n");
}

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
}

int harfSay(char name[], int n) {
	int i,toplam;
	for(i=0; i<n; i++) {
		toplam+=name[i];
	}
	return toplam;
}

/*
int front = 0;
int rear = -1;
int itemCount = 0;


struct qStructs{
	int onV;
	int isAct;
} queue[MAX_ARRAY_SIZE];

int isEmpty() {
   return (itemCount == 0)?1:0;
}

void enqueue(struct qStructs data) {
    if(rear == MAX_ARRAY_SIZE-1) {
       rear = -1;
    }
    queue[++rear] = data;
    itemCount++;
}

struct qStructs dequeue() {
   struct qStructs data = queue[front++];

   if(front == MAX_ARRAY_SIZE) {
      front = 0;
   }

   itemCount--;
   return data;
}
*/



/*void bfs(int movieCounter,int actorCounter){
	int i,isitEmpty;
	struct qStructs onTmp;
	struct qStructs tmp2;

	onTmp.isAct=1;
	onTmp.onV=0;

	enqueue(onTmp);

	isitEmpty=0;
	while(isitEmpty==0){
		onTmp=dequeue();

		if(onTmp.isAct==1){
			printf("AKTOR %d\n",onTmp.onV);
		}else{
			printf("FILM %d\n",onTmp.onV);
		}

		if(onTmp.isAct==1){
			aIs[onTmp.onV]=1;
		}else{
			mIs[onTmp.onV]=1;
		}

		for(i=0;  i< (((onTmp.isAct)==1)?4:7) ; i++){
			if(onTmp.isAct==1){
				if(riley[onTmp.onV][i]==1 && mIs[i]!=1){
					tmp2.isAct=onTmp.isAct;
					tmp2.onV=i;
					enqueue(tmp2);
					mIs[i]=1;
				}
			}else{
				if(riley[i][onTmp.onV]==1 && aIs[i]!=1){
					tmp2.isAct=onTmp.isAct;
					tmp2.onV=i;
					enqueue(tmp2);
					aIs[i]=1;
				}
			}
		}
		isitEmpty=isEmpty();
	}
}*/
void flushString(char string[], int n) {
	int i;
	for(i=0; i<n; i++) {
		string[i]='\0';
	}
}

int fileRead(int *movieCounter, int *actorCounter) {
	int i=0, aC=0, mC=0,j;
	struct actor *tmp = (struct actor*) malloc(sizeof(struct actor));
	FILE *fp=fopen("cast.rated.txt","r");
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


	while(!feof(fp)) {
		flushString(buff,BUFF_SIZE);
		flushString(tmpName,NAME_SIZE);
		fgets(buff, BUFF_SIZE, fp);

		//film adi basla
		printf("------------------");
		i=0;
		while(buff[i]!='/') {
			movie[mC].name[i]=buff[i];
			printf("%c",movie[mC].name[i]);

			i++;
		}
		printf("------------------\n\n");
		i++;
		//film adi bitis

		//oyuncu basla
		j=0;
		while(buff[i]!='\0') {
			if(buff[i]=='/') {
				strcpy(tmp->name,tmpName);
				tmp->lenght=j;
				tmp->harfToplam=harfSay(tmp->name,j);

				puts(tmp->name);
				//printf("\nUzunlugu=%d,HarfToplam=%d\n",tmp->lenght,tmp->harfToplam);

				if(search(&tmp)==NULL) {
					printf("HASH EKLENDI => ");
					puts(tmp->name);
					insert(&tmp);
					aC++;
				}
				flushString(tmp->name,j);
				flushString(tmpName,NAME_SIZE);
				j=0;
			} else {
				tmpName[j++]=buff[i];
			}
			i++;
		}

		/*BIR EKSIK VERI
		*/
		strcpy(tmp->name,tmpName);
		tmp->lenght=j;
		tmp->harfToplam=harfSay(tmp->name,j);

		puts(tmp->name);
		//printf("\nUzunlugu=%d,HarfToplam=%d\n",tmp->lenght,tmp->harfToplam);

		if(search(&tmp)==NULL) {
			printf("HASH EKLENDI => ");
			puts(tmp->name);
			insert(&tmp);
			aC++;
		}


		mC++;
	}
	close(fp);

	*actorCounter=aC;
	*movieCounter=mC;

	return 0;
}

int main(int argc, char *argv[]) {
	int movieCounter=0;
	int actorCounter=0;
	int i;

	fileRead(&movieCounter,&actorCounter);

	printf("Actor sayisi = %d\n",actorCounter);
	for(i=0; i<HASH_SIZE; i++) {
		if(hashArray[i]!=NULL) {
			puts(hashArray[i]->name);
		}
	}

	return 0;
}
