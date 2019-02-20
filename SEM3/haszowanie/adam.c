#include<stdio.h>
#include<string.h>
typedef unsigned long ul;//długie liczby bez znaku
#define LINIE 20000
FILE* Open(){
    return fopen("nazwiskaASCII.txt", "r");
   
}



struct s{
	int stan;//0 nie istnieje, 1 istnieje, -1 del
	int liczba;
	char* nazwisko;	
};

ul hasz(struct s* p, int m){
	int dlgslw = strlen(p->nazwisko);//wyciągamy długość nazwiska
	ul k=256 * p->nazwisko[0] + p->nazwisko[1];//hashowanie nazwiska
        for(ul i=2;i<dlgslw;i+=2){//przechodzimy po nazwisku i robimy xory
            k=(256*p->nazwisko[i] + p->nazwisko[i+1])^k;// -> wyciąganie z wskaźnika na strukturę
        }
        k=k%m;
		return k;
}
void usun(struct s* t, int m){
	int czyusuwac=1;
	for(ul i=0;i<m;i++){
		if(t[i].stan==1){
			if(czyusuwac){
				t[i].stan=-1;
			}
			czyusuwac = !czyusuwac;
		}
	}
}
void testuj(struct s* t,int m,struct s storage[LINIE]){
	int licznik=0;
	memset(t,0, m*sizeof(struct s));
	for(int i=m;i<=m+m*0.8;i++){
		ul h=hasz(storage+i, m);
		int j=0;//ilosc nieudanych prob
		while(t[h+j*j].stan==1){
			j++;
		}
		t[h+j*j]=storage[i];
		t[h+j*j].stan=1;
	}
	usun(t, m);
	for(int i=0;i<=m*0.4;i++){
		ul h=hasz(storage+i, m);
		int j=0;//ilosc nieudanych prob
		while(t[h+j*j].stan==1){
			j++;
		}
		t[h+j*j]=storage[i];
		t[h+j*j].stan=1;
	}
	for(int i=0;i<m;i++){
		if(t[i].stan==-1){
			licznik++;
		}
		
	}
	printf("dla testu o m=%d, pozycji znacznikiem del wypełnionych jest %d\n", m, licznik);
}
void testy(){
	int a;
	char bufor[64];
	
	FILE* f=Open();
	struct s storage[LINIE];
	memset(storage,0, LINIE*sizeof(struct s));
	int i=0;
	while(fscanf(f,"%d %s", &a ,bufor)==2){
		int b=strlen(bufor);//dlugosc co wczytalismy do bufora
		storage[i].nazwisko=calloc(b,sizeof(char));
		strncpy(storage[i].nazwisko,bufor, b);
		storage[i].liczba=a;
		i++;
	}
	struct s test1[1024];
	testuj(test1);
	struct s test2[4567];
	testuj(test2);
	struct s test3[5040];
	testuj(test3);
	struct s test4[1117];
	testuj(test4);
}




int main(){
	testy();
	int m=10;
	struct s tab[m];
	memset(tab,0, m*sizeof(struct s));//zeruje pamięć pól struktury i dodatkową pamięć którą moze zajmować
	tab[0].liczba=220217;
	tab[0].nazwisko="Nowak";
	tab[1].liczba=131940;
	tab[1].nazwisko="Kowalski";
	tab[2].liczba=104418;
	tab[2].nazwisko="Wisniewski";
	tab[3].liczba=92945;
	tab[3].nazwisko="Dabrowski";
	tab[4].liczba=89366;
	tab[4].nazwisko="Lewandowski";
	tab[5].liczba=88932;
	tab[5].nazwisko="Wojcik";
	tab[6].liczba=87935;
	tab[6].nazwisko="Kaminski";
	tab[7].liczba=87690;
	tab[7].nazwisko="Kowalczyk";
	tab[8].liczba=85988;
	tab[8].nazwisko="Zielinski";
	tab[9].liczba=84527;
	tab[9].nazwisko="Szymanski";
	struct s tabhash[m];
	memset(tabhash, 0 , m*sizeof(struct s));
	for(int i=0;i<m;i++){
		ul h=hasz(tab+i, m);
		int j=0;//ilosc nieudanych prob
		while(tabhash[h+j*j].stan==1){
			j++;
		}
		tabhash[h+j*j]=tab[i];
		tabhash[h+j*j].stan=1;
		
		
		printf("dla nazwiska %s, jest %d nieudanych prób. \n", tabhash[h+j*j].nazwisko, j);
	}
}