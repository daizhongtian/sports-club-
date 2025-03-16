#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include <string>
#include "Member.h"
#include "Coach.h"
#include "Team.h"
#include "Event.h"

class Club {
private:
    std::string name;
    std::vector<Member*> members;
    std::vector<Coach*> coaches;
    std::vector<Team*> teams;
    std::vector<Event*> events;

public:
    explicit Club(const std::string& name);

    ~Club();

    void addMember(Member* member);
    void removeMember(Member* member);
    void addCoach(Coach* coach);
    void removeCoach(Coach* coach);
    void addTeam(Team* team);
    void removeTeam(Team* team);
    void organizeEvent(Event* event);
    void cancelEvent(Event* event);
    void addMembersToEvent(const std::string& eventName, const std::vector<Member*>& newMembers);
    void addTeamToEvent(const std::string& eventName, Team* team);  


    Member* findMemberByName(const std::string& name) const;
    std::vector<Member*> findMembersByRole(const std::string& role) const;
    Coach* findCoachByName(const std::string& name) const;
    void updateCoachSpecialty(const std::string& name, const std::string& new_specialty);
    bool hasScheduleConflict(const std::string& date) const;

    Member* findMemberById(int id) const;
    Coach* findCoachById(int id) const;
    void findPersonById(int id) const;

    std::string getClubInfo() const;
    std::vector<Member*> getMembers() const;
    std::vector<Coach*> getCoaches() const;
    std::vector<Team*> getTeams() const;
    std::vector<Event*> getEvents() const;
};

#endif // CLUB_H
