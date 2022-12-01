using namespace std;

#include "Wire.h"
#include "Gate.h"
#include <iostream>

Wire::Wire() {
    value = 0;
    name = "";
    index = 0;
}

void Wire::setValue(int val) {
    this->value = val;
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

void Wire::printHistory() {
    for (vector<string>::iterator i = history.begin(); i != history.end(); ++i) {
        cout << *i << endl;
    }
}