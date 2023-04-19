#include <stdlib.h>
#include <assert.h>

#include "skiplist.h"
#include "rng.h"

typedef struct s_DoubleLinkedNode {
	int value;
	int level;
	struct s_DoubleLinkedNode **prev;
	struct s_DoubleLinkedNode **next;
} *Node;

struct s_SkipList {
	RNG proba;
	int maxLevel;
	int size;
	Node sentinel;
};



SkipList skiplist_create(int nblevels) {
	SkipList skList = malloc(sizeof(struct s_SkipList));

	//initalisation du la struture de rng, et des valeurs "simples"
	skList->proba = rng_initialize(0);
	skList->maxLevel = nblevels;
	skList->size = 0;

	//initialisation de la sentinelle
	skList->sentinel = malloc(sizeof(struct s_DoubleLinkedNode));
	skList->sentinel->level = nblevels;
		//allocation de la mémoire pour les tab de pointeurs
	skList->sentinel->next = malloc(sizeof(Node) * nblevels);
	skList->sentinel->prev = malloc(sizeof(Node) * nblevels);

	for (int i=0; i<nblevels; i++) {
		//on remplit les tableaux de pointeurs (ils pointent tous sur la sentinelle)
		skList->sentinel->prev[i] = skList->sentinel;
		skList->sentinel->next[i] = skList->sentinel;
	}

	return skList;
}

void skiplist_delete(SkipList d) {
	Node nextE;
  for (Node e = d->sentinel->next[0]; e != d->sentinel; e = nextE) {
    nextE = e->next[0];
		free(e->next);
		free(e->prev);
    free(e);

  }

	free(d->sentinel->next);
	free(d->sentinel->prev);
	free(d->sentinel);
	free(d);
	d = NULL;
}

unsigned int skiplist_size(SkipList d) {
	return d->size;
}

int skiplist_ith(skipList d, unsigned int i) { //= skiplist_at()
	Node e = d->sentinel;
	for (unsigned int j=0; i<j; j++) {
		e = e->next[0];
	}
	return e->value;
}

void skiplist_map(SkipList d, ScanOperator f, void *user_data) {

}

SkipList skiplist_insert(SkipList d, int value) {
	(void)value;
	return d;
}
