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

        double leftCost, rightCost, upCost, downCost;

        //if s is on top
        if (s.getState().first == 0) {
            //if s is on top left
            if (s.getState().second == 0) { //can go only right and down
                //right State
                pair<int, int> rightS (x, y + 1);
                rightCost = s.getCost() + mat[x][y + 1];
                succerssors.push_back(new State<pair<int, int>>(rightS, rightCost, &s));
                //down State
                pair<int, int> downS (x + 1, y);
                downCost = s.getCost() + mat[x + 1][y];
                succerssors.push_back(new State<pair<int, int>>(downS, downCost, &s));

                //if s is on top right
            } else if (s.getState().second == getMaxY()) { //can go only left and down
                pair<int, int> leftS (x, y - 1);
                leftCost = s.getCost() + mat[x][y - 1];
                succerssors.push_back(new State<pair<int, int>>(leftS, leftCost, &s));

                pair<int, int> downS (x + 1, y);
                downCost = s.getCost() + mat[x + 1][y];
                succerssors.push_back(new State<pair<int, int>>(downS, downCost, &s));

                //s is on top but not the left or right
            } else {
                //can go left, right and down
                pair<int, int> rightS (x, y + 1);
                rightCost = s.getCost() + mat[x][y + 1];
                succerssors.push_back(new State<pair<int, int>>(rightS, rightCost, &s));

                pair<int, int> leftS (x, y - 1);
                leftCost = s.getCost() + mat[x][y - 1];
                succerssors.push_back(new State<pair<int, int>>(leftS, leftCost, &s));

                pair<int, int> downS (x + 1, y);
                downCost = s.getCost() + mat[x + 1][y];
                succerssors.push_back(new State<pair<int, int>>(downS, downCost, &s));
            }

            //if s is the lowest
        } else if (s.getState().first == getMaxX()) {
            //if s is low left
            if (s.getState().second == 0) {
                //can go only up and right
                pair<int, int> upS (x - 1, y);
                upCost = s.getCost() + mat[x - 1][y];
                succerssors.push_back(new State<pair<int, int>>(upS, upCost, &s));

                pair<int, int> rightS (x, y + 1);
                rightCost = s.getCost() + mat[x][y + 1];
                succerssors.push_back(new State<pair<int, int>>(rightS, rightCost, &s));

                //if s is low right
            } else if (s.getState().second == getMaxY()) {
                //can go only up and left
                pair<int, int> upS (x - 1, y);
                upCost = s.getCost() + mat[x - 1][y];
                succerssors.push_back(new State<pair<int, int>>(upS, upCost, &s));

                pair<int, int> leftS (x, y - 1);
                leftCost = s.getCost() + mat[x][y - 1];
                succerssors.push_back(new State<pair<int, int>>(leftS, leftCost, &s));

                //s is low but not the left or right
            } else {
                //can go left, right, up
                pair<int, int> upS (x - 1, y);
                upCost = s.getCost() + mat[x - 1][y];
                succerssors.push_back(new State<pair<int, int>>(upS, upCost, &s));

                pair<int, int> leftS (x, y - 1);
                leftCost = s.getCost() + mat[x][y - 1];
                succerssors.push_back(new State<pair<int, int>>(leftS, leftCost, &s));

                pair<int, int> rightS (x, y + 1);
                rightCost = s.getCost() + mat[x][y + 1];
                succerssors.push_back(new State<pair<int, int>>(rightS, rightCost, &s));
            }

            //if s is left and not top or low (because we already did it)
        } else if ((s.getState().second == 0) && (s.getState().first != 0) && (s.getState().first != getMaxX())) {
            //can go only up, down and right
            pair<int, int> upS (x - 1, y);
            upCost = s.getCost() + mat[x - 1][y];
            succerssors.push_back(new State<pair<int, int>>(upS, upCost, &s));

            pair<int, int> downS (x + 1, y);
            downCost = s.getCost() + mat[x + 1][y];
            succerssors.push_back(new State<pair<int, int>>(downS, downCost, &s));

            pair<int, int> rightS (x, y + 1);
            rightCost = s.getCost() + mat[x][y + 1];
            succerssors.push_back(new State<pair<int, int>>(rightS, rightCost, &s));

            //if s is right and not top or low
        } else if ((s.getState().second == getMaxY()) && (s.getState().first != 0) && (s.getState().first != getMaxX())) {
            //can go only up, down and left
            pair<int, int> upS (x - 1, y);
            upCost = s.getCost() + mat[x - 1][y];
            succerssors.push_back(new State<pair<int, int>>(upS, upCost, &s));

            pair<int, int> downS (x + 1, y);
            downCost = s.getCost() + mat[x + 1][y];
            succerssors.push_back(new State<pair<int, int>>(downS, downCost, &s));

            pair<int, int> leftS (x, y - 1);
            leftCost = s.getCost() + mat[x][y - 1];
            succerssors.push_back(new State<pair<int, int>>(leftS, leftCost, &s));

            //else, not on edges, can go on every direction
        } else {
            pair<int, int> upS (x - 1, y);
            upCost = s.getCost() + mat[x - 1][y];
            succerssors.push_back(new State<pair<int, int>>(upS, upCost, &s));

            pair<int, int> downS (x + 1, y);
            downCost = s.getCost() + mat[x + 1][y];
            succerssors.push_back(new State<pair<int, int>>(downS, downCost, &s));

            pair<int, int> leftS (x, y - 1);
            leftCost = s.getCost() + mat[x][y - 1];
            succerssors.push_back(new State<pair<int, int>>(leftS, leftCost, &s));

            pair<int, int> rightS (x, y + 1);
            rightCost = s.getCost() + mat[x][y + 1];
            succerssors.push_back(new State<pair<int, int>>(rightS, rightCost, &s));
        }

        return succerssors;
    }


    int calculateCost(State<pair<int, int>> curr, State<pair<int, int>> parent) {
        double totalCost;
        if (parent.getCost() == NULL) {
            totalCost = pointToValue(curr);
        } else {
            totalCost = parent.getCost() + pointToValue(curr);
        }
        return totalCost;
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


    vector<vector<int>> getMat() {
        return this->mat;
    }


    State<pair<int, int>>* getGoalState() {
        return &this->goalState;
    }
};

#endif //EX4_MATRIX_H