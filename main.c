#include "rw.h"

void *reader_thread(void *arg){
  //enter
  acquire_readlock();  
  //read
  printf("------- Reader Time -------\n");
  node_t* result = find((int)arg );
  if(result != NULL)
    printf("Read value: %d\n", result->value);
  else
    printf("Oops! not found\n");
  
  //leave
  release_readlock();
}
void *deleter_thread(void *arg){
  sem_wait(&emptyReaders);
  sem_wait(&emptyWriters);
  // delete
  int key;
  printf("------- Deleter Time -------\n>>>>>> Enter a key to delete:  ");
  scanf("%d",&key);
  int res = deleteNode(key);
  if(res == 1 )
    printf("deleted successfully\n");
  else 
    printf("not found\n");
  
  sem_post(&emptyWriters);
  sem_post(&emptyReaders); 
}

void *inserter_thread(void *argv){
  acquire_writelock();
  pthread_mutex_lock(&dowrite);
  //write to the list
  int key;
  printf("------- Writer Time -------\n>>>>>> Enter a key to insert to our list:  ");
  scanf("%d",&key);
  insertFirst(key);
  printf("\nDone\n");
  pthread_mutex_unlock(&dowrite);
  release_writelock();
}

int main(void) {
  printf("Welcome \u2727 \n");
  //initialize mutexes, semaphores
  init();
  //initialize list with 10 integers
  InitializeList();
  //print the list before start
  printList();
  pthread_t reader[READERS_TOTAL], 
            deleter[DELETERS_TOTAL], 
            inserter[INSERTERS_TOTAL];
  
  for(int i = 0; i < READERS_TOTAL; i++)
    pthread_create(&reader[i], NULL, (void *) reader_thread, (void *)(i+1));
  for(int i = 0; i < INSERTERS_TOTAL; i++)
    pthread_create(&inserter[i], NULL, (void *) inserter_thread, (void *)(READERS_TOTAL + i));
  for(int i = 0; i < DELETERS_TOTAL; i++)
    pthread_create(&deleter[i], NULL, (void *) deleter_thread, NULL);
  
  // join
  for(int i = 0; i < READERS_TOTAL; i++)
    pthread_join(reader[i], NULL);
  for(int i = 0; i < INSERTERS_TOTAL; i++)
    pthread_join(inserter[i], NULL);
  for(int i = 0; i < DELETERS_TOTAL; i++)
    pthread_join(deleter[i], NULL);
  destroyLocks();
  printList();
  printf("The End");
  return 0;
}

void init(){
  readers = 0;
  writers = 0;
  sem_init(&emptyReaders, 0, 1);
  sem_init(&emptyWriters, 0 , 1);  
  pthread_mutex_init(&readlock, NULL);
  pthread_mutex_init(&writelock, NULL);
  pthread_mutex_init(&dowrite, NULL);
  
}
void acquire_writelock(){
  pthread_mutex_lock(&writelock);
  writers++;
  if(writers == 1)
    sem_wait(&emptyWriters);
  pthread_mutex_unlock(&writelock);
}
void release_writelock(){
  pthread_mutex_lock(&writelock);
  writers--;
  if(writers == 0)
    sem_post(&emptyWriters);
  pthread_mutex_unlock(&writelock);
}
void acquire_readlock(){
  pthread_mutex_lock(&readlock);
  readers++;
  if(readers == 1)
    sem_wait(&emptyReaders);
  pthread_mutex_unlock(&readlock);
}
void release_readlock(){
  pthread_mutex_lock(&readlock);
  readers--;
  if(readers == 0)
    sem_post(&emptyReaders);
  pthread_mutex_unlock(&readlock);
}
void destroyLocks(){
  pthread_mutex_destroy(&readlock);
  pthread_mutex_destroy(&writelock);
  pthread_mutex_destroy(&dowrite);
}