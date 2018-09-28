//
// Created by Hasan Yaman on 14.12.2017.
//

#include "Function.h"

Function::Function() {
}

Function::Function(int _id, string _name) {
    this->id = _id;
    this->name = _name;
}

void Function::addInput(Variable *input) {
    this->inputs.push_back(input);
    this->numberOfComing++;
}

void Function::setOutput(Variable *_output) {
    this->output = _output;
    this->numberOfGoing++;
}

Sine::Sine(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Sine::doForward() {
    double aci = this->inputs.at(0)->value;
    double result = sin(aci);
    output->value = result;
}

void Sine::doBackward() {
    double aci = this->inputs.at(0)->value;
    double result = cos(aci) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}

Cosine::Cosine(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Cosine::doForward() {
    double aci = this->inputs.at(0)->value;
    double result = cos(aci);
    output->value = result;
}

void Cosine::doBackward() {
    double aci = this->inputs.at(0)->value;
    double result = (-1) * sin(aci) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}
Tangent::Tangent(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Tangent::doForward() {
    double aci = this->inputs.at(0)->value;
    double result = tan(aci);
    output->value = result;
}

void Tangent::doBackward() {
    double aci = this->inputs.at(0)->value;
    double result = (1 / cos(aci)) * (1 / cos(aci)) * this->output->derivative; // sec kare x
    this->inputs.at(0)->derivative += result;
}

InverseSine::InverseSine(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void InverseSine::doForward() {
    double aci = this->inputs.at(0)->value;
    double result = asin(aci);
    output->value = result;
}

void InverseSine::doBackward() {
    double x = this->inputs.at(0)->value;
    double result = (1 / sqrt(1 - x * x)) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}

InverseCosine::InverseCosine(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}
void InverseCosine::doForward() {
    double aci = this->inputs.at(0)->value;
    double result = acos(aci);
    output->value = result;
}

void InverseCosine::doBackward() {
    double x = this->inputs.at(0)->value;
    double result = ((-1) / sqrt(1 - x * x)) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}

InverseTangent::InverseTangent(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void InverseTangent::doForward() {
    double aci = this->inputs.at(0)->value;
    double result = atan(aci);
    output->value = result;
}

void InverseTangent::doBackward() {
    double x =this->inputs.at(0)->value;
    double result = (1 / (1 + (x * x))) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}

Exponential::Exponential(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Exponential::doForward() {
    double inp = this->inputs.at(0)->value;
    double result = exp(inp);
    output->value = result;
}

void Exponential::doBackward() {
    double x = this->inputs.at(0)->value;
    double result = (exp(x)) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}

Logarithm::Logarithm(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Logarithm::doForward() {
    double inp = this->inputs.at(0)->value;
    double result = log(inp);
    output->value = result;
}

void Logarithm::doBackward() {
    double x = this->inputs.at(0)->value;
    double result = (1 / x) * this->output->derivative;
    this->inputs.at(0)->derivative += result;
}

SquareRoot::SquareRoot(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void SquareRoot::doForward() {
    double inp = this->inputs.at(0)->value;
    double result = sqrt(inp);
    output->value = result;
}

void SquareRoot::doBackward() {
    double x = this->inputs.at(0)->value;
    double result = (0.5 * (1 / sqrt(x))) * this->output->derivative;
    this->inputs.at(0)->derivative += result;

}

Addition::Addition(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Addition::doForward() {
    double arg1 = this->inputs.at(0)->value;
    double arg2 = this->inputs.at(1)->value;
    double result = arg1 + arg2;
    output->value = result;
}

void Addition::doBackward() {
    this->inputs.at(0)->derivative += this->output->derivative;
    this->inputs.at(1)->derivative += this->output->derivative;
}

Multiplication::Multiplication(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Multiplication::doForward() {
    double arg1 = this->inputs.at(0)->value;
    double arg2 = this->inputs.at(1)->value;
    double result = arg1 * arg2;
    output->value = result;
}

void Multiplication::doBackward() {
    double value0 = this->inputs.at(0)->value;
    double value1 = this->inputs.at(1)->value;

    this->inputs.at(0)->derivative += value1 * this->output->derivative;
    this->inputs.at(1)->derivative += value0 * this->output->derivative;
}

Subtraction::Subtraction(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Subtraction::doForward() {
    double arg1 = this->inputs.at(0)->value;
    double arg2 = this->inputs.at(1)->value;
    double result = arg1 - arg2;
    output->value = result;
}

void Subtraction::doBackward() {
    this->inputs.at(0)->derivative += this->output->derivative;
    this->inputs.at(1)->derivative += (-1) * this->output->derivative;

}

Divide::Divide(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Divide::doForward() {
    double arg1 = this->inputs.at(0)->value;
    double arg2 = this->inputs.at(1)->value;
    double result = arg1 / arg2;
    output->value = result;
}

void Divide::doBackward() {
    double value0 = this->inputs.at(0)->value;
    double value1 = this->inputs.at(1)->value;
    this->inputs.at(0)->derivative += (1 / value1) * this->output->derivative;
    this->inputs.at(1)->derivative += (((-1) * value0) / (value1 * value1)) * this->output->derivative;
}

Power::Power(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Power::doForward() {
    double arg1 = this->inputs.at(0)->value;
    double arg2 = this->inputs.at(1)->value;
    double result = pow(arg1,arg2);
    output->value = result;
}

void Power::doBackward() {
    double value0 = this->inputs.at(0)->value;
    double value1 = this->inputs.at(1)->value;
    this->inputs.at(0)->derivative += value1 * pow(value0,(value1-1)) * this->output->derivative;
    this->inputs.at(1)->derivative += log(value0) * pow(value0, value1) * this->output->derivative;
}


Identity::Identity(int _id, string _name) {
    this->id = _id;
    this->name = _name;
    this->isVisited = false;
    this->numberOfComing = 0;
    this->numberOfGoing = 0;
    this->originalComing = 0;
    this->originalGoing = 0;
    this->isBackwardDone = false;
}

void Identity::doForward() {
    double left_side = this->inputs.at(0)->value;
    double right_side = left_side;
    output->value = right_side;
}

void Identity::doBackward() {
    double result = this->output->derivative;
    this->inputs.at(0)->derivative += result;
}
