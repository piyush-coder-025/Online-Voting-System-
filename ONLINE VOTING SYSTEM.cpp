#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Candidate {
public:
    int id;
    string name;
    int votes;
    void input() {
        cout << "Enter Candidate ID: ";
        cin >> id;
        cout << "Enter Candidate Name: ";
        cin >> name;
        votes = 0;
    }
  void display() {
        cout << id << "\t" << name << "\tVotes: " << votes << endl;
    }
};
class Voter {
public:
    int id;
    string name;
    string password;
    bool hasVoted;

    void registerVoter() {
        cout << "Enter Voter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Create Password: ";
        cin >> password;
        hasVoted = false;
    }
};
bool adminLogin() {
    string username, password;
    cout << "\nAdmin Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
 return (username == "admin" && password == "1234");
}
void addCandidate() {
    Candidate c;
    ofstream file("candidates.txt", ios::app);
   c.input();
    file << c.id << " " << c.name << " " << c.votes << endl;
   file.close();
    cout << "Candidate Added Successfully!\n";
}
void viewCandidates() {
    ifstream file("candidates.txt");
    Candidate c;
    cout << "\n--- Candidate List ---\n";
    while (file >> c.id >> c.name >> c.votes) {
        c.display();
    }
    file.close();
}
void registerVoter() {
    Voter v;
    ofstream file("voters.txt", ios::app);
   v.registerVoter();
    file << v.id << " " << v.name << " " << v.password << " " << v.hasVoted << endl;
    file.close();
    cout << "Voter Registered Successfully!\n";
}
bool loginVoter(int &voterID) {
    ifstream file("voters.txt");
    int id;
    string name, password;
    bool voted;
    cout << "\nEnter Voter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;
    while (file >> voterID >> name >> password >> voted) {
        if (voterID == id && password == password) {
            if (voted) {
                cout << "You have already voted!\n";
                return false;
            }
            file.close();
            return true;
        }
    }
    cout << "Invalid Credentials!\n";
    file.close();
    return false;
}
void vote() {
    int voterID;
    if (!loginVoter(voterID)) return;
    ifstream file("candidates.txt");
    Candidate c[10];
    int count = 0;
    while (file >> c[count].id >> c[count].name >> c[count].votes) {
        count++;
    }
    file.close();
    cout << "\n--- Candidates ---\n";
    for (int i = 0; i < count; i++) {
        cout << c[i].id << ". " << c[i].name << endl;
    }
    int choice;
    cout << "Enter Candidate ID: ";
    cin >> choice;
    for (int i = 0; i < count; i++) {
        if (c[i].id == choice) {
            c[i].votes++;
        }
    }
    ofstream out("candidates.txt");
    for (int i = 0; i < count; i++) {
        out << c[i].id << " " << c[i].name << " " << c[i].votes << endl;
    }
    out.close();
    cout << "Vote Cast Successfully!\n";
}
void showResults() {
    ifstream file("candidates.txt");
    Candidate c;
    int maxVotes = 0;
    string winner;
    cout << "\n--- Results ---\n";
    while (file >> c.id >> c.name >> c.votes) {
        cout << c.name << " : " << c.votes << " votes\n";
        if (c.votes > maxVotes) {
            maxVotes = c.votes;
            winner = c.name;
        }
    }
    cout << "\nWinner: " << winner << " with " << maxVotes << " votes!\n";
    file.close();
}
int main() {
    int choice;
    do {
        cout << "\n===== ONLINE VOTING SYSTEM =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Register Voter\n";
        cout << "3. View Candidates\n";
        cout << "4. Vote\n";
        cout << "5. Show Results\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            if (adminLogin()) {
                int adminChoice;
                do {
                    cout << "\n--- Admin Panel ---\n";
                    cout << "1. Add Candidate\n";
                    cout << "2. View Candidates\n";
                    cout << "3. Back\n";
                    cout << "Enter choice: ";
                    cin >> adminChoice;
                    if (adminChoice == 1) addCandidate();
                    else if (adminChoice == 2) viewCandidates();
                } while (adminChoice != 3);
            } else {
                cout << "Wrong Admin Credentials!\n";
            }
            break;
        case 2:
            registerVoter();
            break;
       case 3:
            viewCandidates();
            break;
       case 4:
            vote();
            break;
       case 5:
            showResults();
            break;
       case 6:
            cout << "Exiting...\n";
            break;
     default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 6);
    return 0;
}

