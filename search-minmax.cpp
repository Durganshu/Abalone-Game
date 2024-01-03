/**
 * 
 * Implementation of sequential Minimax strategy
 * 
 * Authors:
 * - Aditya Phopale
 * - Durganshu Mishra
 * - Gaurav Gokhale
 *
 */

#include "search.h"
#include "board.h"
#include "eval.h"
#include <iostream>
#include <algorithm>

/**
 * To create your own search strategy:
 * - copy this file into another one,
 * - change the class name one the name given in constructor,
 * - adjust clone() to return an instance of your class
 * - adjust last line of this file to create a global instance
 *   of your class
 * - adjust the Makefile to include your class in SEARCH_OBJS
 * - implement searchBestMove()
 *
 * Advises for implementation of searchBestMove():
 * - call foundBestMove() when finding a best move since search start
 * - call finishedNode() when finishing evaluation of a tree node
 * - Use _maxDepth for strength level (maximal level searched in tree)
 */
class MinMaxStrategy : public SearchStrategy
{
public:
    // Defines the name of the strategy
    MinMaxStrategy() : SearchStrategy("MinMax") {}

    // Factory method: just return a new instance of this class
    SearchStrategy *clone() { return new MinMaxStrategy(); }

private:
    /**
     * Implementation of the strategy.
     */
    void searchBestMove();

    int MinMax(int currentdepth);
    int _currentDepth;
};

int MinMaxStrategy::MinMax(int currentdepth)//0
{
    
    if (currentdepth >= _maxDepth)
    {
        return evaluate();
    }
    //int eval;
    int max = -999999;
    int min = 999999;
    Move m;
    MoveList list;
    generateMoves(list);

    while(list.getNext(m)){
        int eval;
        playMove(m); 
        if(currentdepth + 1 < _maxDepth){
            eval = -MinMax(currentdepth+1);
        }
        else{
            eval = evaluate();
        }
        takeBack();

        if(eval > max){
            max = eval;
            foundBestMove(currentdepth, m ,eval);

        }
    }
    finishedNode(currentdepth, 0);
    return max;

}

void MinMaxStrategy::searchBestMove()
{
    // we try to maximize bestEvaluation
    int bestEval = minEvaluation();
    int eval;
    _currentDepth = 0;
    eval = MinMax(_currentDepth);
    std::cout <<"Evaluations= " << eval << "\n";
    
}

// register ourselve as a search strategy
MinMaxStrategy minMaxStrategy;
