//Code by Micah Vranyes and Alben Augestine
using namespace std;

class Wire;

struct Event {
    public:
        Wire* wire;
        int time;
        int value;
        Event (Wire* w, int t, int v) : wire(w), time(t), value(v) {}

        friend bool operator<(const Event &lhs, const Event &rhs) {
            return lhs.time > rhs.time;
        }
};
