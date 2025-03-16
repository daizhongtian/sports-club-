#include <cassert>
#include <iostream>
#include "Member.h"
#include "Coach.h"
#include "Team.h"
#include "Event.h"
#include "Club.h"

// Test functions for Member class
void testMember() {
    try {
        Member* m1 = new Member("John", 30, "Athlete", 1);

        // Verify Member creation and getters
        assert(m1->getName() == "John");
        assert(m1->getAge() == 30);
        assert(m1->getRole() == "Athlete");
        assert(m1->getId() == 1);

        // Test updating member details
        m1->updateDetails("John D.", 31);
        assert(m1->getName() == "John D." && m1->getAge() == 31);

        // Test invalid name update
        try {
            m1->updateDetails("", 31);
            std::cerr << "testMember failed: no exception on empty name" << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for empty name: " << e.what() << std::endl;
        }

        // Test invalid age update
        try {
            m1->updateDetails("John D.", -5);
            std::cerr << "testMember failed: no exception on negative age" << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for negative age: " << e.what() << std::endl;
        }

        // Test invalid ID
        try {
            Member* m2 = new Member("Jane", 25, "Athlete", -1);
            std::cerr << "testMember failed: no exception on negative ID" << std::endl;
            delete m2;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for negative ID: " << e.what() << std::endl;
        }

        std::cout << "testMember passed" << std::endl;
        delete m1;
    }
    catch (const std::exception& e) {
        std::cerr << "testMember failed: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "testMember failed: unknown exception" << std::endl;
    }
}

// Test functions for Coach class
void testCoach() {
    try {
        // Correct Creation Test
        Coach* c1 = new Coach("Jane", "Football", 1);
        assert(c1->getName() == "Jane");
        assert(c1->getSpecialty() == "Football");
        assert(c1->getId() == 1);

        // Specialty Assignment Test (Correct)
        c1->setSpecialty("Basketball");
        assert(c1->getSpecialty() == "Basketball");

        // Specialty Assignment Test (Incorrect)
        try {
            Coach* c2 = new Coach("John", "", 2);
            std::cerr << "testCoach failed: no exception on empty specialty" << std::endl;
            delete c2;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for empty specialty: " << e.what() << std::endl;
        }

        // Test negative ID
        try {
            Coach* c3 = new Coach("John", "Football", -1);
            std::cerr << "testCoach failed: no exception on negative ID" << std::endl;
            delete c3;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for negative ID: " << e.what() << std::endl;
        }

        std::cout << "testCoach passed" << std::endl;
        delete c1;
    }
    catch (...) {
        std::cout << "testCoach failed" << std::endl;
    }
}

// Test functions for Team class
void testTeam() {
    // Adding Member Test (Correct)
    try {
        Coach* coach = new Coach("Jane", "Football", 1);
        Team team("Football", coach, 1);

        Member* member1 = new Member("John", 30, "Athlete", 1);
        team.addMember(member1);

        assert(team.getMembers().size() == 1);
        assert(team.getId() == 1);
        std::cout << "testAddingMember passed" << std::endl;

        delete member1;
        delete coach;
    }
    catch (...) {
        std::cout << "testAddingMember failed" << std::endl;
    }

    // Removing Member Test (Correct)
    try {
        Coach* coach = new Coach("Jane", "Football", 1);
        Team team("Football", coach, 1);

        Member* member1 = new Member("John", 30, "Athlete", 1);
        team.addMember(member1);
        assert(team.getMembers().size() == 1);

        team.removeMember(member1);
        assert(team.getMembers().size() == 0);
        std::cout << "testRemovingMember passed" << std::endl;

        delete member1;
        delete coach;
    }
    catch (...) {
        std::cout << "testRemovingMember failed" << std::endl;
    }

    // Removing Non-Existent Member Test (Incorrect)
    try {
        Coach* coach = new Coach("Jane", "Football", 1);
        Team team("Football", coach, 1);

        Member* member1 = new Member("John", 30, "Athlete", 1);
        Member* member2 = new Member("Jane", 25, "Athlete", 2);

        team.addMember(member1);
        assert(team.getMembers().size() == 1);

        team.removeMember(member2); // member2 was never added
        assert(team.getMembers().size() == 1); // Size should remain unchanged
        std::cout << "testRemovingNonExistentMember passed" << std::endl;

        delete member1;
        delete member2;
        delete coach;
    }
    catch (...) {
        std::cout << "testRemovingNonExistentMember failed" << std::endl;
    }

    // Test negative ID
    try {
        Coach* coach = new Coach("Jane", "Football", 1);
        Team* team = new Team("Football", coach, -1);
        std::cerr << "testTeam failed: no exception on negative ID" << std::endl;
        delete team;
        delete coach;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught expected exception for negative ID: " << e.what() << std::endl;
    }
}

