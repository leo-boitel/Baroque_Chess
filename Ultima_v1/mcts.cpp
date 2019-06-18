#include "mcts.h"

//#include "possibleMoves.h"
//#include "board.h"

#include <unordered_map>
#include <climits>
#include <cmath>
#include <boost/functional/hash.hpp>
#include <numeric> //iota
#include <iostream>
#include <ctime>

using namespace std;

//#define RANDMOVE

bool clear_tbl = true;

unordered_map<pos, BoardState, boost::hash<pos>> BoardState::save = unordered_map<pos, BoardState, boost::hash<pos>>();

BoardState::BoardState(pos& p)
{
	//cout<<"Before"<<endl;
	//printBoard(p.first);
	posMoves = possibleMoves(p.first, p.second); //legal ?
	//cout<<"After"<<endl;
	int nb_plays = 0;
	double score = 0.0;
	board = p.first;
	white = p.second;
	//Check for loops ? Position leading to itself
	playout();
}
void BoardState::explore()
{
	//vector<double> ucb(posMoves.size());
	double best_ucb = -1;
	int best_index(0);
	for(size_t i=0;i<posMoves.size();i++)
	{
		unordered_map<pos, BoardState, boost::hash<pos>>::iterator found = save.find(make_pair(doMove(board,posMoves[i]), !white));
		if (found == save.end()) //Faster way ?
		{
			//ucb[i] = INT_MAX;
			best_ucb = INT_MAX; 
			best_index = i;
			break;
		}
		else
		{
			BoardState bs = found->second;
			//ucb[i] = bs.score + bias * sqrt(log(nb_plays)/bs.nb_plays)
				if(bs.nb_plays == INT_MAX)
				{
					continue;
				}
			double ucb = bs.score + bias * sqrt(log(nb_plays)/bs.nb_plays);
			if(ucb>=best_ucb)
			{
				best_ucb = ucb;
				best_index = i;
			}
		}
	}
	pos best_pos = make_pair(doMove(board,posMoves[best_index]), !white);
	unordered_map<pos, BoardState, boost::hash<pos>>::iterator found = save.find(best_pos);
	if(found == save.end())
	{
		found = save.insert(found,{best_pos, BoardState(best_pos)});
	}
	else
		(found->second).explore();
	
	score = (nb_plays * score + found->second.score ) / (nb_plays + 1);
	nb_plays++;
}

void BoardState::playout()
{

	vector<vector<char> > b = board;
	bool w = white;
	// vector<tmove> p = possibleLegalMoves(b,w); //prob slower than checking after playing the move
	#ifndef RANDMOVE
	vector<tmove> p = possibleMoves(b,w);
	vector<vector<char> > backup(b);
	while(p.size()!=0)
	{
		int chosen = rand()%p.size();
		b = doMove(b,p[chosen]);

		if(testCheck(b,w))
		{
			vector<int> range(p.size(),0);
			iota(begin(range),end(range),0);
			while(testCheck(b,w))
			{
				range.erase(range.begin()+chosen);
				if(range.size() == 0)
				{
					goto over;
				}
				chosen = rand()%range.size();
				b = doMove(backup,p[range[chosen]]);

			}
		}
		backup = b;
		w = !w;
	      bool draw = true;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(b[i][j] != '_' && b[i][j] != 'K' && b[i][j] != 'k')
            {
                draw = false;
                break;
            }
        }
    }
    if(draw)
    	break;
	p = possibleMoves(b,w); //legal ?
		//cout<<r<<endl;
	}
	over:
	if(testCheck(backup,w))
	{
		if(w==white)
			score = (nb_plays * score) / (nb_plays + 1);
	
		else
			score = (nb_plays * score + 1.0 ) / (nb_plays + 1);	
	}
	else
		score = (nb_plays * score + 0.5 ) / (nb_plays + 1);
	#endif

	#ifdef RANDMOVE
	int res=0;
	vector<int> rrange(64,0);
    iota(begin(rrange),end(rrange),0);
    vector<vector<char> > backup(b);
    bool draw = false;
	while(rrange.size()!=0)
	{
		//cout<<time(0)<<endl;
	vector<tmove> p = randomPossibleMoves(backup,w,rrange);
	while(p.size()!=0)
	{
		int chosen = rand()%p.size();
		b = doMove(backup,p[chosen]);
		if(testCheck(b,w))
		{
			vector<int> range(p.size(),0);
			iota(begin(range),end(range),0);
			do
			{
				range.erase(range.begin()+chosen);
				if(range.size() == 0)
				{
					goto over;
				}
				chosen = rand()%range.size();
				b = doMove(backup,p[range[chosen]]);

			}while(testCheck(b,w));
		}
		backup = b;
		w = !w;
		rrange = vector<int>(64,0);
		iota(begin(rrange),end(rrange),0);
	     draw = true;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(b[i][j] != '_' && b[i][j] != 'K' && b[i][j] != 'k')
            {
                draw = false;
                break;
            }
        }
    }
    
    if(draw)
    	break;
	p = randomPossibleMoves(b,w,rrange); //legal ?
		//cout<<r<<endl;
	}
	//printBoard(b);
	if(draw)
		break;
	over:
	(void)0;
	}
	if(testCheck(backup,w))
	{
		if(w==white)
			score = (nb_plays * score) / (nb_plays + 1);
	
		else
			score = (nb_plays * score + 1.0 ) / (nb_plays + 1);	
	}
	else
		score = (nb_plays * score + 0.5 ) / (nb_plays + 1);
	#endif
	nb_plays++;
}

tmove BoardState::mcPlay(vector<vector<char> > b, bool w, int depth)
{
	if(clear_tbl)
		BoardState::save = unordered_map<pos, BoardState, boost::hash<pos>>();
	//Clear save map ? Might avoid overspending memory
	//Initialization :
	pos p = make_pair(b, w);
	unordered_map<pos, BoardState, boost::hash<pos>>::iterator found = save.find(p);
	if(found == save.end())
		found = save.insert(found,{p, BoardState(p)});
	else
		found->second.explore();
	for(int i=1;i<depth;i++) //First one done above
	{
		found->second.explore();
	}
	//tmove selection
	int best_move = 0;
	int most_played = 0;
	for(int i=0;i<found->second.posMoves.size();i++)
	{
		unordered_map<pos, BoardState, boost::hash<pos>>::iterator tmp = save.find(make_pair(doMove(b,found->second.posMoves[i]),!w));
		if(tmp != save.end() && tmp->second.nb_plays>most_played)
		{
			most_played = tmp->second.nb_plays;
			#ifndef NDEBUG
			//cout<<most_played<<endl;
			#endif
			best_move = i;
		}
	}
	//cout<<found->second.posMoves.size()<<endl<<best_move<<endl;
	return found->second.posMoves[best_move];
}