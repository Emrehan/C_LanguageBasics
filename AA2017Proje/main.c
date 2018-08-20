#include <stdio.h>
#include <string.h>

#define TEXT_SIZE 1000
#define SHINGLE_SIZE 1000
#define DOC_ARRAY_SIZE 20
#define DOC_10 120
#define MAXINT 9999

#define M 150

typedef struct DOC {
	char text[TEXT_SIZE];
	char shingle4[SHINGLE_SIZE][9];
	char shingle5[SHINGLE_SIZE][9];
	char shingle8[SHINGLE_SIZE][9];
	int count[3];
}DOC;

struct DOC document[DOC_ARRAY_SIZE];

// Her dokumanin 4,5,8li shinglelari ve bunlarin sayilarini atiyor.
void init_documents(int i, char text[], char sh4[][9], char sh5[][9], char sh8[][9], int count[]){
	int j,k;
	strcpy(document[i].text,text);
	
	for(j=0; j<3; j++){
		document[i].count[j]=count[j];
	}
	
	for(j=0; j<count[0]; j++){
		for(k=0; k<4; k++){
			document[i].shingle4[j][k]=sh4[j][k];
		}
	}
	
	for(j=0; j<count[1]; j++){
		for(k=0; k<5; k++){
			document[i].shingle5[j][k]=sh5[j][k];
		}
	}
	
	for(j=0; j<count[2]; j++){
		for(k=0; k<8; k++){
			document[i].shingle8[j][k]=sh8[j][k];
		}
	}
}

//Her dosyayi okur (a-z ve bosluklari, birden fazla boslugu almaz, A-Z'yi a-z yapar)
void readFiles(char text[], char fileName[]){
	FILE *file;
	file = fopen(fileName, "r");
	char c;
	char prev='a';
	int i=0;
	
	if (file) {
	    while ((c = getc(file)) != EOF){
	    	if(c >= 'A' && c <= 'Z'){
	    		c += 'a'-'A';
			}
			if(c == ' ' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ){
	    		if(!(prev==' ' && c==' ')){
	    			text[i]=c;
	        		i++;	
	        		prev=c;
				}
			}
		}
	    fclose(file);
	}else{
		printf("Hatali file name => %s\n",fileName);
	}
}

//Verilen text'in k'ya göre shinglelarini olusturur
int shingle(int k, char text[], char s[][9]){
	int i, j, h=0, c=0, p, z;
	char tmp[9];
	for(i=0; i<TEXT_SIZE; i++){
		for(j=0; j<9; j++){
			s[i][j]='\0';
		}
	}
	while((h+k)<=strlen(text)){
		p=0;
		
		for(z=0; z<9; z++){
			tmp[z]='\0';
		}
		for(j=h; j<h+k; j++){
			tmp[p++]=text[j];
		}
		if( notExist(tmp,s,c,k)==-1){
			strcpy(s[c],tmp);
			c++;
		}
		h++;
	}
		
	return c;
}

//Verilan shingle, shingle matrisine daha önce eklendiyse id'sini döndürür, yoksa -1
int notExist(char target[], char text[][9], int count,  int k){
	int j;
	for(j=0; j<count; j++){
		if( strcmp(text[j],target)==0){
			return j;
		}
	}
	return -1;
}

//Verilen 2 dökümanin jaccard benzerligini hesaplar
float jaccardSimilarity(int d1, int d2, int k){
	int i,j;
	int kesisim=0;
	int countId = (k==4?0:(k==5?1:2));
	
	if(k==4){
		for(i=0; i<document[d1].count[countId]; i++ ){
			for(j=0; j<document[d2].count[countId]; j++){
				if( strcmp(document[d1].shingle4[i], document[d2].shingle4[j]) == 0 ){
					kesisim++;
				}
			}	
		}
	}else if(k==5){
		for(i=0; i< document[d1].count[countId]; i++ ){
			for(j=0; j< document[d2].count[countId]; j++ ){
				if( strcmp(document[d1].shingle5[i], document[d2].shingle5[j]) == 0 ){
					kesisim++;
				}
			}	
		}
	}else if(k==8){
		for(i=0; i< document[d1].count[countId]; i++ ){
			for(j=0; j<document[d2].count[countId]; j++ ){
				if( strcmp(document[d1].shingle8[i], document[d2].shingle8[j]) == 0 ){
					kesisim++;
				}
			}	
		}
	}
	return (float)kesisim/(document[d1].count[countId]+document[d2].count[countId]-kesisim);
}

