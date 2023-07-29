// NAME: Maneesh Wijewardhana
// DATE: 2021-11-30
// ID: 1125828
// CIS*2520 A7

#include "nim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this function mallocs an array of board_size integers and returns a pointer
// to it
int *new_board(int board_size) {
  // mallocing board_size array
  int *tempBoard = malloc(sizeof(int) * board_size);
  // error checking malloc
  if (tempBoard == NULL) {
    fprintf(stderr, "Error: malloc failed (new_board)\n");
    exit(-1);
  }
  // returning array
  return tempBoard;
}

// this funciton mallocs an array of size max_hash struct node and sets values
struct node *mk_nim_hash(int max_hash, int board_size, int *start_board) {
  // mallocing max_hash tempNode
  struct node *tempNode = malloc(sizeof(struct node) * max_hash);
  // error checking malloc
  if (tempNode == NULL) {
    fprintf(stderr, "Error: malloc failed (mk_nim_hash)\n");
    exit(-1);
  }
  // setting values
  for (int i = 0; i < max_hash; i++) {
    tempNode[i].moves = -1;
    tempNode[i].move = NULL;
    tempNode[i].nimsum = -1;
    tempNode[i].board = hash2board(board_size, start_board, i);
  }
  // returning pointer
  return tempNode;
}

// this function frees the board array
void free_board(int *board) { free(board); }

// this function frees each move array and each board array in nim_hash and then
// free nim_hash itself
void free_nim_hash(int max_hash, struct node *nim_hash) {
  for (int i = 0; i < max_hash; i++) {
    free(nim_hash[i].move);
    free(nim_hash[i].board);
  }
  free(nim_hash);
}

// this function creates a board array and inits with string array argv
int *board_from_argv(int board_size, char **argv) {
  // creating new board
  int *tempBoard = new_board(board_size);
  // initializing equivalents of the string array
  for (int i = 0; i < board_size; i++) {
    tempBoard[i] = atoi(argv[i]);
  }
  // returning pointer
  return tempBoard;
}

// this function returns pointer to new_board whos values are init exactly as
// board
int *copy_board(int board_size, int *board) {
  // creating new board
  int *tempBoard = new_board(board_size);
  // initializing exact same values (have to start at 1 because 0 is executable)
  for (int i = 0; i < board_size; i++) {
    tempBoard[i] = board[i];
  }
  // returning pointer
  return tempBoard;
}

// this function returns a value of 1 if there is 1 match and 0 otherwise
int game_over(int board_size, int *board) {
  // creating temp board
  int *tempInt = malloc(sizeof(int) * board_size);
  tempInt = board;
  int counter = 0;
  // if theres still more than 1 match, game keeps going
  for (int i = 0; i < board_size; i++) {
    if (tempInt[i] > 0) {
      counter++;
    }
  }
  // if there is only 1 match, game over
  if (counter == 1) {
    return 1;
  }
  // else 0
  return 0;
}

// this function recursively joins the nodes of the graph
void join_graph(struct node *nim_hash, int hash, int board_size,
                int *start_board) {
  int *newBoard = NULL;
  // checking if moves is -1
  if (nim_hash[hash].moves != -1) {
    return;
  }

  // total # of moves
  int total = 0;
  for (int i = 0; i < board_size; i++) {
    total += nim_hash[hash].board[i];
  }
  // updating moves
  nim_hash[hash].moves = total;
  nim_hash[hash].move = malloc(sizeof(struct move) * total);

  // counter for recursive call
  int i = 0;
  for (int j = 0; j < board_size; j++) {
    for (int k = 1; k <= nim_hash[hash].board[j]; k++) {
      // setting values to appropriate row and match value
      nim_hash[hash].move[i].row = j;
      nim_hash[hash].move[i].matches = k;
      newBoard = copy_board(board_size, nim_hash[hash].board);
      newBoard[j] = newBoard[j] - k;
      nim_hash[hash].move[i].hash =
          board2hash(board_size, start_board, newBoard);
      free(newBoard);
      // recursive call
      join_graph(nim_hash, nim_hash[hash].move[i].hash, board_size,
                 start_board);
      i++;
    }
  }
  // computing
  nim_hash[hash].nimsum = compute_nimsum(board_size, nim_hash[hash].board);
}

// this function computes the nimsum for a board
int compute_nimsum(int board_size, int *board) {
  int nimsum;
  int counter = 0;
  for (int i = 0; i < board_size; i++) {
    // keeping track of counter
    if (board[i] > 1) {
      counter++;
    }
    if (i == 0) {
      nimsum = board[0];
      // xor
    } else {
      nimsum ^= board[i];
    }
  }
  // deciding whether to return negation or not
  if (counter < 1) {
    return !nimsum;
  } else {
    return nimsum;
  }
}
