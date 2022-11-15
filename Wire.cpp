using namespace std;

#include "Wire.h"
#include "Gate.h"

Wire::Wire(){

}

void Wire::setValue(int value) {

}

void Wire::setHistory(vector<string> history) {

}

void Wire::setDrives(vector<Gate *> drives) {

}

int Wire::getValue() const {
    return value;
}

vector Wire::getDrives() const {
    return drives;
}

int Wire::getIndex() const {
    return index;
}

vector Wire::getHistory() const {
    return history;
}

void Wire::printHistory() const {
    for (int i = 0; i < history.) {

    }
}