#include <iostream>

/*
5   8   2   9
0   1   2   3   4

temp = 9

5   9   2   9
0   1   2   3   4
*/

class SparseSet
{
public:
    SparseSet(int cap, int mv)
    {
        capacity = cap;  // dense
        maxValue = mv;   // sparse

        sparse = new int[maxValue];
        for (int i = 0; i < maxValue; i++)
            sparse[i] = -1;

        dense = new int[capacity];
        n     = 0;
    }

    ~SparseSet()
    {
        delete[] sparse;
        delete[] dense;
    }

    int Search(int x)
    {
        if (x > maxValue)
            return -1;

        if (sparse[x] < n && dense[sparse[x]] == x)
            return sparse[x];

        return -1;
    }

    void Insert(int x)
    {
        if (x > maxValue)
            return;
        if (n >= capacity)
            return;
        if (Search(x) != -1)
            return;

        dense[n] = x;

        sparse[x] = n;

        n++;
    }

    void Delete(int x)
    {
        if (Search(x) == -1)
            return;

        dense[sparse[x]]     = dense[n - 1];
        sparse[dense[n - 1]] = sparse[x];

        n--;
    }

    SparseSet Intersection(SparseSet& another_set)
    {
        int minCap = std::min(capacity, another_set.capacity);
        int mv     = std::max(maxValue, another_set.maxValue);

        SparseSet resultSet(minCap, mv);

        if (n < another_set.n)
        {
            for (int i = 0; i < n; i++)
            {
                if (another_set.Search(dense[i]) != -1)
                    resultSet.Insert(dense[i]);
            }
        }
        else
        {
            for (int i = 0; i < another_set.n; i++)
            {
                if (Search(another_set.dense[i]) != -1)
                    resultSet.Insert(another_set.dense[i]);
            }
        }

        return resultSet;
    }

    SparseSet Union(SparseSet& another_set)
    {
        int minCap = capacity + another_set.capacity;
        int mv     = std::max(maxValue, another_set.maxValue);

        SparseSet resultSet(minCap, mv);

        for (int i = 0; i < n; i++)
        {
            resultSet.Insert(dense[i]);
        }

        for (int i = 0; i < another_set.n; i++)
        {
            resultSet.Insert(another_set.dense[i]);
        }

        return resultSet;
    }

    void Print()
    {
        std::cout << "{ ";
        for (int i = 0; i < n; i++)
            std::cout << dense[i] << " ";
        std::cout << "}\n";
    }

    int* sparse;
    int* dense;
    int  n;
    int  capacity;
    int  maxValue;
};

int main()
{
    SparseSet a(10, 20);
    a.Insert(5);
    a.Insert(8);
    a.Insert(2);
    a.Insert(9);
    a.Insert(5);

    std::cout << "a: ";
    a.Print();

    std::cout << "Search 8: " << a.Search(8) << "\n";
    std::cout << "Search 100: " << a.Search(100) << "\n";

    a.Delete(8);
    std::cout << "a after delete 8: ";
    a.Print();

    SparseSet b(10, 20);
    b.Insert(2);
    b.Insert(9);
    b.Insert(15);

    std::cout << "b: ";
    b.Print();

    SparseSet inter = a.Intersection(b);
    std::cout << "Intersection: ";
    inter.Print();

    SparseSet uni = a.Union(b);
    std::cout << "Union: ";
    uni.Print();

    return 0;
}