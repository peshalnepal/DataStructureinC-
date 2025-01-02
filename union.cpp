#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
class Node
{
public:
    Node *Root;
    int index;
    int tree_length;
    Node(Node *Root, int index, int tree_length)
    {
        this->Root = Root;
        this->index = index;
        this->tree_length = tree_length;
    }
};

class Union
{
private:
    map<string, Node *> HashMap;
    vector<int> mapped_num;
    int key_value;

public:
    Union()
    {
        key_value = 0;
    };
    int mapping(string a)
    {
        if (HashMap.count(a) <= 0)
        {
            Node *new_data;
            new_data = new Node(nullptr, key_value, 1);
            new_data->Root = new_data;
            HashMap.insert({a, new_data});
            cout << "Root    ";
            cout << new_data->Root;
            cout << "    ";
            cout << new_data;
            cout << "     ";
            cout << a << " " << to_string(HashMap[a]->index) << endl;
            return key_value;
        }
        else
        {
            return -1;
        }
    }
    void insert(string a)
    {
        int value = mapping(a);
        if (value >= 0)
        {
            mapped_num.push_back(value);
            key_value++;
        }
    }
    template <typename T>
    void print(T x)
    {
        cout << x << endl;
    }
    template <typename T>
    void print(vector<T> x)
    {
        cout << "[ ";
        for (int i = 0; i < x.size(); ++i)
        {
            cout << x[i];
            cout << " , ";
        }

        cout << "]" << endl;
    }
    void join(string a, string b)
    {
        if (HashMap.count(a) <= 0)
        {

            insert(a);
        }
        if (HashMap.count(b) <= 0)
        {
            insert(b);
        }
        Node *test_node_1;
        Node *test_node_2;
        int root_index;
        test_node_1 = HashMap[a];
        test_node_2 = HashMap[b];
        print<string>(a + " index is " + to_string(test_node_1->index) + " with Root of ");
        cout << mapped_num[test_node_1->index] << endl;
        print<string>(b + " index is " + to_string(test_node_2->index) + " with Root of ");
        cout << mapped_num[test_node_2->index] << endl;
        test_node_1 = find_root(test_node_1);
        test_node_2 = find_root(test_node_2);
        print<int>(mapped_num);
        int tree_length = 0;
        if (test_node_1 != test_node_2)
        {
            print<string>("Tree length");
            print<int>(test_node_1->tree_length);
            print<int>(test_node_2->tree_length);
            if (test_node_1->tree_length >= test_node_2->tree_length)
            {
                test_node_2->Root = test_node_1;
                for (vector<int>::iterator i = mapped_num.begin(); i != mapped_num.end(); i++)
                {
                    if (*i == test_node_2->index)
                    {
                        *i = test_node_1->index;
                        tree_length++;
                    }
                }
                test_node_1->tree_length += tree_length;
                test_node_2->tree_length = test_node_1->tree_length;
            }
            else
            {
                test_node_1->Root = test_node_2;
                for (vector<int>::iterator i = mapped_num.begin(); i != mapped_num.end(); i++)
                {
                    if (*i == test_node_1->index)
                    {
                        *i = test_node_2->index;

                        tree_length++;
                    }
                }
                test_node_2->tree_length += tree_length;
                test_node_1->tree_length = test_node_2->tree_length;
            }
            print<int>(mapped_num);
        }
    }
    Node *find_root(Node *test_node)
    {
        if (test_node->Root == test_node)
        {
            return test_node;
        }
        test_node->Root = find_root(test_node->Root);
        return test_node->Root;
    }
    string find(string a)
    {

        cout << "check here" << endl;

        // Node *test = new Node(HashMap[a]->Root, HashMap[a]->index, HashMap[a]->tree_length);

        for (auto &it : HashMap)
        {
            if (mapped_num[HashMap[a]->index] == it.second->index)
            {
                return it.first;
            }
        }
        return "Not found";
    }
};

int main(int argc, char const *argv[])
{
    Union uf; // Create an instance of your Union class

    // ------------------
    // 1. Insert multiple items (all 26)
    // ------------------
    uf.insert("Alice");
    uf.insert("Bob");
    uf.insert("Charlie");
    uf.insert("Delta");
    uf.insert("Echo");
    uf.insert("Foxtrot");
    uf.insert("Golf");
    uf.insert("Hotel");
    uf.insert("India");
    uf.insert("Juliet");
    uf.insert("Kilo");
    uf.insert("Lima");
    uf.insert("Mike");
    uf.insert("November");
    uf.insert("Oscar");
    uf.insert("Papa");
    uf.insert("Quebec");
    uf.insert("Romeo");
    uf.insert("Sierra");
    uf.insert("Tango");
    uf.insert("Uniform");
    uf.insert("Victor");
    uf.insert("Whiskey");
    uf.insert("Xray");
    uf.insert("Yankee");
    uf.insert("Zulu");

    // ------------------
    // 2. Some pairwise joins (simpler set of initial merges)
    // ------------------
    cout << "2. Some pairwise joins" << endl;
    uf.join("Alice", "Bob");     // Merge {Alice, Bob}
    uf.join("Charlie", "Delta"); // Merge {Charlie, Delta}
    uf.join("Echo", "Foxtrot");  // Merge {Echo, Foxtrot}
    uf.join("Golf", "Hotel");    // Merge {Golf, Hotel}
    uf.join("India", "Juliet");  // Merge {India, Juliet}
    uf.join("Kilo", "Lima");     // Merge {Kilo, Lima}

    // ------------------
    // 3. Merge some existing sets
    // ------------------
    cout << "3. Merge some existing sets" << endl;
    uf.join("Bob", "Charlie"); // Merges {Alice,Bob} with {Charlie,Delta}
    uf.join("Delta", "Echo");  // Merges that chain with {Echo,Foxtrot}
    uf.join("Hotel", "India"); // Merges {Golf,Hotel} with {India,Juliet}
    uf.join("Juliet", "Kilo"); // Merges that chain with {Kilo,Lima}

    // ------------------
    // 4. Merge brand-new sets across big clusters
    // ------------------
    cout << "4. Merge brand-new sets across big clusters" << endl;
    uf.join("Foxtrot", "Zulu"); // Connect {Echo,Foxtrot,...} with "Zulu"
    uf.join("Zulu", "Alice");   // Connect "Zulu" to {Alice,Bob,Charlie,Delta,...}

    // ------------------
    // 5. Repeated joins (some do nothing new, but test stability)
    // ------------------
    cout << "5. Repeated joins" << endl;
    uf.join("Alice", "Bob");
    uf.join("Echo", "Delta");
    uf.join("Juliet", "India");
    uf.join("Zulu", "Alice");

    // ------------------
    // 6. Print out final representative for a selection of items
    // ------------------
    cout << "\n6. Print out final representative (root name) for a selection" << endl;
    cout << "Root of 'Alice'    -> " << uf.find("Alice") << endl;
    cout << "Root of 'Golf'     -> " << uf.find("Golf") << endl;
    cout << "Root of 'Hotel'    -> " << uf.find("Hotel") << endl;
    cout << "Root of 'Lima'     -> " << uf.find("Lima") << endl;
    cout << "Root of 'Zulu'     -> " << uf.find("Zulu") << endl;
    cout << "Root of 'Xray'     -> " << uf.find("Xray") << endl; // Xray was never merged

    // A couple more to confirm
    cout << "Root of 'Sierra'   -> " << uf.find("Sierra") << endl; // also unmerged
    cout << "Root of 'Yankee'   -> " << uf.find("Yankee") << endl; // unmerged

    return 0;
}
