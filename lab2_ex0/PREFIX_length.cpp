#include <string>
#include "PREFIX_length.h"
#include <cmath>
#include <utility>
#include <iostream>

using namespace std;

//Konstruktor
Length::Length(float value, std::string unit) :
        value(value),
        unit(unit),
        dict_with_units{{"km",   1000},
                        {"cm",   0.01},
                        {"mm",   0.001},
                        {"mile", 1609.344},
                        {"in",   0.0254},
                        {"ft",   0.3048},
                        {"m",    1}} {}

//getters:
float Length::get_value() {
    return this->value;
}

string Length::get_unit() {
    return this->unit;
}

void Length::convert(string in_which_unit) {
    // converts length in given unit as parameter

    float value_in_meters;

    //converts into meter;
    for (int i = 0; i < 7; i++) {
        if (this->dict_with_units[i].first == this->unit) {
            value_in_meters = this->value * this->dict_with_units[i].second;
            break;
        }
    }

    //converts from meter to new unit
    for (int i = 0; i < 7; i++) {
        if (this->dict_with_units[i].first == in_which_unit) {
            this->value = value_in_meters / this->dict_with_units[i].second;
            this->unit = in_which_unit;
            break;
        }
    }
}

Length Length::add(Length operand_2) {
    this->adjust(operand_2);
    Length returned_length(this->value + operand_2.value, this->unit);
    return returned_length;
}

Length Length::subtract(Length operand_2) {
    this->adjust(operand_2);
    Length returned_length(this->value - operand_2.value, this->unit);
    return returned_length;
}

Length Length::scale(float scalar) {
    Length returned_length(this->value * scalar, this->unit);
    return returned_length;
}

Length Length::divide(float divisor) {
    Length returned_length(this->value / divisor, this->unit);
    return returned_length;
}

string Length::text() {
    return to_string(this->value) + this->unit;
}

void Length::adjust(Length &l2) {
    //adjusts the unit of parameter object to calling object
    if (this->unit != l2.unit) l2.convert(this->unit);
}

int Length::compare(Length l2) {
    this->adjust(l2);
    if (fabs(this->value - l2.value) < 0.001f)
        return 0;
    if (this->value < l2.value)
        return -1;
    return 1;
}

//infix methods

Length Length::operator+(const Length &operand_2) {
    return add(operand_2);
}

Length Length::operator-(const Length &operand_2) {
    return subtract(operand_2);
}

Length Length::operator*(float scalar) {
    return scale(scalar);
}

Length Length::operator/(float divisor) {
    return divide(divisor);
}