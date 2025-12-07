#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include <stdio.h>

// Initialize an empty list of maximum length max_len, that is,
// the list is of length 0.
// Return the pointer to the linked list.
int* list_init(int max_len);

// Insert an element `val` at position `idx` (0-based).
// Shift the remaining elements to the right and increment *len by 1.
// Assume the array `list` has enough space for one extra element.
void list_insert_element(int* list, int* len, int idx, int val);

// Append the element `val` to the end of the array `list`.
// Increment *len by 1.
// Assume there is enough space for one more element.
void list_append_element(int* list, int* len, int val);

// Delete the element at index `idx` (0-based) from the array `list`.
// Shift remaining elements to the left and decrement *len by 1.
void list_delete_element(int* list, int* len, int idx);

// Search for `key` in the array `list` of length `n`.
// Return the index (0-based) if found, or -1 if not found.
int list_search_element(int* list, int n, int key);

// Perform binary search for `key` in the sorted array `list`
// of length `len`.
// Return the index (0-based) if found, or -1 if not found.
int list_binary_search(int *list, int len, int key);

// Concatenate two linear lists: append all elements of
// list2 to the end of list1.
// On success, *len1 is increased accordingly.
// Assume list1 has enough space to hold all elements of list2.
void list_concat(int *list1, int *len1, const int *list2, int len2);

// Print all elements in the list to the stream `out`.
// Numbers are separated by spaces and followed by a newline.
// Use stdout to print on the screen.
void list_fprint(FILE *out, const int *list, int len);

// Given a list of integers of length `len`, sort them
// in ascending order.
void list_sort(int *list, int len);


#endif
