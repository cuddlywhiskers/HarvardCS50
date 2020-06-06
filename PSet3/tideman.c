#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // loop thru candidates and check whether name match
        if (strcmp(name, candidates[i]) == 0)
        {
            // if match, update rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // create two loops to compare the ranks
    for (int i = 0; i < candidate_count; i++)
    {
        int outerLoop = ranks[i];  // store the candidate 'name' (in num)
        for (int j = 0; j < candidate_count; j++)
        {
            int innerLoop = ranks[j];  // store the candidate's 'name' (in num) found in other rank
            if (i < j)
            {
                preferences[outerLoop][innerLoop]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Douple loop through all candidates in preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // compares number of votes for candidate A-B with B-A.
            // updates winner pairs if votes for A-B > B-A.
            // if tie, do not record nor add to pair_count
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int holderWinner, holderLoser;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // get winners scores and compare
            int score1 = preferences[(pairs[i].winner)][(pairs[i]).loser];
            int score2 = preferences[(pairs[j].winner)][(pairs[j]).loser];
            if (score1 < score2)
            {
                // if i < j, replace position i with bigger number & j with smaller number
                holderWinner = pairs[i].winner;
                holderLoser = pairs[i].loser;

                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = holderWinner;
                pairs[j].loser = holderLoser;
            }
        }
    }
    return;
}

// recursive function that returns true/ false
// int p , int l = number of pairs and index of loser repesecitvely

bool no_cycle(int p, int losers)
{
    // base case: do nothing, lock down first winner with greatest victory margin
    if (p == 0)
    {
        return true;
    }

    // check whether loser is winner in previous loop (by checking whether its locked[loser][others] == true)
    else
    {
        for (int i = 0; i < pair_count; i++)
        {
            if (locked[losers][i])
            {
                return false;
            }
        }
        return no_cycle(p - 1, losers);;
    }
}

void lock_pairs(void)
{
    // Run recursion function; if no cycle lock the candidates = true
    for (int p = 0; p < pair_count; p++)
    {
        int winners = pairs[p].winner;
        int losers = pairs[p].loser;

        if (no_cycle(p, losers))
        {
            locked[winners][losers] = true;
        }
        else if (!no_cycle(p, losers))
        {
            locked[winners][losers] = false;
        }
    }
    return;
}


// Print the winner of the election
void print_winner(void)
{
    // loops through locked: locked[others][candidateA] == false -> Candidate A is winner
    for (int i = 0; i < candidate_count; i++)
    {
        // go thru each inner loop to validate
        bool pass = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                pass = false;
                break;
            }
        }

        if (pass)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
