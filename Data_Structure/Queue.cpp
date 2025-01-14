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
    int return_head()
    {
        Node *iterate = head;
        int value = iterate->data;
        head = iterate->next;
        delete iterate;
        return value;
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
class Queue
{
private:
    Double_linked_list *list_;

public:
    Queue()
    {
        list_ = new Double_linked_list();
    }
    void Enqueue(int x)
    {
        list_->add_item(x);
    }
    int Dequeue()
    {

        return list_->return_head();
    }
};
int main(int argc, char const *argv[])
{
    Queue *queue = new Queue();
    int items[4] = {100, 200, 300, 50};
    for (int i = 0; i < 4; i++)
    {
        queue->Enqueue(items[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        cout << queue->Dequeue() << endl;
    }
    return 0;
}
