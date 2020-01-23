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

template <typename T>
class CacheManager {
    int capacity;
    unordered_map<string, pair<T, list<string>::iterator>> cachePointers;
    list<string> cacheList;

public:
    CacheManager(int c) {
        this -> capacity = c;
    }

    void insert(string key, T obj) {
        //create a file named on the key string
        //write to the file
        ofstream oFile;
        oFile.open(T::class_name + key, ios::binary);
        oFile.write((char *) &obj, sizeof(obj));

        auto item = cachePointers.find(key);

        //if item exists, update it and put new value
        if (item != cachePointers.end()) {
            update(item);
            cachePointers[key] = {obj, cacheList.begin()}; //TODO:
            return;
        }
        //item doesn't exist
        if (cachePointers.size() == (unsigned) capacity) { // I had a warning, so I had to change capacity to unsigned int
            cachePointers.erase(cacheList.back());
            cacheList.pop_back();
        }
        cacheList.push_front(key);
        cachePointers.insert({key, {obj, cacheList.begin()}});
    }

    T get (string key) {
        auto item = cachePointers.find(key);

        //if item is not in list, check if has file
        //if item doesn't exist, throw exception
        if (item == cachePointers.end()) {
            ifstream ifile(T::class_name + key);
            if(!ifile) {
                throw "can't find item";
            } else {
                ifstream file;
                file.open(T::class_name + key, ios::binary);
                T obj;
                file.read((char*) &obj, sizeof(obj));

                if (cachePointers.size() == (unsigned) capacity) {
                    cachePointers.erase(cacheList.back());
                    cacheList.pop_back();
                }
                cacheList.push_front(key);
                cachePointers.insert({key, {obj, cacheList.begin()}});

                return obj;
            }
        }
        //update the item to be the first in the list and return it
        update(item);

        return item->second.first; //return the first object in the second value
    }

    void update (typename unordered_map<string, pair<T, list<string>::iterator>>::iterator& it) {
        //erase item from list
        cacheList.erase(it->second.second);
        //add item to the beginning of the list
        cacheList.push_front(it->first);
        //point the pointer to the beginning of the list
        it->second.second = cacheList.begin();
    }

    void foreach(const function<void(T&)> func) {
        for (string it : cacheList) {
            func(cachePointers[it].first);
        }
    }
};

#endif //EX4_CACHEMANAGER_H
