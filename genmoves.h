#ifndef _GENMOVES_H
#define _GENMOVES_H
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
enum MoveType {
    SINGLE = 0,
    DOUBLE,
    TRIPLE,
    SEQUENCER,
    TRIPLEDOUBLE,
    TWIN_TRIPLE,
    TRIPLE_DOUBLE,
    FOUR_BOMB,
    FIVE_BOMB,
    PURE_SEQUENCER,
    SIX_BOMB,
    SEVEN_BOMB,
    EIGHT_BOMB,
    NINE_BOMB,
    TEN_BOMB,
    JOKER_BOMB
};

const int VICE_JOKER = 52;
const int JOKER = 53;
const int nMaxCards = 27; //27
const int nMaxSims = 5; //1000

class Move {
    MoveType mType;
    int nValue;
public:
    vector<int> cards;
public:
    Move(MoveType tp, int v, vector<int> c)
    : mType(tp),
    nValue(v) {
        for(int n=0; n<c.size(); n++)
            cards.push_back(c[n]);
    }
    Move(): mType(SINGLE),
    nValue(0) {}
    bool IsEqual(vector<int> &play) {
        //std::sort(cards.begin(), cards.end());
        if(play.size() != cards.size())
            return false;
        for(int i=0; i<cards.size(); i++) {
            if(cards[i] != play[i])
                return false;
        }
        return true;
    }
    MoveType getType() const { return mType; }
    int getValue() const { return nValue; }
    bool operator<(const Move &vMv) const {
        if(cards.size() != vMv.cards.size())
            return cards.size() < vMv.cards.size();
        return cards[0] < vMv.cards[0];
    }
    bool IsLess(const Move & Mv) const {
        assert(cards.size() == Mv.cards.size());
        return nValue < Mv.getValue();
    }
    std::string toStr() {
        std::sort(cards.begin(), cards.end());
        std::string outStr = "";
        const char outCard[] = "A23456789TJQK";
        const char suit[] = "SHCD";//"♠♡♣♢"
        if(mType == PURE_SEQUENCER) {
            outStr.push_back(suit[cards[0] / 13]);
            for(int i=0; i<cards.size(); i++) {
                outStr += outCard[cards[i] % 13];
            }
        } else if (mType == JOKER_BOMB) {
            outStr = "ffFF";
        } else if (mType == DOUBLE) {
            if(cards[0] == 52)
                outStr = "ff";
            else if(cards[0] == 53)
                outStr = "FF";
            else {
                outStr.push_back(suit[cards[0] / 13]);
                outStr += outCard[cards[0] % 13];
                outStr.push_back(suit[cards[1] / 13]);
                outStr += outCard[cards[1] % 13];
            }
        } else if (mType == SINGLE) {
            if(cards[0] == 52)
                outStr = "f";
            else if(cards[0] == 53)
                outStr = "F";
            else {
                outStr.push_back(suit[cards[0] / 13]);
                outStr += outCard[cards[0] % 13];
            }
        } else {
            for(int i=0; i<cards.size(); i++) {
                outStr.push_back(suit[cards[i] / 13]);
                outStr += outCard[cards[i] % 13];
            }
        }
        return outStr;
    }
};

// Shape represents one possible move list
// We need to concern the number of moves for a shape
class Shape {
public:
    vector<Move> vMoves;
public:
    Shape() {}
    Shape(vector<Move> &vMv) {
        vMoves = vMv;
    }
    long size() const { return vMoves.size(); }
    void push_move(Move &mv) {
        vMoves.push_back(mv);
    }
    void concat_shape(Shape &sp) {
        for(int i=0; i<sp.size(); i++)
            vMoves.push_back(sp.vMoves[i]);
    }
    void sort() {
        std::sort(vMoves.begin(), vMoves.end());
    }
    bool isEqual(Shape &sp) {
        if(vMoves.size() != sp.vMoves.size())
            return false;
        for(int i=0; i<vMoves.size(); i++){
            if(!vMoves[i].IsEqual(sp.vMoves[i].cards))
                return false;
        }
        return true;
    }
};

struct pred {
    bool operator()(Shape const & a, Shape const & b) const {
        return a.size() < b.size();
    }
};

class MoveWithPos {
public:
    int nPos;
    Move mv;
public:
    MoveWithPos():nPos(0) {}
    MoveWithPos(int pos, Move move)
    :nPos(pos),mv(move) {}
};

class Round {
public:
    vector<MoveWithPos> vMoves;
public:
    Round() {}
    void clear() { vMoves.clear(); }
    long size() const { return vMoves.size(); }
    void push_move(int nPos, Move &mv) {
        vMoves.push_back(MoveWithPos(nPos, mv));
    }
    std::string toStr() {
        string outStr = "";
        char chPos[] = "NWSE";
        for(int i=0; i<vMoves.size(); i++){
            char buff[255] = {0};
            sprintf(buff, "%c %s ", chPos[vMoves[i].nPos], vMoves[i].mv.toStr().c_str());
            outStr += buff;
        }
        return outStr;
    }
};
void getRandomCards();
void SimulateGame();
void testSimGame();
Move getFirstMove(vector<int> &deal, int grade,
                  const vector<Round> &rounds, int nPos);
Move getFollowMove(vector<int> &deal, int grade,
                   Move mvFirst, const vector<Round> &rounds, int nPos);
#endif
