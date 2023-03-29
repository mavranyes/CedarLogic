// Author: Micah Vranyes and Alben Augestine 
// Purpose: This is the definiton for the Gate class 
// Date: 12/08/2022


#include <string>

using namespace std;

enum GateType {NOT, AND, OR, XOR, NAND, NOR, XNOR};

class Wire;

class Gate {

    public:

        Gate (GateType type, int delay, Wire *in1, Wire *in2, Wire *outwire);
        int getDelay()const;
        void setInput(int idx, Wire* in);   
        void setOutput(Wire* out);          
        Wire* getInput(int num)const;
        Wire* getOutput()const;
        int evaluate(Wire*, int);//Runs gate logic
        int evaluate();//Runs gate logic
        int distribute(int a, int b);

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

