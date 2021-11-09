#include "names.h"

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    // declating varaibles 32 bit unsigned integers
    int lives[10] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
    uint32_t players;
    uint32_t seed;
    uint32_t round = 0;
    uint32_t lowest = 200;
    uint32_t lowest_index;
    uint32_t left_pos, right_pos;
    uint32_t alive_counter = 0;
    uint32_t roll_1;
    uint32_t roll_2;
    uint32_t roll_total;

    // checking validity of inputs
    // credit to Eugene's lab demo
    printf("Number of players: ");
    if (scanf("%u", &players) != 1) {
        fprintf(stderr, "Invalid number of players.\n");
        return 1;
    }

    // if less than 2 vamps or more than 10
    if (players < 2 || players > 10) {
        fprintf(stderr, "Invalid number of players.\n");
        return 1;
    }

    printf("Random seed: ");
    if (scanf("%u", &seed) != 1) {
        fprintf(stderr, "Invalid random seed.\n");
        return 1;
    }

    // if seed is negative or more than 32 bits
    if (seed < 0 || seed > UINT32_MAX) {
        fprintf(stderr, "Invalid random seed.\n");
        return 1;
    }

    srandom(seed);

    // stop new rounds when only one vamp is alive
    while (alive_counter != 1) {
        // resetting lowest, and counter
        round = round + 1;
        lowest = 200;
        alive_counter = alive_counter * 0;

        printf("Round %d\n", round);

        // looping through all the players
        for (uint32_t i = 0; i < players; i++) {
            // vamps with zero lives roll
            if (lives[i] == 0) {
                continue;
            }

            // using random() to roll a rand amount each round
            roll_1 = random() % 6;
            roll_2 = random() % 6;
            roll_total = roll_1 + roll_2;

            // if they roll a midnight find out who is to the left and right of roller
            if (roll_1 == 5 && roll_2 == 5) {
                left_pos = (i + players - 1) % players;
                right_pos = (i + 1) % players;
            }

            // keep track of who rolled the lowest each round
            if (roll_total < lowest) {
                lowest = roll_total;
                lowest_index = i;
            }

            // printing statements

            // if they rolled a midnight, add a life to left and right player
            if (roll_1 == 5 && roll_2 == 5) {
                lives[left_pos] = lives[left_pos] + 1;
                lives[right_pos] = lives[right_pos] + 1;

                // if left player was dead and right player was dead
                if (lives[left_pos] == 1 && lives[right_pos] == 1) {
                    printf(" - %s rolls %s... resurrects %s resurrects %s\n", names[i],
                        rolls[roll_1][roll_2], names[left_pos], names[right_pos]);
                }

                // if left player was dead and right player was alive
                if (lives[left_pos] == 1 && lives[right_pos] > 1) {
                    printf(" - %s rolls %s... resurrects %s sparkles %s\n", names[i],
                        rolls[roll_1][roll_2], names[left_pos], names[right_pos]);
                }

                // if left player was alive and right player was dead
                if (lives[left_pos] > 1 && lives[right_pos] == 1) {
                    printf(" - %s rolls %s... sparkles %s resurrects %s\n", names[i],
                        rolls[roll_1][roll_2], names[left_pos], names[right_pos]);
                }

                // if both left and right player were alive
                if (lives[left_pos] > 1 && lives[right_pos] > 1) {
                    printf(" - %s rolls %s... sparkles %s sparkles %s\n", names[i],
                        rolls[roll_1][roll_2], names[left_pos], names[right_pos]);
                }
                // else print statement normalls
            } else {
                printf(" - %s rolls %s...\n", names[i], rolls[roll_1][roll_2]);
            }
        }

        // subtract life from lowest roller of round
        lives[lowest_index] = lives[lowest_index] - 1;

        // printing statements for loser of round

        printf("%s is forced to eat garlic!\n", names[lowest_index]);

        if (lives[lowest_index] == 1) {
            printf("%s has %d life remaining.\n", names[lowest_index], lives[lowest_index]);
        }

        if (lives[lowest_index] == 0) {
            printf("%s has died.\n", names[lowest_index]);
        }

        if (lives[lowest_index] > 1) {
            printf("%s has %d lives remaining.\n", names[lowest_index], lives[lowest_index]);
        }
        // checking how many vamps are alive
        for (uint32_t x = 0; x < players; x++) {
            if (lives[x] > 0) {
                alive_counter = alive_counter + 1;
            }
        }
    }
    // checking who is the last vamp alive (winner)
    for (uint32_t y = 0; y < players; y++) {
        if (lives[y] > 0) {
            printf("%s wins the Garlic Game!\n", names[y]);
        }
    }

    return 0;
}
