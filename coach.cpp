#include "Coach.h"
#include <stdexcept>

// Constructor to initialize a Coach object with name, specialty, and ID
// Throws an exception if specialty is empty or ID is negative
Coach::Coach(const std::string& name, const std::string& specialty, int id)
    : name(name), specialty(specialty), id(id) {
    if (specialty.empty()) {
        throw std::invalid_argument("Specialty cannot be empty");
    }
    if (id < 0) {
        throw std::invalid_argument("Coach ID cannot be negative");
    }
}

// Getter for the name of the coach
std::string Coach::getName() const {
    return name;
}

// Getter for the specialty of the coach
std::string Coach::getSpecialty() const {
    return specialty;
}

// Setter to update the specialty of the coach
void Coach::setSpecialty(const std::string& new_specialty) {
    specialty = new_specialty;
}

// Getter for the ID of the coach
int Coach::getId() const {
    return id;
}

// Equality operator to compare two coaches
bool Coach::operator==(const Coach& other) const {
    return name == other.name && specialty == other.specialty;
}
