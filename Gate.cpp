//Code by Micah Vranyes and Alben Augestine
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include "Gate.h"
#include "Wire.h"
#include "Event.h"
#include <sstream>
#include <queue>
#include <map>
#include <string>
#define X 2

Gate::Gate(GateType type, int delay, Wire *in1, Wire *in2, Wire *outwire) {
    this->type = type;
    this->delay = delay;
    this->in1 = in1;
    this->in2 = in2;
    this->outwire = outwire;
}

void Gate::evaluate() {//This needs to be constant but it doesn't work if it is
    int a=in1->getValue();
    int b = -1;
    int out = -1;
    if (in2 != nullptr) {
        b=in2->getValue();
    }
    switch(type){
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
    outwire->setValue(out);
}

int Gate::And(int a, int b){
    if (a==0||b==0){
        return 0;
    }
    else if(a==X||b==X){
        return X;
    }
    return 1;
}

int Gate::Or(int a, int b){
    if (a==1||b==1){
        return 1;
    }
    else if(a==X||b==X){
        return X;
    }
    return 0;
}

int Gate::Not(int a){
    if(a==X){
        return X;
    }
    else if (a==0){
        return 1;
    }
    return 0;
}

int Gate::Xor(int a, int b) {
    return Or(And(Not(a), b), And(a, Not(b)));
}

int Gate::Nand(int a, int b){
    return Not(And(a, b));
}

int Gate::Xnor(int a, int b){
    return Not(Xor(a, b));
}

int Gate::Nor(int a, int b){
    return Not(Or(a, b));
}

/*
class EventCompare {
    bool operator() (const Event* lhs, const Event* rhs) {
        return (lhs->time < rhs->time);
    }
};*/

class Circuit {

    private:
    vector<Gate*> gateVector;
    vector<Wire*> wireVector;//Renamed wire vector instead of array because it's a vector
    priority_queue<Event> events;//Priority queue uses < operator in event.h
    map<string, int> inputs;//Using string to make code more general
    map<string, int> outputs;

    public:
    Circuit(ifstream &cfin, ifstream &vfin) {
        string rawline;
        int Num;

        while (!cfin.eof()) {

            getline(cfin, rawline);
            istringstream line(rawline);
            string op;
            line >> op;

            if (op == "INPUT" || op == "OUTPUT") {
                string s;
                int idx;
                if (op == "INPUT") {
                    inputs.insert(pair<string, int>(s, idx));//make_pair wasn't working so I formatted it differently 
                } else {
                    outputs.insert(pair<string, int>(s, idx));
                }
                if (idx >= wireVector.size() || wireVector.at(idx) == nullptr) {
                    //Wire* newWire = new Wire(); //Why not just add directly at the end?
                    if (idx >= wireVector.size()) {
                        wireVector.resize(idx+1, nullptr);
                    }
                    wireVector.at(idx) = new Wire(0,s,idx);
                }
            }
            else {
                //Pt. 1
                string GateT;
                line >> GateT;
                GateType gateType = hardCodeGateSolve(GateT);//Returns gate type as int
                //Pt. 2
                string inDelay;
                int delay = 0;
                line >> delay;//This should automatically parse the delay
            
                //Convert string to unsigned int 
                // Remove the ns and store the int value in delay
                //delay= stoul(inDelay.substr(0, (inDelay.length() - 2)));

                //Pt. 3-5
                int idx;
                Wire* wireArray[3] = {nullptr};
                for (int i = 0; i < 3; i++){
                    line >> idx;
                    if (idx >= wireVector.size() || wireVector.at(idx) == nullptr) {
                        if (idx >= wireVector.size()) {
                            wireVector.resize(idx+1, nullptr);
                        }
                        wireVector.at(idx) = new Wire(0,"",idx);
                        wireArray[i] = wireVector.at(idx);
                    }
                    if ((gateType == NOT) && (i == 2)) {
                        break;
                    }
                }

                //Takes all pieces and adds to vector here
                gateVector.push_back(new Gate(gateType, delay, wireArray[0], wireArray[1], wireArray[2]));
            }
        }

    }
    //Parsing vector file
    /*
    while (!vfin.eof()) {


    }*/
};

int main() {
    // (1) Parse Gates and Wires
    // (2) Parse starting inputs
    // (3) Simulate
    // (4) Print out
};

GateType hardCodeGateSolve(string gateString) {
    if (gateString == "NOT") {
        return NOT;
    }
    else {
        if (gateString == "AND") {
            return AND;
        }
        else{
            if (gateString == "OR") {
                return OR;
            }
            else {
                if (gateString == "XOR") {
                    return XOR;
                }
                else {
                    if (gateString == "NAND") {
                        return NAND;
                    }
                    else {
                        if (gateString == "NOR") {
                            return NOR;
                        }
                        else {
                            if (gateString == "XNOR") {
                                return XNOR;
                            }
                            else {
                                return AND;//This is dumb
                            }
                        }
                    }
                }
            }
        }
    }
}

/*void createWire(string name, int value, vector<Wire *> wires) {
    if (wires.size() >= stoi(name)) {//Checks if vector long enough
        if (wires.at(stoi(name)) == nullptr) {
            wires.at(stoi(name)) == new Wire(value, name ,0);
        }
    }
    else {
        wires.resize(stoi(name));
        wires.at(stoi(name)) == new Wire(value, name ,0);
    }
}*/
