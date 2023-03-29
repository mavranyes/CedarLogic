// Author: Micah Vranyes and Alben Augestine 
// Purpose: This is the implementation for the Gate class and the defintion and implemtation
// for the circuit class 
// Date: 12/08/2022

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <string>
#include <utility>

using namespace std;

#include "Gate.h"
#include "Wire.h"
#include "Event.h"
#define X 2

Gate::Gate(GateType type, int delay, Wire* in1, Wire* in2, Wire* outwire) {
    this->type = type;
    this->delay = delay;
    this->in1 = in1;
    this->in2 = in2;
    this->outwire = outwire;
}

//Evaluates the gate output with wire change
int Gate::evaluate(Wire* w, int val) {
    int a = X;
    int b = X;
    int out = X;
    if (w == in1) {
        a = val;
        if (in2 != nullptr) {
            b = in2->getValue();
        }
    }
    else if (w == in2) {
        b = val;
        if (in1 != nullptr) {
            a = in1->getValue();
        }
    }
    else {
        a = in1->getValue();
        if (in2 != nullptr) {
            b = in2->getValue();
        }
    }

    out = distribute(a, b);
    return out;
}

//Evaluates the gate output before the wire change
int Gate::evaluate() {
    int a = in1->getValue();
    int b = X;
    int out = X;
    if (in2 != nullptr) {
        b = in2->getValue();
    }
    out = distribute(a, b);
    return out;
}

//Distribute determines which gate type the wire values feed into
int Gate::distribute(int a, int b) {
    int out = -1;
    switch (type) {
    case AND:
        out = And(a, b);
        break;
    case NOT:
        out = Not(a);
        break;
    case OR:
        out = Or(a, b);
        break;
    case XNOR:
        out = Xnor(a, b);
        break;
    case XOR:
        out = Xor(a, b);
        break;
    case NAND:
        out = Nand(a, b);
        break;
    case NOR:
        out = Nor(a, b);
        break;
    }
    return out;
}

//The gates below complete the logical function of their coresponding names

int Gate::And(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    else if (a == X || b == X) {
        return X;
    }
    return 1;
}

int Gate::Or(int a, int b) {
    if (a == 1 || b == 1) {
        return 1;
    }
    else if (a == X || b == X) {
        return X;
    }
    return 0;
}

int Gate::Not(int a) {
    if (a == X) {
        return X;
    }
    else if (a == 0) {
        return 1;
    }
    return 0;
}

int Gate::Xor(int a, int b) {
    return Or(And(Not(a), b), And(a, Not(b)));
}

int Gate::Nand(int a, int b) {
    return Not(And(a, b));
}

int Gate::Xnor(int a, int b) {
    return Not(Xor(a, b));
}

int Gate::Nor(int a, int b) {
    return Not(Or(a, b));
}

int Gate::getDelay()const {
    return delay;
}

Wire* Gate::getInput(int num)const {
    if (num == 1) {
        return in1;
    }
    else {
        if (num == 2) {
            return in2;
        }
        else {
            return nullptr;
        }
    }
}

Wire* Gate::getOutput()const {
    return outwire;
}

void Gate::setInput(int idx, Wire* in) {
    if (idx == 1) {
        in1 = in;
    }
    else {
        in2 = in;
    }
}

void Gate::setOutput(Wire* out) {
    outwire = out;
}


class Circuit {

private:
    
    vector<Wire*> wireVector;
    priority_queue<Event> events;
    map<string, int> inputs;
    map<string, int> outputs;
    map<string, vector<pair<int, int>>> history;
    GateType gateSolve(string gateString);
    string circuitName;
    string vectorName;
    int endTime;
    int eventID;

public:

