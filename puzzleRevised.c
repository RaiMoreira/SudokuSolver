#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define numRows 9
#define numCols 9
#define numValues 9
#define numBoxWidth 3

int grid[numRows][numCols];

int valid (int row, int col, int val);
int solve (int row, int col);

int main(int argc,char *argv[]){

char ch;
int i = 0, j = 0, idx = 0;
int temp;
int buffer[150];   

if (argc != 2)
  {
    fprintf(stderr,"Usage : %s invalid number of arguments\n",argv[0]);
    exit(0);
  }


FILE *file;
file = fopen(argv[1], "r");
if (file == NULL)
{
	fprintf(stderr, "cannot open file for reading\n");
	exit(0);
}


ch = fgetc(file);
printf("problem:\n");	
while (ch != EOF)
    {
        printf ("%c", ch);
        ch = fgetc(file);
    }
rewind(file);


while ((temp = fgetc(file)) != EOF) 
{
if ( temp == '+' || temp == '-' || temp == '|' || temp == '\n') continue;
if (temp == ' ') temp = '0';
buffer[i] = temp - 0;
i++;
}

for (int r=0; r<9; r++){
	for(int c=0; c<9; c++){
	grid[r][c] = buffer[idx++] - '0';
	}
}


	if (solve(0, 0)) {
		printf("solution:\n");
		
		for (int row = 0; row < numRows; row++) {
			printf("+-+-+-+-+-+-+-+-+-+\n|");
			for (int col = 0; col < numCols; col++) {
				printf("%d|", grid[row][col]);
			}
			
			printf("\n");
		}
	printf("+-+-+-+-+-+-+-+-+-+\n");	
	}
	else
		printf("is not solvable\n");
	
return EXIT_SUCCESS;
}

int valid (int row, int col, int val) {
	for (int n = 0; n < numRows; n++) {
		if (grid[n][col] == val || grid[row][n] == val)
			return 0;
	}
	
	int sRow = (row / numBoxWidth) * numBoxWidth;
	int sCol = (col / numBoxWidth) * numBoxWidth;
	
	for (int r = sRow; r < sRow + numBoxWidth; r++) {
		for (int c = sCol; c < sCol + numBoxWidth; c++) {
			if (grid[r][c] == val)
				return 0;
		}
	}
	
	return 1;
}



int solve (int row, int col) {
	if (row == numRows)
		return 1;
	
	if (grid[row][col] != 0) {
		if (col == 8)
			return solve(row + 1, 0);
		
		return solve(row, col + 1);
	}
	
	for (int val = 1; val <= numValues; val++) {
		if (valid(row, col, val)) {
			grid[row][col] = val;
			
			if (col == 8) {
				if (solve(row + 1, 0))
					return 1;
			}
			else {
				if (solve(row, col + 1))
					return 1;
			}
		}
	}
	
	grid[row][col] = 0;
	
	return 0;
}


