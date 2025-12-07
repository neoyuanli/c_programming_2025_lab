#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include <stdio.h>

// A dynamically sized array of integers.
typedef struct {
  // Maximum number of integers that can be stored.
  int max_len;

  // Current number of integers stored (len <= max_len).
  int len;

  // Array of integers: list[0] ... list[len - 1].
  int *list;
} List;

// Initialize an empty list with capacity max_len.
// Returns 0 on success, or non-zero on error.
int list_init(List* list, int max_len);

// Frees the memory allocated for the list's underlying array.
// After calling this function, ptr_list->list is set to NULL,
// and ptr_list->len and ptr_list->max_len are reset to 0.
// The List structure itself is not freed.
void list_free(List *ptr_list);

// Inserts the value `val` at index `idx` (0-based).
// Elements from `idx` onward are shifted one position to the right,
// and ptr_list->len is increased by 1.
// If the underlying array is full, its capacity is doubled before insertion.
// If that happens, the orginal array should be freed.
// Returns 0 on success and a non-zero value on error.
int list_insert_element(List *ptr_list, int idx, int val);

// Appends the value `val` to the end of `ptr_list`.
// Increases ptr_list->len by 1.
// If the underlying array is full, its capacity is doubled before insertion.
// Returns 0 on success and a non-zero value on error.
int list_append_element(List *ptr_list, int val);

// Deletes the element at index `idx` (0-based) from ptr_list.
// Remaining elements are shifted one position to the left,
// and ptr_list->len is decremented by 1.
// Returns 0 on success and a non-zero value on error.
int list_delete_element(List *ptr_list, int idx);

// Searches for `key` in ptr_list.
// Returns the 0-based index of the first matching element,
// or -1 if the key is not found.
int list_search_element(const List *ptr_list, int key);

// Performs a binary search for `key` in the sorted list 
// pointed to by ptr_list.
// Returns the 0-based index of the matching element,
// or -1 if the key is not found.
int list_binary_search(const List *ptr_list, int key);

// Concatenates two linear lists by appending all elements of ptr_list2
// to the end of ptr_list1. On success, ptr_list1->len is increased
// to reflect the additional elements.
// If the array in ptr_list1 is full, keep doubling its capacity until
// it is large enough.
// Returns 0 on success and a non-zero value on error.
int list_concat(List *ptr_list1, const List *ptr_list2);

// Prints all elements of ptr_list to the output stream `out`.
// Elements are separated by spaces and terminated with a newline.
// Use stdout as `out` to print to the screen.
void list_fprint(FILE *out, const List *ptr_list);

// Given a list of integers of length `len`, sort them
// in ascending order.
// Use quick sort to sort the elements.
void list_sort(List* ptr_list);


#endif
