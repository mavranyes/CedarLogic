//Code by Micah Vranyes and Alben Augestine
#include <iostream>

using namespace std;

#include "Wire.h"
#include "Gate.h"

Wire::Wire(int inVal, string inName, int inIndex) {
    value = inVal;
    name = inName;
    index = inIndex;
}

void Wire::addDrive(Gate* drive) {  // BCS
    drives.push_back(drive);        // BCS
}                                   // BCS

void Wire::setValue(int val) {
    value = val;
}

void Wire::setHistory(vector<string> his) {
    for (vector<string>::iterator i = his.begin(); i != his.end(); ++i) {
        history.push_back(*i);
    }
}

void Wire::setDrives(vector<Gate *> drvs) {
    for (vector<Gate *>::iterator i = drvs.begin(); i != drvs.end(); ++i) {
        drives.push_back(*i);
    }
}

int Wire::getValue() const {
    return value;
}

vector<Gate *> Wire::getDrives() const {
    return drives;
}

int Wire::getIndex() const {
    return index;
}

vector<string> Wire::getHistory() const {
    return history;
}

string Wire::getName() const {
    return name;
}

void Wire::printHistory() { //Needs to be const
    for (vector<string>::iterator i = history.begin(); i != history.end(); ++i) {//Not able to convert from constant to non
        cout << *i << endl;
    }
}
