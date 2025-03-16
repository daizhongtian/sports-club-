#include "Event.h"
#include <algorithm>
#include "Team.h"

// Constructor to initialize an Event object with date, location, and name
// Throws an exception if any of the parameters are empty
Event::Event(const std::string& date, const std::string& location, const std::string& name)
    : date(date), location(location), name(name) {
    if (date.empty()) {
        throw std::invalid_argument("Date cannot be empty");
    }
    if (location.empty()) {
        throw std::invalid_argument("Location cannot be empty");
    }
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
}

// Getter for the event date
std::string Event::getDate() const {
    return date;
}

// Getter for the event location
std::string Event::getLocation() const {
    return location;
}

// Getter for the event name
std::string Event::getName() const {
    return name;
}

// Getter for the teams participating in the event
std::vector<Team*> Event::getTeams() const {
    return teams;
}

// Reschedule the event to a new date
void Event::reschedule(const std::string& new_date) {
    date = new_date;
}

// Add a participant to the event
// Throws an exception if the participant is null
void Event::addParticipant(Member* participant) {
    if (participant == nullptr) {
        throw std::invalid_argument("Participant cannot be null");
    }
    participants.push_back(participant);
}

// Getter for the participants of the event
std::vector<Member*> Event::getParticipants() const {
    return participants;
}

// Remove a participant from the event
void Event::removeParticipant(Member* member) {
    auto it = std::find(participants.begin(), participants.end(), member);
    if (it != participants.end()) {
        participants.erase(it);
    }
}

// Add a team to the event
// Throws an exception if the team pointer is null or the team ID is invalid
void Event::addTeam(Team* team) {
    if (team == nullptr) {
        throw std::invalid_argument("Team pointer is null");  // Check for null pointer
    }

    if (team->getId() <= 0) {
        throw std::invalid_argument("Team ID is invalid");  // Check for invalid ID
    }

    // Check if the team already exists in the event by team ID
    auto it = std::find_if(teams.begin(), teams.end(), [team](Team* t) {
        return t->getId() == team->getId();
        });
    if (it != teams.end()) {
        throw std::invalid_argument("Team with this ID is already added to the event");
    }

    teams.push_back(team);

    // Add all team members to the participants list
    for (auto member : team->getMembers()) {
        // Avoid duplicate participants
        if (std::find(participants.begin(), participants.end(), member) == participants.end()) {
            participants.push_back(member);
        }
    }
}

// Remove a team from the event
void Event::removeTeam(Team* team) {
    auto it = std::find(teams.begin(), teams.end(), team);
    if (it != teams.end()) {
        teams.erase(it);
    }
}

// Get the count of participants in the event
size_t Event::getParticipantCount() const {
    return participants.size();
}

// Equality operator to compare two events
bool Event::operator==(const Event& other) const {
    return date == other.date &&
        location == other.location &&
        name == other.name &&
        participants == other.participants;
}
