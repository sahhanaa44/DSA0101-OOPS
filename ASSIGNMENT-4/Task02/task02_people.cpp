#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int id_;
    std::string phone_;

public:
    Person(std::string name = "Unknown", int id = 0, std::string phone = "N/A")
        : name_(std::move(name)), id_(id), phone_(std::move(phone)) {
        std::cout << "Person ";
    }
    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    std::string programme_;
    double cgpa_;

public:
    Student(std::string name, int id, std::string phone,
            std::string programme, double cgpa)
        : Person(std::move(name), id, std::move(phone)),
          programme_(std::move(programme)), cgpa_(cgpa) {
        std::cout << "Student ";
    }
};

class Staff : virtual public Person {
protected:
    std::string department_;
    double salary_;

public:
    Staff(std::string name, int id, std::string phone,
          std::string department, double salary)
        : Person(std::move(name), id, std::move(phone)),
          department_(std::move(department)), salary_(salary) {
        std::cout << "Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string name, int id, std::string phone,
                      std::string programme, double cgpa,
                      std::string department, double salary)
        : Person(std::move(name), id, std::move(phone)),
          Student(name_, id_, phone_, std::move(programme), cgpa),
          Staff(name_, id_, phone_, std::move(department), salary) {
        std::cout << "TeachingAssistant ";
    }

    void print() const {
        std::cout << "\nName: " << name_ << ", ID: " << id_
                  << ", Programme: " << programme_
                  << ", Department: " << department_ << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship_;

public:
    ResearchScholar(std::string name, int id, std::string phone,
                    std::string programme, double cgpa, double fellowship)
        : Person(std::move(name), id, std::move(phone)),
          Student(name_, id_, phone_, std::move(programme), cgpa),
          fellowship_(fellowship) {}

    void print() const {
        std::cout << "Research scholar: " << name_
                  << ", fellowship: " << fellowship_ << '\n';
    }
};

int main() {
    std::cout << "Constructing teaching assistant: ";
    TeachingAssistant ta("Kavya", 192311001, "9876543210",
                         "CSE", 8.7, "Computer Science", 35000);
    ta.print();

    std::cout << "Constructing research scholar: ";
    ResearchScholar rs("Arun", 192311002, "9876500000", "CSE", 9.1, 12000);
    rs.print();
    return 0;
}