// Test functions for Event class
void testEvent() {
    bool allTestsPassed = true;

    // Event Creation Test (Correct)
    try {
        Event event("2024-05-01", "Stadium", "Football Match");
        assert(event.getDate() == "2024-05-01");
        assert(event.getLocation() == "Stadium");
        assert(event.getName() == "Football Match");
    }
    catch (...) {
        std::cout << "Event Creation Test failed" << std::endl;
        allTestsPassed = false;
    }

    // Reschedule Test (Correct)
    try {
        Event event("2024-05-01", "Stadium", "Football Match");
        event.reschedule("2024-06-01");
        assert(event.getDate() == "2024-06-01");
    }
    catch (...) {
        std::cout << "Reschedule Test failed" << std::endl;
        allTestsPassed = false;
    }

    // Add Participant Test (Correct)
    try {
        Event event("2024-05-01", "Stadium", "Football Match");
        Member* member1 = new Member("John", 30, "Athlete", 1);
        event.addParticipant(member1);
        assert(event.getParticipantCount() == 1);
        delete member1;
    }
    catch (...) {
        std::cout << "Add Participant Test failed" << std::endl;
        allTestsPassed = false;
    }

    // Add Invalid Participant Test (Incorrect)
    try {
        Event event("2024-05-01", "Stadium", "Football Match");
        try {
            event.addParticipant(nullptr); // This should fail or be handled appropriately
            std::cerr << "Add Invalid Participant Test failed: no exception on invalid participant" << std::endl;
            allTestsPassed = false;
        }
        catch (const std::invalid_argument& e) {
            // Expected exception, do nothing
        }
        assert(event.getParticipantCount() == 0);
    }
    catch (...) {
        std::cout << "Add Invalid Participant Test failed" << std::endl;
        allTestsPassed = false;
    }

    if (allTestsPassed) {
        std::cout << "testEvent passed" << std::endl;
    }
    else {
        std::cout << "testEvent failed" << std::endl;
    }
}

void testClub() {
    try {
      
        std::cout << "Starting testClub" << std::endl;
        // Create a Club object named "Sports Club"
        Club club("Sports Club");

        // Create members
        std::cout << "Creating members" << std::endl;
        // Create two Member objects m1 and m2
        Member* m1 = new Member("John", 30, "Athlete", 1);
        Member* m2 = new Member("Jane", 25, "Athlete", 2);

        // Add members to the club
        std::cout << "Adding members" << std::endl;
        club.addMember(m1);
        club.addMember(m2);
        std::cout << "Added members" << std::endl;

        // Update details of member m1
        std::cout << "Updating member details" << std::endl;
        m1->updateDetails("John D.", 31);
        std::cout << "Updated member details" << std::endl;

        // Remove member m1 from the club
        std::cout << "Removing member" << std::endl;
        club.removeMember(m1);
        std::cout << "Removed member" << std::endl;
        // Delete member object m1 and set pointer to nullptr
        delete m1;
        m1 = nullptr;

        // Create and add coach c1 to the club
        std::cout << "Creating and adding coach" << std::endl;
        Coach* c1 = new Coach("Jane", "Football", 1);
        club.addCoach(c1);
        std::cout << "Added coach" << std::endl;

        // Remove coach c1 from the club
        std::cout << "Removing coach" << std::endl;
        club.removeCoach(c1);
        std::cout << "Removed coach" << std::endl;
        // Delete coach object c1 and set pointer to nullptr
        delete c1;
        c1 = nullptr;

        // Organize an event e1
        std::cout << "Organizing event" << std::endl;
        Event* e1 = new Event("2024-04-19", "Stadium", "Football Match");
        club.organizeEvent(e1);
        std::cout << "Organized event" << std::endl;

        // Cancel event e1
        std::cout << "Cancelling event" << std::endl;
        club.cancelEvent(e1);
        std::cout << "Cancelled event" << std::endl;
        // Delete event object e1 and set pointer to nullptr
        delete e1;
        e1 = nullptr;

        // Add member to event
        std::cout << "Adding member to event" << std::endl;
        e1 = new Event("2024-04-19", "Stadium", "Football Match");
        club.organizeEvent(e1);
        club.addMember(m2);
        std::vector<Member*> members = { m2 };
        club.addMembersToEvent("Football Match", members);
        std::cout << "Added members to event" << std::endl;
        // Verify the number of participants in the event is 1
        assert(club.getEvents().front()->getParticipants().size() == 1);

        // Create and add coach c2 to the club
        Coach* c2 = new Coach("Jane", "Football", 1);
        club.addCoach(c2);
        // Check if coach c2 exists
        Coach* foundCoach = club.findCoachByName("Jane");
        assert(foundCoach != nullptr);
        // Update the specialty of coach c2
        club.updateCoachSpecialty("Jane", "Basketball");

        // Test duplicate member ID exception
        try {
            Member* m3 = new Member("Jane", 25, "Athlete", 2);
            club.addMember(m3);
            std::cerr << "testDuplicateMember failed: no exception on duplicate member ID" << std::endl;
            delete m3;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for duplicate member ID: " << e.what() << std::endl;
        }

        // Test duplicate coach ID exception
        try {
            Coach* c3 = new Coach("Jane", "Football", 1);
            club.addCoach(c3);
            std::cerr << "testDuplicateCoach failed: no exception on duplicate coach ID" << std::endl;
            delete c3;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Caught expected exception for duplicate coach ID: " << e.what() << std::endl;
        }

        // Create and add team t1 to the club
        Team* t1 = new Team("Football", foundCoach, 1);
        club.addTeam(t1);
        // Verify the number of teams in the club is 1
        assert(club.getTeams().size() == 1);

        std::cout << "testClub passed" << std::endl;

        // Delete remaining objects
        delete m2;
        delete c2;
        delete t1;
    }
    catch (const std::exception& e) {
        std::cerr << "testClub failed: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "testClub failed: unknown exception" << std::endl;
    }
}


