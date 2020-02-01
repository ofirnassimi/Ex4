////
//// Created by ofir on 30/01/2020.
////
//
//#ifndef EX4_BESTFIRSTSEARCH_H
//#define EX4_BESTFIRSTSEARCH_H
//
//#include <vector>
//#include <queue>
//#include "Searcher.h"
//#include <unordered_map>
//
//#include <set>
//#include "Searchable.h"
//#include <list>
//#include <queue>
//#include <iostream>
//#include <sstream>
//
//
//class Compare {
//    vector<vector<int>> matrix;
//    static Compare *c;
//
//public:
//    vector<vector<int>> getMatrix() {
//        return this->instance()->matrix;
//    }
//    int get(pair<int,int> location) {
//        return this->getMatrix()[location.first][location.second];
//    }
//    void setMatrix(vector<vector<int>> matrix) {
//        this->matrix = matrix;
//    }
//    void set(pair<int,int> place, int value) {
//        this->instance()->matrix[place.first][place.second] = value;
//    }
//    static Compare *instance() {
//        if (!c) {
//            c = new Compare;
//        }
//        return c;
//    }
//
//    int operator()(const pair<int, int> & p1, const pair<int, int> & p2) {
//        return this->get(p1) > this->get(p2);
//    }
//};
//
//
//template <typename P, typename S>
//class BestFirstSearch : public Searcher<P,S> {
//private:
//    vector<vector<int>> matrix;
//    pair<int, int> start;
//    pair<int, int> goal;
//
//
//public:
//    BestFirstSearch(vector<vector<int>> m, pair<int,int> s, pair<int,int> g) {
//        this->matrix = m;
//        this->start = s;
//        this->goal = g;
//    }
//
//    struct hash_pair {
//        template<class T1, class T2>
//        size_t operator()(const pair<T1, T2> &p) const {
//            auto hash1 = hash<T1>{}(p.first);
//            auto hash2 = hash<T2>{}(p.second);
//            return hash1 ^ hash2;
//        }
//    };
//
//
//    Compare *Compare::c;
//    S search(P &p) {
//        priority_queue <pair<int,int>, vector<pair<int,int>>, Compare> pq;
//        Compare::instance()->setMatrix(matrix);
//        pq.push(start);
//        vector<vector<bool>> visited = makeVisited(matrix);
//        visited[start.first][start.second] = true;
//        int count = matrix[start.first][start.second];
//        stringstream s;
//
//        while (!pq.empty()) {
//            int i = pq.top().first;
//            int j = pq.top().second;
//            pq.pop();
//            if ((i == goal.first) && (j == goal.second)) {
//                pq = priority_queue <pair<int,int>, vector<pair<int,int>>, Compare>();
//            } else {
//                if ((i + 1 < matrix.size()) && (visited[i + 1][j] == false)) {
//                    count += matrix[i+1][j];
//                    s << "Down (" << count << ") ";
//                    pq.push({i + 1, j});
//                    visited[i + 1][j] = true;
//                }
//                if ((j + 1 < matrix[i].size()) && (visited[i][j + 1] == false)) {
//                    count += matrix[i][j+1];
//                    s << "Right (" << count << ") ";
//                    pq.push({i, j + 1});
//                    visited[i][j + 1] = true;
//                }
//                if ((i > 0) && (visited[i - 1][j] == false)) {
//                    count += matrix[i-1][j];
//                    s << "Up (" << count << ") ";
//                    pq.push({i - 1, j});
//                    visited[i - 1][j] = true;
//                }
//                if ((j > 0) && (visited[i][j - 1] == false)) {
//                    count += matrix[i][j-1];
//                    s << "Left (" << count << ") ";
//                    pq.push({i, j - 1});
//                    visited[i][j - 1] = true;
//                }
//            }
//        }
//        return s.str();
//    }
//
//
//    int getNumberOfNodesEvaluated() {
//        return 0;
//    }
//
//
//    // makes a 'visited' bool matrix to match the tested matrix and initial all of the values to be false.
//    vector<vector<bool>> makeVisited(vector<vector<int>> matrix) {
//        vector<vector<bool>> ret;
//        vector<bool> row;
//        for(int i = 0; i < matrix.size(); i++) {
//            for(int j = 0; j < matrix[i].size(); j++) {
//                row.push_back(false);
//            }
//            ret.push_back(row);
//            row.clear();
//        }
//        return ret;
//    }
//
//
//    //creates a string of the path
//    pair<string, int> recString(pair<int,int> start, pair<int,int> end, vector<vector<int>> matrix,
//                                unordered_map<pair<int,int>, pair<string, pair<int,int>>, hash_pair> priors) {
//        stringstream s;
//
//        if ((end.first == start.first) && (end.second == start.second)) {
//            return {"",matrix[end.first][end.second]};
//        } else {
//            pair<string,int> p = recString(start, priors.at(end).second, matrix, priors);
//            s << p.first << priors.at(end).first << " (" << p.second + matrix[end.first][end.second] << ") ";
//            return {s.str(),p.second+matrix[end.first][end.second]};
//        }
//    }
//};
//
//#endif //EX4_BESTFIRSTSEARCH_H
