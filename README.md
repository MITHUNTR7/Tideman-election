# Ranked Pairs Voting System

This is a C program that simulates a Tideman election, implementing the Ranked Pairs voting system. The program takes candidate names and voter preferences as input and determines the winner of the election using the Tideman algorithm.

## How it Works

The program uses the following data structures and functions:

- `int preferences[MAX][MAX]`: A two-dimensional array to store the number of voters who prefer one candidate over another.
- `bool locked[MAX][MAX]`: A two-dimensional boolean array to represent the candidate graph, indicating whether one candidate is locked in over another.
- `typedef struct pair`: A struct to represent a pair of candidates with a winner and loser.
- `string candidates[MAX]`: An array of strings representing the names of candidates.
- `pair pairs[MAX * (MAX - 1) / 2]`: An array to store all pairs of candidates with one being preferred over the other.
- `bool vote(int rank, string name, int ranks[])`: Function to record a voter's preference for a candidate based on their rank.
- `void record_preferences(int ranks[])`: Function to update the global preferences array based on each voter's ranks.
- `void add_pairs(void)`: Function to add pairs of candidates where one is preferred over the other to the pairs array.
- `void sort_pairs(void)`: Function to sort the pairs array in decreasing order of strength of victory.
- `void lock_pairs(void)`: Function to create the locked graph by adding edges in decreasing order of victory strength, without creating cycles.
- `void print_winner(void)`: Function to print out the name of the candidate who is the winner of the Tideman election.

## How to Use

1. Compile the `tideman.c` file using a C compiler.
2. Run the compiled executable.
3. Provide the names of candidates when prompted.
4. Enter the number of voters and their ranked preferences for the candidates.
5. The program will calculate the winner of the election using the Ranked Pairs algorithm and display the result.

## Project Notes

- The implementation follows the CS50x problem set requirements and adheres to the specified function prototypes.
- The program correctly records voter preferences, creates pairs based on preferences, and sorts them in order of strength of victory.
- It then locks pairs into the graph without creating cycles and identifies the winner as the source of the graph.

Feel free to explore and modify the code to suit your needs. Happy voting!

