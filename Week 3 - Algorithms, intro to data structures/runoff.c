#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for number of votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank1 , rank2, rank3.. rank number of candidates
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid. Enter a name, is vote valid?
bool vote(int voter, int rank, string name)
{
    //loop through every candidate
    for (int a = 0; a < candidate_count; a++)
    {
        //see if name entered matches a candidate
        if (strcmp(name, candidates[a].name) == 0)
        {
            //matches - store the voters preference
            preferences[voter][rank] = a;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //look at each row - row by row
    for (int b = 0; b < voter_count; b++)
    { 
        //column counter
        int g = 0;
        
        //look at each column in while loop to find the candidate within row that is NOT eliminated
        while (candidates[preferences[b][g]].eliminated == true)
        {
            //next column
            g++;
        }
        
        //add one vote to that condidate
        candidates[preferences[b][g]].votes += 1;
        
    }
    
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //find the majority number by dividing total votes by 2
    int majority = voter_count / 2;

    //loop through each candidate
    for (int a = 0; a < candidate_count; a++)
    {
        //see if anyones vote total is the majority, if so print winner
        if (candidates[a].votes > majority)
        {
            printf("%s\n", candidates[a].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_VOTERS;

    //loop through each candidate
    for (int a = 0; a < candidate_count; a++)
    {
        //looking only at non-eliminated cadidates
        if (!candidates[a].eliminated)
        {
            //if the candidates votes is less than the previous one, store in min variable
            if (candidates[a].votes < min)
            {
                min = candidates[a].votes;
            }
        }
    }

    return min;
}

// Return true if the election is tied between all REMAINING candidates, false otherwise
bool is_tie(int min)
{
    //to count number of candidates with the minimum votes
    int counter = 0;
    //counter for number of candidates still left in running
    int counter2 = 0;

    for (int a = 0; a < candidate_count; a++)
    {
        // if has min number and votes and is still in running, add to counter
        if (candidates[a].votes == min && candidates[a].eliminated == false)
        {
            counter += 1;
        }

        //check to see how many candidates still in running
        if (candidates[a].eliminated == false)
        {
            counter2 += 1;
        }
    }

    //tied only if there is a duplicate AND the number of candidates still in running = number of duplicates (aka all remaining are tied)
    if (counter > 1 && counter == counter2)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    //loop through each candidate
    for (int a = 0; a < candidate_count; a++)
    {
        if (candidates[a].votes == min)
        {
            //change candidates status to eliminated if they = the min votes tabulated
            candidates[a].eliminated = true;
        }
    }

    return;
}
