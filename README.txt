LRU cache implementation using HashTable(collision handling by chaining) and Queue(implemented using Double Linked List)

Files:
LRU_policy.c
input.txt
README.txt
randomsitegen.cpp

How to Input: Program reads input from "input.txt"

First line of "input.txt" is length of LRU cache so it needs to be a number.
From second line to second last line contains URLs (strings).
Last line has to be "-1" indicating input has been completed. 

User has to create a "input.txt" following above rules for correct output from the program.
Or user can also create a "input.txt" file using the "randomsitegen.cpp" program.

How to run:
randomsitegen.cpp - User can run it directly or run it in terminal.
LRU_policy.c - User can run it directly or run it in terminal.

Output: For every URL, the program reads from "input.txt" , it first prints that particular URL. Then the URLs in the queue are printed in the order - least recent to most recent from top to bottom. This is done for each URL read which also serves the purpose of degugging as every step can be clearly seen.