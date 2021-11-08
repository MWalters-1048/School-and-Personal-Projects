#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h> 

#include "List.h"

#define FIRST_TEST Empty_length
#define MAXSCORE 30

static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;

enum Test_e {
  Empty_length = 0,
  Append_length,
  Delete_length,

  Max_index,
  Find_index,
  Append_index,
  Delete_index,

  Empty_equals,
  Append_equals,
  Delete_equals,

  NUM_TESTS,
};

char *testName(int test) {
  if (test == Empty_length) return "Empty_length";
  if (test == Append_length) return "Append_length";
  if (test == Delete_length) return "Delete_length";

  if (test == Max_index) return "Max_index";
  if (test == Find_index) return "Find_index";
  if (test == Append_index) return "Append_index";
  if (test == Delete_index) return "Delete_index";

  if (test == Empty_equals) return "Empty_equals";
  if (test == Append_equals) return "Append_equals";
  if (test == Delete_equals) return "Delete_equals";

  return "";
}

uint8_t runTest(List *pA, int test) {
//   printf("case %s\n", testName(test));
  List A = *pA;
  switch(test) {
    case Empty_length: {
        if (length(A) != 0) return 1;
        return 0;
    }
    case Append_length: {
        appendList(A, 3);
        if (length(A) != 1) return 1;

        appendList(A, 1);
        appendList(A, -2);
        appendList(A, 0);
        if (length(A) != 4) return 2;
        return 0;
    }
    case Delete_length: {
        appendList(A, 3);
        appendList(A, 1);
        delElement(A, 0);
        if (length(A) != 1) return 1;

        appendList(A, 1);
        appendList(A, -2);
        appendList(A, 0);
        delElement(A, 0);
        delElement(A, 0);
        if (length(A) != 2) return 2;

        appendList(A, 7);
        if (length(A) != 3) return 3;

        delElement(A, 2);
        delElement(A, 1);
        delElement(A, 0);
        if (length(A) != 0) return 4;
        return 0;
    }
    case Max_index: {
        appendList(A, 1);
        appendList(A, 9);
        appendList(A, 10);
        appendList(A, 7);
        appendList(A, 3);
        if (max(A) != 2) return 1;
        return 0;
    }
    case Find_index: {
        appendList(A, 1);
        appendList(A, 9);
        appendList(A, 10);
        appendList(A, 7);
        appendList(A, 3);
        if (find(A, 10) != 2) return 1;
        if (find(A, 15) != -1) return 2;
        return 0;
    }
    case Append_index: {
        appendList(A, 1);
        appendList(A, 9);
        appendList(A, 10);
        appendList(A, 7);
        appendList(A, 3);
        appendList(A, 10);
        if (max(A) != find(A, 10)) return 1;

        appendList(A, 15);
        if (max(A) != find(A, 15)) return 2;
        return 0;
    }
    case Delete_index: {
        appendList(A, 1);
        appendList(A, 9);
        appendList(A, 10);
        appendList(A, 7);
        appendList(A, 3);
        appendList(A, 10);
        delElement(A, 5);
        delElement(A, 2);
        if (max(A) != 1) return 1;
        if (find(A, 10) != -1) return 2;

        delElement(A, 0);
        delElement(A, 0);
        delElement(A, 0);
        delElement(A, 0);
        if (find(A, 7) != -1) return 3;
        return 0;
    }
    case Empty_equals: {
        char string[100];
        freopen("/dev/null", "a", stdout);
        setbuf(stdout, string);
        freopen ("/dev/tty", "a", stdout);
        if (!strcmp(string, "")) return 1;
        return 0;
    }
    case Append_equals: {
        appendList(A, 1);
        appendList(A, 9);
        appendList(A, 10);
        appendList(A, 7);
        appendList(A, 3);
        char* string = calloc(100, sizeof(char));
        freopen("/dev/null", "a", stdout);
        setbuf(stdout, string);
        printList(A);
        string[strlen(string)-1] = '\0';
        freopen ("/dev/tty", "a", stdout);
        if (strcmp(string, "1, 9, 10, 7, 3, ") != 0) {
            printf("[Expect]: \"1, 9, 10, 7, 3, \"\n");
            printf("[Actual]: \"%s\"\n", string);
            return 1;
        }

        appendList(A, 15);
        appendList(A, -1);
        free(string);
        string = calloc(100, sizeof(char));
        freopen("/dev/null", "a", stdout);
        setbuf(stdout, string);
        printList(A);
        string[strlen(string)-1] = '\0';
        freopen ("/dev/tty", "a", stdout);
        if (strcmp(string, "1, 9, 10, 7, 3, 15, -1, ") != 0) {
            printf("[Expect]: \"1, 9, 10, 7, 3, 15, -1, \"\n");
            printf("[Actual]: \"%s\"\n", string);
            return 2;
        } 
        return 0;
    }
    case Delete_equals: {
        appendList(A, 1);
        appendList(A, 9);
        appendList(A, 10);
        appendList(A, 7);
        appendList(A, 3);
        delElement(A, 2);
        char* string = calloc(100, sizeof(char));
        freopen("/dev/null", "a", stdout);
        setbuf(stdout, string);
        printList(A);
        string[strlen(string)-1] = '\0';
        freopen ("/dev/tty", "a", stdout);
        if (strcmp(string, "1, 9, 7, 3, ") != 0) {
            printf("[Expect]: \"1, 9, 7, 3, \"\n");
            printf("[Actual]: \"%s\"\n", string);
            return 1;
        } 

        appendList(A, 15);
        appendList(A, -1);
        delElement(A, 4);
        delElement(A, 0);
        delElement(A, 0);
        free(string);
        string = calloc(100, sizeof(char));
        freopen("/dev/null", "a", stdout);
        setbuf(stdout, string);
        printList(A);
        string[strlen(string)-1] = '\0';
        freopen ("/dev/tty", "a", stdout);
        if (strcmp(string, "7, 3, -1, ") != 0) {
            printf("[Expect]: \"7, 3, -1, \"\n");
            printf("[Actual]: \"%s\"\n", string);
            return 2;
        } 
        return 0;
    }
  }
  return 255;
}


