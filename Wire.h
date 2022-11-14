using namespace std;

class Gate;

#include <string>
#include <vector>

class Wire {
    public:
        int value;
        string name;
        vector<Gate *> drives;
        int index;
        vector<string> history;
        
        Wire::Wire();
        void setValue(int value);
        void setHistory(vector<string> history);
        void setDrives(vector<Gate *> drives);
        int getValue()const;
        int getName()const;
        vector getDrives()const;
        int getIndex()const;
        vector getHistory()const;
        void printHistory()const;

};
