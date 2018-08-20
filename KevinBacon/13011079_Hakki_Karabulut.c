#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define lineLenght 21000
#define hashLenght 150000
#define kb_index 9567 

typedef struct Actor{
	char *name;
	int movie_id[300];
	int movie_count;
	int actor_id;
	int whichMovie;//graf icin lazim olanlar
	int isVisited;
}Actor;

typedef struct Movie{
	char *name;
    Actor *actors;
    int actor_count;
    int isVisited;// graf icin lazim olanlar
    int whichActor;
}Movie;

typedef struct Queue{
        int *movie;
        int first;
        int last;
        int count;
} Queue ;

int actor_index = 1,MAXV = 0;
Queue movieQ;

unsigned long int calculateHash(char *name,int *hash,Actor *actors)
{
	int i,lenght; 
	unsigned long int index = 0;
	lenght = strlen(name);
	for(i = 0;i < lenght; i++){
		index += (int)name[i]*pow(3,i);
	}
	
	index = index % hashLenght;
	
	while(hash[index] != 0&&strcmp(name,actors[hash[index]].name) != 0){
		index++;
	}
	return index;
}
int addActor(Actor actor,Actor *actors,int movie_id,int *hash)
{
	unsigned long int hashCode=calculateHash(actor.name,hash,actors);
	if(hash[hashCode] == 0){
		actors[actor_index].name = (char *)malloc(sizeof(char)*(strlen(actor.name)+1));
		strcpy(actors[actor_index].name,actor.name);
    	actors[actor_index].movie_count = 1;
    	actors[actor_index].movie_id[0] = movie_id;
    	actors[actor_index].actor_id = actor_index;
    	hash[hashCode] = actor_index++;
	}else {
		actors[hash[hashCode]].movie_id[actors[hash[hashCode]].movie_count] = movie_id;
    	actors[hash[hashCode]].movie_count++;	
	}
	return hash[hashCode];
}
int dequeue()
{
        int x;

        if (movieQ.count <= 0) printf("Warning: empty queue dequeue.\n");
        else {
            x = movieQ.movie[ movieQ.first];
            movieQ.first = (movieQ.first+1);
            movieQ.count = movieQ.count - 1;
        }

        return(x);
}
void enqueue(int x)
{
        if (movieQ.count >= MAXV){
        	printf("Queue tasti x=%d\n",x);
		}
        else {
        	movieQ.movie[ movieQ.last ] = x;
            movieQ.last = (movieQ.last+1);        
            movieQ.count = movieQ.count+1;
        }
}

void searchKB(Actor *actors,Movie *movies,int search)
{
	int i,kb = 0,t = 0,j = 0 ,temp,deQ,temp_last,k;
	void enqueue(int );
	MAXV += 5000 ; 
	movieQ.first = 0;
    movieQ.last = 0;
    movieQ.count = 0;
    
    movieQ.movie = (int *)malloc(sizeof(int)*(MAXV));
	
	for( i = 0; i < actors[search].movie_count; i++){
		enqueue(actors[search].movie_id[i]);
		movies[actors[search].movie_id[i]].isVisited = 1;
		movies[actors[search].movie_id[i]].whichActor = search ;
	}
	temp_last = movieQ.last;
	while(kb < 7 && t == 0){
		while(t == 0 && movieQ.first != temp_last){
			deQ = dequeue();
			while(t == 0 && j < movies[deQ].actor_count){
				if( movies[deQ].actors[j].actor_id == kb_index ){
					t = 1;
				} else {
					temp = movies[deQ].actors[j].actor_id ;
					if(actors[temp].isVisited == 0 ){
						actors[temp].isVisited = 1;
						actors[temp].whichMovie = deQ ;
							for( i = 0; i < actors[temp].movie_count; i++){
								if(movies[actors[temp].movie_id[i]].isVisited == 0){
								enqueue(actors[temp].movie_id[i]);
								movies[actors[temp].movie_id[i]].whichActor = temp ;
								movies[actors[temp].movie_id[i]].isVisited = 1 ;
							}
						}
					}
					j++;			
				}
			}
			j = 0 ;
		}
		temp_last = movieQ.last;
		kb++;
	}	
	if (kb < 7){
		printf("%s adli aktorun Kevin Bacon sayisi :%d\n",actors[search].name,kb);
		printf("%s adli oyuncu ile Bacon, Kevin adli oyuncu / %s adli filmde oynamislardir.\n",actors[movies[deQ].whichActor].name,movies[deQ].name);
		temp = actors[movies[deQ].whichActor].actor_id ; 
		while ( temp != search) {
			printf("%s adli oyuncu ile %s adli oyuncu  / %s adli filme oynamislardir \n",actors[movies[actors[temp].whichMovie].whichActor].name,actors[temp].name,movies[actors[temp].whichMovie].name);
			temp = movies[actors[temp].whichMovie].whichActor ; 
		}
	}else {
		printf("Kb sayisi 6 dan fazla");
	}free(movieQ.movie);
}

int main(int argc, char *argv[]) {
	int i = 0,movie_id = 0,j = 0,actor_count = 0,*hash,search_index;
	char *line,*buffer,*slash="/",*star="**",*search;
	
	int addActor(Actor ,Actor *,int ,int *);
	unsigned long int calculateHash(char *,int *,Actor *);
	void searchKB(Actor *,Movie * , int );
	
	FILE *file;
	file = fopen("cast.rated.txt","r");
	
	
	Movie *movies = (Movie*)malloc(sizeof(Movie)*4530);
	Actor *actors = (Actor*)malloc(sizeof(Actor)*150000);
	line=malloc(sizeof(char)*lineLenght);
	hash=(int*)calloc(hashLenght, sizeof(int));
	
	search=malloc(sizeof(char)*30);
	printf("Kevin Bacon sayisi aranacak ismi giriniz :");
	scanf("%[^\n]%*c",search);
	
	while(!feof(file)){
		fscanf(file,"%[^\n]% s",line);
	
		strcat(line,slash);
		strcat(line,star);
	
		buffer=strtok(line,slash);
		
		movies[movie_id].name=(char *)malloc(sizeof(char)*(strlen(buffer)+1));

		strcpy(movies[movie_id].name,buffer);	
		movies[movie_id].actors=(struct Actor*)malloc(sizeof(struct Actor));
	
		while(strcmp(buffer,star)){
			i++;
			movies[movie_id].actors=(struct Actor*)realloc(movies[movie_id].actors,sizeof(Actor)*i);
			buffer=strtok(NULL,slash);
			
			if(strcmp(buffer,star)){
				movies[movie_id].actors[actor_count].name = (char *)malloc(sizeof(char)*(strlen(buffer)+1));
				strcpy(movies[movie_id].actors[actor_count].name,buffer);		
				movies[movie_id].actors[actor_count].actor_id = addActor(movies[movie_id].actors[actor_count],actors,movie_id,hash);
				actor_count++;
			}
				
		}
		movies[movie_id].actor_count = actor_count;
		i = 0;
		actor_count = 0;
		movie_id++;
		
		free(line);
		line = malloc(sizeof(char)*lineLenght);	
	
	}
	
	search_index = hash[calculateHash(search,hash,actors)];
	
	if (search_index){
		searchKB(actors,movies,search_index);	
	} else {
		printf("Aradiginiz kisinin Kevin Bacon ile baglantisi yok");
	}	
	free(search);
	free(line);
	free(actors);
	free(movies);
	fclose(file);
	return 0;
}

