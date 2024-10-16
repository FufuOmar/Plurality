#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(name, candidates[i].name) == 0){ //Goes through every candidate to see if user input name matches a candidate, and adds a vote
            candidates[i].votes++;
            return true;
        }
    }
   return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate temp;
    int tieCount = 0;
    if(candidate_count == 1) //If only 1 person running, they win
    {
        printf("%s\n", candidates[0].name);
    }
    else
    {
        //Ranking each candidate based on votes
        for(int i = 0; i < candidate_count-1; i++)
        {
            if(candidates[i].votes<candidates[i+1].votes)
            {
            temp = candidates[i+1];
            candidates[i+1] = candidates[i];
            candidates[i] = temp;
            }
        }

        //Checking for tie (and how many)
        for(int i = 0; i < candidate_count-1; i++)
        {
            if(candidates[0].votes == candidates[i+1].votes){
                tieCount++;
            }
        }

        //Prints out all the names of people who tied for 1st
        if(tieCount>0){
             for(int i = 0; i <= tieCount; i++)
             {
                printf("%s\n", candidates[i].name);
             }
        }
        else //Prints out the name with the most votes
        {
            printf("%s\n", candidates[0].name);
        }
    }
    return;
}