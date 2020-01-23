//
// Created by ofir on 19/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include <string>
#include "Solver.h"

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    string solve(string problem) {
        int n = problem.length();
        string solution = "";

        for (int i = n - 1; i >= 0; i--) {
            solution += problem[i];
        }
        return solution;
    }
};

#endif //EX4_STRINGREVERSER_H
