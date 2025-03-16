#include "Member.h"
#include <iostream>
#include <stdexcept>

// Constructor to initialize a Member object with name, age, role, and ID
// Throws an exception if name is empty, age is negative, or ID is negative
Member::Member(const std::string& name, int age, const std::string& role, int id)
    : name(name), age(age), role(role), id(id) {
    if (name.empty()) {
        throw std::invalid_argument("Member name cannot be empty");
    }
    if (age < 0) {
        throw std::invalid_argument("Member age cannot be negative");
    }
    if (id < 0) {
        throw std::invalid_argument("Member ID cannot be negative");
    }
}

// Getter for the member's name
std::string Member::getName() const {
    return name;
}

// Getter for the member's age
int Member::getAge() const {
    return age;
}

// Getter for the member's role
std::string Member::getRole() const {
    return role;
}

// Method to update the member's details
// Throws an exception if new name is empty or new age is negative
void Member::updateDetails(const std::string& new_name, int new_age) {
    if (new_name.empty()) {
        std::cerr << "Error: Name cannot be empty" << std::endl;
        throw std::invalid_argument("Name cannot be empty");
    }

    if (new_age < 0) {
        std::cerr << "Error: Age cannot be negative" << std::endl;
        throw std::invalid_argument("Age cannot be negative");
    }

    name = new_name;
    age = new_age;
}

// Getter for the member's ID
int Member::getId() const {
    return id;
}

// Equality operator to compare two members
bool Member::operator==(const Member& other) const {
    return name == other.name && age == other.age && role == other.role;
}
