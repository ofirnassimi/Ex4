//
// Created by ofir on 27/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include <map>
#include <set>
#include <list>
#include <iostream>
#include "Searcher.h"
#include "State.h"
#include <cmath>
#include <vector>

using namespace std;

template <typename Solution,typename Problem>
class Astar : public Searcher<Solution, Problem> {
    list<State<pair<int, int>>> openList;
    list<State<pair<int, int>>> closeList;
    list<State<pair<int, int>>> final;
    list<State<pair<int, int>>> USES;
    int advCost = 1;
    int goolX = 10;
    int goolY = 10;
    int evaluatedNodes;

    void remove(State<pair<int, int>> &s, list<State<pair<int, int>>> &lst) {
        lst.remove(s);
    }

public:
    int getNumberOfNodesEvaluated() {
        return  this->evaluatedNodes;
    }


    bool inList(State<pair<int, int>> r, list<State<pair<int, int>>> list) {
//        for (auto visit : list) {
//            if (r.getState() != NULL) {
//                if (visit.getState()->equals(*r.getState())) {
//                    return true;
//                }
//            }
//        }
    };


    Solution search(Searchable<Problem> &s) {
//        this->evaluatedNodes = 0;
//        this->advCost = s.advState();
//        this->goolX = s.getGoolState().getPoint()->getX();
//        this->goolY = s.getGoolState().getPoint()->getY();
//        State<pair<int, int>> state = s.getInitialState();
//
//        //        pair<int, int> p(0, (this->goolX - state.getPoint()->getX()) * this->advCost +
////                            (this->goolY - state.getPoint()->getY()) * this->advCost);
//
//
//
//        state.cost = s.Cost(state.getState().first, state.getState().second);
//        State<pair<int, int>> end = s.getGoolState();
//        end.cost = s.Cost(end.getState().first, end.getState().second);
//        if (state.cost == -1 || end.getCost() == -1) {
//            list<State<pair<int, int>>>* p = new list<State<pair<int, int>>>;
//            return *p;
//        }
//        state.fromStart = 0;
//        state.toEnd = abs((this->goolX - state.getState().first) * this->advCost) +abs(
//                (this->goolY - state.getState().second) * this->advCost);
//        this->openList.push_front(state);
//        while (true) {
//            float bigestCost = INFINITY;
//            State<pair<int, int>>* q;// = State<Point *>(nullptr);
//            for (State<pair<int, int>>* x : this->openList) {
//                if((x->fromStart + x->toEnd < bigestCost) && (!inList(x,this->USES)))
//                {
//                    bigestCost = x->fromStart + x->toEnd;// this->allState[&x].first;
//                    q = x;
//                }
//            }
//
//            //this->openList.remove(q);
////            this->USES.push_front(q);
//            remove(q, openList);
//            this->evaluatedNodes++;
//            this->closeList.push_front(q);
//            if (s.isGoalState(q)) {
//                this->final.push_back(q);
//                while (true) {
//                    this->final.push_back(*q->returnFather());
//                    q = *q->returnFather();
//                    pair<int, int> zeroPair (0, 0);
//                    if (q->getPoint()->equals(zeroPair)) {
//                        return this->final;
//                    }
//                }
//            }
//            int i = 0, infinity = 0;
//            vector<State<pair<int, int>>> successor = s.getAllPossibleState(q);
//            for (i = 0; i < successor.size(); i++) {
//                if (successor[i].getCost() == -1) {
//                    infinity++;
//                    if (infinity == successor.size()) {
//                        list<State<pair<int, int>>>* p = new list<State<pair<int, int>>>;
//                        return *p;
//                    }
//                    continue;
//                }
//                if (inList(successor[i], this->closeList)) {
//                    continue;
//                }
//                successor[i].cost = s.Cost(successor[i].getPoint()->getX(), successor[i].getPoint()->getY());
//
//                if ((!inList(successor[i], this->openList)) || ((inList(successor[i], this->openList)) && ((q.fromStart + successor[i].cost < successor[i].fromStart)))) {
//
//                    State<pair<int, int>> *temp = new State<pair<int, int>>(q);
//                    successor[i].Father(temp);
//                    successor[i].fromStart = q.fromStart + successor[i].cost;
//                    successor[i].toEnd = abs((this->goolX - successor[i].getPoint()->getX()) * this->advCost) +abs(
//                            (this->goolY -  successor[i].getPoint()->getY()) * this->advCost);
//                    if ((inList(successor[i], this->openList))) {
//                        remove(successor[i],this->openList);
//                    }
//                    this->openList.push_front(successor[i]);
//                }
//
//
//            }
//        }
//        return this->final;
    }
};

#endif //EX4_ASTAR_H