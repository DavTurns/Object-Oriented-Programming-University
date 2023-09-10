//
// Created by Latitude on 05.04.2023.
//
#include <exception>
#include "L3_Svistea_David_DSM.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

DSM::DSM(int capacity) {

    this->elementCount = 0;
    this->capacity = capacity;

    this->elementNames = new string[capacity];
    this->adjazenzMatrix = new int *[capacity];
}

DSM::DSM(string *elementNamesInput, int elementCount) {
    this->elementCount = elementCount;
    this->capacity = elementCount * 2 + 1;

    //create elementNames and copy all the element names from the parameter
    this->elementNames = new string[capacity];
    for (int i = 0; i < elementCount; i++) {
        elementNames[i] = elementNamesInput[i];
    }

    //create AdjazenzMatrix and set all links => 0
    this->adjazenzMatrix = new int *[capacity];
    for (int i = 0; i < elementCount; i++) {
        adjazenzMatrix[i] = new int[capacity];
        for (int j = 0; j < elementCount; j++) {
            adjazenzMatrix[i][j] = 0;
        }
    }
}

DSM::DSM(const DSM &other) {

    if (this == &other) {
        cout << "Object copies itself! Copy constructor aborted." << endl;
        return;
    }

    this->elementCount = other.elementCount;
    this->capacity = other.capacity;

    //allocate memory and copy all the elementNames
    this->elementNames = new string[capacity];
    for (int i = 0; i < this->elementCount; i++) {
        this->elementNames[i] = other.elementNames[i];
    }

    //create AdjazenzMatrix and copy all links from other.adjazenzmatrix
    this->adjazenzMatrix = new int *[capacity];
    for (int i = 0; i < elementCount; i++) {
        adjazenzMatrix[i] = new int[capacity];
        for (int j = 0; j < elementCount; j++) {
            adjazenzMatrix[i][j] = other.adjazenzMatrix[i][j];
        }
    }
}

DSM::~DSM() {
    delete[] this->elementNames;

    for (int i = 0; i < elementCount; i++) {
        delete[] this->adjazenzMatrix[i];
    }
    delete[] this->adjazenzMatrix;
}

int DSM::size() {
    return this->elementCount;
}

string DSM::getName(int index) {
    return this->elementNames[index];
}

void DSM::setElementName(int index, string elementName) {
    this->elementNames[index] = elementName;
}

int DSM::findIndex(string elementName) {
    //linear search of elementName in elementNames
    //returns index if found, else returns -1
    for (int i = 0; i < this->elementCount; i++) {
        if (this->elementNames[i] == elementName) {
            return i;
        }
    }
    return -1;
}

void DSM::doubleCapacity() {

    capacity = capacity * 2;

    //double capacity of this->elementNames
    string *temp = new string[capacity];
    for (int i = 0; i < this->elementCount; i++) {
        temp[i] = elementNames[i];
    }
    delete[] elementNames;
    elementNames = temp;

    //double capacity of this->adjazenzmatrix

    //double capacity of array with pointer
    int **temp2 = new int *[capacity];
    for (int i = 0; i < this->elementCount; i++) {
        temp2[i] = adjazenzMatrix[i];
    }

    delete[] adjazenzMatrix;
    adjazenzMatrix = temp2;

    //double capacity of array of each pointer in adjazenzmatrix
    for (int i = 0; i < this->elementCount; i++) {
        int *temp = new int[capacity];
        for (int j = 0; j < this->elementCount; j++) {
            temp[j] = adjazenzMatrix[i][j];
        }
        delete[] adjazenzMatrix[i];
        adjazenzMatrix[i] = temp;
    }
}

void DSM::addNewElement(string elementName) {

    if (capacity == elementCount)
        doubleCapacity();

    elementNames[elementCount] = elementName;


    //add new pointer to list
    adjazenzMatrix[elementCount] = new int[capacity];

    //set every value in new list to 0
    for (int i = 0; i < elementCount + 1; i++) {
        adjazenzMatrix[elementCount][i] = 0;
    }

    //add to the end of every already existing list 0
    for (int i = 0; i < elementCount; i++) {
        adjazenzMatrix[i][elementCount] = 0;
    }

    elementCount++;
}

void DSM::addLink(string fromElement, string toElement, int weight) {
    int index_fromElement = findIndex(fromElement);
    if (index_fromElement == -1) {
        addNewElement(fromElement);
        index_fromElement = findIndex(fromElement);
    }

    int index_toElement = findIndex(toElement);
    if (index_toElement == -1) {
        addNewElement(toElement);
        index_toElement = findIndex(toElement);
    }

    adjazenzMatrix[index_fromElement][index_toElement] = weight;

}

void DSM::deleteLink(string fromElement, string toElement) {
    adjazenzMatrix[findIndex(fromElement)][findIndex(toElement)] = 0;
}

bool DSM::hasLink(string fromElement, string toElement) {
    if (adjazenzMatrix[findIndex(fromElement)][findIndex(toElement)] != 0) {
        return true;
    }
    return false;
}

int DSM::linkWeight(string fromElement, string toElement) {
    return adjazenzMatrix[findIndex(fromElement)][findIndex(toElement)];
}

int DSM::countToLinks(string elementName) {
    int count = 0;
    for (int i = 0; i < elementCount; i++) {
        if (adjazenzMatrix[findIndex(elementName)][i] != 0) {
            count++;
        }
    }
    return count;
}

int DSM::countFromLinks(string elementName) {
    int count = 0;
    for (int i = 0; i < elementCount; i++) {
        if (adjazenzMatrix[i][findIndex(elementName)] != 0) {
            count++;
        }
    }
    return count;
}

int DSM::countAllLinks() {
    int count = 0;
    for (int i = 0; i < elementCount; i++) {
        for (int j = 0; j < elementCount; j++) {
            if (adjazenzMatrix[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

void DSM::printMatrix() {

    cout << "matrix is printed...\n";
    for (int i = 0; i < elementCount; i++) {
        for (int j = 0; j < elementCount; j++) {
            cout << adjazenzMatrix[i][j];
        }
        cout << "\n";
    }
}

void DSM::printMatrixToFile(string file_path) {
    ofstream file(file_path, ios::out);
    if (!file.is_open()) {
        cout << "Error - file not found";
        return;
    }

    for (int i = 0; i < elementCount; i++) {
        for (int j = 0; j < elementCount; j++) {
            if (adjazenzMatrix[i][j] != 0) {
                file << elementNames[i] << "," << adjazenzMatrix[i][j] << "," << elementNames[j] << "\n";
            }
        }
    }
    file.close();
}