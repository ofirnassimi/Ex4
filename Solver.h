//
// Created by ofir on 18/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

using namespace std;

template <class P, class S>
class Solver {

public:
   virtual S solve(P p) = 0;
};

#endif //EX4_SOLVER_H
