#ifndef COACH_H
#define COACH_H

#include <string>

class Coach {
private:
    std::string name;
    std::string specialty;
    int id;  

public:
    Coach(const std::string& name, const std::string& specialty, int id);

    std::string getName() const;
    std::string getSpecialty() const;
    void setSpecialty(const std::string& new_specialty);
    int getId() const;
    bool operator==(const Coach& other) const;
};

#endif // COACH_H
