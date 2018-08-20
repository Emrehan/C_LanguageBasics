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
#define HASH_SIZE 130199
//hash size 244003
#define QUEUE_SIZE 250000

typedef struct Actor {
	char name[NAME_SIZE];
	int movies[DETAIL_SIZE];
	int movieCount;
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
struct Actor emptyActor;

void createHash() {
	int i;
	emptyActor.hashCode=-1;
	emptyActor.isVisited=-1;
	emptyActor.lenght=-1;
	emptyActor.name[0]='\0';
	emptyActor.parent=-1;
	emptyActor.movieCount=0;
	for(i=0; i<HASH_SIZE; i++) {
		hashArray[i]=emptyActor;
	}
}

int hashingCode(int x) {
	return (x)%HASH_SIZE;
}

int stringKarsilastir(char name1[], int n1, char name2[], int n2) {
	int i;
	if(n1!=n2) {
		return -1;
	}
	for(i=0; i<n1; i++) {
		if(name1[i]!=name2[i]) {
			return 1;
		}
	}
	return 0;
}

int search(char name[], int hashCode, int lenght) {
	int i=hashingCode(hashCode);
	while(hashArray[i].lenght!=-1) {
		//strcmp(hashArray[i].name,name)==0
		//hashArray[i].hashCode==hashCode && hashArray[i].lenght==lenght && hashArray[i].name[0]==name[0]
		//stringKarsilastir(hashArray[i].name, hashArray[i].lenght, name, lenght)==0 
		if(strcmp(hashArray[i].name,name)==0) {
			return i;
			printf("a");
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

		if(hashArray[i].name != NULL) {
			printf("%d=>",i);
			puts(hashArray[i].name);
		} else {
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
	return toplam*73;
}

int intArray[QUEUE_SIZE];
int front = 0;
int rear = -1;
int itemCount = 0;

int isEmpty() {
	if(itemCount == 0) {
		return 0;
	} else {
		return 1;
	}
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

void bfs(int movieCounter,int actorCounter, char target[]) {
	int i,j,onTmp;
	enQ(  search(    "Bacon, Kevin"   ,       harfSay("Bacon, Kevin",strlen("Bacon, Kevin"))  ,     strlen("Bacon, Kevin")));
	/*while(isEmpty()==0) {
		onTmp=deQ();

		if(strcmp( hashArray[onTmp].name ,target)==0) {
			printf("Bulundu: %s",target);
		}

		hashArray[onTmp].isVisited=1;

		for(i=0; i<hashArray[onTmp].movieCount; i++) {
			for(j=0; j<movie[hashArray[onTmp].movies[i]].actor_size; j++) {
				if( hashArray[movie[hashArray[onTmp].movies[i]].actors[j]].isVisited==0 ) {
					enQ(movie[hashArray[onTmp].movies[i]].actors[j]);
					hashArray[movie[hashArray[onTmp].movies[i]].actors[j]].isVisited=1;
				}
			}
		}
	}	*/
}

void flushString(char string[], int n, char x) {
	int i;
	for(i=0; i<n; i++) {
		string[i]=x;
	}
}

int fileRead(int *movieCounter, int *actorCounter) {
	int i=0, aC=0, mC=0,j=0,code,searchResult,aCWo=0;
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
	char name[100];

	printf("Aranan kisi?");
	scanf("%s",name);
	
	fileRead(&movieCounter,&actorCounter);
	bfs(movieCounter, actorCounter, name);

	printf("\n\nDevam etmek icin 1\n");

	printf("Actor sayisi = %d\n",actorCounter);
	printf("Movie sayisi = %d\n",movieCounter);


	return 0;
}
