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

using namespace std;

class MyTestClientHandler : public ClientHandler {
    Solver<string, string>* s;
    CacheManager<string>* cm;

public:
    MyTestClientHandler(Solver<string, string>* solver) {
        this->s = solver;
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


    string handleClient(int client_socket) {
        char buffer[1024] = {0};
        string str;
        bool isFirst = true;
        vector<vector<int>> mat;
        list<string> buffers;

        int valread = read(client_socket, buffer, 1024);
        while (!isEnd(buffer)) {
            buffers.push_back(buffer);
            buffer[1024] = {0};
            valread = read(client_socket, buffer, 1024);
        }

        //now the last buffer has "end"
        string goalState = buffers.back();
        buffers.pop_back();
        string initialState = buffers.back();
        buffers.pop_back();

        str = cutEnd(buffer);
        if (str.length() > 0) {
            buffers.push_back(str);
        }

        //now we have initialState, goalState and buffers
        Matrix m = buffsToMatrix(buffers, initialState, goalState);
    }


    Searchable<Point> buffsToMatrix(list<string> buffers, string init, string goal) {
        vector<vector<int>> vecs = createVector(buffers.front());
        buffers.pop_front();
        while(!buffers.empty()) {
            vecs = addToMat(buffers.front(), vecs);
            buffers.pop_front();
        }

        Point* is = stringToPoint(init);
        Point* gs = stringToPoint(goal);
        int initialCost = vecs.at(is->getX()).at(is->getY());
        int goalCost = vecs.at(gs->getX()).at(gs->getY());

        State<Point>* initialState = new State<Point>(is, initialCost, NULL);
        State<Point>* goalState = new State<Point>(gs, goalCost, NULL);

        Searchable<Point> mat = new Matrix(vecs, initialState, goalState, State<Point>(Point(), 0, nullptr));

        return mat;
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
                    //mat[0][vecCount] = stoi(curr);
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

    Point* stringToPoint(string str) {
        vector<int> temp;
        int i, j;
        string curr = "";
        int len = str.length();

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

        Point* p = new Point(temp.at(0), temp.at(1));
        return p;
    }

};

#endif //EX4_MYTESTCLIENTHANDLER_H