// Test deleting a club and all associated objects
void testDeleteClub() {
    try {
        std::cout << "Starting testDeleteClub" << std::endl;
        Club* myClub = new Club("Sports Club");

        std::cout << "Adding members and coaches" << std::endl;
        Member* m1 = new Member("John", 30, "Athlete", 1);
        Member* m2 = new Member("Jane", 25, "Athlete", 2);
        myClub->addMember(m1);
        myClub->addMember(m2);

        Coach* c1 = new Coach("Coach A", "Football", 1);
        myClub->addCoach(c1);

        std::cout << "Organizing event" << std::endl;
        Event* e1 = new Event("2024-04-19", "Stadium", "Football Match");
        myClub->organizeEvent(e1);

        std::cout << "Adding team" << std::endl;
        Team* t1 = new Team("Football", c1, 1);
        t1->addMember(m1);
        t1->addMember(m2);
        myClub->addTeam(t1);

        // Deleting club and all associated objects
        std::cout << "Deleting club" << std::endl;
        delete myClub;
        std::cout << "testDeleteClub passed" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "testDeleteClub failed: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "testDeleteClub failed: unknown exception" << std::endl;
    }
}

// Test scheduling conflict for events
void testEventScheduleConflict() {
    try {
        Club club("Sports Club");

        Event* e1 = new Event("2024-04-19", "Stadium", "Football Match");
        Event* e2 = new Event("2024-04-20", "Gym", "Basketball Match");

        club.organizeEvent(e1);

        assert(club.hasScheduleConflict("2024-04-19"));
        assert(!club.hasScheduleConflict("2024-04-20"));

        std::cout << "testEventScheduleConflict passed" << std::endl;

        delete e1;
        delete e2;
    }
    catch (...) {
        std::cout << "testEventScheduleConflict failed" << std::endl;
    }
}

