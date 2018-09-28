//
// Created by Hasan Yaman on 14.12.2017.
//

#ifndef PROJECT4_HASAN_YAMAN_2015400207_MASTER_FUNCTION_H
#define PROJECT4_HASAN_YAMAN_2015400207_MASTER_FUNCTION_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Variable.h"

using namespace std;

class Function : public Node {
public:
    vector<Variable *> inputs;

    // represents the output variable of the function.

    Variable  *output;

    bool isBackwardDone;

    Function();

    Function(int _id, string _name=""); // custom constructor

    // adds given variable as an input of this function
    void addInput(Variable *input);

    // sets the output variable of the function
    void setOutput(Variable *_output);

    virtual void doForward() = 0;
    virtual void doBackward() = 0;
};

class Sine : public Function{
public:
    Sine(int _id, string _name);
    void doForward();
    void doBackward();
};

class Cosine : public Function {
public:
    Cosine(int _id, string _name);
    void doForward();
    void doBackward();
};

class Tangent : public Function {
public:
    Tangent(int _id, string _name);
    void doForward();
    void doBackward();
};

class InverseSine : public Function {
public:
    InverseSine(int _id, string _name);
    void doForward();
    void doBackward();
};

class InverseCosine : public Function {
public:
    InverseCosine(int _id, string _name);
    void doForward();
    void doBackward();
};

class InverseTangent : public Function {
public:
    InverseTangent(int _id, string _name);
    void doForward();
    void doBackward();
};

class Exponential : public Function {
public:
    Exponential(int _id, string _name);
    void doForward();
    void doBackward();
};

class Logarithm : public Function {
public:
    Logarithm(int _id, string _name);
    void doForward();
    void doBackward();
};

class SquareRoot : public Function {
public:
    SquareRoot(int _id, string _name);
    void doForward();
    void doBackward();
};

class Addition : public Function {
public:
    Addition(int _id, string _name);
    void doForward();
    void doBackward();
};

class Multiplication : public Function {
public:
    Multiplication(int _id, string _name);
    void doForward();
    void doBackward();
};

class Subtraction : public Function {
public:
    Subtraction(int _id, string _name);
    void doForward();
    void doBackward();
};

class Divide : public Function {
public:
    Divide(int _id, string _name);
    void doForward();
    void doBackward();
};

class Power : public Function {
public:
    Power(int _id, string _name);
    void doForward();
    void doBackward();
};

class Identity : public Function {
public:
    Identity(int _id, string _name);
    void doForward();
    void doBackward();
};



#endif //PROJECT4_HASAN_YAMAN_2015400207_MASTER_FUNCTİON_H
