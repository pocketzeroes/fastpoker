#include<stdio.h>
#include"arrays.h"
#include"poker.h"
#include<wchar.h>
#include<locale.h>
#include"textcolor.h"
void srand48();
double drand48();
unsigned find_fast(unsigned u){
    unsigned a, b, r;
    u += 0xe91aaa35;
    u ^= u >> 16;
    u += u << 8;
    u ^= u >> 4;
    b  = (u >> 8) & 0x1ff;
    a  = (u + (u << 2)) >> 19;
    r  = a ^ hash_adjust[b];
    return r;
}
void init_deck( int *deck ){
	setlocale(LC_CTYPE,"en_US.utf8");
    int i, j, n = 0, suit = 0x8000;
    for ( i = 0; i < 4; i++, suit >>= 1 )
        for ( j = 0; j < 13; j++, n++ )
            deck[n] = primes[j] | (j << 8) | suit | (1 << (16+j));
}
int find_card( int rank, int suit, int *deck ){
	int i, c;
	for ( i = 0; i < 52; i++ ){
		c = deck[i];
		if ( (c & suit)  &&  (RANK(c) == rank) )
			return( i );
	}
	return( -1 );
}
void shuffle_deck( int *deck ){
    int i, n, temp[52];
    for ( i = 0; i < 52; i++ )
        temp[i] = deck[i];
    for ( i = 0; i < 52; i++ ){
        do {
            n = (int)(51.9999999 * drand48());
        } while ( temp[n] == 0 );
        deck[i] = temp[n];
        temp[n] = 0;
    }
}
void print_hand( int *hand, int n ){
    int i, r;
    static wchar_t rank[13]=L"23456789TJQKA";
    static wchar_t suit;
    for(i=0;i<n;i++){
        r = (*hand >> 8) & 0xF;
        if ( *hand & CLUB)
            suit=L'♣';
        else if ( *hand & DIAMOND ){
        	textcolor(RESET,RED,HIDDEN);
            suit=L'♦';
        }
        else if ( *hand & HEART ){
        	textcolor(RESET,RED,HIDDEN);
            suit=L'♥';
        }
        else
            suit=L'♠';
        hand++;
        if(r==8)
        	wprintf(L"10%lc ",suit);
		else
	        wprintf(L"%lc%lc ",rank[r],suit);
        textcolor(RESET,BLACK,HIDDEN);
    }
    putwchar('\n');
}
int hand_rank( short val ){
    if (val > 6185) return(HIGH_CARD);
    if (val > 3325) return(ONE_PAIR);
    if (val > 2467) return(TWO_PAIR);
    if (val > 1609) return(THREE_OF_A_KIND);
    if (val > 1599) return(STRAIGHT);
    if (val > 322)  return(FLUSH);
    if (val > 166)  return(FULL_HOUSE);
    if (val > 10)   return(FOUR_OF_A_KIND);
    return(STRAIGHT_FLUSH);
}
int eval_5cards(int c1, int c2, int c3, int c4, int c5){
    int q = (c1|c2|c3|c4|c5) >> 16;
    short s;
    if(c1&c2&c3&c4&c5&0xF000)return flushes[q];
    if(s=unique5[q])return s;
    return hash_values[find_fast((c1&0xff)*(c2&0xff)*(c3&0xff)*(c4&0xff)*(c5&0xff))];
}
short eval_5hand( int *hand ){
    int c1, c2, c3, c4, c5;
    c1 = *hand++;
    c2 = *hand++;
    c3 = *hand++;
    c4 = *hand++;
    c5 = *hand;
    return( eval_5cards(c1,c2,c3,c4,c5) );
}
short eval_7hand( int *hand ){
    int i, j, q, best = 9999, subhand[5];
	for ( i = 0; i < 21; i++ ){
		for ( j = 0; j < 5; j++ )
			subhand[j] = hand[ perm7[i][j] ];
		q = eval_5hand( subhand );
		if ( q < best )
			best = q;
	}
	return( best );
}
