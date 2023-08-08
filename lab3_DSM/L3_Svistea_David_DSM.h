//
// Created by Latitude on 05.04.2023.
//

#pragma once

#include <string>

using namespace std;

class DSM {

public:
    //Konstruktoren
    DSM(int);

    DSM(string[], int elementCount);

    //Kopierkonstruktor
    DSM(const DSM &other);

    //hilfsmethoden
    int findIndex(string elementName);

    void doubleCapacity();

    void addNewElement(string elementName);

    //methoden von Aufgaben

    int size();

    string getName(int index);

    void setElementName(int index, string elementName);

    void addLink(string fromElement, string toElement, int weight);

    void deleteLink(string fromElement, string toElement);

    bool hasLink(string fromElement, string toElement);

    int linkWeight(string fromElement, string toElement);

    int countToLinks(string elementName);

    int countFromLinks(string elementName);

    int countAllLinks();


    void printMatrix();

    void readMatrixFromFile(string);

    void printMatrixToFile(string);

    //Destruktor
    ~DSM();

private:
    int elementCount;
    int capacity;

    string *elementNames;
    int **adjazenzMatrix;
};


