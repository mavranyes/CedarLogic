//Code by Micah Vranyes and Alben Augestine
using namespace std;

#include <iostream>
#include <vector>
#include "Gate.h"
#include "Wire.h"
#include <sstream>
#define X 2

Gate::Gate(GateType type, int delay, Wire *in1, Wire *in2, Wire *outwire) {

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

class EventCompare {
    bool operator() (const Event* lhs, const Event* rhs) {
        return (lhs->time < rhs->time);
    }
}

class Circuit {
    private:
    vector<Wire*> wireArray;
    priority_queue<Event*, vector<Event*>, EventCompare> events;
    map<char, int> inputs;
    map<char, int> outputs;
    public:
    Circuit(ifstream cfin, ifstream vfin) {
        string rawline;

        while (!cfin.eof()) {
            getline(cfin, line, '\n');
            stringstream line(rawline);
            string op;
            line >> op;
            if (op == "INPUT" || op == "OUTPUT") {
                char c;
                int idx;
                if (op == "INPUT") {
                    inputs.insert(make_pair(c, idx));
                } else {
                    outputs.insert(make_pair(c, idx));
                }
                if (idx > wireArray.size() || wireArray[idx] == nullptr) {
                    Wire* newWire = new Wire();
                    if (idx >= wireArray.size()) {
                        wireArray.resize(idx+1, nullptr);
                    }
                    wireArray[idx] = newWire;
                }
            } else {
                
            }
        }
    }

}
class Event{
    Wire* wire;
    int value;
    int time;
    void eval();
}

int main() {
    vector<Wire *> wires;
    vector<Gate *> gates;
    string inType;
    char* inDelay;
    string in1;
    string in2;
    string out;
    string name;
    string value;

    int i = 0;
    cin >> inType;
    while (!cin.eof()) {
        if (inType == "INPUT") {//Checks if wire
            cin >> name;
            cin >> value;
            createWire(name, stoi(value), wires);
        } 
        else {
            if (inType == "AND") {//Checks if it's a gate
                //Figure out which enum inType coresponds to
                cin >> inDelay; //Store delay
                int delay = 0;
                scanf(inDelay,"%f", &delay);
                cin >> in1;
                if (contains(in1, wires)) {//Check if the first input wire exits and create and connect one if it doesn't
                    Wire firstWire(0, in1, 0);
                    wires.push_back(firstWire);
                }
                else {//Connect one to the gate if it does exist

                }
                cin >> in2;
                if (contains(in2, wires)) {//Check if the second input wire exits and create and connect one if it doesn't

                }
                else {//Connect one to the gate if it does exist

                }
                cin >> out;
                if (contains(out, wires)) {//Check if the output wire exits and create and connect one if it doesn't

                }
                else {//Connect one to the gate if it does exist

                }
                gates.push_back(new Gate(stoi(inType), delay, ));//Creates the gate with all input information
                cout << "Gate " << i << ": " << inType << endl;
                i++;
            }
        }
    }
};


void createWire(string name, int value, vector<Wire *> wires) {
    if (wires.size() >= stoi(name)) {//Checks if vector long enough
        if (wires.at(stoi(name)) == nullptr) {
            wires.at(stoi(name)) == new Wire(value, name ,0);
        }
    }
    else {
        wires.resize(stoi(name));
        wires.at(stoi(name)) == new Wire(value, name ,0);
    }
}