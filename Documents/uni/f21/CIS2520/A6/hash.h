#ifndef _HASH_H
#define _HASH_H

#define	BUFFER	256
#define HASHSIZE 4096

int char2int( unsigned char c );
long str2int( char *s, int max );
void init_hash_table( long hash_table[ HASHSIZE ] );
int add_hash( long hash_table[ HASHSIZE ], int hash_idx, long file_pos );
void mk_hashfile( char *basename, long hash_table[ HASHSIZE ] );
long hash_lookup( char *key, long hash_table[ HASHSIZE ], FILE *idxfile, FILE *txtfile );
void get_hashtable( char *basename, long hash_table[ HASHSIZE ] );
//long get_idx( char *string, long hash_table[ HASHSIZE ] );
#endif
