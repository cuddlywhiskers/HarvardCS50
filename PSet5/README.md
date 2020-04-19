# Harvard CS50 2020 Problem Set 5

Write 5 functions to implement a [spell-checker](https://cs50.harvard.edu/x/2020/psets/5/speller/) that spells check every word in a text against a dictionary (and in the shortest time possible).

- [x] load: loads all the words into hashtable with linked list. 

- [x] hash<sup>1</sup>: uses a hash function to generate the index of the hash table. 

- [x] size: returns the number of words in text. 

- [x] check: returns boolean value of whether the value is in the dictionary or not. 

- [x] unload: free up and returns all the memory that was previously allocated for generating the array of linked list.

---
hash<sup>1</sup> : the djb2 algorithm used was implemented by http://www.cse.yorku.ca/~oz/hash.html 
