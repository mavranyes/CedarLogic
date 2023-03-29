// Author: Micah Vranyes and Alben Augestine 
// Purpose: This is the idefintion for the wire class
// Date: 12/08/2022

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
        void addDrive(Gate* drive); 
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
