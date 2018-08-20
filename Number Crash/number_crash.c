#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

void delay(double sec)  // Delay fonksiyonunu kullanmak için gereken fonksiyon
{
    clock_t start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < sec);       
}

//Oyunu yazdiran fonksiyon. 0 yazan degerler yerine smile koyuyor..
void game_screen(int game[11][11], int n, int score, int hak) {	
	int i,j,e;
	e=2; //Smile koymak icin gereken ascii degeri
	
	if(hak!=0) printf("Score %d",score);
	printf("\n\n");
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {		
			printf(" ");	
			printf(" ");
			if(game[i][j]==0) {
				printf(" %c ",e);	
			} else {
				printf (" %d ",game[i][j]);	
			}			
			printf(" ");
			
				printf(" ");
					
		}				
		printf("\n\n");
	}
}

//Karsilama ekrani
void welcome_game(){
		printf("              ");
		printf("  ! . Welcome . !\n");printf("              ");
		printf("! . Number Crash. !\n");
}

//Bu fonksiyon anamenu olusturuyor. Dondurdugu integer deger ile kullanicinin gitmek istedigi sayfayi gosteriyor.
int welcome() {
	int devam=1, menu=1; //1-> Oyun 2-> Ayar 3-> Skor 4-> Cikis
	char islem;
	
	while(devam==1) {			
		welcome_game();
	
		if(menu==1) printf("=>"); printf(" Start the Game\n"); 
		if(menu==2) printf("=>"); printf(" Settings\n");
		if(menu==3) printf("=>"); printf(" High Score\n");
		if(menu==4) printf("=>"); printf(" Exit\n");
		
		islem=getch();
		if( (islem=='w') || (islem==72) ) {
			menu--;
		} else if ( (islem=='s') || (islem==80)) {
			menu++;
		} else if (islem==13) {
			devam=0;
		}
		
		if(menu<1) {
			menu=4;
		} else if (menu>4) {
			menu=1;
		}
		
		system("cls");		
	}
	return menu;
}

//Oyuncunun hangi harflerle oynamak istedigini alan fonksiyon. Ayarlar fonksiyonunun alt fonksiyonu
void harf_sec(int harfler[8]) {
	char devam2;
	int devam=1,i,turn,number;

	printf("O  Code=> 0  Point=> 100\n");
	printf("E  Code=> 1  Point=> 90\n");
	printf("U  Code=> 2  Point=> 75\n");
	printf("C  Code=> 3  Point=> 60\n");
	printf("F  Code=> 4  Point=> 50\n");
	printf("T  Code=> 5  Point=> 40\n");
	printf("L  Code=> 6  Point=> 15\n");
	printf("I  Code=> 7  Point=> 5\n");
	printf("You can play all of these latters as default.\nDo you want to chance it? (Y/N)\n");
	scanf("%c",&devam2);
	if ( (devam2=='y') || (devam2=='Y') ) {
		devam=1;
	} else if ( (devam2=='n') || (devam2=='N') ) {
		devam=0;
	}	
	//PUAN 100 90 75 60 50 40 15 5
	//Harfler 0=> O 1=> E 2=> U 3=>C 4=>F 5=> T 6=>L 7=>I
	if(devam==1){
		for(i=0; i<8; i++) {
			harfler[i]=0;
		}
	
	
	printf("How many letters do you want to play? (Max: 7)\n");
	scanf("%d",&turn);
	
	for(i=0; i<turn; i++){
		printf("Enter the letter's code\n");
		scanf("%d",&number);
		harfler[number]=1;
	}
	
	}
}

//Oyuncunun istedigi zorlugu secmesini sagliyor. Menu sistemi var.
int zorluk_sec() {
	int devam=1, devam2=1,menu=2,number; 
	char islem;
	
	while(devam==1) {
		while(devam2==1){
			printf("Settings\n\n");
	
			if(menu==2) printf("=>"); printf(" Easy Mode\n"); 
			if(menu==1) printf("=>"); printf(" Hard Mode\n");
			if(menu==0) printf("=>"); printf(" Back\n");
			if(menu==2) printf("\n\n*2 Chance");
			if(menu==1) printf("\n\n*1 Chance");
			
			islem=getch();
			if( (islem=='w') || (islem==72) ) {
			menu++;
			} else if ( (islem=='s') || (islem==80)) {
			menu--;
			} else if (islem==13) {
			devam2=0;
			}
		
			if(menu<0) {
				menu=2;
			} else if (menu>2) {
				menu=0;
			}
			system("cls");
			}			
			if(menu==2){
				number=2;
				devam=0;
			}
			if(menu==1){
				number=1;
				devam=0;
			}
			if(menu==0){
				devam=0;
			}
			system("cls");
	}
	return number;
}
//Oyuncu range giriyor.
int range_sec() {
	int number;
	
	printf("Enter the range(2-9)\n");
	scanf("%d",&number);
	
	return number;
}
//Boyutu seciyor.
int size_sec() {
	int number;
	
	printf("Enter the game size(5-10)\n");
	scanf("%d",&number);
	
	return number;
}

