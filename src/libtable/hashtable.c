#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "hash.h"
#include "node.h"

// size = 2^24
#define SIZE 0x1000000

static ht_node **hashtable;

int hashtable_init(int slots) {
  hashtable = calloc(slots, sizeof(void*));
  if (hashtable == NULL) {
    return 1;
  }
  return 0;
}

/*
 * Put adds a key/value pair to the hashtable
 * 
 * Returns: 1 if the item was successfully added to the hashtable, 0 otherwise
*/
int put(char *key, void *value) {
  uint32_t pos;
  ht_node *last, *new;

  new = new_node(key, value);

  pos = FNV24(key);

  last = hashtable[pos];
  if (last == NULL) {
    hashtable[pos] = new;
  }

  do {
    if (strcmp(last->item->key, new->item->key) == 0) {
      free_node(new);
      return 0;
    }
  }while (last->next != NULL);

  last->next = new;
  return 1;
}

/*
 * Get returns the value associated with a particular key in the hashtable
 * 
 * Returns: a void pointer to the value stored in the hashtable, or null
*/
void *get(char *key) {
  uint32_t pos;
  ht_node *node;

  pos = FNV24(key);

  node = hashtable[pos];
  while (node != NULL) {
    if (strcmp(node->item->key, key) == 0) {
      return node->item->value;
    }
  }
  return NULL;
}

int main(int argc, char **argv) {
  if (hashtable_init(SIZE) != 0)
    return 1;

  free(hashtable);
}
