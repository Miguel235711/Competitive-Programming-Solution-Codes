
/**
Code solution by: Miguel Angel Munoz Vazquez
Github repository path: https://github.com/Miguel235711/Competitive-Programming-Solution-Codes
Problem link: https://codeforces.com/contest/455/problem/B
Made on: Apr/16/2018
Translated to English on: Sep/07/2018
**/

#include <bits/stdc++.h>
#define printThatPlayer1Wins printf("Second\n");return 0;
#define printThatPlayer0Wins printf("First\n");return 0;

using namespace std ;

int memo [ 100008 ] [ 2 ] ;
int memo2 [ 100008 ] [ 2 ] ;
int memo3 [ 100008 ] [ 2 ] ;
int memo4 [ 100008 ] [ 2 ] ;

map < char , int > trieA [ 100008 ] ; /// data structure "trie" made up of
                                     ///array of maps, each map represents a node of the trie
int currentNodeName = 0 ;

///player 0 tries to lose , player 1 tries to win
int f4 ( int dir , int player ) {
	if ( memo4 [ dir ] [ player ] != -1 ) {
		return memo4 [ dir ] [ player ] ;
	}
	int res = player ;
	if ( ! trieA [ dir ] . empty() ) {
		res = 1 ;
	}
 	for ( auto nextDir = trieA [ dir ] . begin() ; nextDir != trieA [ dir ] .end() ; nextDir ++ ) {
		if ( player ) {
			res &= f4 ( nextDir -> second , 0 ) ;
		}else{
			res &= f4 ( nextDir -> second , 1 ) ;
		}
	}
	memo4 [ dir ] [ player ] = res ;
	return res ;
}

///player 0 tries to win , player 1 tries to lose
int f3 ( int dir , int player ) {
	if ( memo3 [ dir ] [ player ] != -1 ) {
		return memo3 [ dir ] [ player ] ;
	}
	int res = player ;
	if ( ! trieA [ dir ] . empty () ) {
		res = 0 ;
	}
	for ( auto nextDir = trieA [ dir ] . begin() ; nextDir != trieA [ dir ] .end() ; nextDir ++ ) {
		if ( player ) {
			res |= f3 ( nextDir -> second , 0 ) ;
		}else{
			res |= f3 ( nextDir -> second , 1 ) ;
		}
	}
	//cout << dir << " " << player << " " << res << "\n" ;
	memo3 [ dir ] [ player ] = res ;
	return res ;
}

///player 0 tries to lose , player 1 tries to lose
int f2 ( int dir , int player ) {
    if ( memo2 [ dir ] [ player ] != -1 ) {
		return memo2 [ dir ] [ player ] ;
	}
	int res = player ;
	if ( ! trieA [ dir ] . empty()  ) {
		if ( player ) {
			res = 0 ;
		}else{
			res = 1 ;
		}
	}
	for ( auto nextDir = trieA [ dir ] . begin() ; nextDir != trieA [ dir ] .end() ; nextDir ++ ) {
		if ( player ) {
			res |= f2 ( nextDir -> second , 0 ) ;
		}else{
			res &= f2 ( nextDir -> second , 1 ) ;
		}
	}
	memo2 [ dir ] [ player ] = res ;
	return res ;
}

///player 0 tries to win , player 1 tries to win
int f ( int dir , int player ){
	if ( memo [ dir ] [ player ] != -1 ) {
		return memo [ dir ] [ player ] ;
	}
	int res = player ;
	for ( auto nextDir = trieA [ dir ] . begin() ; nextDir != trieA [ dir ] .end() ; nextDir ++ ) {
		if ( player ) {
			res &= f ( nextDir -> second , 0 ) ;
		}else{
			res |= f ( nextDir -> second , 1 ) ;
		}
	}
	memo [ dir ] [ player ] = res ;
	return res ;
}

int N , K ;

char currentWord [ 100008 ] ;


void insertCurrentWordToTrie(){
	int lim = strlen ( currentWord ) - 1 ;
	int dir = 0 ;
	for ( int i = 0 ; i <= lim ; i ++ ) {
		auto it = trieA [ dir ] . find ( currentWord [ i ] ) ;
		if ( it != trieA [ dir ] . end() ) {
			dir = it -> second ;
		}else{
			currentNodeName ++ ;
			trieA [ dir ] . insert ( make_pair ( currentWord [ i ] , currentNodeName ) ) ;
			dir = currentNodeName ;
		}
	}
}

int main()
{
	scanf ( "%d %d" ,  &N , &K ) ;
	///initialize each memory matrix for the recursive methods (DP)
	memset ( memo , -1 , sizeof ( memo ) ) ;
	memset ( memo2 , -1 , sizeof ( memo2 ) ) ;
	memset ( memo3 , -1 , sizeof ( memo3 ) ) ;
	memset ( memo4 , -1 , sizeof ( memo4 ) ) ;
	///read each string/word
	for ( int i = 1 ; i <= N ; i ++ ) {
		scanf ( "%s" , &currentWord ) ;
		insertCurrentWordToTrie () ;///insert currentWord to data structure "trie"
	}
	///when player 0 makes first move
	int player0TryingToWinAndPlayer1TryingToWin = f ( 0 , 0 ) ;
	int player0TryingToLoseAndPlayer1TryingToLose = f2 ( 0 , 0 ) ;
	int Player0TryingToWinAndPlayer1TryingToLose =  f3 ( 0 , 0 ) ;
	int Player0TryingToLoseAnd1TryingToWin = f4 ( 0 , 0 ) ;
	int canPlayer0Win = ( player0TryingToWinAndPlayer1TryingToWin | Player0TryingToLoseAnd1TryingToWin ) & ( Player0TryingToWinAndPlayer1TryingToLose | player0TryingToLoseAndPlayer1TryingToLose ) ;
	int canPlayer0Lose = ! ( player0TryingToLoseAndPlayer1TryingToLose | Player0TryingToLoseAnd1TryingToWin ) ;
        if ( ! canPlayer0Win ) {
		///player 0 always lose
		printThatPlayer1Wins;
	}
	if ( canPlayer0Lose && canPlayer0Win ) {
        ///player 0 can always win or lose
		printThatPlayer0Wins;
	}
	///when player 1 makes first move
	int player1TryingToWinAndPlayer0TryingToWin = ! f ( 1 , 0 ) ;
	int player1TryingToLoseAndPlayer0TryingToLose = ! f2 ( 1 , 0 ) ;
	int player1TryingToWinAndPlayer0TryingToLose = ! f3 ( 1 , 0 ) ;
	int player1TryingToLoseAndPlayer0TryingToWin = ! f4 ( 1 , 0 ) ;
	int canPlayer1Win =  ( player1TryingToWinAndPlayer0TryingToWin | player1TryingToLoseAndPlayer0TryingToWin ) & ( player1TryingToWinAndPlayer0TryingToLose | player1TryingToLoseAndPlayer0TryingToLose );
	if ( canPlayer1Win ) {
		if ( K & 1 ) {
			printThatPlayer0Wins;
		}else{
			printThatPlayer1Wins;
		}
	}else{
		printThatPlayer0Wins;
	}
}
