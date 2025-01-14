#include <iostream>
#include <string>
using namespace std;
class Node
{
public:
    int value;
    Node *right;
    Node *left;
    Node *parent;
    Node(Node *parent, Node *right, Node *left, int value)
    {
        this->right = right;
        this->left = left;
        this->parent = parent;
        this->value = value;
    }
};
class Binarytree
{
private:
    Node *Root;

public:
    Binarytree()
    {
        Root = nullptr;
    }
    void insert(int value)
    {
        if (Root == nullptr)
        {
            Root = new Node(nullptr, nullptr, nullptr, value);
            Root->parent = Root;
        }
        else
        {

            Node *newNode = new Node(nullptr, nullptr, nullptr, value);
            Node *test = Root;
            while (true)
            {
                if (test->value > value)
                {
                    if (test->left != nullptr)
                    {
                        test = test->left;
                    }
                    else
                    {
                        test->left = newNode;
                        newNode->parent = test;
                        break;
                    }
                }
                else if (test->value <= value)
                {
                    if (test->right != nullptr)
                    {
                        test = test->right;
                    }
                    else
                    {
                        test->right = newNode;
                        newNode->parent = test;
                        break;
                    }
                }
                else
                {
                    break;
                }

                /* code */
            }
        }
    }
    Node *get_root()
    {
        return Root;
    }
    void lookitem(int value)
    {
        Node *item = preorder(Root, value);
        if (item != nullptr)

        {
            cout << "items is in the tree" << endl;
        }
        else
        {
            cout << "items can't be found in the tree" << endl;
        }
    }
    void remove(int value)
    {
        Node *parent = preorder(Root, value);
        if (parent == nullptr)

        {
            cout << "items not in the tree" << endl;
        }
        else
        {
            Node *leftchild = parent->left;
            Node *rightchild = parent->right;
            if (leftchild != nullptr && rightchild != nullptr)
            {
                Node *child = rightchild;
                while (child->left != nullptr)
                {
                    child = child->left;
                }
                int update_value;
                update_value = child->value;
                parent->value = update_value;
                Node *succesor = child->right;
                if (succesor != nullptr)
                {
                    succesor->parent = child->parent;

                    if (succesor->parent->left != nullptr && succesor->parent->left == child)
                    {
                        succesor->parent->left = succesor;
                    }
                    else if (succesor->parent->right != nullptr && succesor->parent->right == child)

                    {
                        succesor->parent->right = succesor;
                    }
                }
                else
                {
                    child->parent->left = nullptr;
                }
                delete child;
            }
            else if (leftchild != nullptr || rightchild != nullptr)
            {
                Node *child;
                if (leftchild != nullptr)
                {
                    if (parent == Root)
                    {
                        leftchild->parent = leftchild;
                        Root = leftchild;
                    }
                    else
                    {
                        parent->parent->left = leftchild;

                        leftchild->parent = parent->parent;
                    }
                    delete parent;
                }
                else if (rightchild != nullptr)
                {
                    if (parent == Root)
                    {
                        rightchild->parent = rightchild;
                        Root = rightchild;
                    }
                    else
                    {
                        parent->parent->right = rightchild;
                        rightchild->parent = parent->parent;
                    }
                    delete parent;
                }
                else
                {
                    cout << "can't do anything" << endl;
                }
            }
            else
            { // If it's the only node in the tree
                if (parent == Root)
                {
                    Root = nullptr;
                }
                else
                {
                    Node *p = parent->parent;
                    if (p->left == parent)
                    {
                        p->left = nullptr;
                    }
                    else
                    {
                        p->right = nullptr;
                    }
                }

                delete parent;
            }
        }
        /* code */
    }

    Node *preorder(Node *node, int value)
    {
        if (node != nullptr)
        {
            if (node->value == value)
            {
                return node;
            }
            Node *newnode;
            newnode = preorder(node->left, value);
            if (newnode != nullptr)
            {
                return newnode;
            }
            newnode = preorder(node->right, value);
            if (newnode != nullptr)
            {
                return newnode;
            }
            return nullptr;
        }
        else
        {
            return nullptr;
        }
    }

