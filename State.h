//
// Created by ofir on 21/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

template <typename T>
class State {
    T st;
    double cost;
    State<T>* cameFrom;

public:
    State(T state, double c, State<T>* last) {
        this->st = state;
        this->cost = c;
        this->cameFrom = last;
    }

//    State() {}

    bool Equals(State<T> s) {}

    T getState() {
        return st;
    }

    double getCost() {
        return cost;
    }
};

#endif //EX4_STATE_H
