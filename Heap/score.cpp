#include "Heap.h"

int main()
{
    int total_score = 100;
    int score = 0;
    vector<int> init_elements = {4, 7, 3, 5, 9, 21, 33, 6, 10, 16};
    vector<int> new_elements = {5, 1, 45};

    // maxHeap init test
    Heap<greater<int>> maxHeap(init_elements);
    if(maxHeap.size()==10&&maxHeap.top()==33)
    {
        printf("%-24s%s\n","MaxHeap Create", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap Create", "Failed");
    }

    // maxHeap singleInsert test
    maxHeap.insert(21);
    maxHeap.insert(43);
    if(maxHeap.size()==12&&maxHeap.top()==43)
    {
        printf("%-24s%s\n","MaxHeap SingleInsert", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap SingleInsert", "Failed");
    }

    // maxHeap multiInsert test
    maxHeap.insert(new_elements);
    if(maxHeap.size()==15&&maxHeap.top()==45)
    {
        printf("%-24s%s\n","MaxHeap MultiInsert", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap MultiInsert", "Failed");
    }
    
    // maxHeap pop test
    if(maxHeap.pop()==45&&maxHeap.pop()==43&&maxHeap.pop()==33&&maxHeap.size()==12&&maxHeap.top()==21)
    {
        printf("%-24s%s\n","MaxHeap Pop", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap Pop", "Failed");
    }

    // maxHeap erase test
    maxHeap.erase(16);
    if(maxHeap.size()==11&&maxHeap.pop()==21&&maxHeap.pop()==21&&maxHeap.top()==10)
    {
        printf("%-24s%s\n","MaxHeap Erase", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap Erase", "Failed");
    }

    // minHeap init test
    Heap<less<int>> minHeap(init_elements);
    if(minHeap.size()==10&&minHeap.top()==3)
    {
        printf("%-24s%s\n","MinHeap Create", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap Create", "Failed");
    }

    // minHeap singleInsert test
    minHeap.insert(21);
    minHeap.insert(2);
    if(minHeap.size()==12&&minHeap.top()==2)
    {
        printf("%-24s%s\n","MinHeap SingleInsert", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap SingleInsert", "Failed");
    }

    // minHeap multiInsert test
    minHeap.insert(new_elements);
    if(minHeap.size()==15&&minHeap.top()==1)
    {
        printf("%-24s%s\n","MinHeap MultiInsert", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap MultiInsert", "Failed");
    }
    
    // minHeap pop test
    if(minHeap.pop()==1&&minHeap.pop()==2&&minHeap.pop()==3&&minHeap.size()==12&&minHeap.top()==4)
    {
        printf("%-24s%s\n","MinHeap Pop", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap Pop", "Failed");
    }

    // minHeap erase test
    minHeap.erase(5);
    if(minHeap.size()==11&&minHeap.pop()==4&&minHeap.pop()==5&&minHeap.top()==6)
    {
        printf("%-24s%s\n","MinHeap Erase", "Pass");
        score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap Erase", "Failed");
    }

    printf("%-24s%d/%d\n","Total Score", score, total_score);
    return 0;
}