#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Person_info
{
public:
    uint age;
    string name;
    long phone_number;
    Person_info()
    {
        age = 0;
        name = "";
        phone_number = 0;
    }
};
class Hashtable
{
private:
    int Tablesize_ = 2;
    int n_insert = 0;
    int probition_value = 2;

    Person_info **person;
    float load_factor = 0;
    int gcd(int a, int b)
    {

        // Everything divides 0
        if (a == 0)
            return b;
        if (b == 0)
            return a;

        // If both numbers are equal
        if (a == b)
            return a;

        // If a is greater
        if (a > b)
            return gcd(a - b, b);

        // If b is greater
        return gcd(a, b - a);
    }

    void test_condition()
    {

        while (gcd(probition_value, Tablesize_) != 1)
        {
            probition_value++;
        }
    }
    int linear_probing(int index)
    {
        test_condition();
        return index * probition_value;
    }
    int quadratic_probing(int key)
    {
        return 0;
    }
    int double_hashing(int key)
    {
        return 0;
    }
    int Hashing_function(Person_info *person)
    {
        int index = 0;

        for (char c : person->name)
        {
            index += int(c);
        }
        index = (index + person->age + person->phone_number) % Tablesize_;
        return index;
    }
    Person_info **create_table()
    {
        Person_info *new_person[Tablesize_];
        for (int i = 0; i < Tablesize_; i++)
        {
            new_person[i] = new Person_info();
        }
        return new_person;
    }

    Person_info **initialize_table()
    {
        Person_info **new_person;
        new_person = create_table();
        int index;
        for (int i = 0; i < Tablesize_; i++)
        {

            if (person[i]->name != "")
            {
                index = Hashing_function(person[i]);
                if (new_person[index]->name != "")
                {
                    int j = 0;
                    while (new_person[index]->name != "")
                    {
                        index = (index + linear_probing(j)) % Tablesize_;
                        j++;
                    }
                    new_person[index] = person[i];
                }
                else
                {
                    new_person[index] = person[i];
                }
            }
            else
            {
                new_person[i] = new Person_info();
            }
        }

        return new_person;
    }
    float check_size()
    {
        Person_info **delete_this = person;
        Person_info **new_table;
        int max_insert = 0.7 * Tablesize_;
        if (max_insert <= n_insert)
        {
            Tablesize_ = Tablesize_ * 2;
            new_table = initialize_table();
        }
        delete delete_this;
        person = new_table;
    }

public:
    Hashtable()
    {
        person = create_table();
    }
    void insert()
    {
    }
    ~Hashtable()
    {
    }
};
int main(int argc, char const *argv[])
{
    return 0;
}