//Bu fonksiyon ayarlar menüsünü oluþturuyor. Oyuncunun ayarlar menüsünde gitmek istedigi yeri alýyor ve üst fonksiyona gönderiyor. 
int settings_menu(int ayarlar[3], int menu) {
	int devam=1;
	char islem;

	while(devam==1){
		printf("Settings\n\n");
	
		if(menu==1) printf("=>"); printf(" Letters\n"); 
		if(menu==2) printf("=>"); printf(" Difficult\n");
		if(menu==3) printf("=>"); printf(" Number Range\n");
		if(menu==4) printf("=>"); printf(" Game Size\n");
		if(menu==5) printf("=>"); printf(" Back\n");
		printf("\n\nCurrent Settings\n");
		printf("Difficult => "); if(ayarlar[0]==2) {printf("Easy Mode\n");}else{printf("Hard Mode\n");};
		printf("Range     => %d\n",ayarlar[1]);
		printf("Size      => %d\n",ayarlar[2]);
		
		islem=getch();
		if( (islem=='w') || (islem==72) ) {
			menu--;
		} else if ( (islem=='s') || (islem==80)) {
			menu++;
		} else if (islem==13) {
			devam=0;
		}
		
		if(menu<1) {
			menu=5;
		} else if (menu>5) {
			menu=1;
		}
		system("cls");
	}	
	return menu;
}

//Bu fonksiyon ile kullanici oyunun ayarlarini degistirebiliyor. Ayarlara girmeden oyuna girerse default ayarlarla oynuyor.
void settings(int harfler[8], int ayarlar[3]) {
	int devam=1, menu=1;
	char islem;
	
	while(devam==1) {
		menu=settings_menu(ayarlar,menu);
		
		if(menu==1){
			harf_sec(harfler);
		}
		if(menu==2){
			ayarlar[0]=zorluk_sec();
		}
		if(menu==3){
			ayarlar[1]=range_sec();
		}
		if(menu==4){
			ayarlar[2]=size_sec();
		}
		if(menu==5){
			devam=0;
		}
		system("cls");
	}
	
}

//Sayilar patladiktan sonra bu fonksiyon patlayan sayilari yukariya alip onlar yerine yeni degerler atiyor.
//Bunu yapmak icin oncelikle asagidan yukariya sutunu tarayip 0 olmayan degerleri yine asagidan yukariya baska diziye atiyor.
//Bu degerleri tekrar oyuna atayip sifir olan yerlere rastgele sayi atiyor.
void fall(int game[11][11], int range, int n) {
	int i,j,e=(n-1),sutun[11];
	
	for(i=0; i<n; i++) {
		sutun[i]=0;
	}

	for(j=0; j<n; j++){
		e=(n-1);
		for(i=0; i<n; i++){
			if(game[(n-1)-i][j]!=0){
				sutun[e]=game[(n-1)-i][j];
				e--;
			}
		}
				
	
	for (i=0; i<n; i++) {
			game[i][j]=sutun[i];
		}
	}
	

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (game[i][j]==0) {
				game[i][j]=1+rand()%(range);
			}
		}
	}

}

