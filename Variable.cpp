//
// Created by Hasan Yaman on 14.12.2017.
//

#include "Variable.h"
Variable::Variable(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->value = 0;
    this->derivative = 0;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
}

void Variable::addTo(Function *_to) {
    this->to.push_back(_to);
    this->numberOfGoing++;
}

void Variable::setFrom(Function *_from) {
    this->from = _from;
    this->numberOfComing++;
}