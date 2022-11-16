using namespace std;

#include "Gate.h"
#include "Wire.h"
#define X 2

Gate::Gate() {



}

void evaluate(){
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

int main() {


};