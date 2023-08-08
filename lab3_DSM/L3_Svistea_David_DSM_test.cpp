//
// Created by Latitude on 05.04.2023.
//
#include "L3_Svistea_David_DSM.h"
#include <iostream>
#include <assert.h>

using namespace std;

void testall() {

    string elementnames[] = {"E1", "E2", "E3", "E4", "E5"};
    DSM dsm1(elementnames, 5);

    assert(dsm1.size() == 5);
    assert(dsm1.getName(2) == "E3");

    //wir verändern einen Namen
    dsm1.setElementName(2, "E3_changed");
    assert(dsm1.getName(2) == "E3_changed");

    //wir fügen einen neuen Link hinzu
    dsm1.addLink("E2", "E5", 3);
    assert(true == dsm1.hasLink("E2", "E5"));
    assert(dsm1.linkWeight("E2", "E5") == 3);

    dsm1.addLink("E1", "Extra1", 1);
    assert(dsm1.size() == 6);
    cout << "addlink mit einem Namen bestanden\n";
    dsm1.addLink("Extra2", "Extra3", 2);
    assert(dsm1.size() == 8);
    cout << "addlink mit zwei unbekannten Namen bestanden\n";

    dsm1.addLink("E2", "E4", 1);

    assert(dsm1.countToLinks("E2") == 2);
    assert(dsm1.countFromLinks("E4") == 1);
    assert(dsm1.countAllLinks() == 4);


    DSM dsm2 = DSM(dsm1);

    assert(dsm2.size() == 8);
    assert(dsm2.countToLinks("E2") == 2);
    assert(dsm2.countFromLinks("E4") == 1);
    assert(dsm2.countAllLinks() == 4);
    assert(dsm2.getName(2) == "E3_changed");
    cout << "Copyconstructor test bestanden\n";

    dsm1.deleteLink("E2", "E4");
    assert(dsm1.hasLink("E2", "E4") == false);
    cout << "deleteLink test bestanden \n";

    cout << "----------------------ALLE TESTS BESTANDEN--------------------------------\n\n";
}


int main() {
    testall();
    string elementnames[] = {"Motorrad", "Rad", "Motor", "Benzinkanister", "Reifen", "Zylinder", "Auspuff"};
    DSM motorrad(elementnames, 7);

    motorrad.addLink("Motorrad", "Rad", 2);
    motorrad.addLink("Motorrad", "Motor", 1);
    motorrad.addLink("Motorrad", "Benzinkanister", 1);
    motorrad.addLink("Rad", "Reifen", 1);
    motorrad.addLink("Motor", "Zylinder", 4);
    motorrad.addLink("Motorrad", "Auspuff", 1);

    motorrad.printMatrix();
    motorrad.printMatrixToFile("test.txt");

    system("pause");
    return 0;
}