// Test removing a member and its effect on associated teams and events
void testRemoveMember() {
    std::cout << "Starting testRemoveMember" << std::endl;
    Club myClub("Sports Club");

    Member* m1 = new Member("John", 30, "Athlete", 1);
    Member* m2 = new Member("Jane", 25, "Athlete", 2);
    myClub.addMember(m1);
    myClub.addMember(m2);

    Coach* c1 = new Coach("Coach A", "Football", 1);
    myClub.addCoach(c1);

    Event* e1 = new Event("2024-04-19", "Stadium", "Football Match");
    myClub.organizeEvent(e1);
    myClub.addMembersToEvent("Football Match", { m1, m2 });

    Team* t1 = new Team("Football", c1, 1);
    t1->addMember(m1);
    t1->addMember(m2);
    myClub.addTeam(t1);

    std::cout << "Finding person with ID 1 before deletion:" << std::endl;
    myClub.findPersonById(1);

    std::cout << "Removing member with ID 1:" << std::endl;
    myClub.removeMember(m1);

    std::cout << "Finding person with ID 1 after deletion:" << std::endl;
    myClub.findPersonById(1);

    // Check if the member is removed from the team
    if (t1->getMembers().size() == 1 && t1->getMembers()[0]->getId() == 2) {
        std::cout << "Member successfully removed from team." << std::endl;
    }
    else {
        std::cerr << "Failed to remove member from team." << std::endl;
    }

    // Check if the member is removed from the event
    if (e1->getParticipants().size() == 1 && e1->getParticipants()[0]->getId() == 2) {
        std::cout << "Member successfully removed from event." << std::endl;
    }
    else {
        std::cerr << "Failed to remove member from event." << std::endl;
    }

    std::cout << "testRemoveMember completed" << std::endl;
}

// Test removing a coach and its effect on associated teams
void testRemoveCoach() {
    std::cout << "Starting testRemoveCoach" << std::endl;
    Club myClub("Sports Club");

    Member* m1 = new Member("John", 30, "Athlete", 1);
    Member* m2 = new Member("Jane", 25, "Athlete", 2);
    myClub.addMember(m1);
    myClub.addMember(m2);

    Coach* c1 = new Coach("Coach A", "Football", 1);
    myClub.addCoach(c1);

    Event* e1 = new Event("2024-04-19", "Stadium", "Football Match");
    myClub.organizeEvent(e1);
    myClub.addMembersToEvent("Football Match", { m1, m2 });

    Team* t1 = new Team("Football", c1, 1);
    t1->addMember(m1);
    t1->addMember(m2);
    myClub.addTeam(t1);

    std::cout << "Finding person with ID 1 (Coach) before deletion:" << std::endl;
    myClub.findPersonById(1);

    std::cout << "Removing coach with ID 1:" << std::endl;
    myClub.removeCoach(c1);

    std::cout << "Finding person with ID 1 (Coach) after deletion:" << std::endl;
    myClub.findPersonById(1);

    // Check if the team still exists but without a coach
    if (t1->getCoach() == nullptr) {
        std::cout << "Coach successfully removed from team, team still exists." << std::endl;
    }
    else {
        std::cerr << "Failed to remove coach from team." << std::endl;
    }

    std::cout << "testRemoveCoach completed" << std::endl;
}





void printDivider(const std::string& title) {
    std::cout << "\n-----------------------------------\n";
    std::cout << title << '\n';
    std::cout << "-----------------------------------\n";
}