void segfault_handler(int signal) { // everyone knows what this is
  testStatus = 255;
  longjmp(test_crash, 1);
}

void exit_attempt_handler(void) { // only I decide when you are done
  if (disable_exit_handler) return; // allow this to be disabled
  testStatus = 255;
  longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) { // program killed externally
  testStatus = 255;
  longjmp(test_crash, 3);
}

int main (int argc, char **argv) {
  if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
    printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./ListTest"));
    exit(1);
  }

  printf("\n"); // more spacing
  if (argc == 2) printf("\n"); // consistency in verbose mode

  testsPassed = 0;
  disable_exit_handler = 0;
  atexit(exit_attempt_handler);
  signal(SIGSEGV, segfault_handler);
  //signal(SIGTERM, abrupt_termination_handler); // dangerous
  //signal(SIGINT, abrupt_termination_handler);
  //signal(SIGFPE, abrupt_termination_handler);
  //signal(SIGABRT, abrupt_termination_handler);
  for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {
    // printf("case %d\n", i);
    List A = newList();
    testStatus = runTest(&A, i);
    freeList(&A);
    // printf("checkpoint %d\n", testStatus);
    uint8_t fail_type = setjmp(test_crash);
    if (argc == 2) { // it's verbose mode
      printf("Test %s: %s", testName(i), testStatus == 0 ? "PASSED" :
          "FAILED");
      if (testStatus == 255) {
        printf(": due to a %s\n", fail_type == 1 ? "segfault" : fail_type == 2 ?
            "program exit" : "program interruption");
        continue;
        printf("\nWARNING: Program will now stop running tests\n\n");
        break;
      } else if (testStatus != 0) {
        printf(": test %d\n", testStatus);
      } else {
        printf("\n");
      }
    }
    if (testStatus == 0) {
      testsPassed++;
    }
  }

  disable_exit_handler = 1;

  uint8_t totalScore = testsPassed*3;

  //if (argc == 2 && testStatus != 255) printf("\nYou passed %d out of %d tests\n", testsPassed,
  if (argc == 2 ) printf("\nYou passed %d out of %d tests\n", testsPassed,
      NUM_TESTS);
  /*
  else if (testStatus == 255) {
    totalScore = 10; // charity points
    if (argc == 2) printf("Receiving charity points because your program crashes\n");
  }
  */
  printf("\nYou will receive %d out of %d possible points on the unit tests\n\n",
      totalScore, MAXSCORE);
  exit(0);
  return 0;
}