//Jaccard benzerligi matrisini yazdirir
void printfJaccard(float m[][DOC_ARRAY_SIZE]){
	int i,j;
	printf("\n*************** Jaccard Benzerligi **********************\n");
	printf("      ");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		printf("%d",i+1);
		printf("%s",(i<9?"     ":"    "));
	}
	printf("\n");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		printf("%d",i+1);
		printf("%s",(i<9?"   ":"  "));
		for(j=0; j<DOC_ARRAY_SIZE;j++){
			printf("%.2f  ",m[i][j]);
		}
		printf("\n");
	}
}

//Verilen 4-5-8li shinglelarin sayilarini structa atar
int getShingleSize(char shingles[][9], int k){
	int i,j, count=0;
	
	strcpy(shingles[count],document[0].shingle4[0]);
	count++;
	if(k==4){
		for(i=0; i<DOC_ARRAY_SIZE; i++){
			for(j=0; j<document[i].count[0];j++){
				if(notExist(document[i].shingle4[j], shingles, count, k) == -1){
					strcpy(shingles[count],document[i].shingle4[j]);
					count++;
				}
			}	
		}
	}else if(k==5){
		for(i=0; i<DOC_ARRAY_SIZE; i++){
			for(j=0; j<document[i].count[1];j++){
				if(notExist(document[i].shingle5[j], shingles, count, k) == -1){
					strcpy(shingles[count],document[i].shingle5[j]);
					count++;
				}
			}	
		}
	}else if(k==8){
		for(i=0; i<DOC_ARRAY_SIZE; i++){
			for(j=0; j<document[i].count[2];j++){
				if(notExist(document[i].shingle8[j], shingles, count, k) == -1){
					strcpy(shingles[count],document[i].shingle8[j]);
					count++;
				}
			}	
		}
	}
	
	return count;
}

//Her döküman icin 4-5-8li shinglelari hesaplar ve struca ata
void initDoc(){
	char text[TEXT_SIZE];
	char s4[TEXT_SIZE][9], s5[TEXT_SIZE][9], s8[TEXT_SIZE][9];
	
	char *file[] = {
		"data/1.txt",
		"data/2.txt",
		"data/3.txt",
		"data/4.txt",
		"data/5.txt",
		"data/6.txt",
		"data/7.txt",
		"data/8.txt",
		"data/9.txt",
		"data/10.txt",
		"data/11.txt",
		"data/12.txt",
		"data/13.txt",
		"data/14.txt",
		"data/15.txt",
		"data/16.txt",
		"data/17.txt",
		"data/18.txt",
		"data/19.txt",
		"data/20.txt",
	};
	
	int i,j,h,c[3];

	for(i=0; i<DOC_ARRAY_SIZE; i++){
		for(j=0; j<TEXT_SIZE; j++){
			text[j]='\0';
		}	
		readFiles(text,file[i]);
		c[0] = shingle(4,text,s4);
		c[1] = shingle(5,text,s5);
		c[2] = shingle(8,text,s8);
		
		init_documents(i,text,s4,s5,s8,c);
	}
}

//Jaccard benzerligini hesaplar
void jaccard(int k, float thresh){
	int i,j;
	
	float jMatrix[DOC_ARRAY_SIZE][DOC_ARRAY_SIZE];
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){
			jMatrix[i][j] = (float)jaccardSimilarity(i,j,k);
		}
	}
	printfJaccard(jMatrix);
	
	printf("******************** Thresholddan buyuk dokuman ciftleri(Jaccard) ******************** \n");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){
			if(jMatrix[i][j] > thresh && i!=j){
				printf("%d-%d   ",i+1,j+1);
			}
		}
	}
}

//Dokumandaki shingle sizelerini yazar
void printfShingleSize(int k){
	int i;
	int countId = (k==4?0:(k==5?1:2));
	
	printf("******************** K shingle sayilari ******************** \n");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		printf("%d. ",i+1);
		if(i<9) printf(" ");
		printf("Dokuman => %d\n",document[i].count[countId]);
	}
}

int hash(int a, int x){
	return ((a*x)+1)%M;
}

