; Thomas Hoerger - Copyright © 2024 Insertion Sort
; Define a global variable to store the original list
(defvar *my-list* nil)

; Define a global variable to store the sorted list
(defvar *sorted-list* nil)

; Function to insert an item into a sorted list in descending order
(defun insert-into-sorted (item sorted-list)
  "Insert ITEM into a sorted list in descending order."
  (if (null sorted-list)
      (list item)  ; If the sorted list is empty, create a new list with the item
      (if (>= item (car sorted-list))
          (cons item sorted-list)  ; If the item is greater or equal, insert at the beginning
          (cons (car sorted-list) (insert-into-sorted item (cdr sorted-list))))))  ; Otherwise, recursively insert into the rest of the list

; Function to perform Insertion Sort on a list
(defun insertion-sort (unsorted-list sorted-list)
  "Perform Insertion Sort on a list."
  (if (null unsorted-list)
      sorted-list  ; If the unsorted list is empty, return the sorted list
      (insertion-sort (cdr unsorted-list)
                      (insert-into-sorted (car unsorted-list) sorted-list))))  ; Recursively insert the first element of unsorted-list into the sorted list

; Function to initiate descending Insertion Sort on a list
(defun descending-insertion-sort (lst)
  "Sort a list in descending order using Insertion Sort."
  (insertion-sort lst '()))  ; Call insertion-sort with an empty sorted list to initiate the process

; Example usage
(setq *my-list* '(5 2 9 1 5 6 3 8 4 7))
(print "Original List:")
(print *my-list*)

; Perform descending Insertion Sort and store the result in *sorted-list*
(setq *sorted-list* (descending-insertion-sort *my-list*))

; Print the sorted list
(print "Sorted List (Descending Order):")
(print *sorted-list*)

