#include <stdio.h>
#include "poker.h"
int main(){
    int deck[52],ea,eb;
    srand48(getpid());
    init_deck(deck);
	shuffle_deck(deck);
	ea=eval_5hand(deck);
	eb=eval_5hand(deck+5);
	if(ea<eb){
		wprintf(L"Alice wins with %s\n",value_str[hand_rank(ea)]);
		print_hand(deck,5);
		wprintf(L"Bob had %s\n",value_str[hand_rank(eb)]);
		print_hand(deck+5,5);
	}else if(ea>eb){
		wprintf(L"Bob wins with %s\n",value_str[hand_rank(eb)]);
		print_hand(deck+5,5);
		wprintf(L"Alice had %s\n",value_str[hand_rank(ea)]);
		print_hand(deck,5);
	}else{
		wprintf(L"Split pot %s\n",value_str[hand_rank(ea)]);
		wprintf(L"Alice hand\n");
		print_hand(deck,5);
		wprintf(L"Bob hand\n");
		print_hand(deck+5,5);
	}
	return 0;
}
