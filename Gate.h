using namespace std;

class Wire;

class Gate {
    private:
        Wire *in1, *in2;
        Wire *outwire;
};