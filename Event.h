//Code by Micah Vranyes and Alben Augestine
using namespace std;

class Wire;

class Event {
    public:
        Event (Wire* wire, int time, int value);
        friend bool operator<(const Event &lhs, const Event &rhs) {
            return lhs.time < rhs.time;
        }
        Wire* getWire() {
            return this->wire;
        }
        int getTime() {
            return this->time;
        }
        int getValue() {
            this->value;
        }
        
    private:
        Wire* wire;
        int time;
        int value;
        void eval();
};
