#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MUL 10
#define RSIZE 5
#define N 48000000

int length = 0;
int mod = 10;

struct item{
	char *key;
	char *data;
	struct item *next;
};

struct item *novy(char *key, char *data){
	struct item *novy = malloc(sizeof(struct item));
	novy->key = (char *) malloc (strlen(key));
	novy->data = (char *) malloc (strlen(data));
	strcpy(novy->key, key);
	strcpy(novy->data, data);	
	novy->next = NULL;
	length++;
	return novy; 	
};

int hash(char *str){
	int i, sum = 0, mul = 1;
	
	for (i = 0; i < strlen(str); i++){
		if (i % 3 == 0)
			sum -= str[i];
		else
			sum += str[i];	
		if (i % 2 == 0 && str[i] != 0)
			mul *= (str[i]+1);	
	}
		
	return (unsigned int) (sum + mul*mul) % mod;
}

void insert(struct item **table, char *key, char *data);

void resize(struct item **table){
	printf("som v resize\n");
	
	int i;
	*table = (struct item*) realloc (*table, MUL*mod*sizeof(struct item));
		
	struct item *arr;
	arr = (struct item*) malloc (mod * sizeof(struct item));
	
	for (i = 0; i < mod; i++){
		arr[i].next = NULL;
		arr[i].key = NULL;
	}

	for (i = mod; i < (MUL * mod); i++){
		(*table)[i].next = NULL;
		(*table)[i].key = NULL;
	}

	mod *= MUL;
	struct item *akt;
	for (i = 0; i < (mod / MUL); i++){
		if ((*table)[i].key != NULL){
			if (hash((*table)[i].key) >= mod / MUL)
				insert((table), (*table)[i].key , (*table)[i].data);
			else
				insert(&arr, (*table)[i].key, (*table)[i].data);
			length--;		
			if ((*table)[i].next != NULL){
				akt = (*table)[i].next;
				while (1){
					if (hash(akt->key) >= mod / MUL)
						insert((table), akt->key, akt->data);
					else
						insert(&arr, akt->key, akt->data);
					length--;
					if (akt->next != NULL)
						akt = akt->next;
					else
						break;
				}
			}
		}
	}
	
	for (i = 0; i < (mod / MUL); i++)	
		(*table)[i] = arr[i];		
	
	printf("SKONCIL RESIZE\n");	
}

void insert(struct item **table, char *key, char *data){
	
	int has = hash(key);
	if ((*table)[has].key == NULL){
		(*table)[has].key = (char *) malloc (strlen(key));
		(*table)[has].data = (char *) malloc (strlen(data));
		strcpy((*table)[has].key, key);
		strcpy((*table)[has].data, data);
		length++;
	}
	else
		if ((*table)[has].next == NULL)
			(*table)[has].next = novy(key, data);
		else{
			struct item *act = (*table)[has].next;
			while(1){
				if (act->next == NULL){
					act->next = novy(key, data);
					break;
				}
				else{
					act = act->next;
				}
			}
		}	
		
	if (length == RSIZE * mod)
		resize(table);	
		
}

void search(struct item *table, char *key, char *data){
	if (table[hash(key)].key == NULL){
		printf("NIE JE TO TU CHAPES MA KAMARAT\n");
		return;
	}
	if (!strcmp(table[hash(key)].key, key))
		printf("je to tu\n");
	else{
		if (table[hash(key)].next == NULL)
			printf("NIE JE TO TU CHAPES MA KAMARAT\n");
		else if (!strcmp(table[hash(key)].next->key, key))
			printf("je to tu\n");
		else{
			struct item *act = table[hash(key)].next;	
			while(1){
				if (act->next == NULL){
					printf("NIE JE TO TU CHAPES MA KAMARAT\n");
					break;
				}
				else
					if (!strcmp(act->next->key, key)){	
						printf("je to tu\n");
						break;
					}
					else
						act = act->next;	
			}
		}
	}
}

char *vytvor(int item){
	
	if (item == 1){
		char *str = (char *) malloc (2);
		str[0] = (rand() % ('z' - 'a' + 1)) + 'a';
		str[1] = '\0';
		return str;
	}
	
	int i;
	
	char *str = (char *) malloc (10);
	for(i = 0; i < 9; i++)
		str[i] = (rand() % ('z' - 'a' + 1)) + 'a';
	
	str[i] = '\0';
	//printf("%s\n",str);
	return str;
}

int main(){ 
    clock_t start, end;
    double cpu_time_used;
    srand(time(0)); 
    
    int i;
    struct item *table;
	table = (struct item*) malloc (mod * sizeof(struct item));
    
    
    for (i = 0; i < mod; i++){
		table[i].next = NULL;
		table[i].key = NULL;
	}
	
	char **strings, **keys;

	if ((strings = (char **) malloc (N * sizeof(char *))) == NULL){
		printf("Nedostatok pamate");
		return 0;
	}
	if ((keys = (char **) malloc (N * sizeof(char *))) == NULL){
		printf("Nedostatok pamate");
		return 0;
	}
	
	printf("po malokovani\n");
	
	for (i = 0; i < N; i++){
		strings[i] = vytvor(1);
		keys[i] = vytvor(2);
	}
	printf("Vytvoril som stringy\n");
	

	char p[100];
	
	/*for (i=0; i<1000000; i++){
		scanf("%s",p);
		insert(&table, p);
	}*/	
		
	start = clock();
	
	for (i = 0; i < N; i++)
		insert( &table, keys[i] , strings[i] );
	
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Cas: %lf\n",cpu_time_used);    
	printf("%d\n",length);
	
	/*
	while (scanf("%s",p) == 1){
		search(table, p);
		if (strcmp(p,"koniec") == 0)
			break;
	}
	*/
	//printf("bolo mi potesenim\n");
	//printf("%s\n",p);

/*	for (i=0; i<1500; i++){
		value = rand()+rand();
		root = insert(root, value);
	}*/

	return 0;
} 
