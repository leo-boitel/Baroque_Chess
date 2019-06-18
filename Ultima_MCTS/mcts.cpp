#include "mcts.h"
#include "possibleMoves.h"
#include "board.h"

//#include <unordered_map>
#include <climits>
#include <cmath>
#include <boost/functional/hash.hpp>
#include <numeric> //iota
#include <iostream>

using namespace std;


unordered_map<pos, BoardState, boost::hash<pos>> BoardState::save = unordered_map<pos, BoardState, boost::hash<pos>>();

BoardState::BoardState(pos& p)
{
	posMoves = possibleMoves(p.first, p.second);
	int nb_plays = 0;
	double score = 0;
	white = p.second;
	//Check for loops ? Position leading to itself
	playout(p.first);
}
void BoardState::explore()
{
	//vector<double> ucb(posMoves.size());
	double best_ucb = -1;
	int best_index;
	for(size_t i=0;i<posMoves.size();i++)
	{
		/*switch(getResult(posMoves[i],!white))
		{
			case 0:
				break;
			case 2:
				break;
			case 1:
				score = 1.0;
				nb_plays = INT_MAX;
				return;
			case 3:
				score = (score>.5) ? score : .5; //correct ?
				nb_plays++;
				return;
		}*/
		unordered_map<pos, BoardState, boost::hash<pos>>::iterator found = save.find(make_pair(posMoves[i], !white));
		if (found == save.end()) //Faster way ?
		{
			//ucb[i] = INT_MAX;
			best_ucb = INT_MAX; //RANDOMLY SELECT INSTEAD
			best_index = i;
			break;
		}
		else
		{
			BoardState bs = found->second;
			//ucb[i] = bs.score + bias * sqrt(log(nb_plays)/bs.nb_plays)
			double ucb = bs.score + bias * sqrt(log(nb_plays)/bs.nb_plays);
			if(ucb>=best_ucb)
			{
				best_ucb = ucb;
				best_index = i;
			}
		}
	}
	unordered_map<pos, BoardState, boost::hash<pos>>::iterator found = save.find(make_pair(posMoves[best_index], !white));
	if(found == save.end())
	{
		pos newp = make_pair(posMoves[best_index],!white);
		found = save.insert(found,{newp, BoardState(newp)});
	}
	else
		(found->second).explore();
	score = (nb_plays * score + found->second.score ) / (nb_plays + 1);
	nb_plays++;
}

void BoardState::playout(vector<vector<char> > b)
{
	bool w = white;
	int r = getResult(b,w);
	if(r==3)
	{
		score = 0.5;
		nb_plays = INT_MAX;
		return;
	}
	if(r==1 && w == white)
	{
		score = 0.0;
		nb_plays = INT_MAX;
		return;
	}
	if(r==1) // && w != white
	{
		score = 1.0;
		nb_plays = INT_MAX;
		return;
	}
	int cnter = 0;
	while(r == 0 || r==2)
	{
		cnter++;
		vector<vector<vector<char> > > p = possibleMoves(b,w);
		int chosen = rand()%p.size();
		b = p[chosen];
		//cout<<endl<<w<<p.size()<<endl;
		//printBoard(b);
		if(testCheck(b,w))
		{
			vector<int> range(p.size(),0);
			iota(begin(range),end(range),0);
			while(testCheck(b,w))
			{
				range.erase(range.begin()+chosen);
				chosen = rand()%range.size();
				b = p[range[chosen]];
				// cout<<endl<<"Trying to avoid giving the king..."<<endl<<w<<range.size()<<endl;
				// printBoard(b);
			}
		}
		w = !w;
		r = getResult(b,w);
		//cout<<r<<endl;
	}
	if(r==3)
		score = (nb_plays * score + 0.5 ) / (nb_plays + 1);
	else if(w !=white )
		score = (nb_plays * score + 1.0 ) / (nb_plays + 1);	
	else
		score = (nb_plays * score) / (nb_plays + 1);	
	nb_plays++;
}

vector<vector<char> > BoardState::mcPlay(vector<vector<char> > b, bool w, int depth)
{
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
	//Move selection
	int best_move = 0;
	int most_played = 0;
	for(int i=0;i<found->second.posMoves.size();i++)
	{
		unordered_map<pos, BoardState, boost::hash<pos>>::iterator tmp = save.find(make_pair(found->second.posMoves[i],!w));
		if(tmp != save.end() && tmp->second.nb_plays>most_played)
		{
			most_played = tmp->second.nb_plays;
			best_move = i;
		}
	}
	//cout<<found->second.posMoves.size()<<endl<<best_move<<endl;
	return found->second.posMoves[best_move];
}