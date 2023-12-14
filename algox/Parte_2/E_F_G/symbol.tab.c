#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.tab.h"

/* current scope */
int cur_scope = 0;

void init_hash_table(){
	int i; 
	hash_table = malloc(SIZE * sizeof(list_t*));

	if(!hash_table){
		exit(1);
	}

	for(i = 0; i < SIZE; i++){
		hash_table[i] = NULL;
	}
}

unsigned int hash(char *key){
	unsigned int hashval = 0;
	for(;*key!='\0';key++){
		hashval += *key;
	}
	hashval += key[0] % 11 + (key[0] << 3) - key[0];
	return hashval % SIZE;
}

void insert(char *name, int len, int type, int lineno){
	unsigned int hashval = hash(name);
	list_t *l = hash_table[hashval];
	
	while ((l != NULL) && (strcmp(name,l->st_name) != 0)){
		l = l->next;
	}

	/* variable not yet in table */
	if (l == NULL){
		l = (list_t*) malloc(sizeof(list_t));
		strncpy(l->st_name, name, len);  
		/* add to hashtable */
		l->st_type = type;
		l->inf_type = type;
		l->scope = cur_scope;
		l->lines = (RefList*) malloc(sizeof(RefList));
		l->lines->lineno = lineno;
		l->lines->next = NULL;
		l->next = hash_table[hashval];
		hash_table[hashval] = l; 
		printf("%s na linha %d foi inserido pela primeira vez!\n", name, lineno); // error checking
	}
	/* found in table, so just add line number */
	else{
		l->scope = cur_scope;
		RefList *t = l->lines;
		while (t->next != NULL) t = t->next;
		/* add linenumber to reference list */
		t->next = (RefList*) malloc(sizeof(RefList));
		t->next->lineno = lineno;
		t->next->next = NULL;
		printf("%s encontrado novamente na linha %d!\n", name, lineno);
	}
}

list_t *lookup(char *name){ /* return symbol if found or NULL if not found */
	unsigned int hashval = hash(name);
	list_t *l = hash_table[hashval];

	while ((l != NULL) && (strcmp(name,l->st_name) != 0)){
		l = l->next;
	}
	
	return l; // NULL is not found
}

list_t *lookup_scope(char *name, int scope){ /* return symbol if found or NULL if not found */
	unsigned int hashval = hash(name);
	list_t *l = hash_table[hashval];

	while ((l != NULL) && (strcmp(name,l->st_name) != 0) && (scope != l->scope)){
		l = l->next;
	}
	
	return l; // NULL is not found
}

void hide_scope(){ /* hide the current scope */
	if(cur_scope > 0){
		cur_scope--;
	}
}

void incr_scope(){ /* go to next scope */
	cur_scope++;
}

/* print to stdout by default */ 
void symtab_dump(FILE * of){  
  int i;
  fprintf(of,"-------------------- ------------------- -------------\n");
  fprintf(of,"Nome                 Tipo                Linha(s)\n");
  fprintf(of,"-------------------- ------------------- --------------\n");
  for (i=0; i < SIZE; ++i){ 
	if (hash_table[i] != NULL){ 
		list_t *l = hash_table[i];
		while (l != NULL){ 
			RefList *t = l->lines;
			fprintf(of,"%-20s ",l->st_name);
			if (l->st_type == INT_TYPE) fprintf(of,"%-18s","int");
			else if (l->st_type == REAL_TYPE) fprintf(of,"%-18s","real");
			else if (l->st_type == STR_TYPE) fprintf(of,"%-18s","string");
			else if (l->st_type == ARRAY_TYPE_INT){
				fprintf(of,"vetor de ");
				fprintf(of,"%-9s","int");
			}
			else if (l->st_type == ARRAY_TYPE_REAL){
				fprintf(of,"vetor de ");
				fprintf(of,"%-9s","real");
			}
			else fprintf(of,"%-18s","indefinido"); // if indefinido or 0
			while (t != NULL){
				fprintf(of,"%4d ",t->lineno);
			t = t->next;
			}
			fprintf(of,"\n");
			l = l->next;
		}
    }
  }
}
