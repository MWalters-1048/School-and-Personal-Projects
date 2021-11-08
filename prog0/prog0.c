// prog0

#include <stdio.h>
#include <stdlib.h>

int rows, cols, bound, color, x, y;

void color_shape(int x, int y, int color, int bound, int **matrix) {


  // base case
  if (matrix[x][y] == bound || matrix[x][y] == color) {
    return;
  }


  // coloring element in matrix
  matrix[x][y] = color;

  // checks boundaries
  // then recursivly colors north, east, south, west
  if ((x + 1) < rows && (x + 1) > 0 && y < cols) {
    color_shape(x + 1, y, color, bound, matrix);
 }

 if (x < rows && (y + 1) < cols && (y + 1) > 0) {
   color_shape(x, y + 1, color, bound, matrix);
 }

  if ((x - 1) < rows && (x - 1) >= 0 && y < cols && y >= 0) {
    color_shape(x - 1, y, color, bound, matrix);
  }

  if (x < rows && x >= 0 && (y - 1) < cols && (y - 1) >= 0) {
    color_shape(x, y - 1, color, bound, matrix);
  }

  return;
}

int main(void) {

  fscanf(stdin, "%d %d", &rows, &cols);
  fscanf(stdin, "%d", &bound);
  fscanf(stdin, "%d", &color);
  fscanf(stdin, "%d %d", &x, &y);

  // allocating memory for matrix
  int **matrix = (int **)calloc(rows, sizeof(int *));

  for (int i = 0; i < rows; i++) {
    matrix[i] = (int *)calloc(cols, sizeof(int));
  }

  // scanning in elements to matrix
  // from lab section
  int cue;
  int i = 0;
  int j = 0;
  while (fscanf(stdin, "%d", &cue) != EOF) {
    matrix[i][j] = cue;
    if (j < cols - 1) {
      j++;
    } else {
      j = 0;
      i++;
    }
  }

  // calling recursive function
  color_shape(x, y, color, bound, matrix);

  // prints colored matrix
  // from lab section
  for (int i = 0; i < rows; i++) {
    putchar('\n');
    for (int j = 0; j < cols; j++) {
      printf("%d\t", matrix[i][j]);
    }
  }
  return 0;
}
