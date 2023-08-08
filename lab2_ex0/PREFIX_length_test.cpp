#include "PREFIX_length.h"
#include <string>
#include <iostream>
#include <assert.h>
#include <stdexcept>

using namespace std;

void tests() {
    Length länge_a(10, "m");
    Length länge_b(2000, "m");
    Length länge_c(6, "km");

    //test Addieren mit Konvertierung der Länge
    Length länge_output = länge_a + länge_c;
    assert(länge_output.get_value() == 6010);
    assert(länge_output.get_unit() == "m");

    //test Subtrahieren mit Konvertierung der Länge
    länge_output = länge_c - länge_b;
    assert(länge_output.get_value() == 4);
    assert(länge_output.get_unit() == "km");

    //test Skalieren von Länge
    länge_output = länge_a * 3;
    assert(länge_output.get_value() == 30);
    assert(länge_output.get_unit() == "m");

    //test Division von Länge
    länge_output = länge_b / 4;
    assert(länge_output.get_value() == 500);
    assert(länge_output.get_unit() == "m");

    //test vergleich
    assert(länge_a.compare(länge_b) == -1);
    assert(länge_b.compare(länge_c) == -1);
    assert(länge_c.compare(länge_a) == 1);
    assert(länge_a.compare(länge_a) == 0);

}

void verify_unit(string unit) {
    if (unit != "km" and unit != "m" and unit != "cm" and unit != "mm" and unit != "mile" and unit != "in" and
        unit != "ft")
        throw std::runtime_error("Ungultige Eingabe. Gib bitte km, m, cm, mm, mile, ft oder in ein");
}

void userdemo() {

    float l1_value;
    float l2_value;
    string l1_unit;
    string l2_unit;
    float numb;

    //INPUT, Eingabeüberprüfung fehlt

    cout << "\nGeben Sie den Wert der ersten Zahl ein:";
    cin >> l1_value;

    cout << "\nGeben Sie die Einheit der ersten Zahl ein:";
    cin >> l1_unit;
    verify_unit(l1_unit);

    cout << "\nGeben Sie den Wert der zweiten Zahl ein:";
    cin >> l2_value;

    cout << "\nGeben Sie die Einheit der zweiten Zahl ein:";
    cin >> l2_unit;
    verify_unit(l2_unit);

    cout << "\nGeben Sie ein Skalar ein:";
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