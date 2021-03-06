//
// Created by ofir on 13/01/2020.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include <iostream>
#include "ClientHandler.h"
#include "Solver.h"
#include "Matrix.h"
#include <bits/stdc++.h>
#include "Searchable.h"
#include "State.h"
#include "CacheManager.h"
#include "ObjectAdapter.h"
#include <string>
#include <unordered_map>

using namespace std;

class MyTestClientHandler : public ClientHandler {
    Solver<Matrix, string>* s;
    CacheManager<string, string>* cm;

public:
    MyTestClientHandler(Solver<Matrix, string>* solver, CacheManager<string, string>* cache) {
        this->s = solver;
        this->cm = cache;
    }

    //this string includes the "end"
    bool isEnd(char buffer[]) {
        string buff = buffer;
        for (int i = 0; i < buff.length(); i++)  {
            if ((buff[i] == 'e') && (buff[i + 1] == 'n') && (buff[i + 2] == 'd')) {
                return true; //includes "end"
            }
        }
        return false; //doesn't include "end"
    }

    //returns the last buffer without the string "end"
    string cutEnd(char buffer[]) {
        string buff = buffer;
        string ret = "";

        for (int i = 0; i < buff.length(); i++) {
            if ((buff[i] == 'e') && (buff[i + 1] == 'n') && (buff[i + 2] == 'd')) {
                return ret;
            } else {
                ret += buff[i];
            }
        }
        return ret;
    }


    void handleClient(int client_socket) {
    //virtual string handleClient(int client_socket) {
        char buffer[1024] = {0};
        string str;
        bool isFirst = true;
        vector<vector<int>> mat;
        list<string> buffers;
        string solution;

        //memset(buffer, 0, 1024);
        int valread = read(client_socket, buffer, 1024);
        while (!isEnd(buffer)) {
            buffers.push_back(buffer);
            memset(buffer, 0, 1024);
            valread = read(client_socket, buffer, 1024);
        }

        string matrixString = listToString(buffers);

        string goalState = buffers.back();
        buffers.pop_back();
        string initialState = buffers.back();
        buffers.pop_back();

        //convert the buffers list to a matrix
        Matrix m = buffsToMatrix(buffers, initialState, goalState);

        //convert the matrix to string by sending it to hash
        hash<string> hasher;
        int hash = int(hasher(matrixString));
        string problem = to_string(hash);

        //if we already solved this problem, take it from cache
        if (cm->isExist(problem)) {
            solution = cm->getSolution(problem);
        } else {
            solution = s->solve(m);
            cm->insert(problem, solution);
        }

        int is_sent = send(client_socket, solution.c_str(), strlen(solution.c_str()), 0);
        if (is_sent == -1) {
            cout << "Error sending message" << endl;
        }
    }


    Matrix buffsToMatrix(list<string> buffers, string init, string goal) {
        vector<vector<int>> vecs = createVector(buffers.front());
        buffers.pop_front();
        while (!buffers.empty()) {
            vecs = addToMat(buffers.front(), vecs);
            buffers.pop_front();
        }

        pair<int, int> is = stringToPair(init);
        pair<int, int> gs = stringToPair(goal);
        int initialCost = vecs[is.first][is.second];
        int goalCost = vecs[gs.first][gs.second];

        State<pair<int, int>> initialState = State<pair<int, int>>(is, initialCost, NULL);
        State<pair<int, int>> goalState = State<pair<int, int>>(gs, goalCost, NULL);

        return Matrix(vecs, initialState, goalState);
    }

    static vector<vector<int>> addToMat(string buffer, vector<vector<int>> mat) {
        vector<int> temp;
        string curr = "";
        int vecCount = 0;
        int len = buffer.length();

        for (int i = 0; i < len; i++) {
            if ((buffer[i] == ' ') || (buffer[i] == ',')) {
                if (curr != "") {
                    temp.push_back(stoi(curr));
                    curr = "";
                    vecCount++;
                }
            } else {
                curr += buffer[i];
            }
        }
        temp.push_back(stoi(curr));
        mat.push_back(temp);
        return mat;
    }

    //If it's the first time we read to a buffer, we create a vector and return it
    static vector<vector<int>> createVector(string buffer) {
        vector<vector<int>> mat;
        vector<int> temp;
        string curr = "";
        int vecCount = 0;
        int len = buffer.length();

        for (int i = 0; i < len; i++) {
            if ((buffer[i] == ' ') || (buffer[i] == ',')) {
                if (curr != "") {
                    temp.push_back(stoi(curr));
                    curr = "";
                    vecCount++;
                }
            } else {
                curr += buffer[i];
            }
        }
        //add the last "curr" to the temp vector
        temp.push_back(stoi(curr));

        //push temp to mat
        mat.push_back(temp);

        return mat;
    }

    pair<int, int> stringToPair(string str) {
        vector<int> temp;
        int x, y;
        string curr = "";
        int len = str.length();
        int i = 0;

        for (int i = 0; i < len; i++) {
            if ((str[i] == ' ') || (str[i] == ',')) {
                if (curr != "") {
                    temp.push_back(stoi(curr));
                    curr = "";
                }
            } else {
                curr += str[i];
            }
        }
        temp.push_back(stoi(curr));

        pair<int, int> ret;
        ret.first = temp.at(0);
        ret.second = temp.at(1);

        return ret;
    }

    string listToString(list<string> buffers) {
        list<string> copy = buffers;
        string str = "";
        while (copy.size() != 0) {
            str += copy.front();
            copy.pop_front();
        }
        return str;
    }
};

#endif //EX4_MYTESTCLIENTHANDLER_H