//Asagidaki fonksiyonlar isimlerindeki harfleri patlatmak icin kullaniliyor. Patlayan sayilar yerine 0 geliyor ve puan burda ekleniyor.
void patlat_o(int game[11][11], int n, int *score) { 

	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++){
			if( (game[i][j]==game[i+1][j]) && (game[i+1][j]==game[i+2][j]) && (game[i][j+2]==game[i+1][j+2]) && (game[i+1][j+2]==game[i+2][j+2]) && (game[i][j+1]==game[i+2][j+1]) && (game[i][j]!=0) ) {
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
				game[i][j+2]=0;
				game[i+1][j+2]=0;
				game[i+2][j+2]=0;
				game[i][j+1]=0;
				game[i+2][j+1]=0;										
				*score+=100;				
			}			
		}
}
}
void patlat_e(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++){
			if( (game[i][j]==game[i+1][j]) && (game[i+1][j]==game[i+2][j]) && (game[i][j+1]==game[i+1][j+1]) && (game[i+1][j+1]==game[i+2][j+1]) && (game[i][j+2]==game[i+2][j+2]) && (game[i][j]!=0) ) {
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
				game[i][j+1]=0;
				game[i+1][j+1]=0;
				game[i+2][j+1]=0;
				game[i][j+2]=0;
				game[i+2][j+2]=0;										
				*score+=90;				
			}	
		}
}
}
void patlat_u(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++){
			if( (game[i][j]==game[i+1][j]) && (game[i+1][j]==game[i+2][j]) && (game[i][j+2]==game[i+1][j+2]) && (game[i+1][j+2]==game[i+2][j+2]) && (game[i][j]==game[i+2][j+1]) && (game[i][j]!=0) ) {
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
				game[i+2][j+1]=0;
				game[i][j+2]=0;
				game[i+1][j+2]=0;
				game[i+2][j+2]=0;
				*score+=75;					
			}	
		}
}	
}
void patlat_c(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++)
		{
			if(game[i][j]==game[i+1][j] && game[i+1][j]==game[i+2][j] && game[i][j]==game[i][j+1] && game[i][j+1]==game[i][j+2] && game[i+2][j]==game[i+2][j+1] && game[i][j+1]==game[i][j+2]  && (game[i][j]!=0))
			{
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
				game[i][j+1]=0;
				game[i][j+2]=0;
				game[i+2][j+1]=0;
				game[i+2][j+2]=0;
				*score+=60;				
			}
		}
	}
}
void patlat_f(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++)
		{
			if(game[i][j]==game[i+1][j] && game[i+1][j]==game[i+2][j] && game[i][j]==game[i][j+1] && game[i][j+1]==game[i][j+2] && game[i+1][j]==game[i+1][j+1]  && (game[i][j]!=0) )
			{
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
				game[i][j+1]=0;
				game[i][j+2]=0;
				game[i+1][j+1]=0;
				*score+=50;
			}			
		}
	}
}
void patlat_t(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++){
			if( (game[i][j]==game[i][j+1]) && (game[i][j+1]==game[i][j+2])&&(game[i][j+1]==game[i+1][j+1])&&(game[i][j+1]==game[i+2][j+1])  && (game[i][j]!=0)) {
				game[i][j]=0;
				game[i][j+1]=0;
				game[i][j+2]=0;
                game[i+1][j+1]=0;
                game[i+2][j+1]=0;
            	*score+=40;				
			}				
		}
}
}
void patlat_l(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<(n-2);j++){
			if( (game[i][j]==game[i+1][j]) && (game[i+1][j]==game[i+2][j])&&(game[i+2][j]==game[i+2][j+1])&&(game[i+2][j+1]==game[i+2][j+2]) && (game[i][j]!=0) ) {
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
                game[i+2][j+1]=0;
                game[i+2][j+2]=0;
                *score+=15;                				
			}				
		}
}
}
void patlat_i(int game[11][11], int n, int *score) {
	int i,j;
	for(i=0;i<(n-2);i++)
	{
		for(j=0;j<n;j++){
			if( (game[i][j]==game[i+1][j]) && (game[i+1][j]==game[i+2][j])  && (game[i][j]!=0)) {
				game[i][j]=0;
				game[i+1][j]=0;
				game[i+2][j]=0;
				*score+=5;							
			}				
		}
}
}
// Patlatma sonu

//Oyun matrisine rastgele degerler aliyor. Bu rastgele degerler kullanicidan gelen degerlere gore degisiyor.
//Ayrýca oyunda sayilar patlamayana kadar patlatarak ilk gelen oyunda patlamaya hazir sayilarin olmasini engelliyor.
void random_number(int game[11][11], int range, int n,int harfler[8]) {
	srand(time(NULL)); // Rand fonksiyonunu kullanmak için saat bilgisini çekiyoruz.
	int i,j,skor=1;
	int counter=100;
	
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++){
			game[i][j]=1+rand()%(range);
		}
	}
	
	while( skor!=0 ){
	
	if (counter==0) {
		counter=100;
		for (i=0; i<n; i++) {
			for (j=0; j<n; j++){
				game[i][j]=1+rand()%(range);
			}
		}
	}
	
	skor=0;
	if(harfler[0]==1){
		patlat_o(game,n,&skor);
	}
	if(harfler[1]==1){
		patlat_e(game,n,&skor);
	}
	if(harfler[2]==1){
		patlat_u(game,n,&skor);
	}
	if(harfler[3]==1){
		patlat_c(game,n,&skor);
	}
	if(harfler[4]==1){
		patlat_f(game,n,&skor);
	}
	if(harfler[5]==1){
		patlat_t(game,n,&skor);
	}
	if(harfler[6]==1){
		patlat_l(game,n,&skor);
	}
	if(harfler[7]==1){
		patlat_i(game,n,&skor);
	}
	counter--;
	}
}

