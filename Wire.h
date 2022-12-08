//Code by Micah Vranyes and Alben Augestine
class Gate;

#include <string>
#include <vector>

using namespace std;


class Wire {
    public:
        Wire(int value, string name, int index);
        void setValue(int val);
        void setHistory(vector<string> his);
        void setDrives(vector<Gate *> drivs);
        void addDrive(Gate* drive); // BCS
        int getValue()const;
        string getName()const;
        vector<Gate *> getDrives()const;
        int getIndex()const;
        vector<string> getHistory()const;
        void printHistory();

    private:
        int value;
        string name;
        vector<Gate *> drives;
        int index;
        vector<string> history;

};
