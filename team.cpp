#include "Team.h"
#include <algorithm>

// Constructor to initialize a Team object with sport type, coach, and ID
// Throws an exception if sport type is empty, coach is null, or ID is negative
Team::Team(const std::string& sport_type, Coach* coach, int id)
    : sport_type(sport_type), coach(coach), id(id) {
    if (sport_type.empty()) {
        throw std::invalid_argument("Sport type cannot be empty");
    }
    if (coach == nullptr) {
        throw std::invalid_argument("Coach cannot be null");
    }
    if (id < 0) {
        throw std::invalid_argument("Team ID cannot be negative");
    }
}

// Method to add a member to the team
void Team::addMember(Member* member) {
    members.push_back(member);
}

// Method to remove a member from the team
void Team::removeMember(Member* member) {
    auto it = std::find(members.begin(), members.end(), member);
    if (it != members.end()) {
        members.erase(it);
    }
}

// Method to set the coach of the team
void Team::setCoach(Coach* coach) {
    this->coach = coach;
}

// Getter for the sport type of the team
std::string Team::getSportType() const {
    return sport_type;
}

// Getter for the members of the team
std::vector<Member*> Team::getMembers() const {
    return members;
}

// Getter for the coach of the team
Coach* Team::getCoach() const {
    return coach;
}

// Getter for the ID of the team
int Team::getId() const {
    return id;
}

// Method to remove the coach from the team
void Team::removeCoach() {
    coach = nullptr;
}

// Equality operator to compare two teams
bool Team::operator==(const Team& other) const {
    return sport_type == other.sport_type && coach == other.coach && members == other.members;
}

// Operator to combine two teams
Team Team::operator+(const Team& other) const {
    Team combined_team(sport_type, coach, id);
    combined_team.members = members;
    combined_team.members.insert(combined_team.members.end(), other.members.begin(), other.members.end());
    return combined_team;
}

// Method to get the count of members in the team
size_t Team::getMemberCount() const {
    return members.size();
}
