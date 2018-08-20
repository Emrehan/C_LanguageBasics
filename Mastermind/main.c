#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void oyunu_olustur(char dizi[]) {
	int i=0,goster;
	for(i=0; i<4; i++) {
		int sayi=rand()%6;

		switch (sayi) {
			case 0:
				dizi[i]='R';
				break;
			case 1:
				dizi[i]='G';
				break;
			case 2:
				dizi[i]='B';
				break;
			case 3:
				dizi[i]='Y';
				break;
			case 4:
				dizi[i]='P';
				break;
			case 5:
				dizi[i]='O';
				break;
		}
	}
	printf("Bilgisayarin olusturdugu dizi gosterilsin mi? 1/0\n");
	scanf("%d",&goster);
	if(goster==1) printf("Bilgisayarin olusturdugu dizi = ");
	if(goster==1) puts(dizi);
}

int tahmin(char dizi[]) {
	int dogruTahmin=0,i,bildiMi=0;
	char *tahmin=(char*)calloc(4,sizeof(char));

	gets(tahmin);

	while(strlen(tahmin)!=4) {
		printf("4 renk tahmin edin = ");
		gets(tahmin);
	}
	for(i=0; i<4; i++) {
		if(tahmin[i]>'a' && tahmin[i]<'z') {
			tahmin[i]+='A'-'a';
		}
	}

	printf("Sizin tahmininiz = ");
	puts(tahmin);

	for(i=0; i<4; i++) {
		if( dizi[i]==tahmin[i] ) {
			dogruTahmin++;
		}
	}
	if(dogruTahmin==0) {
		printf("Hic dogru tahmininiz yok.\n");
	} else {
		printf("%d rengin yeri dogru, %d yeri yanlis.\n",dogruTahmin,(4-dogruTahmin));
		if(dogruTahmin==4) {
			bildiMi=1;
		}
	}
	return bildiMi;
}

int main() {
	srand(time(NULL));

	int hak,bildiMi=0,turn=0;
	char *dizi=(char*)calloc(4,sizeof(char));

	printf("Hak sayisini giriniz.\n");
	scanf("%d",&hak);

	oyunu_olustur(dizi);

	printf("Renkler: R=Red G=Green B=Blue Y=Yellow P=Purple O=Orange\n");
	while(bildiMi==0 && (turn++)<hak) {
		printf("%d. tahmininizi giriniz : ",turn);
		bildiMi=tahmin(dizi);
	}
	if(bildiMi==1) printf("Tebrikler! %d adimda bildiniz.\n",turn);
	if(bildiMi==0) printf("Kaybettiniz!\n");
	printf("Dogru renk dizilimi : ");
	puts(dizi);

	return 0;
}
