//
// Created by ofir on 19/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

#include <unordered_map>
#include <list>
#include <string>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <functional>

using namespace std;

template <typename P, typename S>
class CacheManager {
public:
    virtual void insert(P problem, S solution) = 0;
    virtual S getSolution(P problem) = 0;
    virtual void update(typename unordered_map<string, pair<S, list<string>::iterator>>::iterator& it) = 0;
    virtual bool isExist(P problem) = 0;
};



#endif //EX4_CACHEMANAGER_H