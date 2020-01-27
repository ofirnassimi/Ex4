//
// Created by ofir on 20/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"

using namespace std;

class FileCacheManager : public CacheManager<string, string> {
    int capacity = 10;
    unordered_map<string, pair<string, list<string>::iterator>> cachePointers;
    list<string> cacheList;

public:
    FileCacheManager() {}

    void insert(string problem, string solution) {
        //create a file named on the key string
        //write to the file
        ofstream oFile;
        oFile.open(problem, ios::binary);
        oFile.write((char *) &solution, sizeof(solution));

        auto item = cachePointers.find(problem);

        //if item exists, update it and put new value
        if (item != cachePointers.end()) {
            update(item);
            cachePointers[problem] = {solution, cacheList.begin()};
            return;
        }
        //item doesn't exist
        if (cachePointers.size() == (unsigned) capacity) { // I had a warning, so I had to change capacity to unsigned int
            cachePointers.erase(cacheList.back());
            cacheList.pop_back();
        }
        cacheList.push_front(problem);
        cachePointers.insert({problem, {solution, cacheList.begin()}});
    }


    string getSolution(string problem) {
        auto item = cachePointers.find(problem);

        //if item is not in list, check if has file
        //if item doesn't have file, throw exception
        if (item == cachePointers.end()) {
            ifstream ifile(problem);
            if(!ifile) {
                throw "can't find item";
            } else {
                ifstream file;
                file.open(problem, ios::binary);
                string solution;
                file.read((char*) &solution, sizeof(solution));

                if (cachePointers.size() == (unsigned) capacity) {
                    cachePointers.erase(cacheList.back());
                    cacheList.pop_back();
                }
                cacheList.push_front(problem);
                cachePointers.insert({problem, {solution, cacheList.begin()}});

                return solution;
            }
        }
        //update the item to be the first in the list and return it
        update(item);

        return item->second.first; //return the first object in the second value
    }

    //void update(string problem, string solution) {
    void update (typename unordered_map<string, pair<string, list<string>::iterator>>::iterator& it) {
        //erase item from list
        cacheList.erase(it->second.second);
        //add item to the beginning of the list
        cacheList.push_front(it->first);
        //point the pointer to the beginning of the list
        it->second.second = cacheList.begin();
    }

    void foreach(const function<void(string&)> func) {
        for (string it : cacheList) {
            func(cachePointers[it].first);
        }
    }


    bool isExist(string problem) {
        auto item = cachePointers.find(problem);

        //if item exists, update it to be first in the list
        if (item != cachePointers.end()) {
            update(item);
            return true;
        }
        return false;
    }
};

#endif //EX4_FILECACHEMANAGER_H
