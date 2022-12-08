//Code by Micah Vranyes and Alben Augestine
using namespace std;

class Wire;

struct Event {
    public:
        Wire* wire;
        int time;
        int value;
        int id;
        Event (Wire* w, int t, int v, int i) : wire(w), time(t), value(v), id(i) {}

        friend bool operator<(const Event &lhs, const Event &rhs) {
            if (lhs.time == rhs.time) {
                return lhs.id > rhs.id;
            }
            return lhs.time > rhs.time;
        }
};
