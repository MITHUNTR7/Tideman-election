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
void winner_margin(void);
bool helper(int a, int b);

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
        if (strcmp(name, candidates[i]) == 0) // Checks whether name is there in candidates array
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{


    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{



    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                pairs[i + j - 1].winner = i;
                pairs[i + j - 1].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[i + j - 1].winner = j;
                pairs[i + j - 1].loser = i;
                pair_count ++;
            }
            else if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }
        }
    }
    return;
}




// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    pair swap[1];
    int max_index;
    for (int i = 0; i < pair_count - 1; i++)
    {
        max_index = i;

        int margin1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        for (int j = i + 1; j < pair_count; j++)
        {
            int margin2 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (margin1 < margin2)
            {
                max_index = j;
            }
        }

        if (max_index != i)
        {
            swap[0] = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = swap[i];
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        if (!helper(pairs[i].loser, pairs[i].winner)) // Checks whether helper function return false
        {
            locked[pairs[i].winner][pairs[i].loser] = true; // Locking the graph from i to j
        }

    }
    return;
}
// Checks whether the loser is a winner with some locked other pair
bool helper(int x, int y)
{
    if (locked[x][y] == true)
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {

        if (locked[x][j] == false)
        {
            continue;
        }
        else if (locked[x][j] == true)
        {
            int temp = j; // This variable is for the special case where final pair forms cycle
            if (helper(temp, y) == true)
            {
                return true;
            }
        }
    }
    return false;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int counter = 0; // Variable to keep track of number of false counters
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                counter ++;
                continue;
            }
            else if (locked[j][i] == false)
            {
                counter ++;
                continue;
            }
            else if (locked[j][i] == true)
            {
                break; // If there is a arrow pointing at i then it is not the source
            }
        }
        if (counter == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
