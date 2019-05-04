#include <vector>
#include <algorithm>

using namespace std;

class IndexTree
{
private:
    struct Node
    {
        pair<int, int> sumIndex;
        long long int sum;
        pair<int, int> childIndex;
    };
    int rootIndex;
    vector<Node> segmentHeap;
    int length = 0;

    static long long int getPartialSum(vector<long long int> *v, int begin, int end)
    {
        long long int sum = 0;
        for(int i = begin; i < end; i++)
        {
            sum += v->at(i);
        }
        return sum;
    }

    int build(vector<long long int> *v, int begin, int end)
    {
        int mid = (begin + end) / 2;
        if(end - begin == 1)
        {
            segmentHeap.push_back({{begin, end}, v->at(begin), {-1, -1}});
        }
        else
        {
            segmentHeap.push_back({{begin, end}, getPartialSum(v, begin, end), {build(v, begin, mid), build(v, mid, end)}});
        }
        int ret = length;
        length += 1;
        return ret;
    }

    long long int fetchSumRecursive(int begin, int end, int nodeIndex)
    {
        Node currentNode = segmentHeap.at(nodeIndex);
        int divisor = (currentNode.sumIndex.first + currentNode.sumIndex.second) / 2;
        if (currentNode.sumIndex == pair<int, int>{begin, end})
        {
            return currentNode.sum;
        }
        else
        {
            if (end <= divisor)
            {
                return fetchSumRecursive(begin, end, currentNode.childIndex.first);
            }
            else if (divisor <= begin)
            {
                return fetchSumRecursive(begin, end, currentNode.childIndex.second);
            }
            else
            {
                return 
                    fetchSumRecursive(begin, divisor, currentNode.childIndex.first) +
                    fetchSumRecursive(divisor, end, currentNode.childIndex.second);
            }
        }
    }

    void changeValueRecursive(int index, long long int newValue, int nodeIndex)
    {
        Node currentNode = segmentHeap.at(nodeIndex);
        int divisor = (currentNode.sumIndex.first + currentNode.sumIndex.second) / 2;

        if(divisor == index && divisor == currentNode.sumIndex.first)
        {
            segmentHeap[nodeIndex].sum = newValue;
            return;
        }
    
        if(index < divisor)
        {
            changeValueRecursive(index, newValue, currentNode.childIndex.first);
        }
        else
        {
            changeValueRecursive(index, newValue, currentNode.childIndex.second);
        }

        segmentHeap[nodeIndex].sum = segmentHeap[currentNode.childIndex.first].sum + segmentHeap[currentNode.childIndex.second].sum;
    }

public:
    IndexTree(vector<long long int> v)
    {
        rootIndex = build(&v, 0, v.size());
    }

    int Length()
    {
        return length;
    }

    void print()
    {
        for(auto a : segmentHeap)
        {
            cout << a.sumIndex.first << "~" << a.sumIndex.second << " : " << a.sum << " : " << a.childIndex.first << ", " << a.childIndex.second << endl;
        }
    }

    long long int getSum(int begin, int end)
    {
        return fetchSumRecursive(begin, end, rootIndex);
    }

    void changeNumber(int index, long long int newValue)
    {
        changeValueRecursive(index, newValue, rootIndex);
    }
};