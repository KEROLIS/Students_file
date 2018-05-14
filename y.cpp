
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string encrypt(string word)
{
    for (int i = 0; i < word.length(); i++)
        word[i] = word[i] + 2;
    return word;
}
string decrypt(string word)
{
    for (int i = 0; i < word.length(); i++)
        word[i] = word[i] - 2;
    return word;
}

class person
{
  private:
    string id, name, stage;

  public:
    person()
    {
        id = name = stage = "";
    }
    int sort_record(fstream &f, person per[])
    {
        int i =0;
        person temp;
        while (getline(f, per[i].id, '|'))
        {
            getline(f, per[i].name, '|');
            getline(f, per[i].stage);
            i++;
        }
        for (int x =1;x < i; x++)
        {
            for (int y =0;y < i -1;y++)
            {
                if (per[y].id > per[y +1].id)
                {
                    temp = per[y];
                    per[y] = per[y +1];
                    per[y +1] = temp;
                }
            }
        }
        return i;
    }
    void person_enter()
    {
        cout << "enter id : ";
        cin >> id;
        cout << "enter name :";
        cin >> name;
        cout << "enter stage : ";
        cin >> stage;
    }
    void write_person(fstream &f)
    {
        f << id << '|';
        f << encrypt(name) << '|';
        f << encrypt(stage) << '|';
        f << "\n";
    }
    void write_personW(fstream &f)
    {
        f << id << '|';
        f << name << '|';
        f << stage << '|';
        f << "\n";
    }
    void read_person(fstream &f)
    {
        while (getline(f, id, '|'))
        {
            getline(f, name, '|');
            getline(f, stage, '|');
            f << "\n";
            cout << "id = " << id << endl;
            cout << "name = " << decrypt(name) << endl;
            cout << "stage = " << decrypt(stage) << endl;
        }
    }
    void search_person(fstream &f, int per_id)
    {
        bool flage = false;
        while (getline(f, id, '|'))
        {
            getline(f, name, '|');
            getline(f, stage, '|');
            if (per_id == atoi(id.c_str()))
            {
                cout << "id = " << id << endl;
                cout << "name = " << decrypt(name) << endl;
                cout << "stage = " << decrypt(stage) << endl;
                flage = true;
                break;
            }
        }
        if (flage)
            cout << "record not found !! \n";
    }

    int update_record(fstream &f, person per[], int per_id)
    {
        int i = 0;
        while (1)
        {
            getline(f, per[i].id, '|');
            if (f.fail())
                break;
            getline(f, per[i].name, '|');
            getline(f, per[i].stage);
            if (per_id == atoi(per[i].id.data()))
                per[i].person_enter();
            i++;
        }
        return i;
    }
    int delet_record(fstream &f, person per[])
    {
        int i = 0;
        while (1)
        {
            getline(f, per[i].id, '|');
            if (f.fail())
                break;
            getline(f, per[i].name, '|');
            getline(f, per[i].stage, '|');
            i++;
        }
        return i;
    }
    string return_id()
    {
        return id;
    }
};

int main()
{

    fstream file;
    person p;
    int id;
    char Choice = 'n';
    int choice = 0;
    cout << "do you want to start [Y-N] \n";
    cin >> Choice;
    while (Choice == 'y' || Choice == 'Y')
    {
        system("clear");
        cout << "=========================================<< Sudent Controle System >>=========================================\n\n";
        cout << " [1]-add a new student .  \n ";
        cout << "[2]-show all students . \n ";
        cout << "[3]-search for a student by id . \n ";
        cout << "[4]-update information for a student .  \n ";
        cout << "[5]-delete a student .  \n ";
        cout << "[6]-sort the student id .  \n ";
        cout << "your choice  : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            char ch = 'n';
            file.open("student.txt", ios::app);
            do
            {
                system("clear");
                p.person_enter();
                p.write_person(file);
                cout << "do you want to add another student  [Y-N]:\n#> ";
                cin >> ch;
            } while (ch == 'y' || ch == 'Y');
            file.close();
            break;
        }
        case 2:
        {
            system("clear");
            file.open("student.txt", ios::in);
            p.read_person(file);
            file.close();
            break;
        }
        case 3:
        {
            system("clear");
            cout << "enter person'id ur want to search : ";
            cin >> id;
            file.open("student.txt", ios::in);
            p.search_person(file, id);
            file.close();
            break;
        }

        case 4:
        {
            system("clear");
            int n, j = 0;
            person per[30];
            file.open("student.txt", ios::in);
            cout << "enter student'id ur want to update : ";
            cin >> id;
            n = p.update_record(file, per, id);
            file.close();
            file.open("student.txt", ios::out);
            while (j < n)
            {
                per[j].write_person(file);
                j++;
            }
            file.close();
            break;
        }
        case 5:
        {
            system("clear");
            int n, j =
                       0;
            person per[30];
            file.open("student.txt", ios::in);
            cout << "enter student'id ur want to delete : ";
            cin >> id;
            n = p.delet_record(file, per);
            file.close();
            file.open("student.txt", ios::out);
            while (j < n)
            {
                if (atoi(per[j].return_id().data()) == id)
                {
                    j++;
                    continue;
                }
                per[j].write_personW(file);
                j++;
            }
            file.close();
            break;
        }
        case 6:
        {
            system("clear");
            int n, j = 0;
            person per[30];
            file.open("student.txt", ios::in);
            n = p.sort_record(file, per);
            file.close();
            file.open("student.txt", ios::out);
            file.seekg(0);
            while (j < n)
            {
                per[j].write_personW(file);
                j++;
            }
            file.close();
            break;
        }

        default:
        {
            system("clear");
            cout << "invild input " << endl;
            file.close();
            break;
        }
        }
        cout << "******************** \n start again[Y-N] : \n#>";
        cin >> Choice;
        cout << endl
             << endl;
    }

    return 0;
}
