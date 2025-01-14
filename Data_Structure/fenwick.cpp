#include <iostream>
using namespace std;
#define Table_size 40
#include <cassert>
class Fenwick_tree
{
private:
    int sum_tree[Table_size];
    int value_tree[Table_size];
    int table_size = 0;
    int calculate_sum(int index1)
    {
        int sum = 0;
        while (index1 > 0)

        {
            sum = sum + sum_tree[index1 - 1];
            index1 -= index1 & -index1;
        }
        return sum;
    }
    int calculate_sum(int index1, int index2)
    {
        int sum = 0;
        sum = calculate_sum(index2) - calculate_sum(index1 - 1);
        return sum;
    }
    void update_tree(int i = 1, int value = 0)
    {
        int value_remove;
        value_remove = value_tree[i - 1];
        value_tree[i - 1] = value;
        while (i <= Table_size)
        {
            sum_tree[i - 1] += (value - value_remove);
            i += i & -i;
        }
    }
    void initialize_tree(int i = 1, int value = 0)
    {
        value_tree[i - 1] = value;

        while (i <= Table_size)
        {
            sum_tree[i - 1] += value;
            i += i & -i;
        }
    }

public:
    Fenwick_tree()
    {
        for (int i = 0; i < Table_size; i++)
        {
            value_tree[i] = 0;
            sum_tree[i] = 0;
        }
    }
    Fenwick_tree(int *value, int array_size)
    {
        for (int i = 0; i < Table_size; i++)
        {
            value_tree[i] = 0;
            sum_tree[i] = 0;
        }
        for (int i = 1; i <= array_size; i++)
        {

            initialize_tree(i, value[i - 1]);
        }
    }
    void insert(int index, int value)
    {
        update_tree(index, value);
        table_size++;
    }
    void insert(int index, int *value)
    {
        for (int i = 1; i <= Table_size; i++)
        {
            update_tree(i, value[i - 1]);
        }
    }

    void remove(int index)
    {
        int value_remove;
        value_remove = value_tree[index - 1];

        value_tree[index - 1] = 0;
        while (index <= Table_size)
        {
            sum_tree[index - 1] -= value_remove;
            index += index & -index;
        }
    }
    void print_all_data()
    {
        for (int i = 0; i < Table_size; i++)
        {
            cout << value_tree[i] << " , ";
        }
        cout << endl;
    }
    int sum(int index1, int index2)
    {
        return calculate_sum(index1, index2);
    }
};
void run_tests()
{
    // Create an array with known values. For simplicity, let’s fill first 10 with 1,2,...,10 and the rest 0.
    int test_array[Table_size] = {0};
    for (int i = 1; i <= 10; i++)
    {
        test_array[i - 1] = i; // test_array[0] = 1, test_array[1] = 2, ... test_array[9] = 10
    }

    // Create a Fenwick_tree object using the test_array.
    Fenwick_tree ft(test_array, 10);

    // Test 1: Sum of the first element (index1 = 1, index2 = 1)
    // Expected result: 1
    int result1 = ft.sum(1, 1);
    cout << "Test 1 - Sum(1,1): " << result1 << " (expected 1)" << endl;
    assert(result1 == 1);

    // Test 2: Sum of the first five elements: 1+2+3+4+5 = 15.
    int result2 = ft.sum(1, 5);
    cout << "Test 2 - Sum(1,5): " << result2 << " (expected 15)" << endl;
    assert(result2 == 15);

    // Test 3: Sum from index 3 to index 7: 3+4+5+6+7 = 25.
    int result3 = ft.sum(3, 7);
    cout << "Test 3 - Sum(3,7): " << result3 << " (expected 25)" << endl;
    assert(result3 == 25);

    // Test 4: Sum over entire array (only first 10 elements are non-zero). Expected sum = 55.
    int result4 = ft.sum(1, 10);
    cout << "Test 4 - Sum(1,10): " << result4 << " (expected 55)" << endl;
    assert(result4 == 55);

    // Test 5: Query range where no values were inserted (e.g., index 11 to index 20 should be 0)
    int result5 = ft.sum(11, 20);
    cout << "Test 5 - Sum(11,20): " << result5 << " (expected 0)" << endl;
    assert(result5 == 0);

    // Test 6: Remove a value at index 5 (set it to 0).

    ft.remove(5);

    int result6 = ft.sum(1, 10);
    cout << "Test 6 - Sum(1,10) after removing index 5: " << result6 << " (expected 50)" << endl;
    assert(result6 == 50); // 55 - 5 (value at index 5)

    // Test 7: Ensure index 5 is now zero.
    int result7 = ft.sum(5, 5);
    cout << "Test 7 - Sum(5,5) after removing index 5: " << result7 << " (expected 0)" << endl;
    assert(result7 == 0);

    cout << "All tests passed!" << endl;
}

int main(int argc, char const *argv[])
{
    run_tests();
    return 0;
}
