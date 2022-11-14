using namespace std;

class Gate;

#include <string>

class Wire {
    public:
       string name; 
    private:

        vector<Gate *> drives;
};
