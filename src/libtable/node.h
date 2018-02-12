#ifndef NODE_H
#define NODE_H

/* Allows items of any type to be stored by a variable.
 * If the type does not exist, store it as a void pointer and make sure to
 * store its size
 */
/*struct generic_item {
  enum {
    typeUndefined,
    typeChar,
    typeInt,
    typeUint,
    typeShort,
    typeUshort,
    typeLong,
    typeUlong,
    typeLongLong,
    typeUlongLong,
    typeFloat,
    typeDouble,
    typeLongDouble,
    typeString,
    typeVoid
  } type;
  union {
    char c;
    int i;
    unsigned int ui;
    short s;
    unsigned short us;
    long l;
    unsigned long ul;
    long long ll;
    unsigned long long ull;
    float f;
    double d;
    long double ld;
    char *s;
    void *v;
  } item;
  size_t size;
};*/
struct hashtable_item {
  char *key;
  size_t keysize;
  void *value;
  size_t valuesize;
};

/* struct fro the nodes in the hashtable array
 * Each slot in the array stores the head of a linked list
 * The node also contains the key and value, as void pointers which can be
 * type cast on retrieval.  This allows for simple use of generics
*/
struct hashtable_node {
  struct hashtable_node *next;
  struct hashtable_item *item;
};

typedef struct hashtable_node ht_node;

void free_item(struct hashtable_item *item);

ht_node *new_node(char *key, void *value);
void free_node(ht_node *node);

#endif
