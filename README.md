# Concurrent(Search-Insert-Delete)

In this program, multiple threads can search through a singly linkedlist concurrently; the searchers(readers) are essentially identical to the readers from before. 
However, the writers are broken into two distinct types of threads: inserters and deleters.

The read and write locks should be granted according to the following logic:
    
  * Deletions are mutually exclusive with all other accesses to the list.
  * Concurrent reads/searches are allowed.
  * Insertions are mutually exclusive with themselves (just one can insert at a time), and with deletions.

## Compile and Run

     gcc ./main.c -o rw  
     ./rw
