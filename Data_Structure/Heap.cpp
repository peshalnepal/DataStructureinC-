#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include <string>
template <typename T>
void print(const T &a)
{
    cout << a << endl;
}
class Heap
{
private:
    vector<int> heap_data;
    map<int, vector<int>> HashMap;

public:
    Heap(/* args */);
    ~Heap();
    void print_HaspMap()
    {
        for (const auto &pair : HashMap)
        {
            std::cout << "Key: " << pair.first << " => ";
            for (int val : pair.second)
            {
                std::cout << val << " ";
            }
            std::cout << "\n";
        }
    }
    void insert(int x)
    {
        heap_data.push_back(x);
        int recent_index = heap_data.size() - 1;
        int heap_size = heap_data.size();
        int recent_data = x;
        int compare_data = 0;
        auto key = HashMap.find(x);
        if (key == HashMap.end())
        {
            HashMap.insert({x, {recent_index}});
        }
        else
        {

            HashMap[x].push_back(recent_index);
        }
        Heap_up();
    }
    void remove_item(int item = -1)
    {
        bool found = false;
        if (HashMap.count(item) > 0)
        {
            vector<int> located = HashMap[item];
            int iterationCount = 0;
            for (vector<int>::iterator i = located.begin(); i != located.end(); ++i)
            {
                if (item >= 0)
                {
                    int index = *i;

                    for (int i = 0; i < HashMap[heap_data[(heap_data.size() - 1)]].size(); ++i)
                    {
                        if (HashMap[heap_data[(heap_data.size() - 1)]][i] == (heap_data.size() - 1))
                        {
                            HashMap[heap_data[(heap_data.size() - 1)]][i] = index;
                            break;
                        }
                    }

                    HashMap[item].erase(HashMap[item].begin() + iterationCount);
                    heap_data[index] = heap_data[(heap_data.size() - 1)];
                    heap_data[(heap_data.size() - 1)] = item;
                    heap_data.pop_back();
                    // print_HaspMap();
                    if (heap_data[int((index - 1) / 2)] >= heap_data[index])
                    {
                        Heap_up(index);
                    }
                    else
                    {

                        Heap_down(index);
                    }
                    iterationCount++;
                    found = true;
                }
            }
            if (HashMap[item].size() == 0)
            {
                HashMap.erase(item);
            }
        }
        if (found != true)
        {
            cout << "Can't remove items" << endl;
        }
    }
    vector<int> get_Heap()
    {
        return heap_data;
    }

    void Heap_up(int index = -1)
    {
        if (index == -1)
        {
            index = heap_data.size() - 1;
        }
        int value = 0;
        while (index > 0 && heap_data[int((index - 1) / 2)] >= heap_data[index])
        {

            value = heap_data[int((index - 1) / 2)];
            for (int i = 0; i < HashMap[value].size(); ++i)
            {
                if (HashMap[value][i] == int((index - 1) / 2))
                {
                    HashMap[value][i] = index;
                    break;
                }
            }
            for (int i = 0; i < HashMap[heap_data[index]].size(); ++i)
            {
                if (HashMap[heap_data[index]][i] == index)
                {
                    HashMap[heap_data[index]][i] = int((index - 1) / 2);
                    break;
                }
            }
            heap_data[int((index - 1) / 2)] = heap_data[index];
            heap_data[index] = value;
            index = int((index - 1) / 2);
        }
    }
    void Heap_down(int index = 0)
    {
        int child = 0;
        while (index < heap_data.size())
        {

            if (int(2 * index + 1) < heap_data.size() && heap_data[index] >= heap_data[int(2 * index + 1)])
            {
                child = heap_data[int(2 * index + 1)];
                for (int i = 0; i < HashMap[child].size(); ++i)
                {
                    if (HashMap[child][i] == int(2 * index + 1))
                    {
                        HashMap[child][i] = index;
                        break;
                    }
                }
                for (int i = 0; i < HashMap[heap_data[index]].size(); ++i)
                {
                    if (HashMap[heap_data[index]][i] == index)
                    {
                        HashMap[heap_data[index]][i] = int(2 * index + 1);
                        break;
                    }
                }

                heap_data[int(2 * index + 1)] = heap_data[index];
                heap_data[index] = child;
                index = int(2 * index + 1);
            }
            else if (int(2 * index + 2) < heap_data.size() && heap_data[index] >= heap_data[2 * index + 2])
            {
                child = heap_data[int(2 * index + 2)];
                for (int i = 0; i < HashMap[child].size(); ++i)
                {
                    if (HashMap[child][i] == int(2 * index + 2))
                    {
                        HashMap[child][i] = index;
                        break;
                    }
                }
                for (int i = 0; i < HashMap[heap_data[index]].size(); ++i)
                {
                    if (HashMap[heap_data[index]][i] == index)
                    {
                        HashMap[heap_data[index]][i] = int(2 * index + 2);
                        break;
                    }
                }

                heap_data[int(2 * index + 2)] = heap_data[index];
                heap_data[index] = child;
                index = int(2 * index + 2);
            }
            else
            {
                break;
            }
        }
    }
};

Heap::Heap(/* args */)
{
}

Heap::~Heap()
{
}

int main(int argc, char const *argv[])
{
    Heap *heap_obj = new Heap();
    heap_obj->insert(2);
    heap_obj->insert(1);
    heap_obj->insert(7);
    heap_obj->insert(5);
    heap_obj->insert(3);
    heap_obj->insert(4);
    heap_obj->insert(0);
    heap_obj->insert(1);
    vector<int> heap_data = heap_obj->get_Heap();
    for (vector<int>::iterator i = heap_data.begin(); i != heap_data.end(); ++i)
    {
        cout << *i << endl;
    }
    heap_obj->print_HaspMap();
    heap_obj->remove_item(9);
    heap_obj->print_HaspMap();
    heap_data = heap_obj->get_Heap();
    for (vector<int>::iterator i = heap_data.begin(); i != heap_data.end(); ++i)
    {
        cout << *i << endl;
    }
    /* code */
    return 0;
}
