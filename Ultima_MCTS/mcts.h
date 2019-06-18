#ifndef MCST_H_INCLUDED
#define MCST_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>

typedef std::pair< std::vector<std::vector<char> >, bool> pos;

class BoardState {
	public:
	static std::unordered_map<pos, BoardState, boost::hash<pos>> save;// = unordered_map<std::pair<std::vector<std::vector<std::vector<char> > >, bool>();
	static const double bias;
	int nb_plays;
	double score;
	bool white;
	std::vector<std::vector<std::vector<char> > > posMoves;
	BoardState(pos& p);
	void explore();
	void playout(std::vector<std::vector<char> > b);
	static std::vector<std::vector<char> > mcPlay(std::vector<std::vector<char> > b, bool w, int depth);

};

#endif
