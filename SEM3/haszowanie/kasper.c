#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct element {
	int key;
	char val[30];
} hash;


int hashing(int k, int i, int m) {
	int wynik = ((k%m) + i * i) % m;
	return wynik;
}

int isFilled(hash *T,int m){
	int i;
	int counter=0;
	for(i=0;i<m;i++){
		if(T[i].key!=-1){
			counter++;
		}
	}
	float is80 = (float)counter/(float)m;
	if(is80>=0.8){
		return 1;
	}
	return 0;
}

int hashInsert(hash *tableT,hash T,int m){
	int i=0;
	
	do
	{
		int j=hashing(T.key,i,m);
		//
		i++;
		if(tableT[j].key==-1){
			tableT[j]=T;
			return j;
		}
		
	}while(i<m);
}

//
void delete(hash *T, int m) {
	int counter= 0;
	int i;
	do {
		if (T[i].key != 0) {

			T[i].key = -1;
			int j;
			for (j = 0; j < 30; j++) {
				T[i].val[j] = 0;
			}
			counter++;
		}
		
	} while (counter > 0.4*m);
}

void print(hash *T, int m) {
	int i;
	for (i = 0; i < m; i++) {
		printf("%d. Liczba: %d \nKlucz: %s\n\n", i + 1, T[i].key, T[i].val);
	}

}

int countDeleted(hash *T, int m){
	int counter=0;
	
	int i;
	for (i = 0; i < m; i++) {
		if (T[i].key == -1)
			counter++;

	}
	return counter;
}

//[U+UK]
int main(int argc, char *argv[]) {
	
	hash *T;
	int m=11;
	
	T=(hash *)calloc(m,sizeof(hash));
	
	int size=m*0.8;
	int insertedValues[size];
	printf("m = %d \n",size);
	
	FILE *file = fopen("nazwiskaASCII.txt", "r");
	
	if(file == NULL){
		printf("error");
		return 1;
	}
	int i;
	for(i=0;i<m;i++){
		T[i].key=-1;
	}
	
	

		int key;
		char *val;
		int counter=0;
		do
		{
				if(fscanf(file, "%d %s", &key,&val)==1){
					break;						
				}

					hash el;
				 	el.key=key;
					strcpy(el.val,&val);
					int index = hashInsert(T,el,m);
					insertedValues[counter]=index;
					counter++;
					
		}
		while (isFilled(T,m)!=1); 
print(T, m);

int k;
for(k=0;k<size;k++){
	if(k%2==0){
		int index=insertedValues[k];
		T[index].key=-1;
		int j;
		for(j=0;j<30;j++){
			T[index].val[j]=0;
		}
	}
}
print(T, m);

	do
		{
				if(fscanf(file, "%d %s", &key,&val)==1){
					break;						
				}
					hash el;
				 	el.key=key;
					strcpy(el.val,&val);
					int cos = hashInsert(T,el,m);

					
		}
		while (isFilled(T,m)!=1); 

		fclose(file);

		print(T, m);
		printf("%d",countDeleted(T, m));

	
	
	free(T);
	
	return 0;
}