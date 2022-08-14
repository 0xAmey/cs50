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
    int i = 0;
    while(candidates[i]) {
        if(strcmp(candidates[i], name) == 0) {
            // printf("%i\n", rank);
            // printf("%i\n", i);
            ranks[rank] = i;
            // printf("%i\n", ranks[rank]);
            return true;
        }
        i++;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        for(int j = i+1; j< candidate_count; j++) {
                preferences[ranks[i]][ranks[j]] += 1;
        }
        //printf("%i\n", preferences[ranks[i]][ranks[i+1]]);
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i+1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pair myPair = {i, j};
                pairs[pair_count] = myPair;
                pair_count += 1;
            }
            else if(preferences[j][i] > preferences[i][j]) {
                pair myPair = {j, i};
                pairs[pair_count] = myPair;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int i, j;
    for (i = 0; i < pair_count-1; i++) {
        for (j = 0; j < pair_count-i-1; j++) {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j+1].winner][pairs[j+1].loser]) {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }
    return;
}

bool cycle(end, cycle_start) {
        if (end == cycle_start) {
            return true;
        }
        for (int i = 0; i < candidate_count; i++ ) {
            if(locked[end][i]) {
                if(cycle(i, cycle_start)){
                    return true;
                }
            }
        }
        return false;
    }

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // deciding to lock a pair or not
    bool isTrue = true;
    for (int i = 0; i < pair_count; i++) {
        if(!cycle(pairs[i].loser, pairs[i].winner))
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

// Tally: Once all of the voters have indicated all of their preferences,determine,
// for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
//
// Sort: Sort the pairs of candidates in decreasing order of strength of victory,
// where strength of victory is defined to be the number of voters who prefer the preferred candidate.
//
// Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in”
// each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.
