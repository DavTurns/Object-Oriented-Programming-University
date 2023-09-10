#include "PREFIX_length.h"
#include <string>
#include <iostream>
#include <assert.h>
#include <stdexcept>

using namespace std;

void tests() {
    Length length_a(10, "m");
    Length length_b(2000, "m");
    Length length_c(6, "km");

    //test add with conversion
    Length length_output = length_a + length_c;
    assert(length_output.get_value() == 6010);
    assert(length_output.get_unit() == "m");

    //test subtract with conversion
    length_output = length_c - length_b;
    assert(length_output.get_value() == 4);
    assert(length_output.get_unit() == "km");

    //test scale
    length_output = length_a * 3;
    assert(length_output.get_value() == 30);
    assert(length_output.get_unit() == "m");

    //test division
    length_output = length_b / 4;
    assert(length_output.get_value() == 500);
    assert(length_output.get_unit() == "m");

    //test comparison
    assert(length_a.compare(length_b) == -1);
    assert(length_b.compare(length_c) == -1);
    assert(length_c.compare(length_a) == 1);
    assert(length_a.compare(length_a) == 0);
}

bool is_valid_unit(string unit) {
    if (unit != "km" and unit != "m" and unit != "cm" and unit != "mm" and unit != "mile" and unit != "in" and
        unit != "ft") {
        cout << "\nIncorrect input. Please enter km, m, cm, mm, mile, ft or in:";
        return false;
    }
    return true;
}

void userdemo() {

    float l1_value;
    float l2_value;
    string l1_unit;
    string l2_unit;
    float numb;

    cout << "\nEnter value of first length:";
    cin >> l1_value;

    cout << "\nEnter unit of first length:";
    input_first_unit:
    cin >> l1_unit;
    if(!is_valid_unit(l1_unit)) goto input_first_unit;

    cout << "\nEnter value of second length:";
    cin >> l2_value;

    cout << "\nEnter unit of second length:";
    input_second_unit:
    cin >> l2_unit;
    if(!is_valid_unit(l2_unit)) goto input_second_unit;

    cout << "\nEnter scalar:";
    cin >> numb;

    Length l1(l1_value, l1_unit);
    Length l2(l2_value, l2_unit);

    Length l3 = l1.add(l2);

    //"normal" methods
    /*
    cout <<"\n" << l1.text() << " + " << l2.text() << " = " << l3.text();

    l3 = l1.subtract(l2);
    cout <<"\n" << l1.text() << " - " << l2.text() << " = " << l3.text();

    l3 = l1.scale(numb);
    cout <<"\n" << l1.text() << " * " << numb << " = " << l3.text();

    l3 = l1.divide(numb);
    cout <<"\n" << l1.text() << " / " << numb << " = " << l3.text();
    */

    //infix methods
    l3 = l1 + l2;

    cout << "\n" << l1.text() << " + " << l2.text() << " = " << l3.text();

    l3 = l1 - l2;
    cout << "\n" << l1.text() << " - " << l2.text() << " = " << l3.text();

    l3 = l1 * numb;
    cout << "\n" << l1.text() << " * " << numb << " = " << l3.text();

    l3 = l1 / numb;
    cout << "\n" << l1.text() << " / " << numb << " = " << l3.text();

    switch (l1.compare(l2)) {
        case -1:
            cout << "\n" << l1.text() << " < " << l2.text();
            break;
        case 0:
            cout << "\n" << l1.text() << " = " << l2.text();
            break;
        case 1:
            cout << "\n" << l1.text() << " > " << l2.text();
            break;
    }
    l1.convert("km");
    cout << "\n" << l1.text();
    l1.convert("m");
    cout << "\n" << l1.text();
    l1.convert("cm");
    cout << "\n" << l1.text();
}

int main() {
    tests();
    userdemo();
    cout << "\n";
    system("pause");
    return 0;
}