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
                if (idx > wireVector.size() || wireVector.at(idx) == nullptr) {
                    //Wire* newWire = new Wire(); //Why not just add directly at the end?
                    if (idx >= wireVector.size()) {
                        wireVector.resize(idx+1, nullptr);
                    }
                    wireVector.at(idx) = new Wire(0,s,idx);
                }
            }
            else {
                
                string GateT;
                line >> GateT;
                int gateType = hardCodeGateSolve(GateT);//Returns gate type as int
                
                string inDelay;
                int delay = 0;
                line >> delay;//This should automatically parse the delay
            
                //Convert string to unsigned int 
                // Remove the ns and store the int value in delay
                //delay= stoul(inDelay.substr(0, (inDelay.length() - 2)));

                line >> Num;

                int NUM[3]={0};

                for (int i=1; i<=3; i++){
                    NUM[i]=Num;
                    if (Num >= wireVector.size()){
                        wireVector.resize(Num+1, nullptr);
                    }
                    if (wireVector[Num] == nullptr){
                        Wire* newWire = new Wire();
                        wireVector[Num] = newWire;
                    }

                    if ((GateT=="NOT") && (i==2)) {
                        break;
                    }
                    line>>Num;
                }
                gateVector.push_back(new Gate(gateType, delay, ));
            }
        }

    }
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

int hardCodeGateSolve(string gateString) {
    if (gateString == "NOT") {
        return 0;
    }
    else {
        if (gateString == "AND") {
            return 1;
        }
        else{
            if (gateString == "OR") {
                return 2;
            }
            else {
                if (gateString == "XOR") {
                    return 3;
                }
                else {
                    if (gateString == "NAND") {
                        return 4;
                    }
                    else {
                        if (gateString == "NOR") {
                            return 5;
                        }
                        else {
                            if (gateString == "XNOR") {
                                return 6;
                            }
                            else {
                                return -1;
                            }
                        }
                    }
                }
            }
        }
    }
}

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

/*vector<Wire *> wires;
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
    }*/