#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
   int data;
   Node next;
   Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object. Initializes next, prev, and data fields.
Node newNode(int data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = N->prev = NULL;
   return N;
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if (pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// Returns reference to new empty List object.
List newList(void) {
   List L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return L;
}

// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL != NULL && *pL != NULL) { 
      while(length(*pL) != 0) { 
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// // Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return L->index;
}

// Returns front element of L. 
// Pre: length() > 0
int front(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling front() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   return L->front->data;
}

// Returns back element of L. 
// Pre: length()>0
int back(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling back() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   return L->back->data;
}

// Returns cursor element of L. 
// Pre: length()>0, index()>=0
int get(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling get() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling get() on List with undefined cursor element\n");
      exit(EXIT_FAILURE);
   }
   return L->cursor->data;
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
   bool equals = false;
   Node A2 = NULL;
   Node B2 = NULL;

   if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   // Checks whether both lists have the same length.
   // If they do not, then the function will return False.
   equals = A->length == B->length;
   A2 = A->front;
   B2 = B->front;

   // This loop will proceed when the lists are the same length and there are more nodes to be checked.
   while (equals && (A2 != NULL)) {
      equals = (A2->data == B2->data);
      A2 = A2->next;
      B2 = B2->next;
   }
   return equals;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   while (length(L) != 0) {
      deleteFront(L);
   }
   
   L->index = -1;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling set() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling set() on List with undefined cursor element\n");
      exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if (L->length == 0) {
      return;
   } else {
      L->cursor = L->front;
      L->index = 0;
   }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if (L->length == 0) {
      return;
   } else {
      L->cursor = L->back;
      L->index = length(L) - 1;
   }
}

// If cursor is defined and not at front, move cursor one step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor == NULL) {
      return;
   } else if (L->cursor != L->front) {
      L->cursor = L->cursor->prev;
      L->index -= 1;
   } else {
      L->cursor = NULL;
      L->index = -1;
   }
}

// If cursor is defined and not at back, move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor == NULL) {
      return;
   } else if (L->cursor != L->back) {
      L->cursor = L->cursor->next;
      L->index += 1;
   } else {
      L->cursor = NULL;
      L->index = -1;
   }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
   Node N = newNode(x);

   if (L == NULL) {
      fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (L->length == 0) {
      L->front = L->back = N;
      L->cursor = L->front;
   } else {
      L->front->prev = N;
      N->next = L->front;
      L->front = N;
   }

   L->length += 1;
   L->index += 1;
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
   Node N = newNode(x);

   if (L == NULL) {
      fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   if (L->length == 0) {
      L->front = L->back = N;
      L->cursor = L->back;
      L->index = 0;
   } else {
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length += 1;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
   Node N = newNode(x);

   if (L == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling insertBefore() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling insertBefore() on List with undefined cursor element\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor == L->front) {
      L->cursor->prev = N;
      N->next = L->cursor;
      L->front = N;
   } else {
      L->cursor->prev->next = N;
      N->prev = L->cursor->prev;
      N->next = L->cursor;
      L->cursor->prev = N;
   }
   
   L->length += 1;
   L->index += 1;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
   Node N = newNode(x);

   if (L == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling insertBefore() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling insertBefore() on List with undefined cursor element\n");
      exit(EXIT_FAILURE);
   }

   if (L->cursor == L->back) {
      L->cursor->next = N;
      N->prev = L->cursor;
      L->back = N;
   } else {
      L->cursor->next->prev = N;
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next = N;
   }
   
   L->length += 1;
}

// Delete the front element. 
// Pre: length()>0
void deleteFront(List L) {
   Node N = NULL;
   
   if (L == NULL) {
      fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling deleteFront() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;

   // If the cursor is pointing to the front of the list, set it to undefined.
   if (L->cursor == L->front) {
      L->cursor = NULL;
   }

   if (length(L) > 1) {
      L->front = L->front->next;
      L->front->prev = NULL;
   } else {
      L->front = L->back = NULL;
   }

   L->length -= 1;
   L->index -= 1;
   freeNode(&N);
}

// Delete the back element. 
// Pre: length()>0
void deleteBack(List L) {
   Node N = NULL;

   if (L == NULL) {
      fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling deleteBack() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   N = L->back;

   // If the cursor is pointing to the back of the list, set it to undefined.
   if (L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
   }

   if (length(L) > 1) {
      L->back = L->back->prev;
      L->back->next = NULL;
   } else {
      L->front = L->back = NULL;
   }

   L->length -= 1;
   freeNode(&N);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
   Node N = NULL;

   if (L == NULL) {
      fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) < 1) {
      fprintf(stderr, "List Error: calling delete() on List with no elements\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling delete() on List with undefined cursor element\n");
      exit(EXIT_FAILURE);
   }
   N = L->cursor;

   if (length(L) == 1) {
      L->front = L->back = NULL;
   } else if (L->cursor == L->front) {
      L->front = L->cursor->next;
      L->front->prev = NULL;
   } else if (L->cursor == L->back) {
      L->back = L->cursor->prev;
      L->back->next = NULL;
   } else {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
   }

   L->cursor = NULL;
   L->index = -1;
   L->length -= 1;
   freeNode(&N);
}

// Other operations ------------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
   Node N = NULL;

   if(L == NULL) {
      fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for (N = L->front; N != NULL; N = N->next) {
      fprintf(out, "%d ", N->data);
   }
}

// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L) {
   Node N = NULL;
   
   if(L == NULL) {
      fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   List L2 = newList();
   for (N = L->front; N != NULL; N = N->next) {
      append(L2, N->data);
   }

   return L2;
}
