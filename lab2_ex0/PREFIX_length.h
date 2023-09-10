#include <string>
#include <utility>
using namespace std;
class Length
{
private:
    /* data */
    float value;
    string unit;
    pair<string,float> dict_with_units[7];
public:

//constructor
Length(float, string);

//getters
float get_value();
string get_unit();


Length add(Length);
Length subtract(Length);

Length scale(float);
Length divide(float);

string text();

int compare(Length);
void adjust(Length&);

//infix methods
Length operator+(const Length&);
Length operator-(const Length&);
Length operator*(float);
Length operator/(float);

void convert(string);
};

