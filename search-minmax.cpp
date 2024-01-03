/**
 * 
 * Implementation of sequential MiniMax strategy 
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

class MinMaxStrategy : public SearchStrategy
{
public:
    MinMaxStrategy() : SearchStrategy("MinMax") {}

    SearchStrategy *clone() { return new MinMaxStrategy(); }

private:

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
