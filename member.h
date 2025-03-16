#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <stdexcept>

class Member {
private:
    std::string name;
    int age;
    std::string role;
    int id;  

public:
    Member(const std::string& name, int age, const std::string& role, int id);

    std::string getName() const;
    int getAge() const;
    std::string getRole() const;
    void updateDetails(const std::string& new_name, int new_age);
    int getId() const;  
    bool operator==(const Member& other) const;
};

#endif // MEMBER_H
