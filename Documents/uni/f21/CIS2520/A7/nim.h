#ifndef _NIM_H
#define _NIM_H

/* header file for nim.c and nimhelp.c
 */

// represents the edge in a graph
struct move {
  int row;		// from from which to take matches
  int matches;		// number of matches to take
  int hash;		// hash of board that is the result
};

// represents a snapshot of the game at given point in time
struct node {
  int nimsum;		// win/lose number
  int *board;		// array of pieces per row
  int moves;		// number of possible moves
  struct move *move;	// array of possible moves
};


// memory allocation and free functions
int *new_board( int board_size );
struct node *mk_nim_hash( int max_hash, int board_size, int *start_board );
void free_board( int *board );
void free_nim_hash( int max_hash, struct node *nim_hash );

// other functions for students to write
int *board_from_argv( int board_size, char **argv );
int *copy_board( int board_size, int *board );
int game_over( int board_size, int *board );
void join_graph( struct node *nim_hash, int hash, int board_size, 
    int *start_board );

int compute_nimsum( int board_size, int *board );


// functions provided in nimhelp.c
void print_board( int board_size, int *board );
int compute_max_hash( int board_size, int *start_board );
int board2hash( int board_size, int *start_board, int *current_board );
int *hash2board( int board_size, int *start_board, int hash );

#endif