//Bu fonksiyon kullanicinin istedigi 2 yan yana elemanin yerini degistiriyor.
void change(int game[11][11],int x, int y, char yon) {
	int tmp;
	
	if(yon==8){
		tmp=game[x-1][y];
		game[x-1][y]=game[x][y];
		game[x][y]=tmp;		
	}if(yon==4){
		tmp=game[x][y-1];
		game[x][y-1]=game[x][y];
		game[x][y]=tmp;
	}if(yon==5){
		tmp=game[x+1][y];
		game[x+1][y]=game[x][y];
		game[x][y]=tmp;
	}if(yon==6){
		tmp=game[x][y+1];
		game[x][y+1]=game[x][y];
		game[x][y]=tmp;
	}
	
}

//Bu fonksiyon kullanicinin oynamak istedigi harfleri patlatiyor ve bilgilendirme mesajý veriyor.
int patlat(int harfler[8], int game[11][11],int n, int skor, int range, int hak) {
	int yedekskor,i;
	yedekskor=skor;
	
	if(harfler[0]==1){
		patlat_o(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit O structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[1]==1){
		patlat_e(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit E structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[2]==1){
		patlat_u(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit U structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[3]==1){
		patlat_c(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit C structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[4]==1){
		patlat_f(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit F structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[5]==1){
		patlat_t(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit T structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[6]==1){
		patlat_l(game,n,&skor);
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit L structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	if(harfler[7]==1){
		patlat_i(game,n,&skor);		
		if(yedekskor!=skor){	
		system("cls");
		game_screen(game,n,skor,hak);
		printf("You hit I structure(s)! This match gives you %d POINTS!",skor-yedekskor);
		fall(game,range,n);
		delay(2);
	}
	}
	fall(game,range,n);
	yedekskor=skor;
	delay(3); system("cls");
	game_screen(game,n,skor,hak);
	
	return skor;
}
//Kullanici bir harf patlattiktan sonra patlatabileceði baska harflerin gelme ihtimali var.
//Bu ihtimali sifirlamak icin boyle bisey mumkun mu diye kontrol ediyor. Mumkunse sadece bilgilendiriyor. Degisiklik yapmýyor.
int patliyor_mu(int game[11][11], int n,int harfler[8], int scor) {
	int i,j,score=1,skor;
	score=scor;
	skor=scor;
	
	if(harfler[0]==1){
		patlat_o(game,n,&skor);
	}
	if(harfler[1]==1){
		patlat_e(game,n,&skor);
	}
	if(harfler[2]==1){
		patlat_u(game,n,&skor);
	}
	if(harfler[3]==1){
		patlat_c(game,n,&skor);
	}
	if(harfler[4]==1){
		patlat_f(game,n,&skor);
	}
	if(harfler[5]==1){
		patlat_t(game,n,&skor);
	}
	if(harfler[6]==1){
		patlat_l(game,n,&skor);
	}
	if(harfler[7]==1){
		patlat_i(game,n,&skor);
	}
	
	if( score==skor) {
		return 0;
	} else {
		return 1;
	}

}

//Kullanicinin oyun tahtasi uzerinde bir imlec gezdirmesini ve sectigi 2 kutunun degismesini sagliyor. 
int xy_al(int *x, int *y, int game[11][11], int n, int skor,int hak){
	int devam3=1,i,j,e=3;
	char islem,yon;
	int yer;
	int a,b;
	
	if(n%2==0) {
		a=(n-1)/2;
		b=(n-1)/2;
	} else {
		a=(n-1)/2;
		b=(n-1)/2;
	}
	
	system("cls");
	while(devam3==1){
		if(hak!=0) printf("Score %d              ",skor); if (hak==2) { printf("%c%c",e,e); } else { printf(" %c",e); };
		printf("\n\n");
		for (i=0; i<n; i++) {
			for (j=0; j<n; j++) {
				
				if( (a==i) && (b==j) ) {
					printf("|");
				} else {
					printf(" ");
				}
				printf (" %d ",game[i][j]);
				if( (a==i) && (b==j) ) {
					printf("|");
				} else {
					printf(" ");
				}		
		}				
		printf("\n\n");
	}	
	printf("\n\nArrows => Cursor\nW/A/S/D => Move \n\n\n");
	
	islem=getch();
	
	if( 			(islem==72) ) {
			a--;
		} else if ( (islem==80)) {
			a++;
		} else if (	(islem==75)) {
			b--;
		} else if ( (islem==77)) {
			b++;
		} else if ( (islem=='w') || islem=='a' || islem=='s' || islem=='d' ) {
			*x=a;
			*y=b;
	
		//yon=getch();
		if( islem=='w' ) yer=8;
		if( islem=='a' ) yer=4;
		if( islem=='s' ) yer=5;
		if( islem=='d' ) yer=6;
		
		devam3=0;
		}
			
		if(a<0) {
			a=n-1;
		} else if (a>(n-1)) {
			a=0;
		}
		if(b<0) {
			b=n-1;
		} else if (b>(n-1)) {
			b=0;
		}
		
		system("cls");
	}
	return yer;
}


//Oyunun oynandigi asil fonksiyon. Diger kucuk fonksiyonlarin birlesimi
/*
Oyun su sirayla oynaniyor

Degisecek kutulari alma
Yedek Alma
Kutulari degistirme
Sayilari patlatma

*/
void play(int game[11][11], int range, int n, int *score, int harfler[8], int ayarlar[3], int hak) {	
	int x,y,i,j,skor,yedekskor,yedek[11][11],tmp,lastone=1, ischance, turn,e=3;
	int yon;
	char son;
	skor=*score;
	yedekskor=*score;
	random_number(game,range,n,harfler);
	turn=hak;
	
	game_screen(game,n,skor,turn);
	while (turn>0) {

	// YÖN ALMA
	printf("Enter the coordinats.\n\n\n");
	yon=xy_al(&x,&y,game,n,skor,turn);
	/*  YÖN ALMA SON */
	
	// YEDEK ALMA
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			yedek[i][j]=game[i][j];
		}
	}
	//YEDEK ALMA SON
	
	//CHANGE
	change(game,x,y,yon);	
	//CHANGE SON
	
	//PATLATMA
	//Harfler 0=>O    1=>E    2=>U    3=>C    4=>F    5=>T    6=>L    7=>I	
	
	ischance=patliyor_mu(game,n,harfler,skor);
	if( ischance ) {
		while ( patliyor_mu(game,n,harfler,skor) )  {		
			skor=patlat(harfler, game,n, skor, range, turn);	
		}		
	} else {
		printf("You didn't hit any structure!\n");
		printf("%c %c",e,e);
		delay(1);
		system("cls");
		printf("You didn't hit any structure!\n");
		printf("%c",e);
		delay(1);
		turn--;
		for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
				game[i][j]=yedek[i][j];
			}
		}
	}
	//PATLATMA SON
	
	
	}
	if(turn==0){
		system("cls");
		game_screen(game,n,score,turn);
		printf("Game Over!\nYour points=%d\nPree any key to continue.",skor);
		delay(1);
	}
	*score=skor;
	son=getch();
}

//Main fonksiyonu sadece menu ve gereken bazi ilklendirmeleri iceriyor. 
int main () {
	int i,j, menu,zorluk,harfler[8],devam=1,e=1,n=5,range=4,ayarlar[3],score=0,hak=2,high_score=0;
	int game[11][11];
	system("color F0");
	
	// ayarlar       0 => zorluk             1=> range             2=> oyun boyutu
	ayarlar[0]=2; ayarlar[1]=4; ayarlar[2]=6;
	for(i=0; i<8; i++){
		harfler[i]=1;
	}	
	while(devam==1) {
	menu=welcome();
	
	//Oyunun oynandigi menu
	if(menu==1) {
		score=0;
		play(game,range,n,&score,harfler,ayarlar,hak);
		if(score>high_score){
			high_score=score;
		}
		system("cls");
	}
	
	//Ayarlar menusu
	if(menu==2){
		settings(harfler, ayarlar);
		n=ayarlar[2];
		range=ayarlar[1];
		hak=ayarlar[0];
	
	}
	
	//Yuksek skor menusu
	if(menu==3) {
		printf("    High Score\n");
		printf("*-*-*-*-*-*-*-*-*\n");
		printf("    %d POINTS!",high_score);
		delay(3);
		system("cls");
	}	
	
	//Oyunu kapatan menu
	if(menu==4){
		devam=0;
		printf("See you later! %c",e);
	}
	
	}
	return 0;
}
