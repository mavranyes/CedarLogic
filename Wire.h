using namespace std;

class Gate;

#include <string>

class Wire {
    public:
       string type; 
    private:

        vector<Gate *> drives;
};
