#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define READERS_TOTAL 10
#define INSERTERS_TOTAL 5
#define DELETERS_TOTAL 1
typedef struct node {
  int value;
  struct node * next;
} node_t;
node_t *head;
int listlength;
//mutexes
int readers, writers;
sem_t emptyReaders, emptyWriters;
pthread_mutex_t readlock, writelock, dowrite;
//mutexes hold/release functions
void init();
void acquire_writelock();
void release_writelock();
void release_readlock();
void acquire_readlock();
void destroyLocks();
//linkedlist functions
node_t* deleteFirst();
void insertFirst(int key);
node_t* find(int key);
void InitializeList();
void printList();
int deleteNode(int key);