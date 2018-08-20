#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

struct kart_turu {
	char *numara;
	char *sekil;
};
typedef struct kart_turu kart;

void kart_destesi_olustur(kart k[], char *sayi[], char *sekil[]);
void kart_destesi_karistir(kart k[]);
void yazdir_kart(kart k[]);

int main(int argc, char *argv[]) {
	kart k[52];
	char *sekil[]={ "Karo","Kupa", "Maca", "Sinek" };
	char *sayi[]={"As", "Iki", "Uc", "Dort", "Bes", "Alti", "Yedi", "Sekiz", "Dokuz", "On", "Joker", "Kiz", "Papaz"};
	srand(time(NULL));
	
	printf("Kartlar hazirlaniyor................................................\n");
	kart_destesi_olustur(k,sayi,sekil);
	printf("Kartlar hazir yazdiriliyor..........................................\n");
	yazdir_kart(k);
	kart_destesi_karistir(k);
	printf("Kartlar karisti yazdiriliyor........................................\n");
	yazdir_kart(k);
	
	return 0;
}

void kart_destesi_olustur(kart k[], char *sayi[], char *sekil[]) {
	int i;
	
	for(i=0; i<52; i++) {
		k[i].sekil=sekil[i/13];
		k[i].numara=sayi[i%13];
	}	
}

void kart_destesi_karistir(kart *k) {
	kart tmp;
	int i,j;
	
	for(i=0; i<52; i++) {
		j=(rand()%52);
		
		tmp=k[j];
		k[j]=k[i];
		k[i]=tmp;
	}
	
}

void yazdir_kart(kart *k) {
	int i;
	
	for(i=0; i<52; i++) {
		printf("%s%s%s\n",k[i].numara," ",k[i].sekil);
	}
}
