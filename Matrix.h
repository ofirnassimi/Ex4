//
// Created by ofir on 20/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include <iostream>
#include <vector>
#include "Searchable.h"

using namespace std;

class Matrix : public Searchable<pair<int, int>> {
    vector<vector<int>> mat;
    State<pair<int, int>> initialState;
    State<pair<int, int>> goalState;

public:
    Matrix(const vector<vector<int>> &m, State<pair<int, int>> &init, State<pair<int, int>> &goal) :
    mat(m), initialState(init), goalState(goal) {};


    State<pair<int, int>>* getInitialState() {
        return &this->initialState;
    }


    bool isGoalState(State<pair<int, int>> &s) {
        if (goalState.getState().first == s.getState().first) {
            if (goalState.getState().second == s.getState().second) {
                return true;
            }
        }
        return false;
    }


    list<State<pair<int, int>>*> getAllPossibleStates(State<pair<int, int>> &s) {
        int x = s.getState().first;
        int y = s.getState().second;
        list<State<pair<int, int>>*> succerssors;

        int leftCost, rightCost, upCost, downCost;

        //if s is on top
        if (s.getState().first == 0) {
            //if s is on top left
            if (s.getState().second == 0) {
                //can go only right and down
                //rightCost = calculateCost();

                //if s is on top right
            } else if (s.getState().second == getMaxY()) {
                //can go only left and down

                //s is on top but not the left or right
            } else {
                //can go left, right and down
            }

            //if s is the lowest
        } else if (s.getState().first == getMaxX()) {
            //if s is low left
            if (s.getState().second == 0) {
                //can go only up and right

                //if s is low right
            } else if (s.getState().second == getMaxY()) {
                //can go only up and left

                //s is low but not the left or right
            } else {
                //can go left, right, up
            }

            //if s is left and not top or low (because we already did it)
        } else if ((s.getState().second == 0) && (s.getState().first != 0) && (s.getState().first != getMaxX())) {
            //can go only up, down and right

            //if s is right and not top or low
        } else if ((s.getState().second == getMaxY()) && (s.getState().first != 0) && (s.getState().first != getMaxX())) {
            //can go only up, down and left

            //else, not on edges, can go on every direction
        } else {

        }

//        //TODO: change costs!!!!
//        //TODO: Change the way of checking if this variable is in matrix borders!!!
//        int leftCost = mat[x][y - 1];
//        int rightCost = mat[x][y + 1];
//        int upCost = mat[x - 1][y];
//        int downCost = mat[x + 1][y];
//
//        if (leftCost != NULL) {
//            pair<int, int> l;
//            l.first = x;
//            l.second = y;
//            //State<pair<int, int>>* sp = new State<pair<int, int>>(l, left, &s);
//            succerssors.push_back(new State<pair<int, int>>(l, leftCost, &s));
//        }
//        if (rightCost != NULL) {
//            pair<int, int> r;
//            r.first = y + 1;
//            r.second = x;
//            //State<pair<int, int>>* sp = new State<pair<int, int>>(r, right, &s);
//            succerssors.push_back(new State<pair<int, int>>(r, rightCost, &s));
//        }
//        if (upCost != NULL) {
//            pair <int, int> u;
//            u.first = y;
//            u.second = x - 1;
//            succerssors.push_back(new State<pair<int, int>>(u, upCost, &s));
//        }
//        if (downCost != NULL) {
//            pair <int, int> d;
//            d.first = y;
//            d.second = x + 1;
//            succerssors.push_back(new State<pair<int, int>>(d, downCost, &s));
//        }

        return succerssors;
    }


    int calculateCost(State<pair<int, int>> curr, State<pair<int, int>> parent) {
        return parent.getCost() + pointToValue(parent);
    }


    int pointToValue(State<pair<int, int>> s) {
        int x = s.getState().first;
        int y = s.getState().second;
        return mat[x][y];
    }


    int getMaxY() {
        return mat[0].size() - 1;
    }


    int getMaxX() {
        return mat.size() - 1;
    }
};

#endif //EX4_MATRIX_H