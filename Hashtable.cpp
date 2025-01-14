#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define MAX_Character 256;

class Person_info
{
public:
    uint age;
    uint phonenumber;
    string name;
    Person_info *next;
    Person_info()
    {
        next = nullptr;
        this->age = 0;
        this->phonenumber = 0;
        this->name = "";
    }
    Person_info(uint age, uint phonenumber, string name)
    {
        next = nullptr;
        this->age = age;
        this->phonenumber = phonenumber;
        this->name = name;
    }
};
class Hashtable
{
private:
    int tablesize = 10;
    Person_info **person_array;

public:
    void initialize_Hashtable()
    {
        person_array = new Person_info *[10];
        for (int i = 0; i < tablesize; i++)
        {

            Person_info *newperson = new Person_info();
            cout << "initialize hash value" << endl;
            person_array[i] = newperson;
        }
    }
    Hashtable()
    {
        initialize_Hashtable();
    }
    ~Hashtable()
    {
        for (int i = 0; i < tablesize; i++)
        {
            Person_info *current = person_array[i];
            while (current != nullptr)
            {
                Person_info *toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] person_array; // since we used new Person_info*[tablesize]
    }

    int Hasfunction(Person_info *firstperson)
    {
        int hashvalue = firstperson->age + firstperson->phonenumber;
        for (char c : firstperson->name)
        {
            hashvalue += uint(c);
        }
        return hashvalue % tablesize;
    }

    void insert(Person_info *firstperson)
    {
        int index = Hasfunction(firstperson);
        Person_info *newperson = new Person_info(firstperson->age, firstperson->phonenumber, firstperson->name);
        if (person_array[index]->name != "")
        {

            newperson->next = person_array[index];
            person_array[index] = newperson;
        }
        else
        {
            newperson->next = nullptr;
            person_array[index] = newperson;
        }
    }

    Person_info *lookup(Person_info *firstperson)
    {
        cout << firstperson->name << endl;
        int index = Hasfunction(firstperson);
        Person_info *person_search = person_array[index];
        cout << person_search->name << endl;
        while (true)
        {
            if (person_search->next == nullptr || person_search->name == firstperson->name)
            {
                break;
            }
            person_search = person_search->next;
        }
        // cout << (person_search->name) << endl;
        if (person_search->name == firstperson->name)
        {
            cout << "Found user" << endl;
            return person_search;
        }
        else
        {
            cout << "Unable to find user" << endl;
            return person_search;
        }
    }

    void delete_value(Person_info *firstperson)
    {
        int index = Hasfunction(firstperson);
        Person_info *current_person = person_array[index];
        Person_info *prev_person = person_array[index];

        while (true)
        {

            if (current_person->next == nullptr || current_person->name == firstperson->name)
            {
                break;
            }
            prev_person = current_person;
            current_person = prev_person->next;
        }

        if (current_person->name == firstperson->name)
        {
            if (current_person->next != nullptr)
            {
                Person_info *next_person = current_person->next;
                prev_person->next = next_person;
                delete (current_person);
            }
            else if (current_person->next == nullptr && prev_person != current_person)
            {
                prev_person->next = nullptr;
                delete (current_person);
            }
            else
            {
                current_person->next = nullptr;
                current_person->age = 0;
                current_person->phonenumber = 0;
                current_person->name = "";
            }
        }
        else
        {
            cout << "Unable to delete value" << endl;
        }
    }

    // Print the entire hash table and show collisions, addresses, etc.
    void printTable() const
    {
        cout << "\n=======================" << endl;
        cout << " Current Hash Table" << endl;
        cout << "=======================" << endl;
        for (int i = 0; i < tablesize; i++)
        {
            cout << "[Bucket " << i << "]: ";
            Person_info *cur = person_array[i];

            // If we're using "dummy" nodes, we might want to skip empty ones
            // Here, let's just check if the node has a name or not
            while (cur != nullptr && cur->name != "")
            {
                cout << "(" << cur // show memory address
                     << ") " << cur->name
                     << " | Age: " << cur->age
                     << " | Phone: " << cur->phonenumber
                     << " -> ";
                cur = cur->next;
            }
            cout << "NULL" << endl;
        }
        cout << "=======================\n"
             << endl;
    }
};

int main()
{
    Hashtable *table = new Hashtable();

    // Create a larger dataset to force collisions.
    // The table size is only 10, so multiple entries are likely to fall in the same bucket.
    vector<Person_info *> people = {
        new Person_info(25, 1234, "Alice"),
        new Person_info(30, 2345, "Bob"),
        new Person_info(22, 3456, "Charlie"),
        new Person_info(40, 4567, "David"),
        new Person_info(30, 5678, "Eve"),
        new Person_info(22, 6789, "Frank"),
        new Person_info(45, 7890, "Grace"),
        new Person_info(50, 8901, "Hannah"),
        new Person_info(29, 9012, "Ian"),
        new Person_info(33, 1234, "Jack"),
        new Person_info(27, 2345, "Karen"),
        // More data to test collisions thoroughly
        new Person_info(25, 4321, "Alice2"),
        new Person_info(25, 1234, "Alice3"), // same phone as original Alice
        new Person_info(90, 9999, "Zack"),
        new Person_info(33, 1234, "Jack2"),
        new Person_info(22, 3456, "Charlie2"),
        new Person_info(40, 1111, "David2"),
        new Person_info(45, 2222, "Grace2"),
        new Person_info(22, 6789, "Frank2"),
        new Person_info(25, 5555, "OverflowTest")};

    cout << "--- Inserting People ---" << endl;
    for (auto person : people)
    {
        table->insert(person);
        cout << "Inserted: " << person->name << endl;
    }

    // Print the table to see how collisions are distributed
    table->printTable();

    cout << "\n--- Lookup Test ---" << endl;
    for (auto person : people)
    {
        Person_info *found = table->lookup(person);
        if (found)
        {
            cout << "Found: " << found->name
                 << " (Age: " << found->age
                 << ", Phone: " << found->phonenumber << ")" << endl;
        }
        else
        {
            cout << "Failed to find: " << person->name << endl;
        }
    }

    // Lookup a non-existent entry
    Person_info *nonexistent = new Person_info(50, 5555, "Zoe");
    cout << "\n--- Lookup for non-existent person: " << nonexistent->name << " ---" << endl;
    Person_info *found = table->lookup(nonexistent);
    if (!found)
    {
        cout << "Correctly unable to find: " << nonexistent->name << endl;
    }
    else
    {
        cout << "Error: found a user that should not exist." << endl;
    }

    cout << "\n--- Deletion Test ---" << endl;
    for (auto person : people)
    {
        cout << "Deleting: " << person->name << endl;
        table->delete_value(person);
        cout << "Deleted: " << person->name << endl;
    }

    // Print table after deletions to confirm buckets are cleared
    table->printTable();

    cout << "\n--- Post-Deletion Lookup ---" << endl;
    for (auto person : people)
    {
        Person_info *found = table->lookup(person);
        if (!found)
        {
            cout << "Correctly deleted: " << person->name << endl;
        }
        else
        {
            cout << "Error: " << person->name
                 << " was found after deletion." << endl;
        }
    }

    // Cleanup
    delete nonexistent;
    // Delete the table (this will also delete all internal nodes)
    delete table;

    // Also cleanup all Person_info pointers from the vector
    for (auto person : people)
    {
        delete person;
    }
    people.clear();

    return 0;
}
