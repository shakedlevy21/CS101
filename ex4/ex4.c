/******************
Name: Shaked Levy
ID: 212730311
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

//task 1
#define ROBOT_SPACE_SIZE 20

//task 2
#define CHEERLEADERS_WEIGHTS_SIZE 15
#define CHEERLEADERS_LEVELS 5
float Cheerleaders_Weights[CHEERLEADERS_WEIGHTS_SIZE] = {0};
float cheerleaders_array[CHEERLEADERS_LEVELS][CHEERLEADERS_LEVELS];

//task 4
#define QUEENS_SPACE_SIZE 20

//task 5
#define PUZZLE_MAX_SIZE 30
#define MAX_SLOTS_SIZE 100
#define STR_LEN 15
#define COORDINATE_SIZE 3
#define X_COORDINATE 0
#define Y_COORDINATE 1
#define LENGTH_COORDINATE 2

//functions
int task1_robot_paths(char Robot_Space[][ROBOT_SPACE_SIZE], int x, int y);
float task2_human_pyramid(int cheerleader_location, int row, int col);
int task3_parenthesis_validator(char checkFor);
int task4_queens_battle(char Board_Space[][QUEENS_SPACE_SIZE], char Queens_Area[QUEENS_SPACE_SIZE], int dim, int row,
    int col,int index, int placedQueens);
void initBoard(char Board_Space[][QUEENS_SPACE_SIZE], char Queen_Area[QUEENS_SPACE_SIZE],
    int dim, int row, int col, char queenAreaPlace, int index);
int isInQueenArea(char Queen_Area[QUEENS_SPACE_SIZE], int size, int index, char color);
int isValidPoint(char Board_Space[][QUEENS_SPACE_SIZE], int row, int col, int dim, char currentColor);
int checkCol(char Board_Space[][QUEENS_SPACE_SIZE], int col, int dim, int rowIndex);
int checkRow(char Board_Space[][QUEENS_SPACE_SIZE], int row, int dim, int colIndex);
void printBoard(char Board_Space[][QUEENS_SPACE_SIZE], int dim);
int task5_crossword_generator(char Puzzle_Grid[][PUZZLE_MAX_SIZE], int dim, char strings[][STR_LEN], int wordsInDict,
    int slotSize, char directions[], int coordinates[][COORDINATE_SIZE],
    int index_of_string, int index_of_direction, int wordsPlaced);
int insertStrHor(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
    int dim, int indexOfStr, int charIndex, int x, int y);
int insertStrVer(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
    int dim, int indexOfStr, int charIndex, int x, int y);
void removeStrHor(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
    int dim, int indexOfStr, int charIndex, int x, int y);
void removeStrVer(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
    int dim, int indexOfStr, int charIndex, int x, int y);
int checkHor(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y);
int checkVer(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y);

int main()
{
    //for the switch case
    int task = -1;
    //for task 1
    int task1_x_given, task1_y_given;
    char Robot_Space[ROBOT_SPACE_SIZE][ROBOT_SPACE_SIZE] = {
        "####################",
        "#@                 #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "####################",
    };
    //for task 4
    char Board_Space[QUEENS_SPACE_SIZE][QUEENS_SPACE_SIZE];
    char Queen_Area[QUEENS_SPACE_SIZE];

    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");
        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;
            case 1:
                {
                //we will get an input from the user and initialize it according to the array
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &task1_x_given, &task1_y_given);

                //to correct for the boundaries of the array "#" I will add 1
                printf("The total number of paths the robot can take to reach home is: "
                       "%d\n", task1_robot_paths(Robot_Space, task1_x_given+1, task1_y_given+1));
                break;
                }
            case 2:
                {
                    printf("Please enter the weights of the cheerleaders:\n");
                    //for loop just for printing and checking for a negative weight
                    int isNegative = 0;
                    for (int i = 0; i < CHEERLEADERS_WEIGHTS_SIZE; i++) {
                        scanf(" %f", &Cheerleaders_Weights[i]);
                        if (Cheerleaders_Weights[i] < 0) {
                            isNegative = 1;
                            break;
                        }
                    }
                    if (isNegative) {
                        printf("Negative weights are not supported.\n");
                        break;
                    }
                    printf("The total weight on each cheerleader is:\n");
                    int location = 0;
                    for (int i = 1; i <= CHEERLEADERS_LEVELS; i++) {
                        for (int j = 1; j <= i; j++) {
                            printf("%.2f " ,task2_human_pyramid(location,i,j));
                            location++;
                        }
                        printf("\n");
                    }
                    break;
                }
            case 3:
            {
                //we will clear the buffer for using it to scan the string without making a dynamic array
                scanf("%*[^\n]");
                printf("Please enter a term for validation:\n");
                scanf(" ");
                if (task3_parenthesis_validator('\0')) {
                    printf("The parentheses are balanced correctly.\n");
                } else {
                    printf("The parentheses are not balanced correctly.\n");
                }
                break;
            }
            case 4:
            {
                int dim = 0;
                char areaChar;
                printf("Please enter the board dimensions:\n");
                scanf("%d", &dim);
                printf("Please enter a %d*%d puzzle board:\n", dim, dim);
                for (int i = 0; i < dim; i++) {
                    for (int j = 0; j < dim; j++) {
                        scanf(" %c", &areaChar);
                        Board_Space[i][j] = areaChar;
                    }
                }
                // the \0 is just for some NULL char to check if the provided char is different from it
                initBoard(Board_Space, Queen_Area, dim, 0, 0, '\0', 0);

                if(task4_queens_battle(Board_Space, Queen_Area, dim, 0, 0, 0, 0)) {
                    printf("Solution:\n");
                    printBoard(Board_Space, dim);
                }
                else {
                    printf("This puzzle cannot be solved.\n");
                }
                break;
            }
            case 5:
            {
                int dim, slotSize, wordsInDict, coordinates[MAX_SLOTS_SIZE][COORDINATE_SIZE];
                char Puzzle_Grid[PUZZLE_MAX_SIZE][PUZZLE_MAX_SIZE];
                char strings[MAX_SLOTS_SIZE][STR_LEN], directions[STR_LEN];

                printf("Please enter the dimensions of the crossword grid:\n");
                scanf("%d", &dim);
                //loop for initializing the puzzle board
                for (int i = 0; i < dim; i++) {
                    for (int j = 0; j < dim; j++) {
                        Puzzle_Grid[i][j] = '#';
                    }
                }
                printf("Please enter the number of slots in the crossword:\n");
                scanf("%d", &slotSize);
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                //the coordinates array will be the amount of strings and for each one - X,Y and length
                for (int i = 0; i < slotSize; i++) {
                    scanf(" %d %d %d %c", &coordinates[i][0], &coordinates[i][1], &coordinates[i][2], &directions[i]);
                }

                printf("Please enter the number of words in the dictionary:\n");
                do {
                    scanf("%d", &wordsInDict);
                    if (wordsInDict < slotSize) {
                        printf("The dictionary must contain at least %d words."
                               " Please enter a valid dictionary size:\n", slotSize);
                        scanf("%d", &wordsInDict);
                    } else {
                        break;
                    }
                } while (1);

                printf("Please enter the words for the dictionary:\n");
                for (int i = 0; i < wordsInDict; i++) {
                    scanf(" %s", strings[i]);
                }

                task5_crossword_generator(Puzzle_Grid, dim, strings, wordsInDict,
                                    slotSize, directions, coordinates, 0, 0, 0);
                if(task5_crossword_generator(Puzzle_Grid, dim, strings, wordsInDict,
                    slotSize, directions, coordinates, 0, 0, 0)) {
                    for (int i = 0; i < dim; i++) {
                        for (int j = 0; j < dim; j++) {
                            printf("| %c ", Puzzle_Grid[i][j]);
                        }
                        printf("|\n");
                    }
                } else {
                    printf("This crossword cannot be solved.\n");
                }

                break;
                default:
                    printf("Please choose a task number from the list.\n");
                break;
            }
            }
        }
        else
        {
            scanf("%*s");
        }
    } while(task != 6);
}


//end point for task 1 is 1,1 because the array counts the columns upside down
int task1_robot_paths(char Robot_Space[][ROBOT_SPACE_SIZE], int x, int y)
{
    if (Robot_Space[x][y] == '@') {
        return 1;
    }
    if (Robot_Space[x][y] == '#') {
        return 0;
    }
    return task1_robot_paths(Robot_Space, x, y-1) +
        task1_robot_paths(Robot_Space, x-1, y);
}

float task2_human_pyramid(int cheerleader_location, int row, int col)
{
    //this function is looking at the pyramid like a 1D array
    //we will recurse back up every time and return the sum of the above until the first cheerleader
    if(row == 1) {
        return Cheerleaders_Weights[cheerleader_location];
    }

    //we need to go up in a different way on the sides:
    if(col == row) {
        return task2_human_pyramid(cheerleader_location-row, row-1, col-1)/2 +
            Cheerleaders_Weights[cheerleader_location];
    }
    if(col == 1) {
        return task2_human_pyramid(cheerleader_location-row+1, row-1, col)/2 +
            Cheerleaders_Weights[cheerleader_location];
    }

    return task2_human_pyramid(cheerleader_location-row, row-1, col-1)/2 +
           task2_human_pyramid(cheerleader_location-row+1, row-1, col)/2 +
            Cheerleaders_Weights[cheerleader_location];
}


int task3_parenthesis_validator(char checkFor) {
    //char c = (char)getchar();
    char matchingPar;
    char c;
    scanf("%c", &c);
    //end of input check
    if (c == '\0' || c == '\n') {
        if (checkFor == '\0') {
            return 1;
        }
        //if there is still another parenthesis to check at the end than it is not balanced
        return 0;
    }
    //found matching
    if (c == checkFor) {
        return 1;
    }
    //make a matching pair
    if (c == '(') {
        matchingPar = ')';
    }
    else if (c == '{') {
        matchingPar = '}';
    }
    else if (c == '[') {
        matchingPar = ']';
    }
    else if (c == '<') {
        matchingPar = '>';
    }
    //if the current char is not matchiing than go back
    else if (c == ')' || c == '}' || c == ']' || c == '>') {
        return 0;
    }
    else {
        //the char is not a parenthesis than go to next char
        return task3_parenthesis_validator(checkFor);
    }
    //check for next parenthesis
    if (!task3_parenthesis_validator(matchingPar)) {
        return 0;
    }
    //check the next input with the previous checkFor
    return task3_parenthesis_validator(checkFor);
}


int task4_queens_battle(char Board_Space[][QUEENS_SPACE_SIZE], char Queens_Area[QUEENS_SPACE_SIZE],
    int dim, int row, int col, int index, int placedQueens){
    //we placed all the queens
    if (placedQueens == dim) {
        return 1;
    }
    //no solutions
    if (index >= dim) {
        return 0;
    }
    //out of bounds
    if (row >= dim) {
        return 0;
    }
    //out of col - next row
    if (col >= dim) {
        //we will use placedQueens for minimizing the board for less calculation
        return task4_queens_battle(Board_Space, Queens_Area, dim, row+1, 0, index, placedQueens);
    }

    if (Queens_Area[index] == Board_Space[row][col] && isValidPoint(Board_Space, row, col, dim, Queens_Area[index])) {
        char original = Board_Space[row][col]; // save the original char
        Board_Space[row][col] = '-'; // Place the queen
        //we  move to the next column for placing the next queen (index+1)
        if (task4_queens_battle(Board_Space, Queens_Area, dim, 0, col + 1, index + 1, placedQueens+1)) {
            return 1; // If successful, propagate success upwards
        }

        // reverse the change since it didn't lead to a solution
        Board_Space[row][col] = original;
    }
    // if placing at [row][col] did not work out we will try the next column in the same row
    return task4_queens_battle(Board_Space, Queens_Area, dim, row, col + 1, index, placedQueens);


}

int isInQueenArea(char Queen_Area[QUEENS_SPACE_SIZE], int size, int index, char color) {
    if (index >= size) {
        return 1;
    }
    if (Queen_Area[index] == color) {
        return 0;
    }
    return isInQueenArea(Queen_Area, size, index+1, color);
}

void initBoard(char Board_Space[][QUEENS_SPACE_SIZE], char Queen_Area[QUEENS_SPACE_SIZE],
int dim, int row, int col, char queenAreaPlace, int index) {
    //this function is made to make a 1D array of all the different areas in the board
    if (row >= dim) {
        return;
    }
    if (col >= dim) {
        initBoard(Board_Space, Queen_Area, dim, row+1, 0, queenAreaPlace, index);
        return;
    }
    if (isInQueenArea(Queen_Area, dim, 0, Board_Space[row][col])) {
        Queen_Area[index] = Board_Space[row][col];
        initBoard(Board_Space, Queen_Area, dim, row, col+1, queenAreaPlace, index+1);
    } else {
        initBoard(Board_Space, Queen_Area, dim, row, col+1, queenAreaPlace, index);
    }
}

int isValidPoint(char Board_Space[][QUEENS_SPACE_SIZE], int row, int col, int dim, char currentColor) {

    if (row < 0 || col < 0 || row >= dim || col >= dim) {
        return 0; //  out of bounds
    }
    if (currentColor != Board_Space[row][col]) {
        return 0;
    }
    //check for all col and row
    if (!checkCol(Board_Space, col, dim, 0) || !checkRow(Board_Space, row, dim, 0)) {
        return 0;
    }

    //check for around the point
    if ((row - 1 >= 0 && col - 1 >= 0 && Board_Space[row-1][col-1] == '-') || //up left
        (row + 1 < dim && col + 1 < dim && Board_Space[row+1][col+1] == '-') || //down right
        (row - 1 >= 0 && col + 1 < dim && Board_Space[row-1][col+1] == '-') || //up right
        (row + 1 < dim && col - 1 >= 0 && Board_Space[row+1][col-1] == '-')) { //down left
        return 0;
    }
    return 1;

}

int checkCol(char Board_Space[][QUEENS_SPACE_SIZE], int col, int dim, int rowIndex) {
    if (rowIndex >= dim) {
        return 1;
    }
    if (Board_Space[rowIndex][col] == '-') {
        return 0;
    }
    return checkCol(Board_Space, col, dim, rowIndex + 1);
}

int checkRow(char Board_Space[][QUEENS_SPACE_SIZE], int row, int dim, int colIndex) {
    if (colIndex >= dim) {
        return 1;
    }
    if (Board_Space[row][colIndex] == '-') {
        return 0;
    }
    return checkRow(Board_Space, row, dim, colIndex + 1);
}

void printBoard(char Board_Space[][QUEENS_SPACE_SIZE], int dim){
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (Board_Space[i][j] != '-') {
                printf(" * ");
            }
            else {
                printf(" X ");
            }
        }
        printf("\n");
    }
}

int task5_crossword_generator(char Puzzle_Grid[][PUZZLE_MAX_SIZE], int dim, char strings[][STR_LEN], int wordsInDict,
int slotSize, char directions[], int coordinates[][COORDINATE_SIZE], int index_of_string,
int index_of_direction, int wordsPlaced) {
    //to make it easier to see
    int x = coordinates[index_of_direction][X_COORDINATE];
    int y = coordinates[index_of_direction][Y_COORDINATE];
    int placementLength = coordinates[index_of_direction][LENGTH_COORDINATE];
    int wordLength = strlen(strings[index_of_string]);

    //placed all words
    if (wordsPlaced >= wordsInDict) {
        return 1;
    }

    if (index_of_string >= slotSize) {
        return 1;
    }

    //went through all the slots and no place to put the word
    if (index_of_direction >= slotSize) {
        return 0;
    }

    if (directions[index_of_direction] == 'H' && wordLength + y <= dim && wordLength <= placementLength) {
        if (checkHor(Puzzle_Grid, strings, dim, index_of_string, 0, x, y)) {
            insertStrHor(Puzzle_Grid, strings, dim, index_of_string, 0, x, y);
            if (task5_crossword_generator(Puzzle_Grid, dim, strings, wordsInDict, slotSize,
                directions, coordinates, index_of_string+1, 0, wordsPlaced+1)) {
                return 1; // Success
            }
            removeStrHor(Puzzle_Grid, strings, dim, index_of_string, 0, x, y);
        }

    }


    if (directions[index_of_direction] == 'V' && wordLength + x <= dim && wordLength <= placementLength) {
        if (checkVer(Puzzle_Grid, strings, dim, index_of_string, 0, x, y)) {
            insertStrVer(Puzzle_Grid, strings, dim, index_of_string, 0, x, y);
            if (task5_crossword_generator(Puzzle_Grid, dim, strings, wordsInDict, slotSize,
                directions, coordinates, index_of_string+1, 0, wordsPlaced+1)) {
                return 1; // Success
            }
            //remove the word if did not get a solution
            removeStrVer(Puzzle_Grid, strings, dim, index_of_string, 0, x, y);
        }
    }


    return task5_crossword_generator(Puzzle_Grid, dim, strings, wordsInDict,
        slotSize, directions, coordinates, index_of_string, index_of_direction+1, wordsPlaced);
}

int insertStrHor(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y) {

    if (charIndex >= (int)strlen(strings[indexOfStr])) {
        return 1;
    }
    if (Puzzle_Grid[x][y] != '#' && Puzzle_Grid[x][y] != strings[indexOfStr][charIndex]) {
        return 0;
    }
    Puzzle_Grid[x][y] = strings[indexOfStr][charIndex];
    return insertStrHor(Puzzle_Grid, strings, dim, indexOfStr, charIndex+1, x, y+1);
}

int insertStrVer(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y) {

    if (charIndex >= (int)strlen(strings[indexOfStr])) {
        return 1;
    }
    if (Puzzle_Grid[x][y] != '#' && Puzzle_Grid[x][y] != strings[indexOfStr][charIndex]) {
        return 0;
    }
    Puzzle_Grid[x][y] = strings[indexOfStr][charIndex];
    return insertStrVer(Puzzle_Grid, strings, dim, indexOfStr, charIndex+1, x+1, y);
}

void removeStrHor(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y) {

    if (charIndex >= (int)strlen(strings[indexOfStr])) {
        return;
    }
    Puzzle_Grid[x][y] = '#';
    removeStrHor(Puzzle_Grid, strings, dim, indexOfStr, charIndex+1, x, y+1);
}

void removeStrVer(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y) {

    if (charIndex >= (int)strlen(strings[indexOfStr])) {
        return;
    }
    Puzzle_Grid[x][y] = '#';
    removeStrVer(Puzzle_Grid, strings, dim, indexOfStr, charIndex+1, x+1, y);
}

int checkHor(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y) {

    if (charIndex >= (int)strlen(strings[indexOfStr])) {
        return 1;
    }
    if (Puzzle_Grid[x][y] != '#' && Puzzle_Grid[x][y] != strings[indexOfStr][charIndex]) {
        return 0;
    }
    return checkHor(Puzzle_Grid, strings, dim, indexOfStr, charIndex+1, x, y+1);
}

int checkVer(char Puzzle_Grid[][PUZZLE_MAX_SIZE], char strings[][STR_LEN],
int dim, int indexOfStr, int charIndex, int x, int y) {

    if (charIndex >= (int)strlen(strings[indexOfStr])) {
        return 1;
    }
    if (Puzzle_Grid[x][y] != '#' && Puzzle_Grid[x][y] != strings[indexOfStr][charIndex]) {
        return 0;
    }
    return checkVer(Puzzle_Grid, strings, dim, indexOfStr, charIndex+1, x+1, y);
}