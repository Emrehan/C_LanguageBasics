/*
*		Emrehan ILHAN
*		13011021
*
*		Algoritma Analizi 4. Odev
*		Hashing(Double Hashing, OpenAdress)
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define M 503

//Word struct, bir gozde kelime olup olmadigini(dolu) ve varsa kelimeyi(str) tutar
typedef struct Word {
	char *str;
	int dolu;
} Word;
Word *word;

//Binary denemesi yapmak icin gereken dizi
Word *binary; //Binary search testi icin kullanilacak dizi

//Delay ve Count fonksiyonlari ekranin duzgun gozukmesi icin algoritma icin gerekmeyen 2 fonksiyon
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

//Flush String bir string'in icini bosaltmak icin gereken fonksiyon
void flushString(char string[], int n) {
	int i;
	for(i=0; i<n; i++) {
		string[i]='\0';
	}
}

//Kelimelerin yazili oldugu dosyayi okuyan fonksiyon
void dosya_adi(char name[]) {
	int devam;
	strcpy(name,"alg.txt");
	printf("Dosya adi varsayilan (%s) olarak devam etmek ister misiniz?\n",name);
	printf("Evet = 1 / Hayir = 0\n");
	scanf("%d",&devam);
	if(devam==0) {
		printf("\nDosya adini giriniz. \n=");
		scanf("%s",name);
	}
	printf("Kullanilan dosya adi = |%s|\n\n",name);
	count(3);
	system("cls");
}

//Her harften sonra hangi harfin geldigini gosteren fonksiyon
char arttir(char c) {
	if(c>='a' && c<='y') {
		return c+1;
	} else if(c='z') {
		return 'a';
	}
}

// Odev dosyasinda belirtildigi gibi double hashing yapan fonksiyonlar
//Key, kelimeden gereken keyi olusturuyor
//hash, h1 ve h2'yi kullanip gereken hash'i uretiyor.
int key(char str[]) {
	int key=0,i;

	for(i=0; i<strlen(str); i++) {
		key+=(str[i]-'a')*26*i;
	}
	return;
}
int h1(char str[]) {
	return key(str)%M;
}
int h2(char str[]) {
	return (1+(key(str)%(M-2)));
}
int hash(char str[], int i) {
	return (h1(str) + i*h2(str))%M;
}

//Hashtable'a kelimeyi ekleyen fonksiyon
int addWord(char kelime[]) {
	char *str=(char *)malloc(sizeof(char)*strlen(kelime));
	strcpy(str,kelime);
	
	int i=0;					//Adim sayisi
	int hashCode=hash(str,i);	//Gereken hashCode

	//Kelimenin eklenecegi yerin adresini bulma
	if(word[hashCode].dolu==1) {
		while(word[hashCode].dolu==1) {
			hashCode=hash(str,(++i));
		}
	}

	//Yer bulduktan sonra allocate edip yerlestirme
	word[hashCode].str = (char*) calloc (strlen(str),sizeof(char));
	strcpy(word[hashCode].str,str);
	word[hashCode].dolu=1;

	//Hash'e eklenen kelimeleri ve HashKodlarini gormek icin asagidaki fonksiyonu calistirabilirsiniz.
	//printf("Kelime=%s,HashCode=%d\n",str,hashCode);
	return hashCode;
}

//Dosyadan okunan kelimeler parse edilip hem binary hem hash dizisine ekleniyor.
int create_hash() {
	//Degisken tanimlama
	int i=0;				// gecici kelime isaretcisi
	int kelime_sayisi=0;	// dosyadan okunan kelime sayisi
	char c;					// Kelimeleri char char okurken tutan degisken
	char onceki;			// Üst üste 2kez bosluk gelirse dosya islemi biter
	char fileName[100];		// Kelimelerin yazili oldugu dosya adi
	char tmp[100];			// Dosyadaki kelimeleri gecici tutan string
	flushString(tmp,100);	// String flush eden fonksiyon
	//degisken tanimlama bitis

	dosya_adi(fileName);	// Dosya adi okuma
	FILE *fp=fopen(fileName,"r");
	if(!fp) {
		printf("Error!");
		return -1;
	}

	i=0;
	while(!feof(fp)) {
		fscanf(fp,"%s ",tmp);

		//Binary search icin kullanilacak diziye atama
		binary[kelime_sayisi].str = (char*) calloc (strlen(tmp),sizeof(char));
		strcpy(binary[kelime_sayisi].str,tmp);

		//Hash'e atama
		addWord(tmp);

		//Sonraki kelime icin hazirliklar
		i=0;
		flushString(tmp,100);
		kelime_sayisi++;
	}

	return kelime_sayisi;
}

//Verilen kelimenin once hash adresi bulunuyor. Sonra kelime o hash adresinde mi diye bakiliyor.
//Yoksa bos goz, aranan kelime, yada baslangic yerine gelene kadar double hashing yapiliyor.
int searchWordHash(char kelime[]) {
	char *str=(char *)malloc(sizeof(char)*strlen(kelime));
	strcpy(str,kelime);
	
	int i=0;					//
	int hashCode;	// HashCode olusturma
	int first=hashCode;			// HashCode yine ilk degerini almis mi kontrol etmek icin sakliyoruz
	int devam=1;				// Donguden cikma nedeni anlamak icin
	int adim_sayisi=1;
	
	char *tmp=(char *)malloc(sizeof(char)*strlen(str));
	strcpy(tmp,str);
	
	hashCode=hash(tmp,i);
	if( strcmp(word[hashCode].str,tmp)==0 ) {
		return adim_sayisi;
	}
	i++;
	hashCode=hash(tmp,i);
	while( ((word[hashCode].dolu==1)&&(hashCode!=first))&&(strcmp(word[hashCode].str,tmp)!=0)) {
		i++;
		hashCode=hash(tmp,i);
		adim_sayisi++;
	}
	if(word[hashCode].dolu==0) {
		return -1;
	} else if(hashCode==first) {
		return -1;
	} else if(strcmp(word[hashCode].str,tmp)==0) {
		return adim_sayisi;
	}

}

//Verilen kelimeye yakin keliemeler onerilir.
int kelimeOner(char str[]) {
	char *test=(char *)malloc(sizeof(char)*strlen(str));	//Hem hash hem binary search aramasi icin
	strcpy(test,str);										//Onerilecek kelimeler icin

	int i,j,tmp;												// iterasyon degiskenleri
	int onerilen_kelime=0;									// Onerilen kelime sayisini tutar

	printf("---------------Bunu mu demek istediniz---------------\n");

	//Her harf sirayla degisecek
	for(i=0; i<strlen(test); i++) {
		for(j=0; j<26; j++) {  //Tum ihtimallere bakmak icin alfabedeki tum kelimeleri deniyoruz.
			test[i]=arttir(test[i]); //i. harfi diger tum harflere bakacak sekilde bir sonraki harfe donusturuyoruz.
			tmp=searchWordHash(test);
			if(tmp!=-1) {
				printf("%s\n",test);  //Eger kelime varsa onerilen kelime olarak yazdiriyoruz.
				onerilen_kelime++;
			}
		}
	}
	return onerilen_kelime;
}
int searchWordBinary(char str[],int kelime_sayisi) {
	int low=0;
	int high=kelime_sayisi;
	int i;
	int adim_sayisi=0;

	while (low <= high) {
		adim_sayisi++;
		i=(low + high)/2;
		if (strcmp(binary[i].str,str)==0) {
			break;
		} else if (strcmp(binary[i].str,str)>0) {
			high = i - 1;
		} else {
			low = i + 1;
		}
	}

	if(strcmp(binary[i].str,str)==0) {
		return adim_sayisi;
	} else if(strcmp(binary[low].str,str)==0) {
		return adim_sayisi;
	} else if(strcmp(binary[high].str,str)==0) {
		return adim_sayisi;
	}
}


int main() {
	//Degisken tanimlari
	int i;
	int iHash;					// Kelimenin hashle kac adimda bulundugu
	int iBinary;				// Kelimenin binary ile kac adimda bulundugu
	int totalHash=0;				// Toplam adim sayisi hash icin
	int totalBinary=0;			//	Toplam adim sayisi binary icin
	int wordCounter=0;			//Dosyadaki kelime sayisi
	char kelime[100];			//Aranacak kelime
	//Degisken tanimlari bitis

	//Struct tanimlari
	word=(struct Word*)calloc(M,sizeof(struct Word));
	for(i=0; i<M; i++) {
		word[i].dolu=0;
	}
	binary=(struct Word*)calloc(400,sizeof(struct Word));

	if(!word) {
		printf("Error! Dynamic struct\n");
		return -1;
	}
	//Struct tanimlari bitis

	wordCounter=create_hash();
	printf("Kelime sayisi = %d\n",wordCounter);

	int devam=141;
	do {
		printf("Aranacak kelime?\n");
		scanf("%s",kelime);

		iHash=searchWordHash(kelime);
		iBinary=searchWordBinary(kelime,wordCounter);
		totalBinary+=iBinary;
		totalHash+=iHash;
		if(iHash==(-1)) {			
			printf("(%s) bulunamadi.\n",kelime);
			i=kelimeOner(kelime);
			
			printf("Onerilen kelime sayisi = %d\n",i);
		} else {
			printf("Kelime mevcut! (%s)\n\n",kelime);
			printf("Bunu HashMap ile %d adimda bulduk.\n\n",iHash);
			printf("Eger binary search kullansaydik %d adimda bulacaktik.\n\n",iBinary);
		}

		printf("\nDevam? (1/0)\n");
		scanf("%d",&devam);
		count(1);
	} while(devam>0);
	count(3);
	printf("Emrehan ILHAN - 13011021");

	return 0;
}
/*
c=fgetc(fp);

		//Gelen karakter bosluk degilse harftir ve gecici degiskene yazilir.
		if(c>='a' && c<='z') {
			tmp[i++]=c;
		} else { // Gelen karakter bosluksa kelime bitmistir hash ve binary array'e eklenir
			if(onceki!=' ') {
				//Binary search icin kullanilacak diziye atama
				binary[kelime_sayisi].str = (char*) calloc (strlen(tmp),sizeof(char));
				strcpy(binary[kelime_sayisi].str,tmp);

				//Hash'e atama
				addWord(tmp);

				//Sonraki kelime icin hazirliklar
				i=0;
				flushString(tmp,100);
				kelime_sayisi++;
			}
		}
		//Ust uste 2 bosluk gelme durumunu kontrol ediyor.
		onceki=c;
*/
