#include "Club.h"
#include <algorithm>
#include <iostream>

// Constructor to initialize the club with a given name
Club::Club(const std::string& name) : name(name) {}

// Destructor to clean up all dynamically allocated memory
Club::~Club() {
    // Delete all members
    for (auto member : members) {
        delete member;
    }
    members.clear();

    // Delete all coaches
    for (auto coach : coaches) {
        delete coach;
    }
    coaches.clear();

    // Delete all teams
    for (auto team : teams) {
        delete team;
    }
    teams.clear();

    // Delete all events
    for (auto event : events) {
        // delete event;              //controversial with test.cpp
    }
    events.clear();
}

// Add a member to the club
void Club::addMember(Member* member) {
    // Check if the member with the same ID already exists
    for (const auto& existing_member : members) {
        if (*existing_member == *member) {
            throw std::invalid_argument("Member with this ID already exists in the club");
        }
    }
    members.push_back(member);
}

// Remove a member from the club
void Club::removeMember(Member* member) {
    std::cout << "Attempting to remove member: " << member->getName() << std::endl;
    auto it = std::find(members.begin(), members.end(), member);
    if (it != members.end()) {
        // Remove the member from all teams
        std::cout << "Removing member from teams..." << std::endl;
        for (auto& team : teams) {
            team->removeMember(member);
        }

        // Remove the member from all events
        std::cout << "Removing member from events..." << std::endl;
        for (auto& event : events) {
            event->removeParticipant(member);
        }

        // Delete the member object and remove the pointer from the vector
        std::cout << "Deleting member object..." << std::endl;
        // delete* it;
        members.erase(it);

        std::cout << "Removed and deleted member: " << member->getName() << std::endl;
    }
    else {
        std::cout << "Member not found in club: " << member->getName() << std::endl;
    }
}

// Add a coach to the club
void Club::addCoach(Coach* coach) {
    // Check if the coach with the same ID already exists
    for (const auto& existing_coach : coaches) {
        if (*existing_coach == *coach) {
            throw std::invalid_argument("Coach with this ID already exists in the club");
        }
    }
    coaches.push_back(coach);
}

// Remove a coach from the club
void Club::removeCoach(Coach* coach) {
    auto it = std::find(coaches.begin(), coaches.end(), coach);
    if (it != coaches.end()) {
        // Delete the coach object and remove the pointer from the vector
        // delete* it;
        coaches.erase(it);
    }
}

// Add a team to the club
void Club::addTeam(Team* team) {
    teams.push_back(team);
}

// Remove a team from the club
void Club::removeTeam(Team* team) {
    auto it = std::find(teams.begin(), teams.end(), team);
    if (it != teams.end()) {
        // Remove the team from all events
        for (auto& event : events) {
            event->removeTeam(team);
        }

        // Delete the team object and remove the pointer from the vector
        delete* it;
        teams.erase(it);
    }
}

// Organize a new event in the club
void Club::organizeEvent(Event* event) {
    events.push_back(event);
}

// Cancel an event in the club
void Club::cancelEvent(Event* event) {
    auto it = std::find(events.begin(), events.end(), event);
    if (it != events.end()) {
        // Delete the event object and remove the pointer from the vector
        // delete* it;
        events.erase(it);
    }
}

// Add members to an event by event name
void Club::addMembersToEvent(const std::string& eventName, const std::vector<Member*>& newMembers) {
    for (auto& event : events) {
        if (event->getName() == eventName) {
            for (auto& member : newMembers) {
                event->addParticipant(member);
            }
        }
    }
}

// Add a team to an event by event name
void Club::addTeamToEvent(const std::string& eventName, Team* team) {
    for (auto& event : events) {
        if (event->getName() == eventName) {
            event->addTeam(team);
        }
    }
}

// Get the name of the club
std::string Club::getClubInfo() const {
    return name;
}

// Get the list of members in the club
std::vector<Member*> Club::getMembers() const {
    return members;
}

// Get the list of coaches in the club
std::vector<Coach*> Club::getCoaches() const {
    return coaches;
}

// Get the list of teams in the club
std::vector<Team*> Club::getTeams() const {
    return teams;
}

// Get the list of events in the club
std::vector<Event*> Club::getEvents() const {
    return events;
}

// Find a member by name
Member* Club::findMemberByName(const std::string& name) const {
    for (const auto& member : members) {
        if (member->getName() == name) {
            return member;
        }
    }
    return nullptr;
}

// Find members by role
std::vector<Member*> Club::findMembersByRole(const std::string& role) const {
    std::vector<Member*> result;
    for (const auto& member : members) {
        if (member->getRole() == role) {
            result.push_back(member);
        }
    }
    return result;
}

// Find a coach by name
Coach* Club::findCoachByName(const std::string& name) const {
    for (const auto& coach : coaches) {
        if (coach->getName() == name) {
            return coach;
        }
    }
    return nullptr;
}

// Find a member by ID
Member* Club::findMemberById(int id) const {
    for (const auto& member : members) {
        if (member->getId() == id) {
            return member;
        }
    }
    return nullptr;
}

// Find a coach by ID
Coach* Club::findCoachById(int id) const {
    for (const auto& coach : coaches) {
        if (coach->getId() == id) {
            return coach;
        }
    }
    return nullptr;
}

// Find a person (either member or coach) by ID and print their details
void Club::findPersonById(int id) const {
    Member* member = findMemberById(id);
    if (member != nullptr) {
        std::cout << "Member found: " << std::endl;
        std::cout << "Name: " << member->getName() << std::endl;
        std::cout << "Age: " << member->getAge() << std::endl;
        std::cout << "Role: " << member->getRole() << std::endl;
        std::cout << "ID: " << member->getId() << std::endl;
        return;
    }

    Coach* coach = findCoachById(id);
    if (coach != nullptr) {
        std::cout << "Coach found: " << std::endl;
        std::cout << "Name: " << coach->getName() << std::endl;
        std::cout << "Specialty: " << coach->getSpecialty() << std::endl;
        std::cout << "ID: " << coach->getId() << std::endl;
        return;
    }

    std::cout << "No person found with ID: " << id << std::endl;
}

// Update the specialty of a coach by name
void Club::updateCoachSpecialty(const std::string& name, const std::string& new_specialty) {
    auto coach = findCoachByName(name);
    if (coach) {
        coach->setSpecialty(new_specialty);
    }
}

// Check if there is a schedule conflict for a given date
bool Club::hasScheduleConflict(const std::string& date) const {
    for (const auto& event : events) {
        if (event->getDate() == date) {
            return true;
        }
    }
    return false;
}
