#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "input.h"
#include "cards.h"
#include "deck.h"
#include "future.h"

static int last_future_indexes[100];
static size_t last_hand_n_cards = 0;
/**
 * @brief
 * parse a line of input into a deck_t *
 * @param input
 * @return card_t
 */
deck_t * hand_from_string(const char * str, future_cards_t * fc){
  deck_t* hand = malloc(sizeof(*hand));
  hand->n_cards = 0;
  hand->cards = NULL;
  char * line = strdup(str);
  char* saveptr = NULL;
  char * token = strtok_r(line, " \n\r\t", &saveptr);

  size_t card_idx = 0;
  while (token != NULL) {
    if(token[0] == '?' && isdigit(token[1])){
      // future card
      size_t index = atoi(token+1);
      card_t * placeholder = add_empty_card(hand);
      add_future_card(fc, index, placeholder);
      last_future_indexes[card_idx++] = index; // store the index of the future card
    } else if(strlen(token) == 2) {
      // normal card
      char value_let = token[0];
      char suit_let = token[1];
      card_t c = card_from_letters(value_let, suit_let);
      assert_card_valid(c);
      add_card_to(hand, c);
      last_future_indexes[card_idx++] = -1; // no future card for this index
    } else {
      fprintf(stderr, "Invalid card format: %s\n", token);
      exit(EXIT_FAILURE);
    }
    token = strtok_r(NULL, " \n\r\t", &saveptr);
  }
    free(line);

    if(hand->n_cards < 5){
        fprintf(stderr, "Error: Hand must contain at least 5 cards.\n");
        free_deck(hand);
        exit(EXIT_FAILURE);
    }
    last_hand_n_cards = hand->n_cards; //store the number of cards in the last hand
    return hand;
}
/**
 * @brief 
 * dynamically read input to the array of deck_t pointers.
 * every line is parsed by hand_from_string.
 * @param f 
 * @param n_hands 
 * @param fc 
 * @return deck_t** 
 */
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  size_t hands_size = 10;   // initial size of the hands array
  size_t hand_count = 0; // number of hands read
  deck_t ** hands = malloc(hands_size * sizeof(*hands));

  char * line = NULL;
  size_t sz = 0;
  ssize_t nread;

  while((nread = getline(&line, &sz, f)) != -1) {
    //skip empty lines
    char* p = line;
    while(isspace(*p)) p++;
    if (*p == '\0' || *p == '#') {
      continue; // skip empty lines or comments
    }

    if (hand_count >= hands_size) {
      hands_size *= 2; // double the size of the array
      hands = realloc(hands, hands_size * sizeof(*hands));
    }
    hands[hand_count++] = hand_from_string(line, fc);
  }
    free(line);

    if (hand_count == 0) {
        fprintf(stderr, "Error: No hands read from input.\n");
        free(hands);
        exit(EXIT_FAILURE);
    }
    *n_hands = hand_count;
    return hands;
    
}
