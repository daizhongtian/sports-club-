#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include "Member.h"
#include "Coach.h"

class Team {
private:
    std::string sport_type;
    std::vector<Member*> members;
    Coach* coach;
    int id;

public:
   
    Team(const std::string& sportType, Coach* coach, int id);

    void addMember(Member* member);
    void removeMember(Member* member);
    void setCoach(Coach* coach);

    std::string getSportType() const;
    std::vector<Member*> getMembers() const;
    Coach* getCoach() const;
  
    void removeCoach();
    bool operator==(const Team& other) const;
    Team operator+(const Team& other) const;
    int getId() const;
    size_t getMemberCount() const;
};

#endif // TEAM_H
