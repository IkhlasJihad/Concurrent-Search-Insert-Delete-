// Linked list implementation in C
#include "rw.h"
//insert at the head
void insertFirst(int key) {
   node_t *node = (node_t*) malloc(sizeof(node_t));
   node->value = key;	
   node->next = head;
   head = node;
   listlength++;
}
//delete first item
node_t* deleteFirst() {
  node_t *tempnode = head;
  head = head->next;
  listlength--;
  return tempnode;
}
int deleteNode(int key){
  if(listlength == 0)
    return -1;
  node_t *iter = head;
  if(iter == NULL)
    return -1;
  if(head->value == key){
    deleteFirst();
    return 1;
  }
  else{
    while (iter->next != NULL) {
      if (iter->next->value == key) {
        iter->next = iter->next->next;
        listlength--;
        return 1;
      }
      iter = iter->next;
    }
    return -1;
  }
}
//find node with a given value
node_t* find(int key) {
  node_t* current = head;
  //if list is empty
  if(head == NULL) {
    return NULL;
  }
  //navigate through list
  while(current->value != key) {
    if(current->next == NULL) {
      return NULL;
    } else {
      current = current->next;
    }
   }      
   return current;
}
//create Initial List with integers [1,10]
void InitializeList(){
  head = (node_t*) malloc(sizeof(node_t));
  node_t *one = (node_t*) malloc(sizeof(node_t));
  node_t *two = (node_t*) malloc(sizeof(node_t));
  node_t *three = (node_t*) malloc(sizeof(node_t));
  node_t *four = (node_t*) malloc(sizeof(node_t));
  node_t *five = (node_t*) malloc(sizeof(node_t));
  node_t *six = (node_t*) malloc(sizeof(node_t));
  node_t *seven = (node_t*) malloc(sizeof(node_t));
  node_t *eight = (node_t*) malloc(sizeof(node_t));
  node_t *nine = (node_t*) malloc(sizeof(node_t));
  node_t *ten = (node_t*) malloc(sizeof(node_t));
  listlength = 10;
  // Assign value values
  one->value = 1;
  two->value = 2;
  three->value = 3;
  four->value = 4;
  five->value = 5;
  six->value = 6;
  seven->value = 7;
  eight->value = 8;
  nine->value = 9;
  ten->value = 10;
  // Connect nodes
  one->next = two;
  two->next = three;
  three->next = four;
  four->next = five;
  five->next = six;
  six->next = seven;
  seven->next = eight;
  eight->next = nine;
  nine->next = ten;
  ten->next = NULL;
  
  head = one;
}
void printList(){
  node_t* cur = head;
  printf("---------- Our list ----------\n[");
  while(cur != NULL){
    printf("%d", cur->value);
    if(cur->next != NULL)
      printf("%s", ", ");
    cur = cur->next;
  }
  printf("%s", "]\n");

}