    void clear(Node *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    Node *preorder(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        cout << node->value;
        cout << " , ";
        preorder(node->left);

        preorder(node->right);
        return nullptr;
    }
    Node *inorder(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        inorder(node->left);
        cout << node->value;
        cout << " , ";
        inorder(node->right);
        return nullptr;
    }
    Node *postorder(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        postorder(node->left);

        postorder(node->right);
        cout << node->value;
        cout << " , ";
        return nullptr;
    }
    ~Binarytree()
    {
        clear(Root); // call a recursive function that deletes all nodes
    }
}

;
int main()
{
    Binarytree tree;

    // 1) Insert a bunch of values
    //    (covers normal insertion, root creation, repeated values, etc.)
    cout << "Inserting values: 30, 10, 40, 5, 20, 35, 50, 37\n";
    tree.insert(30);
    tree.insert(10);
    tree.insert(40);
    tree.insert(5);
    tree.insert(20);
    tree.insert(35);
    tree.insert(50);
    tree.insert(37); // extra node in right subtree of 35

    // 2) Print traversals after insert
    cout << "\nInorder (Should be sorted):\n";
    tree.inorder(tree.get_root());
    cout << "\n\nPreorder:\n";
    tree.preorder(tree.get_root());
    cout << "\n\nPostorder:\n";
    tree.postorder(tree.get_root());
    cout << "\n\n";

    // 3) Remove a **leaf** node (e.g. 37 or 5). Print afterwards
    cout << "Removing leaf node 37...\n";
    tree.remove(37);

    cout << "\nInorder after removing 37:\n";
    tree.inorder(tree.get_root());
    cout << "\n\n";

    // 4) Remove a node with **one child** (e.g. remove 10 if you inserted 10->(5,20))
    cout << "Removing node 10 (has two children in your insertion? If so, pick another)\n";
    // If 10 has two children (5 and 20), choose a different example for one-child scenario.
    // Let's say we re-insert something that only has one child.
    // For demonstration, if 10 has both left(5) and right(20), that’s “two children.”
    // Instead, remove 5 if it has no children. Or remove 20 if it only has one child.
    // We'll assume 5 is a leaf right now. Let’s pick something that definitely has one child:

    // For this test, let's *ensure* 5 is a leaf by removing 20 first (so 10 has only left child).
    // Then remove 10.

    cout << "First removing 20 (so 10 has only one child: 5)\n";
    tree.remove(20);

    cout << "\nInorder after removing 20:\n";
    tree.inorder(tree.get_root());
    cout << "\n\n";

    cout << "Now removing node 10 (it should have exactly one child, 5)...\n";
    tree.remove(10);

    cout << "\nInorder after removing 10:\n";
    tree.inorder(tree.get_root());
    cout << "\n\n";

    // 5) Remove a node with **two children** (e.g. remove 30 if it still has left and right subtrees)
    //    Or remove 40 if 40 still has both (35 and 50). Let's do 30:
    cout << "Removing 30 (two children scenario)...\n";
    tree.remove(30);

    cout << "\nInorder after removing 30:\n";
    tree.inorder(tree.get_root());
    cout << "\n\n";

    // 6) Remove the **root** (if it’s not already removed).
    //    If 30 was originally the root, we just did that. So let's remove the current root:
    Node *currentRoot = tree.get_root();
    if (currentRoot)
    {
        cout << "Removing the current root (" << currentRoot->value << ")...\n";
        tree.remove(currentRoot->value);

        cout << "\nInorder after removing the root:\n";
        tree.inorder(tree.get_root());
        cout << "\n\n";
    }
    else
    {
        cout << "Tree is empty, cannot remove root.\n\n";
    }

    // 7) Remove a value **not found** in the tree
    cout << "Removing value 999 (not in tree)...\n";
    tree.remove(999);
    cout << "\n\n";

    // 8) Remove nodes until the tree is empty
    //    Let's remove 35, 40, 50, 5, or whichever remain
    cout << "Removing remaining nodes (if any):\n";
    cout << "\n\nPreorder:\n";
    tree.preorder(tree.get_root());
    // We'll do a few calls. Adjust as needed depending on what's left in your tree.
    tree.remove(5); // might or might not exist now
    tree.remove(35);
    tree.remove(40);

    tree.remove(50);

    cout << "Inorder at the end:\n";
    tree.inorder(tree.get_root());
    cout << "\n\n";

    // 9) Final check if tree is empty or partially empty
    if (tree.get_root() == nullptr)
    {
        cout << "Tree is now empty.\n";
    }
    else
    {
        cout << "Tree still has nodes.\n";
    }

    return 0;
}
