#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>  
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

/**
 * @brief Determines the winning hand from an array of hands for one trial.
 * @param hands An array of pointers to deck_t (which represent hands).
 * @param n_hands The number of hands in the array.
 * @param win_counts A pointer to an array where win/tie counts are stored.
 * The winning hand's index will have its count incremented, or the tie
 * index (at win_counts[n_hands]) will be incremented.
 */
void determine_winner(deck_t ** hands, size_t n_hands, unsigned * win_counts) {
  // Pass 1: Find the index of the hand with the highest rank.
  size_t best_hand_idx = 0;
  for (size_t i = 1; i < n_hands; i++) {
    // compare_hands returns >0 if hand1 wins, <0 if hand2 wins, 0 for a tie.
    if (compare_hands(hands[best_hand_idx], hands[i]) < 0) {
      best_hand_idx = i; // Found a new best hand.
    }
  }

  // Pass 2: Check if any other hand ties with the best hand.
  int is_a_tie = 0;
  for (size_t i = 0; i < n_hands; i++) {
    if (i == best_hand_idx) {
      continue; // Don't compare the best hand to itself.
    }
    if (compare_hands(hands[best_hand_idx], hands[i]) == 0) {
      is_a_tie = 1; // Found a tie.
      break;      // No need to check further.
    }
  }

  // Increment the appropriate counter.
  if (is_a_tie) {
    win_counts[n_hands]++; // The last element is for ties.
  }
  else {
    win_counts[best_hand_idx]++; // Increment the winner's count.
  }
}

int main(int argc, char ** argv) {
  // 1. Check command line arguments.
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: poker input_filename [num_trials]\n");
    return EXIT_FAILURE;
  }

  // 2. Parse the number of Monte Carlo trials. Default is 10,000.
  unsigned num_trials = 10000;
  if (argc == 3) {
    num_trials = atoi(argv[2]);
    if (num_trials == 0) {
      fprintf(stderr, "Error: Invalid number of trials specified.\n");
      return EXIT_FAILURE;
    }
  }

  // 3. Open the input file for reading.
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error opening input file");
    return EXIT_FAILURE;
  }

  // 4. Initialize structures for reading input.
  size_t n_hands = 0;
  future_cards_t fc = { .decks = NULL, .n_decks = 0 };
  deck_t ** hands = read_input(f, &n_hands, &fc);

  // 5. Build the deck of remaining cards.
  deck_t * remaining_deck = build_remaining_deck(hands, n_hands);

  // 6. Create an array to count wins (n_hands elements) and ties (1 element).
  unsigned * win_counts = calloc(n_hands + 1, sizeof(*win_counts));
  assert(win_counts != NULL); // Use assert to ensure memory allocation succeeded.

  // 7. Seed the random number generator for shuffling.
  srand(time(NULL));

  // 8. Run the Monte Carlo simulation loop.
  for (unsigned i = 0; i < num_trials; i++) {
    // a. Shuffle the deck of remaining cards.
    shuffle(remaining_deck);

    // b. Assign unknown cards from the shuffled deck.
    future_cards_from_deck(remaining_deck, &fc);

    // c. Compare hands and determine the winner for this trial.
    determine_winner(hands, n_hands, win_counts);
  }

  // 9. Print the final results in the required format.
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n",
           i,
           win_counts[i],
           num_trials,
           (double)win_counts[i] / num_trials * 100.0);
  }
  printf("And there were %u ties\n", win_counts[n_hands]);

  // 10. Free all allocated memory to prevent leaks.
  free(win_counts);
  free_deck(remaining_deck);

  for (size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);

  for (size_t i = 0; i < fc.n_decks; i++) {
    free(fc.decks[i].cards);
  }
  free(fc.decks);

  // 11. Close the file.
  if (fclose(f) != 0) {
    perror("Failed to close file");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
