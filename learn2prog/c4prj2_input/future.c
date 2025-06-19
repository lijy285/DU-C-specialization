#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "future.h"
#include <assert.h>

/**
 * @brief 
 * ensure fc->deck contains at least index+1 decks,(rellocate)
 * register the card ptr "?index" in the fc->decks[index] deck.
 * support ?0, ?3, ?2, etc ranking
 * @param fc 
 * @param index 
 * @param ptr 
 */
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
    //expand the fc->decks array if necessary
    if(fc->n_decks <= index){
      size_t old_n = fc->n_decks;
      fc->decks = realloc(fc->decks, (index+1)*sizeof(*fc->decks));
      assert(fc->decks != NULL && "Memory allocation failed for future cards");
      //initialize the new decks
      for (size_t i = old_n; i <= index; ++i){
        fc->decks[i].cards = NULL;
        fc->decks[i].n_cards = 0;
      }
      fc->n_decks = index + 1; // update the number of decks
    }
    //add the card ptr to the fc->decks[index] deck
    deck_t * deck = &fc->decks[index];
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
    assert(deck->cards != NULL && "Memory allocation failed for future card deck");
    deck->cards[deck->n_cards] = ptr; // add the card pointer
    deck->n_cards++; // increment the number of cards in the deck
}

/**
 * @brief 
 * take cards from the deck one by one, assign value to the placeholder cards in future cards.
 * if there is not enough cards in the deck, return error.
 * only assign value, not replace the pointer.
 * @param deck 
 * @param fc 
 */
void future_cards_from_deck(deck_t *deck, future_cards_t * fc) {
    if(fc == NULL || deck == NULL) {
        fprintf(stderr, "Error: future_cards_t or deck_t is NULL.\n");
        exit(EXIT_FAILURE);
    }
    size_t card_to_draw_idx = 0; // index for the card to draw from the deck
    // loop through all the cards in the deck
    for (size_t i = 0; i < fc->n_decks; i++) {
        
        if(fc->decks[i].n_cards > 0) {
            //check if the deck has any cards to assign
            if (card_to_draw_idx >= deck->n_cards) {
                fprintf(stderr, "Error: Not enough cards in the deck to assign to future cards.\n");
                exit(EXIT_FAILURE);
            }
        }
        //draw a card from the deck
        card_t *drawn_card = deck->cards[card_to_draw_idx];

        for(size_t j = 0; j < fc->decks[i].n_cards; ++j) {
            // dereference the pointer to get the card
            *(fc->decks[i].cards[j]) = *drawn_card; // assign the card value to the placeholder
        }
        card_to_draw_idx++; // move to the next card in the deck
    }
}
