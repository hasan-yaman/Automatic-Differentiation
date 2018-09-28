#include <iostream>
#include <vector>
#include <unordered_map>
#include "Function.h"
#include <fstream>
#include <iomanip>

using namespace std;

enum TYPES {
    VARIABLE, FUNCTION
};

int main(int argc, char *argv[]) {
    vector<Node *> nodes;

    vector<string> nonConstantNames; // to hold input names
    int inputNamesSize;

    unordered_map<int, TYPES> type;
    unordered_map<string, int> id;
    unordered_map<int, Variable *> vars;
    unordered_map<int, Function *> fncs;

    bool haveCycle = false;

    int idCounter = 0;

    ifstream function_define_file(argv[1]);
    ifstream input_values_file(argv[2]);
    ofstream output_values_file(argv[3]);
    ofstream derivative_output_values_file(argv[4]);
    string s;

    // process of function define file
    while (function_define_file >> s) {
        if (s == "input") {
            // input case
            string name;
            function_define_file >> name;

            Variable *variable = new Variable(idCounter, name);
            ++idCounter;

            nodes.push_back(&(*variable));
            vars.emplace(variable->id, variable);
            type.emplace(variable->id, VARIABLE);
            id.emplace(name, variable->id);

            nonConstantNames.push_back(name);
            ++inputNamesSize;

        } else if (s == "output") {
            // output case
            string name;
            function_define_file >> name;

            Variable *variable = new Variable(idCounter, name);
            ++idCounter;

            nodes.push_back(&(*variable));
            vars.emplace(variable->id, variable);
            type.emplace(variable->id, VARIABLE);
            id.emplace(name, variable->id);
        } else {
            unordered_map<string, int>::const_iterator iterator = id.find(s);

            nonConstantNames.push_back(s);

            bool isCreatedBefore = false;
            if (iterator != id.end()) {
                isCreatedBefore = true;
            }

            string assignment;
            function_define_file >> assignment;

            string function_name;
            function_define_file >> function_name;

            unordered_map<string, int>::const_iterator nameIDite = id.find(function_name);
            if (nameIDite == id.end()) {
                string inp1;
                function_define_file >> inp1;

               /* unordered_map<string, int>::const_iterator iterator1 = id.find(s);
                if(iterator1 != id.end()) {
                    if(iterator1->second != inputNamesSize) {

                        haveCycle = true;
                    }

                } */

                if (find(nonConstantNames.begin(), nonConstantNames.end(), inp1) != nonConstantNames.end()) {
                    // inputNames have inp1
                } else {
                    // inp1 is constant
                    Variable *constantVariable = new Variable(idCounter, inp1);
                    ++idCounter;

                    double constantValue = stod(inp1);
                    constantVariable->value = constantValue;

                    nodes.push_back(&(*constantVariable));
                    vars.emplace(constantVariable->id, constantVariable);
                    type.emplace(constantVariable->id, VARIABLE);
                    id.emplace(inp1, constantVariable->id);

                }
                // process first input
                Variable *input1;

                unordered_map<string, int>::const_iterator IDIte1 = id.find(inp1);

                if (IDIte1 == id.end()) {
                    haveCycle = true;
                    break;
                } else {
                    int inp1ID = id.at(inp1);

                    if (type.at(inp1ID) == VARIABLE) {
                        input1 = vars.at(inp1ID);
                    } else {
                        input1 = fncs.at(inp1ID)->output;
                    }
                }

                if (function_name == "sin") {
                    // sine
                    Sine *sine = new Sine(idCounter, s);
                    ++idCounter;

                    sine->addInput(input1);
                    input1->addTo(sine);

                    // find output
                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(sine);
                    sine->setOutput(output);

                    nodes.push_back(&(*sine));
                    id.emplace(sine->name, sine->id);
                    fncs.emplace(sine->id, sine);
                    type.emplace(sine->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "cos") {
                    Cosine *cosine = new Cosine(idCounter, s);
                    ++idCounter;
                    cosine->addInput(input1);
                    input1->addTo(cosine);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(cosine);
                    cosine->setOutput(output);

                    nodes.push_back(&(*cosine));
                    id.emplace(cosine->name, cosine->id);
                    fncs.emplace(cosine->id, cosine);
                    type.emplace(cosine->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "tan") {
                    Tangent *tangent = new Tangent(idCounter, s);
                    ++idCounter;
                    tangent->addInput(input1);
                    input1->addTo(tangent);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(tangent);
                    tangent->setOutput(output);

                    nodes.push_back(&(*tangent));
                    id.emplace(tangent->name, tangent->id);
                    fncs.emplace(tangent->id, tangent);
                    type.emplace(tangent->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "acos") {
                    InverseCosine *cosine = new InverseCosine(idCounter, s);
                    ++idCounter;
                    cosine->addInput(input1);
                    input1->addTo(cosine);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(cosine);
                    cosine->setOutput(output);

                    nodes.push_back(&(*cosine));
                    id.emplace(cosine->name, cosine->id);
                    fncs.emplace(cosine->id, cosine);
                    type.emplace(cosine->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);


                } else if (function_name == "asin") {
                    InverseSine *sine = new InverseSine(idCounter, s);
                    ++idCounter;
                    sine->addInput(input1);
                    input1->addTo(sine);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(sine);
                    sine->setOutput(output);

                    nodes.push_back(&(*sine));
                    id.emplace(sine->name, sine->id);
                    fncs.emplace(sine->id, sine);
                    type.emplace(sine->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "atan") {
                    InverseTangent *tangent = new InverseTangent(idCounter, s);
                    ++idCounter;
                    tangent->addInput(input1);
                    input1->addTo(tangent);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(tangent);
                    tangent->setOutput(output);

                    nodes.push_back(&(*tangent));
                    id.emplace(tangent->name, tangent->id);
                    fncs.emplace(tangent->id, tangent);
                    type.emplace(tangent->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "exp") {
                    Exponential *exponential = new Exponential(idCounter, s);
                    ++idCounter;
                    exponential->addInput(input1);
                    input1->addTo(exponential);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(exponential);
                    exponential->setOutput(output);

                    nodes.push_back(&(*exponential));
                    id.emplace(exponential->name, exponential->id);
                    fncs.emplace(exponential->id, exponential);
                    type.emplace(exponential->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "log") {
                    Logarithm *logarithm = new Logarithm(idCounter, s);
                    ++idCounter;
                    logarithm->addInput(input1);
                    input1->addTo(logarithm);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(logarithm);
                    logarithm->setOutput(output);

                    nodes.push_back(&(*logarithm));
                    id.emplace(logarithm->name, logarithm->id);
                    fncs.emplace(logarithm->id, logarithm);
                    type.emplace(logarithm->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else if (function_name == "sqrt") {
                    SquareRoot *squareRoot = new SquareRoot(idCounter, s);
                    ++idCounter;
                    squareRoot->addInput(input1);
                    input1->addTo(squareRoot);

                    Variable *output = new Variable(idCounter, s + "out");
                    ++idCounter;
                    if (isCreatedBefore) {
                        output = vars.at(inputNamesSize);
                        --idCounter;
                    }

                    output->setFrom(squareRoot);
                    squareRoot->setOutput(output);

                    nodes.push_back(&(*squareRoot));
                    id.emplace(squareRoot->name, squareRoot->id);
                    fncs.emplace(squareRoot->id, squareRoot);
                    type.emplace(squareRoot->id, FUNCTION);

                    nodes.push_back(&(*output));
                    id.emplace(output->name, output->id);
                    vars.emplace(output->id, output);
                    type.emplace(output->id, VARIABLE);

                } else {
                    // functions that have 2 inputs
                    string inp2;
                    function_define_file >> inp2;

                    if (find(nonConstantNames.begin(), nonConstantNames.end(), inp2) != nonConstantNames.end()) {
                    } else {
                        // inp2 is constant
                        Variable *constantVariable = new Variable(idCounter, inp2);
                        ++idCounter;

                        double constantValue = stod(inp2);
                        constantVariable->value = constantValue;

                        nodes.push_back(&(*constantVariable));
                        vars.emplace(constantVariable->id, constantVariable);
                        type.emplace(constantVariable->id, VARIABLE);
                        id.emplace(inp2, constantVariable->id);
                    }

                    // process second input
                    Variable *input2;

                    unordered_map<string, int>::const_iterator idIte = id.find(inp2);
                    if (idIte == id.end()) {
                        haveCycle = true;
                        break;
                    } else {
                        int inp2ID = id.at(inp2);

                        if (type.at(inp2ID) == VARIABLE) {
                            input2 = vars.at(inp2ID);
                        } else {
                            input2 = fncs.at(inp2ID)->output;
                        }
                    }

                    if (function_name == "add") {
                        Addition *addition = new Addition(idCounter, s);
                        ++idCounter;

                        addition->addInput(input1);
                        addition->addInput(input2);
                        input1->addTo(addition);
                        input2->addTo(addition);

                        Variable *output = new Variable(idCounter, s + "out");
                        ++idCounter;
                        if (isCreatedBefore) {
                            output = vars.at(inputNamesSize);
                            --idCounter;
                        }

                        output->setFrom(addition);
                        addition->setOutput(output);

                        nodes.push_back(&(*addition));
                        id.emplace(addition->name, addition->id);
                        fncs.emplace(addition->id, addition);
                        type.emplace(addition->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);

                    } else if (function_name == "mult") {
                        Multiplication *multiplication = new Multiplication(idCounter, s);
                        ++idCounter;

                        multiplication->addInput(input1);
                        multiplication->addInput(input2);
                        input1->addTo(multiplication);
                        input2->addTo(multiplication);

                        Variable *output = new Variable(idCounter, s + "out");
                        ++idCounter;
                        if (isCreatedBefore) {
                            output = vars.at(inputNamesSize);
                            --idCounter;
                        }

                        output->setFrom(multiplication);
                        multiplication->setOutput(output);

                        nodes.push_back(&(*multiplication));
                        id.emplace(multiplication->name, multiplication->id);
                        fncs.emplace(multiplication->id, multiplication);
                        type.emplace(multiplication->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);

                    } else if (function_name == "subs") {
                        Subtraction *subtraction = new Subtraction(idCounter, s);
                        ++idCounter;

                        subtraction->addInput(input1);
                        subtraction->addInput(input2);
                        input1->addTo(subtraction);
                        input2->addTo(subtraction);

                        Variable *output = new Variable(idCounter, s + "out");
                        ++idCounter;
                        if (isCreatedBefore) {
                            output = vars.at(inputNamesSize);
                            --idCounter;
                        }

                        output->setFrom(subtraction);
                        subtraction->setOutput(output);

                        nodes.push_back(&(*subtraction));
                        id.emplace(subtraction->name, subtraction->id);
                        fncs.emplace(subtraction->id, subtraction);
                        type.emplace(subtraction->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);

                    } else if (function_name == "divide") {
                        Divide *divide = new Divide(idCounter, s);
                        ++idCounter;

                        divide->addInput(input1);
                        divide->addInput(input2);
                        input1->addTo(divide);
                        input2->addTo(divide);

                        Variable *output = new Variable(idCounter, s + "out");
                        ++idCounter;
                        if (isCreatedBefore) {
                            output = vars.at(inputNamesSize);
                            --idCounter;
                        }

                        output->setFrom(divide);
                        divide->setOutput(output);

                        nodes.push_back(&(*divide));
                        id.emplace(divide->name, divide->id);
                        fncs.emplace(divide->id, divide);
                        type.emplace(divide->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);

                    } else if (function_name == "pow") {
                        Power *power = new Power(idCounter, s);
                        ++idCounter;

                        power->addInput(input1);
                        power->addInput(input2);
                        input1->addTo(power);
                        input2->addTo(power);

                        Variable *output = new Variable(idCounter, s + "out");
                        ++idCounter;
                        if (isCreatedBefore) {
                            output = vars.at(inputNamesSize);
                            --idCounter;
                        }

                        output->setFrom(power);
                        power->setOutput(output);

                        nodes.push_back(&(*power));
                        id.emplace(power->name, power->id);
                        fncs.emplace(power->id, power);
                        type.emplace(power->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);
                    }
                }
            } else {
                // identity case
                cout << "identity" << endl;
                unordered_map<string, int>::const_iterator idIterator = id.find(function_name + "out");
                //unordered_map<string, int>::const_iterator idIterator2 = id.find(function_name);
                cout << "function_name: " << function_name << endl;
                if(idIterator == id.end()) {
                    cout << "HERE" << endl;
                    //haveCycle = true;
                    break;
                } else {
                    cout << "HERE-2" << endl;
                    int fncNameID = id.at(function_name + "out");

                    Variable *input = vars.at(fncNameID);

                    cout << "HERE-3" << endl;
                    unordered_map<string, int>::const_iterator outputIDIterator = id.find(s);
                    if(outputIDIterator == id.end()) {
                        Variable *output = new Variable(idCounter,s);
                        ++idCounter;

                        Identity *identity = new Identity(idCounter, "identity");
                        ++idCounter;

                        identity->addInput(input);
                        input->addTo(identity);

                        output->setFrom(identity);
                        identity->setOutput(output);

                        nodes.push_back(&(*identity));
                        id.emplace(identity->name, identity->id);
                        fncs.emplace(identity->id, identity);
                        type.emplace(identity->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);

                    } else {

                        int outputID = id.at(s);

                        Variable *output = vars.at(outputID);
                        Identity *identity = new Identity(idCounter, "identity");
                        ++idCounter;

                        identity->addInput(input);
                        input->addTo(identity);

                        output->setFrom(identity);
                        identity->setOutput(output);

                        nodes.push_back(&(*identity));
                        id.emplace(identity->name, identity->id);
                        fncs.emplace(identity->id, identity);
                        type.emplace(identity->id, FUNCTION);

                        nodes.push_back(&(*output));
                        id.emplace(output->name, output->id);
                        vars.emplace(output->id, output);
                        type.emplace(output->id, VARIABLE);
                    }
                }
            }


        }
    }

    for (int i = 0; i < nodes.size(); ++i) {
        Node *current = nodes.at(i);
        current->originalComing = current->numberOfComing;
        current->originalGoing = current->numberOfGoing;
        nodes[i] = current;
    }


    if (!haveCycle) {
        // handle first lines of output files!

        string outputName = vars.at(inputNamesSize)->name;
        output_values_file << outputName + '\n';
        for (int k = 0; k < inputNamesSize; ++k) {
            string inpName = vars.at(k)->name;
            string outName = "d" + outputName + "/d" + inpName;
            derivative_output_values_file << outName + " ";
        }

        // process of input values file
        for (int i = 0; i < inputNamesSize; ++i) {
            string inputName;
            input_values_file >> inputName;
        }

        string value;

        while (input_values_file >> value) {
            double valueDouble = stod(value);

            Variable *input = vars.at(0);
            input->value = valueDouble;

            for (int k = 1; k < inputNamesSize; ++k) {
                input_values_file >> value;
                valueDouble = stod(value);

                Variable *inp = vars.at(k);
                inp->value = valueDouble;
            }

            int currentID = -1;

            for (int i = 0; i < nodes.size(); ++i) {
                Node *current = nodes.at(i);
                if (!current->isVisited && current->numberOfComing == 0) {
                    currentID = current->id;
                    current->isVisited = true;
                    break;
                }
            }
            // start of forward pass
            while (currentID != -1) {

                unordered_map<int, TYPES>::const_iterator iterator = type.find(currentID);
                if (iterator != type.end()) {

                    if (iterator->second == VARIABLE) {
                        // Variable
                        unordered_map<int, Variable *>::const_iterator var_iterator = vars.find(currentID);
                        Variable *current = var_iterator->second;

                        for (int i = 0; i < current->to.size(); ++i) {
                            Function *function = current->to.at(i);
                            function->numberOfComing--;
                            current->to[i] = function;
                        }

                    } else {
                        // Function
                        unordered_map<int, Function *>::const_iterator fnc_iterator = fncs.find(currentID);
                        Function *current = fnc_iterator->second;

                        Variable *current_output = current->output;
                        current_output->numberOfComing--;
                        current->output = current_output;

                        current->doForward();
                    }
                }
                // find next node!
                for (int i = 0; i < nodes.size(); ++i) {
                    Node *current = nodes.at(i);
                    currentID = -1;
                    if (!current->isVisited && current->numberOfComing == 0) {
                        currentID = current->id;
                        current->isVisited = true;
                        nodes[i] = current;
                        break;
                    }
                }
            }
            // prepare for backward pass
            for (int i = 0; i < nodes.size(); ++i) {
                Node *current = nodes.at(i);
                current->isVisited = false;
                nodes[i] = current;
            }
            // find ouput and write its value
            Variable *outputVariable = vars.at(inputNamesSize);
            double outputValue = outputVariable->value;
            output_values_file << setprecision(16) << outputValue << '\n';
            outputVariable->derivative = 1;

            // start of backward pass
            int d_currentID = -1;
            for (int i = 0; i < nodes.size(); ++i) {
                Node *current = nodes.at(i);
                if (!current->isVisited && current->numberOfGoing == 0) {
                    d_currentID = current->id;
                    current->isVisited = true;
                    nodes[i] = current;
                    break;
                }
            }

            while (d_currentID != -1) {
                unordered_map<int, TYPES>::const_iterator iterator = type.find(d_currentID);

                if (iterator->second == VARIABLE) {
                    // Variable
                    unordered_map<int, Variable *>::const_iterator var_iterator = vars.find(d_currentID);
                    Variable *current = var_iterator->second;

                    if (current->to.size() == 0) {
                    } else {
                        for (int i = 0; i < current->to.size(); ++i) {
                            Function *current_to_function = current->to.at(i);

                            if (!current_to_function->isBackwardDone) {
                                current_to_function->doBackward();
                                current_to_function->isBackwardDone = true;
                            }
                        }
                    }

                    if (current->from != nullptr) {
                        current->from->numberOfGoing--;
                    }


                } else {
                    // Function
                    unordered_map<int, Function *>::const_iterator fnc_iterator = fncs.find(d_currentID);
                    Function *current = fnc_iterator->second;

                    for (int i = 0; i < current->inputs.size(); ++i) {
                        Variable *variable = current->inputs.at(i);
                        variable->numberOfGoing--;
                        current->inputs[i] = variable;
                    }

                }
                // find next node
                for (int i = 0; i < nodes.size(); ++i) {
                    Node *current = nodes.at(i);
                    d_currentID = -1;
                    if (!current->isVisited && current->numberOfGoing == 0) {
                        d_currentID = current->id;
                        current->isVisited = true;
                        nodes[i] = current;
                        break;
                    }
                }
            }

            // write derivative values to file
            derivative_output_values_file << '\n';
            for (int k = 0; k < inputNamesSize; ++k) {
                Variable *inp = vars.at(k);
                double inpDerivative = inp->derivative;
                derivative_output_values_file << setprecision(18) << inpDerivative;
                derivative_output_values_file << " ";
            }

            // reset graph!
            for (int i = 0; i < nodes.size(); ++i) {
                Node *current = nodes.at(i);
                current->isVisited = false;
                current->numberOfGoing = current->originalGoing;
                current->numberOfComing = current->originalComing;
                nodes[i] = current;

                int curID = current->id;
                if (type.at(curID) == FUNCTION) {
                    Function *curFunction = fncs.at(curID);
                    curFunction->isBackwardDone = false;
                    fncs[curID] = curFunction;
                } else {
                    Variable *curVariable = vars.at(curID);
                    curVariable->value = 0;
                    curVariable->derivative = 0;
                }
            }
        }
    } else {
        output_values_file << "ERROR: COMPUTATION GRAPH HAS CYCLE!";
        derivative_output_values_file << "ERROR: COMPUTATION GRAPH HAS CYCLE!";
    }

    function_define_file.close();
    input_values_file.close();
    output_values_file.close();
    derivative_output_values_file.close();
}