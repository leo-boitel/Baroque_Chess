#ifndef MCTS_H_INCLUDED
#define MCTS_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include "possibleMoves.h"

class BoardState {
	public:
	static std::unordered_map<pos, BoardState, boost::hash<pos>> save;// = unordered_map<std::pair<std::vector<std::vector<std::vector<char> > >, bool>();
	static const double bias;
	int nb_plays;
	double score;
	bool white;
	std::vector<std::vector<char> > board;
	std::vector<tmove> posMoves;
	BoardState(pos& p);
	void explore();
	void playout();
	static tmove mcPlay(std::vector<std::vector<char> > b, bool w, int depth);

};

#endif
