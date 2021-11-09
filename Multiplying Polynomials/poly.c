#include "List.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// returns true if c is +
int isPlus(char c) { return c == '+'; }

// returns true if c is -
int isMinus(char c) { return c == '-'; }

// returns true if c in [a..z]
int isVar(char c) { return c >= 'a' && c <= 'z'; }

// returns true if c is ^
int isPower(char c) { return c == '^'; }

// returns true if c is blank or tab
int isWhite(char c) { return c == ' ' || c == '\t'; }

// max length of string
#define MAX_LEN 1000

// defining additional functions
void parse_order_poly(char *line, int len, List *ordered_deg,
                      List *ordered_coef, char *var);
void print_poly(List deg, List coef, char var);
void multiply_polys(List deg1, List coef1, char v1, List deg2, List coef2,
                    char v2, List *result_deg, List *result_coef);

int get_val(List L, int index);

int main(void) {

  // max len of char input
  char line[MAX_LEN];
  int len;

  fgets(line, MAX_LEN, stdin);
  len = strlen(line);
  List p1_deg, p1_coef;
  char v1, v2;
  parse_order_poly(line, len, &p1_deg, &p1_coef, &v1);

  fgets(line, MAX_LEN, stdin);
  len = strlen(line);
  List p2_deg, p2_coef;
  parse_order_poly(line, len, &p2_deg, &p2_coef, &v2);

  print_poly(p1_deg, p1_coef, v1);
  puts("multiply by");
  print_poly(p2_deg, p2_coef, v2);
  puts("is");
  List rdeg, rcoef;
  multiply_polys(p1_deg, p1_coef, v1, p2_deg, p2_coef, v2, &rdeg, &rcoef);
  print_poly(rdeg, rcoef, v1);
  puts("which simplifies to ");

  // simplifies poly
  int d, c, ret;
  List simplified_d = newList();
  List simplified_c = newList();
  while (length(rdeg)) {
    d = delElement(rdeg, 0);
    c = delElement(rcoef, 0);
    ret = find(rdeg, d);
    while (ret >= 0) {
      // add all coef's of same degree
      c += delElement(rcoef, ret);
      delElement(rdeg, ret);
      ret = find(rdeg, d);
    }
    if (c) {
      appendList(simplified_d, d);
      appendList(simplified_c, c);
    }
  }

  // prints final simplified poly
  print_poly(simplified_d, simplified_c, v1);

  freeList(&p1_deg);
  freeList(&p1_coef);
  freeList(&p2_deg);
  freeList(&p2_coef);
  freeList(&rdeg);
  freeList(&rcoef);
  freeList(&simplified_d);
  freeList(&simplified_c);

  return 0;
}

void multiply_polys(List deg1, List coef1, char v1, List deg2, List coef2,
                    char v2, List *result_deg, List *result_coef) {
  if (v1 != v2) {
    puts("Error mismatched variables");
    exit(-1);
  }

  List resc = newList();
  List resd = newList();
  for (int i = 0; i < length(deg1); i++) {
    for (int j = 0; j < length(deg2); j++) {
      appendList(resc, get_val(coef1, i) * get_val(coef2, j));
      appendList(resd, get_val(deg1, i) + get_val(deg2, j));
    }
  }

  *result_deg = resd;
  *result_coef = resc;
}

void print_poly(List deg, List coef, char var) {
  int c, d;
  for (int i = 0; i < length(deg); i++) {
    c = get_val(coef, i);
    d = get_val(deg, i);
    if ((c != 1 && c != -1) || !d) {
      printf("%d", (c > 0 || !i) ? c : -c);
    }

    // for the first term only, print the '-' for coef -1 non-zero degree
    if (c == -1 && d && !i) {
      putchar('-');
    }
    if (d) {
      printf("%c", var);
    }
    if (d > 1) {
      printf("^%d", d);
    }

    if (i != length(deg) - 1) {
      c = get_val(coef, i + 1);
      if (c > 0) {
        printf(" + ");
      } else {
        printf(" - ");
      }
    }
  }
  putchar('\n');
}

void parse_order_poly(char *line, int len, List *ordered_deg,
                      List *ordered_coef, char *var) {
  List p1_degree = newList();
  List p1_coef = newList();

  int i = 0, negative = 0;
  while (i < len) {
    while (isspace(line[i]))
      i++;
    if (i >= len) {
      // shouldn't happen
      break;
    }

    // puts coefficients and degrees into lists
    if (isdigit(line[i]) || (line[i] == '-' && isdigit(line[i + 1]))) {
      if (!negative) {
        appendList(p1_coef, atoi(&line[i]));
      } else {
        appendList(p1_coef, -atoi(&line[i]));
      }
      if (line[i] == '-')
        i++;
      while (isdigit(line[i]))
        i++;
    } else if (line[i] == '-' && isVar(line[i + 1])) {
      appendList(p1_coef, -1);
      i++;
    } else {
      appendList(p1_coef, (negative) ? -1 : 1);
    }

    if (i >= len) {
      appendList(p1_degree, 0);
      break;
    }

    if (isspace(line[i])) {
      appendList(p1_degree, 0);
      goto add_sub;
    }

    if (!isVar(line[i])) {
      // for debugging
      printf("expected variable, got '%c' at %d\n", line[i], i);
      return;
    } else {
      *var = line[i];
      i++;
    }

    if (i >= len) {
      appendList(p1_degree, 1);
      break;
    }

    if (isspace(line[i])) {
      appendList(p1_degree, 1);
      goto add_sub;
    }

    if (line[i] == '^') {
      i++;
      appendList(p1_degree, atoi(&line[i]));
      while (isdigit(line[i]))
        i++;
    } else {
      appendList(p1_degree, 1);
    }

  add_sub:
    while (isspace(line[i]))
      i++;
    if (line[i] == '+') {
      negative = 0;
      i++;
    } else if (line[i] == '-') {
      negative = 1;
      i++;
    }
  }

  *ordered_coef = newList();
  *ordered_deg = newList();

  int m;
  while (length(p1_degree)) {
    m = max(p1_degree);
    appendList(*ordered_coef, delElement(p1_coef, m));
    appendList(*ordered_deg, delElement(p1_degree, m));
  }

  freeList(&p1_coef);
  freeList(&p1_degree);
}
