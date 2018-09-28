//
// Created by Hasan Yaman on 14.12.2017.
//

#ifndef PROJECT4_HASAN_YAMAN_2015400207_MASTER_VARIABLE_H
#define PROJECT4_HASAN_YAMAN_2015400207_MASTER_VARIABLE_H

#include <vector>
#include <string>

using namespace std;

class Function;

class Node {
public:
    int id;
    string name;

    bool isVisited;
    int numberOfComing;
    int numberOfGoing;

    int originalComing;
    int originalGoing;
};

class Variable : public Node {
public:
    double value;

    double derivative;

    // represents that which function determines the variable
    // it will be null for inputs or constants
    Function *from;

    // represents the list of functions that takes the variable as input
    vector<Function *> to;

    Variable(int _id, string _name);

    void setFrom(Function *_from);

    // adds the given function to 'to' vector
    void addTo(Function *_to);
};


#endif //PROJECT4_HASAN_YAMAN_2015400207_MASTER_VARİABLE_H
