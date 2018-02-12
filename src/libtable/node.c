#include <stdlib.h>
#include <string.h>

#include "node.h"

ht_node *new_node(char *key, void *value) {
  struct hashtable_item *item;
  ht_node *new;

  item = malloc(sizeof(struct hashtable_item));
  item->key = key;
  item->value = value;
  item->keysize = strlen(key);

  new = malloc(sizeof(ht_node));
  new->next = NULL;
  new->item = item;

  return new;
}

void free_item(struct hashtable_item *item) {
  free(item->key);
  free(item->value);
  free(item);
}

/* Frees the hashtable node and the item within it.
 * this includes the key and the value associated with the node
 */
void free_node(ht_node *node) {
  free_item(node->item);
  free(node);
}
