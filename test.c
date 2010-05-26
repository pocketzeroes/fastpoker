#include <stdio.h>
#include "poker.h"
int main(){
    int deck[52], hand[5], freq[10];
    int a, b, c, d, e, i, j;
    srand48( getpid() );
    init_deck( deck );
    for ( i = 0; i < 10; i++ )
        freq[i] = 0;
    for(a=0;a<48;a++){
		hand[0] = deck[a];
		for(b=a+1;b<49;b++){
			hand[1] = deck[b];
			for(c=b+1;c<50;c++){
				hand[2] = deck[c];
				for(d=c+1;d<51;d++){
					hand[3] = deck[d];
					for(e=d+1;e<52;e++){
						hand[4] = deck[e];
						i = eval_5hand( hand );
						j = hand_rank(i);
						freq[j]++;
					}
				}
			}
		}
    }
    for(i=1;i<=9;i++)
		printf( "%15s: %8d\n", value_str[i], freq[i] );
	return 0;
}
