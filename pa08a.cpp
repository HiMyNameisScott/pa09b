/// @file pa08
/// @author Scott T. Koss <Scott.Koss@student.csn.edu>
/// @date 04/13/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Shoots and Ladders, processes inputs and displays thed position of a player using arrays
/// @note

#include <iostream>

using namespace std;

void information(int &players, int &dieRolls, int &snakeLads);
void initializePlayers(int playerArray[], int players);
void placeSnakesAndLadders(int snakeLads, int gameBoard[]);
void diceHandler(int playerArray[], int dieRolls, int gameBoard[]);
void placement(int playerArray[], int players);

int main()
{
    int testCases;              //  Number of times for program to be run.
    int players;                //  Number of players in the game
    int dieRolls;               //  Number of dierolls to be processed
    int snakeLads;              //  number of snakes and Ladders to be processed
    int gameBoard[99] = {0};    //  Tracks snakes and ladders
    int playerArray[999] = {0}; //  Tracks a players spot on the game board.

    // input
    cin >> testCases;
    for (int i = 0; i < testCases; i++)
    {
        information(players, dieRolls, snakeLads);

        // process/Setup
        initializePlayers(playerArray, players);
        placeSnakesAndLadders(snakeLads, gameBoard);
        diceHandler(playerArray, dieRolls, gameBoard);

        // output

        placement(playerArray, players);
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Functions!
////////////////////////////////////////////////////////////////////////////////

void diceHandler(int playerArray[], int dieRolls, int gameBoard[])
{

    int roll;      //  Used to store roll
    int count = 0; //  Used for count, as i is used for tracking the players not the # of rolls to be processed.

    for (int i = 0; count < dieRolls; i++)
    {
        cin >> roll;
        if (playerArray[i] >= 1)
        {
            playerArray[i] += roll;
        }
        else
        {
            i = 0;
        }

        if (gameBoard[playerArray[i]] != 0)
        {
            playerArray[i] += gameBoard[playerArray[i]];
        }

        if (playerArray[i] < 1)
        {
            playerArray[i] = 1;
        }

        if (playerArray[i] >= 100)
        {
            count = dieRolls;
            playerArray[i] = 100;
        }

        count += 1;
    }
}

/// This does not return anything, it simply just changes the variable directly, however this function handles
/// the dice rolls and board palcement. Also checks to make sure that we are not above 100 or below 0.
///@param playerArray  This will access the player array, or player positions.
///@param dieRolls  This is to check the # of die rolls to be processed.
///@param gameBoard  This is used to check wheter or not the player is on a snake or ladder.

void information(int &players, int &dieRolls, int &snakeLads)
{

    cin >> players >> snakeLads >> dieRolls;
}

///  Does not return anything, this function is used to simply take in the data from input.
///  @param &players This will access the int for the # of players, and assign the players
///  @param &dieRolls This will acess the int for the # of die rolls, and assign dice rolls
///  @param &snakeLads this is the var for the # of snakes and ladders to be processed.


void initializePlayers(int playerArray[], int players)
{
    for (int i = 0; i < players; i++)
    {
        playerArray[i] = 1;
    }
}

///  Player array is set to {0} so when checking for who is a player we only check if the player is 'initialized'
///  or has as value of 1 or more in order to see if they are active.
///  @param playerArray[] access player array to initialize the number of people actually playing the game
///  @param players will initialize to the appropriate number of players.

void placement(int playerArray[], int players)
{
    for (int i = 0; i < players; i++)
    {
        cout << "Player " << i + 1 << " is at position " << playerArray[i]
             << "." << endl;
    }
}

///  This funciton is used for outputting the position of the players
///  @param playerArray[] this is where data is kept for the players position on the board.
///  @param players[] This is used to output where the player is and reference where they are at on the board.

void placeSnakesAndLadders(int snakeLads, int gameBoard[])
{
    int start;   //  Where the snake/Lad Starts
    int stop;    //  Where the snake/Lad Ends
    int landing; //  The difference between start and stop
    for (int i = 0; i < snakeLads; i++)
    {
        cin >> start;
        cin >> stop;
        landing = stop - start;
        gameBoard[start] = landing;
    }
}

///  This function takes in and places the snake and ladders on the game board.
///  @param snakeLads This is the number of snakes or ladders we need to process
///  @param gameBoard This is the gameboard where we will add the snakes and ladders

