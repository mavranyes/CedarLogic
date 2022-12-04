//Code by Micah Vranyes and Alben Augestine
using namespace std;

#include <string>

enum GateType {NOT, AND, OR, XOR, NAND, NOR, XNOR};

class Wire;

class Gate {
    public:
        Gate (GateType type, int delay, Wire *in1, Wire *in2, Wire *outwire);
        int getDelay()const;
        Wire* getInput(int num)const;
        Wire* getOutput()const;
        int evaluate();//Runs gate logic
    private:
        int And(int, int);
        int Or(int, int);
        int Not(int);
        int Xor(int, int);
        int Nand(int, int);
        int Xnor(int, int);
        int Nor(int, int);

        GateType type;
        int delay;
        Wire *in1, *in2;
        Wire *outwire;
};

