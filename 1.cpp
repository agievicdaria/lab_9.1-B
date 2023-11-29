#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialty
{
    COMPUTER_SCIENCE,
    INFORMATICS,
    MATH_ECON,
    PHYS_INF,
    HANDICRAFT
};

union ThirdGrade
{
    double programmingGrade; // COMPUTER_SCIENCE
    double numericalMethodsGrade; // INFORMATICS
    double pedagogyGrade; // MATH_ECON, PHYS_INF, HANDICRAFT
};

struct Student
{
    string lastName;
    int course;
    Specialty specialty;
    double physicsGrade;
    double mathGrade;
    ThirdGrade thirdGrade;
};

string specialtyStr[] = {"computer science", "informatics", "math and economics", "physics and informatics", "handicraft"};

void Create(Student *students, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; ++i)
    {
        cout << "Студент #" << i + 1 << ":\n";
        cin.ignore();
        cout << "Прізвище: ";
        getline(cin, students[i].lastName);
        cout << "Курс: ";
        cin >> students[i].course;
        cout << "Спеціальність (0 - комп'ютерні науки, 1 - інформатика, 2 - математика та економіка, 3 - фізика та інформатика, 4 - трудове навчання): ";
        int specialty;
        cin >> specialty;
        students[i].specialty = static_cast<Specialty>(specialty);
        cout << "Оцінка з фізики: ";
        cin >> students[i].physicsGrade;
        cout << "Оцінка з математики: ";
        cin >> students[i].mathGrade;

        switch (students[i].specialty)
        {
        case COMPUTER_SCIENCE:
            cout << "Оцінка з програмування: ";
            cin >> students[i].thirdGrade.programmingGrade;
            break;
        case INFORMATICS:
            cout << "Оцінка з чисельних методів: ";
            cin >> students[i].thirdGrade.numericalMethodsGrade;
            break;
        default:
            cout << "Оцінка з педагогіки: ";
            cin >> students[i].thirdGrade.pedagogyGrade;
            break;
        }

        cout << endl;
    }
}

void PrintTable(const Student *students, const int numberOfStudents)
{
    cout << "==========================================================================================================================="
         << endl;
    cout << "| №  | Прізвище | Курс | Спеціальність            | Фізика | Математика | Програмування | Чисельні методи | Педагогіка   |"
         << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------"
         << endl;

    for (int i = 0; i < numberOfStudents; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
             << "| " << setw(9) << left << students[i].lastName
             << "| " << setw(5) << right << students[i].course
             << "| " << setw(25) << left << specialtyStr[static_cast<int>(students[i].specialty)]
             << "| " << setw(7) << right << students[i].physicsGrade
             << "| " << setw(11) << right << students[i].mathGrade;

        switch (students[i].specialty)
        {
        case COMPUTER_SCIENCE:
            cout << "| " << setw(13) << right << students[i].thirdGrade.programmingGrade
                 << " |                 |              |";
            break;
        case INFORMATICS:
            cout << "|               | " << setw(15) << right << students[i].thirdGrade.numericalMethodsGrade
                 << " |              |";
            break;
        default:
            cout << "|               |                 | " << setw(13) << right << students[i].thirdGrade.pedagogyGrade << "|";
            break;
        }

        cout << endl;
    }
    cout << "==========================================================================================================================="
         << endl;
    cout << endl;
}

void PrintExcellentStudents(const Student *students, int numberOfStudents)
{
    cout << "Студенти, які вчаться на 'відмінно':\n";
    for (int i = 0; i < numberOfStudents; ++i)
    {
        if (students[i].physicsGrade == 5.0 &&
            students[i].mathGrade == 5.0 &&
            (students[i].specialty == COMPUTER_SCIENCE && students[i].thirdGrade.programmingGrade == 5.0 ||
             students[i].specialty == INFORMATICS && students[i].thirdGrade.numericalMethodsGrade == 5.0 ||
             (students[i].specialty != COMPUTER_SCIENCE && students[i].specialty != INFORMATICS && students[i].thirdGrade.pedagogyGrade == 5.0)))
        {
            cout << students[i].lastName << endl;
        }
    }
}

double CalculatePercentageOfStudents(const Student *students, int numberOfStudents)
{
    int countHighGrades = 0;
    for (int i = 0; i < numberOfStudents; ++i)
    {
        double averageGrade = (students[i].physicsGrade + students[i].mathGrade +
                               (students[i].specialty == COMPUTER_SCIENCE ? students[i].thirdGrade.programmingGrade :
                                students[i].specialty == INFORMATICS ? students[i].thirdGrade.numericalMethodsGrade :
                                students[i].thirdGrade.pedagogyGrade)) / 3.0;

        if (averageGrade > 4.5)
        {
            ++countHighGrades;
        }
    }

    return static_cast<double>(countHighGrades) / static_cast<double>(numberOfStudents) * 100.0;
}

int main()
{
    int numberOfStudents;
    cout << "Введіть кількість студентів: ";
    cin >> numberOfStudents;

    Student *students = new Student[numberOfStudents];

    Create(students, numberOfStudents);
    PrintTable(students, numberOfStudents);

    PrintExcellentStudents(students, numberOfStudents);

    double percentageHighGrades = CalculatePercentageOfStudents(students, numberOfStudents);
    cout << "Процент студентів із середнім балом більше 4,5: " << fixed << setprecision(2) << percentageHighGrades << "%" << endl;

    delete[] students;
    return 0;
}
