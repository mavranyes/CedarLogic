//Code by Micah Vranyes and Alben Augestine
using namespace std;

#include <string>

class Wire;

class Gate {
    public:
        string type;
        int delay;
        Wire *in1, *in2;
        Wire *outwire;

        Gate::Gate (string type, int delay, Wire *in1, Wire in2, Wire outwire);
        int getDelay()const;
        Wire* getInput(int num)const;
        Wire* getOutput()const;
        string evaluate()const;//Runs gate logic



};