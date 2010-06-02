#include <stdio.h>
#include "poker.h"
#include<wchar.h>
#include<locale.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#define delay 2
wchar_t p1name[10];
wchar_t p2name[10];
bool t=true;
wchar_t*turn(){
	if(t=!t)
		return p2name;
	else
		return p1name;
}
wchar_t*act(){
	return act_str[rand()%6];
}
int main(){
	srand((unsigned)time(NULL));
    setlocale(LC_CTYPE,"en_US.utf8");
    int deck[52],ea,eb;
	wprintf(L"player one please enter your name:\n");
	wscanf(L"%ls",p1name);
	wprintf(L"player two please enter your name:\n");
	wscanf(L"%ls",p2name);
    srand48(getpid());
    init_deck(deck);
	shuffle_deck(deck);
	ea=eval_5hand(deck);
	eb=eval_5hand(deck+5);
	wprintf(L"%S posts the Small Blind\n",turn());sleep(delay);
	wprintf(L"%S posts the Big Blind\n",turn());sleep(delay);
	wprintf(L"preflop\n");
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"flop\n");
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"turn\n");
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"river\n");
	wprintf(L"%S %S\n",turn(),act());sleep(delay);
	wprintf(L"%S %S\n",turn(),act());
	wprintf(L"showdown\n");sleep(delay);
	if(ea<eb){
		wprintf(L"%ls wins with %ls\n",p1name,value_str[hand_rank(ea)]);
		print_hand(deck,5);
		wprintf(L"%ls had %ls\n",p2name,value_str[hand_rank(eb)]);
		print_hand(deck+5,5);
	}else if(ea>eb){
		wprintf(L"%ls wins with %ls\n",p2name,value_str[hand_rank(eb)]);
		print_hand(deck+5,5);
		wprintf(L"%ls had %ls\n",p1name,value_str[hand_rank(ea)]);
		print_hand(deck,5);
	}else{
		wprintf(L"Split pot %ls\n",value_str[hand_rank(ea)]);
		wprintf(L"%ls hand\n",p1name);
		print_hand(deck,5);
		wprintf(L"%ls hand\n",p2name);
		print_hand(deck+5,5);
	}
	return 0;
}