//Min hashing yöntemini yapar. 
void minhashing(int k, float threshold){
	int i,j,ii,jj,s; //iter degiskenleri
	
	int countId = (k==4?0:(k==5?1:2)); // K'ya göre countId degeri
	
	// Tüm shinglelarin listesini ve sayisini tutan degiskenler
	int sSize=0;
	char shingles[20000][9];
	
	// 100 elemanli hashin a degerlerini tutan array
	int hashA[100]; 
	
	//minhash benzerligi icin gerekli matrisler
	int sig[100][DOC_ARRAY_SIZE];
	float similar[DOC_ARRAY_SIZE][DOC_ARRAY_SIZE];
	int *hashmin[1000];
	for (i=0; i<1000; i++)
         hashmin[i] = (int *)malloc(DOC_10 * sizeof(int));
	
	//Benzerlige en büyük int degeri ataniyor
	for(i=0; i<100; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){
			sig[i][j]=MAXINT;
		}
	}
	
	//min hashler 1,3,5 diye ataniyor
	j=1;
	for(i=0; i<100; i++){
		hashA[i]=10+j;
		j+=3;
	}
	
	//Tüm shinglelar olusturuluyor
	sSize = getShingleSize(shingles,k);

	printf("\n\n************ Toplam farkli shingle sayisi %d ***********\n\n",sSize);

	// Her dokumanda belirlenen shinglelar var mi yok mu diye boolean matrisi olusturuyor
	for(j=0; j<DOC_ARRAY_SIZE; j++){
		for(i=0; i<sSize; i++){
			hashmin[i][j]= (notExist(shingles[i], document[j].shingle4, document[j].count[countId],k)==-1)?0:1;
		}
	}
	
	//Her shingle icin hash degeri hesaplaniyor.
	for(j=DOC_ARRAY_SIZE; j<DOC_ARRAY_SIZE+100; j++){
		for(i=0; i<sSize; i++){
			hashmin[i][j]=hash(hashA[j-DOC_ARRAY_SIZE],i+10);
		}
	}
	
	//En son benzerlik matrisi olusturuluyor
	for(i=0; i<sSize; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){
			if( hashmin[i][j]==1 ){
				for(ii=0; ii<100; ii++){
					if(sig[ii][j]>hashmin[i][DOC_ARRAY_SIZE+ii]){
						sig[ii][j]=hashmin[i][DOC_ARRAY_SIZE+ii];
					}
				}
			}
		}
	}
	
	float sum=0.0;
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){	
			sum=0.0;
			for(ii=0; ii<100; ii++){
				if( sig[ii][i] == sig[ii][j] ){
					sum+=1.0;
				}
			}
			similar[i][j]=(float)(sum/100);
		}
	}
	
	//imza matrisi benzerligi
	
	printf("\n******************** Min Hashing icin imza benzerlik orani ******************** \n");
	printf("      ");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		printf("%d",i+1);
		printf("%s",(i<9?"     ":"    "));
	}
	printf("\n");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		printf("%d",i+1);
		printf("%s",(i<9?"   ":"  "));
		for(j=0; j<DOC_ARRAY_SIZE;j++){
			printf("%.2f  ",similar[i][j]);
		}
		printf("\n");
	}
	/*for(i=0; i<DOC_ARRAY_SIZE; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){
			printf("%.2f ",similar[i][j]);
		}
		printf("\n");
	}*/
	
	printf("\n******************** Thresholddan buyuk dokuman ciftleri(Min Hash) ******************** \n");
	for(i=0; i<DOC_ARRAY_SIZE; i++){
		for(j=0; j<DOC_ARRAY_SIZE; j++){
			if(similar[i][j] > threshold){
				printf("%d-%d    ",i,j);
			}
		}
	}
}

int main(){		
	int i,j,k, devam=1;
	float thresh;
	
	initDoc();
	
	while(devam==1){
		printf("K degeri?\n");
		scanf("%d",&k);
		
		printf("Threshold?\n");
		scanf("%f",&thresh);
		
		printfShingleSize(k);
		jaccard(k,thresh);
		minhashing(k,thresh);	
		
		printf("\n\n******************** Tekrar? 1/0 ******************** \n");
		scanf("%d",&devam);
	}
	
	return 0;
}
