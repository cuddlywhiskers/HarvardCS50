# Harvard CS50x 2020 Problem Set 3

This problem set consists of 3 questions (1 optional ones), kindly refer to this link for more info: https://cs50.harvard.edu/x/2020/psets/3/
The three questions below attempts to implement three different ways to run an election


- [x] **Plurality**: Each person votes for a single candidate, sum all the candidate scores and the candidate with highest score wins. 

| Functions | Description |
|-|-|
| `vote` | checks whether candidate's name exist in candidate list and adds to struct if name exist |
| `print_winner`| sorts all votes and prints the winner with highest votes or, prints all winners if tie. |

Disadvantages: 
1. creates a tie situation if both candidates have same score. 
2. Disregards preferences and only goes by number of candidates in Rank 1.  

---

- [x] **Runoff**: Ranked-choice voting system to avoid tie-situation. Person with lowest vote is eliminated and the next vote is cast to the next preferred individual. 

| Functions | Description |
|-|-|
| `vote` | checks whether candidate's name exist in candidate list |
| `tabuluate` | tabulates votes for candidates that are yet to be eliminated |
| `print_winner`| return winner if there is no tie |
| `find_min` | retrieves the min score using sorting algorithm, bubble sort was used here |
| `is_tie` | boolean value for tied election | 
| `eliminate` | changes candidates[i].eliminated (struct) type to true if candidate has lowest vote | 

Disadvantages: 
1. Although it eliminates candidates with lowest score and cast vote to the next best person to avoid tie, it could still end off with a deadlock.

---

- [x] **Tideman**: Ranked-choice voting system whereby each candidate is ranked over another. All candidates are paired together and winner of each pair is determined by score ratio between the two and the score margin.

| Functions | Description |
|-|-|
| `vote` | checks whether candidate's name exist and updates ranks |
| `record preferences`| 2D array; loops through each voter and checks the vote of each candidate over another |
| `add_pairs` | compares the number of votes between pairs | 
| `sort_pairs` | uses bubble sort to sort pairs, from highest victory to lowest |
| `lock_pairs` | checks whether there's a locked situation, if so, skip the candidate pair | 
| `print_winner` | prints winner if candidate doesnt have a winner over him/her | 
