#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct HashEntry
{
    int key;
    Node *node;
    struct HashEntry *next;
} HashEntry;

typedef struct LRUCache
{
    int capacity;
    int size;
    int hashSize;
    Node *head;
    Node *tail;
    HashEntry **table;
} LRUCache;

int hashFunction(LRUCache *cache, int key)
{
    return abs(key) % cache->hashSize;
}

Node *createNode(int key, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void removeNode(LRUCache *cache, Node *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        cache->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        cache->tail = node->prev;
}

void addToHead(LRUCache *cache, Node *node)
{
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head)
        cache->head->prev = node;
    cache->head = node;

    if (!cache->tail)
        cache->tail = node;
}

void moveToHead(LRUCache *cache, Node *node)
{
    removeNode(cache, node);
    addToHead(cache, node);
}

Node *hashMapGet(LRUCache *cache, int key)
{
    int hashIndex = hashFunction(cache, key);
    HashEntry *entry = cache->table[hashIndex];

    while (entry)
    {
        if (entry->key == key)
            return entry->node;
        entry = entry->next;
    }
    return NULL;
}

void hashMapPut(LRUCache *cache, int key, Node *node)
{
    int hashIndex = hashFunction(cache, key);
    HashEntry *entry = cache->table[hashIndex];
    HashEntry *prev = NULL;

    while (entry)
    {
        if (entry->key == key)
        {
            entry->node = node;
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    HashEntry *newEntry = (HashEntry *)malloc(sizeof(HashEntry));
    newEntry->key = key;
    newEntry->node = node;
    newEntry->next = NULL;

    if (prev)
        prev->next = newEntry;
    else
        cache->table[hashIndex] = newEntry;
}

void hashMapRemove(LRUCache *cache, int key)
{
    int hashIndex = hashFunction(cache, key);
    HashEntry *entry = cache->table[hashIndex];
    HashEntry *prev = NULL;

    while (entry)
    {
        if (entry->key == key)
        {
            if (prev)
                prev->next = entry->next;
            else
                cache->table[hashIndex] = entry->next;
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

LRUCache *lruCacheCreate(int capacity)
{
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->hashSize = capacity * 2; // Simple hash size
    cache->head = NULL;
    cache->tail = NULL;
    cache->table = (HashEntry **)calloc(cache->hashSize, sizeof(HashEntry *));
    return cache;
}

int lruCacheGet(LRUCache *cache, int key)
{
    Node *node = hashMapGet(cache, key);
    if (!node)
        return -1;

    moveToHead(cache, node);
    return node->value;
}

void lruCachePut(LRUCache *cache, int key, int value)
{
    Node *node = hashMapGet(cache, key);
    if (node)
    {
        node->value = value;
        moveToHead(cache, node);
        
    }
    else
    {
        Node *newNode = createNode(key, value);
        
        if (cache->size >= cache->capacity)
        {
            Node *lruNode = cache->tail;
            hashMapRemove(cache, lruNode->key);
            removeNode(cache, lruNode);
            free(lruNode);
            cache->size--;
        }
        addToHead(cache, newNode);
        hashMapPut(cache, key, newNode);
        
        cache->size++;
    }
}

void lruCacheFree(LRUCache *cache)
{
    Node *current = cache->head;
    while (current)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(cache->table);
    free(cache);
}

int main()
{
    LRUCache *cache = lruCacheCreate(2);

    lruCachePut(cache, 1, 10);
    lruCachePut(cache, 2, 20);
    printf("Get 1: %d\n", lruCacheGet(cache, 1)); // returns 10

    lruCachePut(cache, 3, 30); // evicts key 2
    printf("Get 2: %d\n", lruCacheGet(cache, 2)); // returns -1 (not found)

    lruCachePut(cache, 4, 40); // evicts key 1
    printf("Get 3: %d\n", lruCacheGet(cache, 3)); // returns 30
    printf("Get 4: %d\n", lruCacheGet(cache, 4)); // returns 40

    lruCacheFree(cache);
    return 0;
}