void testClubFunctionality() {
    printDivider("Creating Club: Elite Sports Club");
    Club club("Elite Sports Club");

    printDivider("Adding Members: Jack, Kelly and Bob");
    Member* m1 = new Member("Jack", 24, "Athlete", 1);
    Member* m2 = new Member("Kelly", 26, "Athlete", 2);
    Member* m3 = new Member("Bob", 30, "Athlete", 3);
    club.addMember(m1);
    club.addMember(m2);
    club.addMember(m3);

    std::cout << "Current Members:\n";
    for (const auto& member : club.getMembers()) {
        std::cout << "Name: " << member->getName() << ", Age: " << member->getAge() << ", Role: " << member->getRole() << ", ID: " << member->getId() << '\n';
    }

    printDivider("Adding Coaches: Laura (Tennis) and Sam (Swimming)");
    Coach* c1 = new Coach("Laura", "Tennis", 1);
    Coach* c2 = new Coach("Sam", "Swimming", 2);
    club.addCoach(c1);
    club.addCoach(c2);

    std::cout << "Current Coaches:\n";
    for (const auto& coach : club.getCoaches()) {
        std::cout << "Name: " << coach->getName() << ", Specialty: " << coach->getSpecialty() << ", ID: " << coach->getId() << '\n';
    }

    printDivider("Creating and Adding Teams: Tennis Team and Swimming Team");
    Team* t1 = new Team("Tennis", c1, 1);
    Team* t2 = new Team("Swimming", c2, 2);
    t1->addMember(m1);
    t1->addMember(m2);
    t2->addMember(m3);
    club.addTeam(t1);
    club.addTeam(t2);

    std::cout << "Current Teams:\n";
    for (const auto& team : club.getTeams()) {
        std::cout << "Sport Type: " << team->getSportType() << ", ID: " << team->getId() << '\n';
        std::cout << "Team Members:\n";
        for (const auto& member : team->getMembers()) {
            std::cout << "  Name: " << member->getName() << ", ID: " << member->getId() << '\n';
        }
    }

    printDivider("Organizing Events: Tennis Tournament and Swimming Competition");
    Event* e1 = new Event("2024-08-20", "City Arena", "Tennis Tournament");
    Event* e2 = new Event("2024-09-10", "Aquatic Center", "Swimming Competition");
    club.organizeEvent(e1);
    club.organizeEvent(e2);
    club.addMembersToEvent("Tennis Tournament", { m1, m2 });
    club.addMembersToEvent("Swimming Competition", { m3 });

    std::cout << "Current Events:\n";
    for (const auto& event : club.getEvents()) {
        std::cout << "Event Name: " << event->getName() << ", Date: " << event->getDate() << ", Location: " << event->getLocation() << '\n';
        std::cout << "Event Participants:\n";
        for (const auto& participant : event->getParticipants()) {
            std::cout << "  Name: " << participant->getName() << ", ID: " << participant->getId() << '\n';
        }
    }

    printDivider("Updating Coach Specialty: Laura to Basketball");
    club.updateCoachSpecialty("Laura", "Basketball");

    std::cout << "Updated Coach:\n";
    for (const auto& coach : club.getCoaches()) {
        std::cout << "Name: " << coach->getName() << ", Specialty: " << coach->getSpecialty() << ", ID: " << coach->getId() << '\n';
    }

    printDivider("Checking Schedule Conflict for 2024-08-20 and 2024-09-10");
    bool conflict1 = club.hasScheduleConflict("2024-08-20");
    bool conflict2 = club.hasScheduleConflict("2024-09-10");
    std::cout << "Schedule Conflict on 2024-08-20: " << (conflict1 ? "Yes" : "No") << '\n';
    std::cout << "Schedule Conflict on 2024-09-10: " << (conflict2 ? "Yes" : "No") << '\n';

    printDivider("Finding Members by Role: Athlete");
    auto athletes = club.findMembersByRole("Athlete");
    for (const auto& member : athletes) {
        std::cout << "Name: " << member->getName() << ", ID: " << member->getId() << '\n';
    }

    printDivider("Finding Member by Name: Kelly");
    Member* foundMember = club.findMemberByName("Kelly");
    if (foundMember) {
        std::cout << "Found Member: " << foundMember->getName() << ", ID: " << foundMember->getId() << '\n';
    }
    else {
        std::cout << "Member not found\n";
    }

    printDivider("Removing Member: Jack");
    club.removeMember(m1);
    std::cout << "Current Members after removal:\n";
    for (const auto& member : club.getMembers()) {
        std::cout << "Name: " << member->getName() << ", ID: " << member->getId() << '\n';
    }

    printDivider("Removing Coach: Laura");
    club.removeCoach(c1);
    std::cout << "Current Coaches after removal:\n";
    for (const auto& coach : club.getCoaches()) {
        std::cout << "Name: " << coach->getName() << ", ID: " << coach->getId() << '\n';
    }

    printDivider("Removing Team: Tennis Team");
    club.removeTeam(t1);
    std::cout << "Current Teams after removal:\n";
    for (const auto& team : club.getTeams()) {
        std::cout << "Sport Type: " << team->getSportType() << ", ID: " << team->getId() << '\n';
    }

    printDivider("Canceling Event: Tennis Tournament");
    club.cancelEvent(e1);
    std::cout << "Current Events after cancellation:\n";
    for (const auto& event : club.getEvents()) {
        std::cout << "Event Name: " << event->getName() << ", Date: " << event->getDate() << ", Location: " << event->getLocation() << '\n';
    }


    delete m2;
    delete m3;
    delete c2;
    delete t1;
    delete t2;
    delete e2;
}





int main() {
    testMember();
    testCoach();
    testTeam();
    testEvent();
    testClub();
    testDeleteClub();
    testEventScheduleConflict();
    testRemoveMember();
    testRemoveCoach();



   testClubFunctionality();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