    Circuit(ifstream& cfin, ifstream& vfin) {

        string rawline;
        getline(cfin, rawline, '\n');
        circuitName = rawline.substr(rawline.find(" ") + 1);
        string cName = circuitName;
        eventID = 0;

        while (!cfin.eof()) {
            getline(cfin, rawline);
            istringstream line(rawline);
            string op;
            line >> op;
            if (op == "") {
                break;
            }
            //Creates wires
            if (op == "INPUT" || op == "OUTPUT") {

                string s;
                int idx;
                line >> s >> idx;
                history.insert({ s, {{0, X}} });
                if (op == "INPUT") {
                    inputs.insert(pair<string, int>(s, idx));
                }
                else {
                    outputs.insert(pair<string, int>(s, idx));
                }
                //Checks if the wire exits and/or the vector contains enough room for the wire
                if (idx >= wireVector.size() || wireVector.at(idx) == nullptr) {
                    if (idx >= wireVector.size()) {
                        wireVector.resize(idx + 1, nullptr);
                    }
                    wireVector.at(idx) = new Wire(X, s, idx);
                }
            }

            else {
                
                //Returns gate type as int
                GateType gateType = gateSolve(op);
                int delay = 0;

                //Convert string to unsigned int 
                // Remove the ns and store the int value in delay
                string ns;
                line >> delay >> ns;

                int idx;
                // Create new gate 
                Gate* g = new Gate(gateType, delay, nullptr, nullptr, nullptr);
                
                //Change size of vector if greater number of wires are created. 
                for (int i = 0; i < 3; i++) {
                    line >> idx;
                    if (idx >= wireVector.size() || wireVector.at(idx) == nullptr) {
                        if (idx >= wireVector.size()) {
                            wireVector.resize(idx + 1, nullptr);
                        }
                        wireVector[idx] = new Wire(X, "", idx);
                    }

                    //Connects the wires to the gate
                    if (i == 0) {
                        g->setInput(1, wireVector[idx]);
                        wireVector[idx]->addDrive(g);
                    }
                    else if (i == 1) {
                        if (gateType == NOT) {
                            g->setOutput(wireVector[idx]);
                            break;
                        }
                        else {
                            g->setInput(2, wireVector[idx]);
                            wireVector[idx]->addDrive(g);
                        }
                    }
                    else {
                        g->setOutput(wireVector[idx]);
                    }
                }
            }
        }

        //This is the parsing of the vector file
        getline(vfin, rawline, '\n');
        vectorName = rawline.substr(rawline.find(" ") + 1);

        while (!vfin.eof()) {
            //Read input 
            getline(vfin, rawline);
            istringstream line(rawline);
            string op, s;
            line >> op >> s;
            if (s == "") {
                break;
            }

            Wire* wire = wireVector[inputs[s]];
            int time = 0;
            char valChar = 'X';
            int val = 0;
            
            // Reads in char and checks and assigns the correct integer 
            // for the represented charcter
            line >> time >> valChar;
            if (valChar == 'X') {
                val = 2;
            }
            else if (valChar == '1') {
                val = 1;
            }
            else {
                val = 0;
            }
            Event e(wire, time, val, eventID++);
            events.push(e);
        }

    }

    // Pushes into pririty que and evlauvtes the logic 
    void simulate() {
        endTime = 0;
        while (!events.empty() && endTime < 60) {
            Event e = events.top();
            //Updates endTime which is used in print function
            if (e.time > endTime) {
                endTime = e.time;
            }

            //Adds an event to history used in print function
            string iopadName = e.wire->getName();
            if (iopadName != "") {
                history[iopadName].push_back({ e.time, e.value });
            }

            //Loops through for every gate driven by this wire
            for (Gate* g : e.wire->getDrives()) {

                int oldResult = g->evaluate();

                int result = g->evaluate(e.wire, e.value);
                //Compares previous circuit output to new circuit output
                if (result != oldResult) {
                    int newTime = e.time + g->getDelay();
                    Event nextE(g->getOutput(), newTime, result, eventID++);
                    events.push(nextE);
                }
            }
            //Updates wire value then deletes event
            e.wire->setValue(e.value);
            events.pop();
        }
    }

    void print() {
        for (auto iopad : history) { // iopad = {"A", vector of pairs}
            string iopadName = iopad.first;
            vector<pair<int, int>> iopadChanges = iopad.second;
            cout << iopadName << " ";
            //Loops through all wire histories
            for (int i = 0; i < iopadChanges.size(); ++i) {
                int changeTime = iopadChanges[i].first;
                int changeValue = iopadChanges[i].second;
                int diffTime;
                //Calculates diffTime depending on if it reaches the end
                if (i + 1 == iopadChanges.size()) {
                    diffTime = endTime - changeTime + 1;
                }
                else {
                    diffTime = iopadChanges[i + 1].first - changeTime;
                }
                //Translates int to char and outputs for diffTime
                char c;
                switch (changeValue) {
                case 0:
                    c = '_';
                    break;
                case 1:
                    c = '-';
                    break;
                case X:
                    c = 'X';
                    break;
                }
                string disp(diffTime, c);
                cout << disp;
            }
            cout << endl;
        }
    }
};

int main(int argc, char* argv[]) {

    cout << "Enter File: ";
    string baseFile;
    cin >> baseFile;
    //string baseFile = argv[1];
    string circuitFile = baseFile + ".txt";
    string vectorFile = baseFile + "_v.txt";
    ifstream cfin;
    ifstream vfin;
    cfin.open(circuitFile.c_str());
    vfin.open(vectorFile.c_str());
    // (1) Parse Gates and Wires
    // (2) Parse starting inputs
    Circuit c(cfin, vfin);
    // (3) Simulate
    c.simulate();
    // (4) Print out
    c.print();
}

map<string, GateType> gateTypes{
    {"NOT", NOT},
    {"AND", AND},
    {"OR", OR},
    {"XOR", XOR},
    {"NAND", NAND},
    {"NOR", NOR},
    {"XNOR", XNOR},
};

//Determines what enum the string coresponds to
GateType Circuit::gateSolve(string gateString) {
    return gateTypes[gateString];
}
