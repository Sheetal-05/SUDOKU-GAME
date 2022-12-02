#include <iostream>
#define N 9
using namespace std;


// the fixed grid 
int fgrid[N][N] = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
    
    };

// The unsolved grid
    int grid[N][N] = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
    
    };

// To show the grid
void show_grid()
{
  for (int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
    {
      if (col == 3 || col == 6)
        cout << " | ";
      cout << grid[row][col] << " ";
    }
    if (row == 2 || row == 5)
    {
      cout << endl;
      for (int i = 0; i < N; i++)
        cout << "---";
    }
    cout << endl;
  }
}



// store the value entred by user

int updated_grid(int row, int col, int value)
{

  grid[row][col] = value;
  return 0;
}

// to play the game
void game(int choice)
{
  int row, col, value;

  while (choice == 1)
  {
    int ch;
    cout << "TO CONTINUE PRESS '1' AND TO QUIT PRESS '0' :" << endl;
    cin >> choice;
    if (choice == 1)
    {
      cout << "KINDLY ENTER THE VALUE OF ROW [0-8] : " << endl;
      cin >> row;

      cout << "KINDLY ENTER THE VALUE OF COLUMN [0-8] :" << endl;
      cin >> col;

      // to check the blank spaces only
      if (fgrid[row][col] == 0)
      {
        cout << "KINDLY ENTER THE NUMBER [1-9] :" << endl;
        cin >> value;

        cout << endl;

        cout << "YOUR RESPONSE HAS BEEN STORED : ";
        cout << endl;
        updated_grid(row, col, value);
        cout << endl;
        show_grid();
        cout << endl;
      }
      else
      {
        // you can not change the already existed number
        cout << "------------------------------------INVALID PLACE !!---------------------------------------" << endl;
      }
    }

    else
    {
      exit;
    }
  }
}

// -----------------------using sudoku solver to find the correct solution-----------------


#include <iostream>
#define N 9
using namespace std;
int xgrid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                  {5, 2, 0, 0, 0, 0, 0, 0, 0},
                  {0, 8, 7, 0, 0, 0, 0, 3, 1},
                  {0, 0, 3, 0, 1, 0, 0, 8, 0},
                  {9, 0, 0, 8, 6, 3, 0, 0, 5},
                  {0, 5, 0, 0, 9, 0, 6, 0, 0},
                  {1, 3, 0, 0, 0, 0, 2, 5, 0},
                  {0, 0, 0, 0, 0, 0, 0, 7, 4},
                  {0, 0, 5, 2, 0, 6, 3, 0, 0}};

                  
bool isPresentInCol(int col, int num)
{ // check whether num is present in col or not
    for (int row = 0; row < N; row++)
        if (xgrid[row][col] == num)
            return true;
    return false;
}
bool isPresentInRow(int row, int num)
{ // check whether num is present in row or not
    for (int col = 0; col < N; col++)
        if (xgrid[row][col] == num)
            return true;
    return false;
}
bool isPresentInBox(int boxStartRow, int boxStartCol, int num)
{ // check whether num is present in 3x3 box or not
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (xgrid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}
void sudokuGrid()
{ // print the sudoku grid after solve
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if (col == 3 || col == 6)
                cout << " | ";
            cout << xgrid[row][col] << " ";
        }
        if (row == 2 || row == 5)
        {
            cout << endl;
            for (int i = 0; i < N; i++)
                cout << "---";
        }
        cout << endl;
    }
}
bool findEmptyPlace(int &row, int &col)
{ // get empty location and update row and column
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (xgrid[row][col] == 0) // marked with 0 is empty
                return true;
    return false;
}
bool isValidPlace(int row, int col, int num)
{
    // when item not found in col, row and current 3x3 box
    return !isPresentInRow(row, num) && !isPresentInCol(col, num) &&
           !isPresentInBox(row - row % 3, col - col % 3, num);
}
bool solveSudoku()
{
    int row, col;
    if (!findEmptyPlace(row, col))
        return true; // when all places are filled
    for (int num = 1; num <= 9; num++)
    { // valid numbers are 1 - 9
        if (isValidPlace(row, col, num))
        { // check validation, if yes, put the number in the grid
            xgrid[row][col] = num;
            if (solveSudoku()) // recursively go for other rooms in the grid
                return true;
            xgrid[row][col] = 0; // turn to unassigned space when conditions are not satisfied
        }
    }
    return false;
}


void correct_solution(){
    
    if (solveSudoku() == true)
        sudokuGrid();
    else
        cout << "No solution exists";
}


// solution of the given sudoku
int result_grid[N][N] = {
    {3, 1, 6, 5, 7, 8, 4, 9, 2},
    {5, 2, 9, 1, 3, 4, 7, 6, 8},
    {4, 8, 7, 6, 2, 9, 5, 3, 1},
    {2, 6, 3, 4, 1, 5, 9, 8, 7},
    {9, 0, 0, 8, 6, 3, 1, 2, 5},
    {5, 5, 1, 7, 9, 2, 6, 4, 3},
    {1, 3, 8, 9, 4, 7, 2, 5, 6},
    {6, 9, 2, 3, 5, 1, 8, 7, 4},
    {7, 4, 5, 2, 8, 6, 3, 1, 9}};

// show result grid
int show_resultgrid()
{
  for (int row = 0; row < N; row++)
  {
    for (int col = 0; col < N; col++)
    {
      if (col == 3 || col == 6)
        cout << " | ";
      cout << result_grid[row][col] << " ";
    }
    if (row == 2 || row == 5)
    {
      cout << endl;
      for (int i = 0; i < N; i++)
        cout << "---";
    }
    cout << endl;
  }
  return 0;
}

// --------------------------------------------main function-----------------------------------------------

int main()

{
  cout << endl
       << "*****************************************************----<-SUDOKU GAME->----************************************************" << endl;
  cout << endl;
  cout << "###############################################------<-WELCOME->-------####################################################";
  cout << endl;
  cout << endl
       << "SOLVE THE GIVEN SUDOKU :" << endl;
  cout << endl;

  show_grid();
  cout << endl;
  int choice;

  cout << endl
       << "ARE YOU READY? PLEASE PRESS '1' :" << endl;

  cin >> choice;

  game(choice);

  cout << "#############################################---<-THE END->----###############################################";

  cout << endl;
  cout << endl;

  // for submitting the solution:
  int row, col, value, result;
  cout << "TO SUBMIT YOUR SOLUTION KINDLY PRESS '2': " << endl;
  cin >> result;

  if (result == 2)
  {

    if (updated_grid(row, col, value) == result_grid[8][8])
    {
      cout << "##########################----WOHOOO !!! --CONGRATULATIONS YOU WON !!!!----!##############################" << endl;
    }
    else
    {
      cout << "############################### -------BETTER LUCK NEXT TIME!!------ #######################################" << endl;
    }
  }

  // for the correct solution:
  int place;
  cout<<endl;
  cout << "TO SEE THE SOLVED SUDOKU KINDLY PRESS '5' :" << endl;
  cin >> place;
  cout << endl;
  if (place == 5)
  {
    cout << "**********************************--------------THE CORRECT SOLUTION IS:------------------*********************************** " << endl;
    cout<<endl;
    correct_solution();
    cout << endl;
  }
}
