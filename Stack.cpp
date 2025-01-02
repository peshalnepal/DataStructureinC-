#include <iostream>
using namespace std;
class Node
{
public:
    int data;
    Node *prev;
    Node *next;
    Node(int data, Node *prev, Node *next)
    {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
};
class Double_linked_list
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    Double_linked_list()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void add_first_item(int item)
    {
        if (size == 0)
        {
            Node *newNode = new Node(item, nullptr, nullptr);
            head = newNode;
            tail = newNode;
            size++;
            // delete newNode;
        }
        else
        {
            Node *newNode = new Node(item, nullptr, head);
            head->prev = newNode;
            head = newNode;
            size++;
            // delete newNode;
        }
    }
    void add_last_item(int item)
    {
        if (size == 0)
        {
            Node *newNode = new Node(item, nullptr, nullptr);
            head = newNode;
            tail = newNode;
            size++;
            // delete newNode;
        }
        else
        {
            Node *newNode = new Node(item, tail, nullptr);
            tail->next = newNode;
            tail = newNode;
            size++;
            // delete newNode;
        }
    }
    void add_item(int item)
    {
        add_last_item(item);
    }
    void add_item(int item, int pos)
    {
        if (pos >= 0 && pos < size)
        {

            if (pos < int(size / 2))
            {
                Node *iterate = head;
                for (int i = 0; i < int(size / 2); i++)
                {
                    if (pos == i)
                    {
                        Node *newNode = new Node(item, iterate->prev, iterate);
                        iterate->prev->next = newNode;
                        iterate->prev = newNode;
                        iterate = newNode;
                        size++;
                    }
                    iterate = iterate->next;
                }
            }
            else
            {
                Node *iterate = tail;
                for (int i = size - 1; i >= int(size / 2); i--)
                {
                    if (pos == i)
                    {
                        Node *newNode = new Node(item, iterate, iterate->next);
                        iterate->next->prev = newNode;
                        iterate->next = newNode;
                        iterate = newNode;
                        size++;
                    }
                    iterate = iterate->prev;
                }
            }
        }
    }
    int len()
    {
        return size;
    }
    int get(int pos)
    {
        if (pos >= 0)
        {
            Node *iterate = head;
            for (int i = 0; i < size; i++)
            {
                if (i == pos)
                {
                    return iterate->data;
                }
                iterate = iterate->next;
            }
            return -1;
        }
        return -1;
    }

    int Get_index(int item)
    {

        Node *iterate = head;
        for (int i = 0; i < size; i++)
        {
            if (iterate->data == item)
            {
                return i;
            }
            iterate = iterate->next;
        }
        return -1;
    }
    int remove_item(int item)
    {

        Node *iterate = head;
        for (int i = 0; i < size; i++)
        {
            if (iterate->data == item)
            {
                if (iterate->prev != nullptr && iterate->next != nullptr)
                {
                    iterate->prev->next = iterate->next;
                    iterate->next->prev = iterate->prev;
                    delete iterate;
                    size--;
                    return 0;
                }
                else if (iterate == head)
                {
                    iterate->next->prev = nullptr;
                    head = iterate->next;
                    delete iterate;
                    size--;
                    return 0;
                }
                else if (iterate == tail)
                {
                    iterate->prev->next = nullptr;
                    tail = iterate->prev;
                    delete iterate;
                    size--;
                    return 0;
                }
            }
            iterate = iterate->next;
        }
        cout << "item not found" << endl;
        return -1;
    }

    void remove_at_pos(int pos)
    {
        if (pos >= 0 && pos < size)
        {

            if (pos <= int(size / 2))
            {
                Node *iterate = head;
                for (int i = 0; i < int(size / 2); i++)
                {
                    if (pos == i)
                    {
                        if (iterate->prev != nullptr && iterate->next != nullptr)
                        {
                            iterate->prev->next = iterate->next;
                            iterate->next->prev = iterate->prev;
                        }
                        else if (iterate == head)
                        {
                            iterate->next->prev = nullptr;
                            head = iterate->next;
                        }
                        delete iterate;
                        size--;
                        break;
                    }
                    iterate = iterate->next;
                }
            }
            else
            {
                Node *iterate = tail;
                for (int i = size - 1; i >= int(size / 2); i--)
                {
                    if (pos == i)
                    {
                        if (iterate->prev != nullptr && iterate->next != nullptr)
                        {
                            iterate->prev->next = iterate->next;
                            iterate->next->prev = iterate->prev;
                        }
                        else if (iterate == tail)
                        {
                            iterate->prev->next = nullptr;
                            tail = iterate->prev;
                        }
                        delete iterate;
                        size--;
                        break;
                    }
                    iterate = iterate->prev;
                }
            }
        }
    }
};
class Stack
{
private:
    Double_linked_list *list_;

public:
    Stack()
    {
        list_ = new Double_linked_list();
    }
    void Push(int x)
    {
        list_->add_first_item(x);
    }
    int Pop()
    {
        int value = list_->get(0);
        list_->remove_at_pos(0);
        return value;
    }
};
int main(int argc, char const *argv[])
{
    Stack *stack = new Stack();
    int items[4] = {100, 200, 300, 50};
    for (int i = 0; i < 4; i++)
    {
        stack->Push(items[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        cout << stack->Pop() << endl;
    }

    // list_->add_item(items[0]);
    // list_->add_item(items[1]);
    // list_->add_last_item(items[2]);
    // list_->add_first_item(items[3]);
    // for (int i = 0; i < list_->len(); i++)
    // {
    //     cout << list_->get(i) << endl;
    // }
    // list_->remove_item(100);
    // int index = 0;
    // for (int i = 0; i < 4; i++)
    // {
    //     index = list_->Get_index(items[i]);
    //     if (index >= 0)
    //     {
    //         cout << index << " index of" << items[i] << endl;
    //     }
    //     else
    //     {
    //         cout << "Given item " << items[i] << " is not found" << endl;
    //     }
    // }
    return 0;
}
