//Code by Micah Vranyes and Alben Augestine

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <string>

using namespace std;

#include "Gate.h"
#include "Wire.h"
#include "Event.h"
#define X 2

Gate::Gate(GateType type, int delay, Wire *in1, Wire *in2, Wire *outwire) {
    this->type = type;
    this->delay = delay;
    this->in1 = in1;
    this->in2 = in2;
    this->outwire = outwire;
}

int Gate::evaluate() {//This needs to be constant but it doesn't work if it is
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
    return out;
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

class Circuit {
    private:
    //vector<Gate*> gateVector;
    vector<Wire*> wireVector;//Renamed wire vector instead of array because it's a vector
    priority_queue<Event> events;//Priority queue uses < operator in event.h
    map<string, int> inputs;//Using string to make code more general
    map<string, int> outputs;
    map<string, vector<pair<int,int>>> history;
    GateType gateSolve(string gateString);
    string circuitName;
    string vectorName;

    public:
    Circuit(ifstream &cfin, ifstream &vfin) {
        string rawline;
        int Num;
        getline(cfin, rawline, '\n');
        circuitName = rawline.substr(rawline.find(" ")+1);
        while (!cfin.eof()) {

            getline(cfin, rawline);
            istringstream line(rawline);
            string op;
            line >> op;

            if (op == "INPUT" || op == "OUTPUT") {
                string s;
                int idx;
                line >> s >> idx;
                if (op == "INPUT") {
                    inputs.insert(pair<string, int>(s, idx));
                } else {
                    outputs.insert(pair<string, int>(s, idx));
                }
                if (idx >= wireVector.size() || wireVector.at(idx) == nullptr) {
                    if (idx >= wireVector.size()) {
                        wireVector.resize(idx+1, nullptr);
                    }
                    wireVector.at(idx) = new Wire(0,s,idx);
                }
            }
            else {
                //Pt. 1
                GateType gateType = gateSolve(op);//Returns gate type as int
                //Pt. 2
                string inDelay;
                line >> inDelay;//This should automatically parse the delay
                int delay = 0;

                //Convert string to unsigned int 
                // Remove the ns and store the int value in delay
                delay = stoi(inDelay.substr(0, (inDelay.length() - 2)));

                //Pt. 3-5
                int idx;
                //Wire* wireArray[3] = {nullptr};
                for (int i = 0; i < 3; i++){
                    line >> idx;
                    if (idx >= wireVector.size() || wireVector.at(idx) == nullptr) {
                        if (idx >= wireVector.size()) {
                            wireVector.resize(idx+1, nullptr);
                        }
                        wireVector.at(idx) = new Wire(0,"",idx);
                        //wireArray[i] = wireVector.at(idx);
                    }
                    if ((gateType == NOT) && (i == 1)) {
                        break;
                    }
                }

                //Takes all pieces and adds to vector here
                //gateVector.push_back(new Gate(gateType, delay, wireArray[0], wireArray[1], wireArray[2]));
            }
        }

        //Parsing vector file
        getline(vfin, rawline, '\n');
        vectorName = rawline.substr(rawline.find(" ")+1);
        while (!vfin.eof()) {
            getline(vfin, rawline);
            istringstream line(rawline);
            string op, s;
            line >> op >> s;

            Wire* wire = inputs[s];
            int time = 0;
            int val = 0;

            line >> time >> val;
            Event e(wire, time, val);
            events.push(e);
        }
    }

    void simulate() {
        while(!events.empty()){
            Event e = events.top();
            events.pop();
            e.wire->setValue(e.value);

            for (Gate* g : e.wire->getDrives()) {
                int result= g->evaluate();
                Wire* out= g->getOutput();
                int newTime = e.time + g->getDelay();
                Event e(g->getOutput(), newTime, e.value);
                events.push(e);
            }
        }
    }

    void print() {
        string wireName;
        vector<pair<int,int>> timeValues;
        int i = 0;
        int time = 0;
        while (i < time) {
            time = 0;
            history.insert(wireName, timeValues);//It doesn't like the data format
        }
    }
};

int main() {
    // (1) Parse Gates and Wires
    // (2) Parse starting inputs
    // (3) Simulate
    // (4) Print out
};

GateType Circuit::gateSolve(string gateString) {//Determines what enum the string coresponds to
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
                        }
                    }
                }
            }
        }
    }
}