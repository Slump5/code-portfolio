; Thomas Hoerger - Copyright © 2024 Bottom-up Mergesort
(defvar *my-list* nil)

(defun my-merge (list1 list2)
  "Merge two sorted lists into a single sorted list."
  (if (null list1)
      list2
      (if (null list2)
          list1
          (if (< (car list1) (car list2))
              (cons (car list1) (my-merge (cdr list1) list2))
              (cons (car list2) (my-merge list1 (cdr list2)))))))

(defun bottom-up-merge-sort (lst)
  "Perform bottom-up Mergesort on a list."

  ; Step (a): Partition the list into sorted pairs and merge them
  (let* ((lists (mapcar #'list lst)) ; Initial partition
         (sorted-lists (loop for (l1 l2) on lists by #'cddr
                             collect (my-merge l1 l2))))
  
    ; Step (b): Merge adjacent lists until there's only one sorted list remaining
    (if (oddp (length lists))
        (loop for (l1) on sorted-lists by #'cddr
              collect l1) ; If there's an odd number, collect the last list separately
        sorted-lists)))  ; Otherwise, return the sorted lists

(setq *my-list* '(1 7 2 1 8 6 5 3 7 9 4))

; Print the result of bottom-up Mergesort on *MY-LIST*
(print (bottom-up-merge-sort *my-list*))
