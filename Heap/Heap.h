/*
 * File Heap.h
 * -----------
 * You should finish your homework in this file
 */

#ifndef _heap_h
#define _heap_h

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/*
 * Class Heap
 * ----------
 * This is the class you should implement.
 * It is a template class, Compare can be greater<int>, less<int> and so on.
 * When you define a Heap like Heap<greater<int>>, it should be a maxHeap (who's top this the max element)
 * When you define a Heap like Heap<less<int>>, it should be a minHeap (who's top this the min element)
 * So, when you want to compare two element while implement the member function, you should use the member variable cmp, rather than <,<=,>,>=
 */ 
template<class Compare>
class Heap
{
    private:
      // use elements to store the element
      map<int,vector<int>> elements;

      // cmp is a comparer that can help you to compare two element's priority
      // Usage:
      // cmp(element_1, element_2)
      // if element_1's priority is higher than element_2, it will return true, otherwise, return false
      // Example:
      // when you define a Heap like Heap<greater<int>>, it means Compare is greater<int>, and cmp is an instance of greater<int>
      // So, cmp(1,2) and cmp(1,1) will return false and cmp(2,1) will return true
      // when you define a Heap like Heap<less<int>>, it means Compare is less<int>, and cmp is an instance of less<int>
      // So, cmp(2,1) and cmp(1,1) will return false and cmp(1,2) will return true
      // By this way, you can implement minHeap and maxHeap using one class
      Compare cmp;

      // the Top element's index, can make the code more readable
      // It's up to you whether to use it
      pair<int,int> topIndex = make_pair(0,0);

      // Some help function, can improve the code structure
      // It's up to you whether to use them
      pair<int,int> getParentIndex(pair<int,int> index)
      {
          if(index==topIndex) {return make_pair(-1,-1);}//return (-1,-1) when without parent node
          else {return make_pair(index.first-1,index.second/2);}
      }

      pair<int,int> getLeftIndex(pair<int,int> index)
      {
          if(index.first==elements.size()-1){ return make_pair(-1,-1);}
          else {
              if(elements[index.first+1].size()>index.second*2){ return make_pair(index.first+1,index.second*2);}
              else return make_pair(-1,-1);
          }
      }

      pair<int,int> getRightIndex(pair<int,int> index)
      {
          if(index.first==elements.size()-1){ return make_pair(-1,-1);}
          else {
              if(elements[index.first+1].size()>index.second*2+1){ return make_pair(index.first+1,index.second*2+1);}
              else return make_pair(-1,-1);
          }
      }

      bool isInRange(pair<int,int> index)
      {
          if(index.first<elements.size()&&index.second<elements[elements.size()-1].size()&&index.second<(1<<index.first))
              return true;
          else
              return false;
      }
      bool isTop(pair<int,int> index)
      {
          if(index==topIndex) return true;
          return false;
      }
      void swap(pair<int,int> index_1, pair<int,int> index_2)
      {
          int tmpFirst =index_1.first;
          int tmpSecond = index_1.second;
          int tmpValue=elements[index_1.first][index_1.second];
          index_1.first=index_2.first;index_1.second=index_2.second;
          elements[index_1.first][index_1.second]=elements[index_2.first][index_2.second];
          index_2.first=tmpFirst;index_2.second=tmpSecond;
          elements[index_2.first][index_2.second]=tmpValue;
      }

      pair<int,int> findIndex(int element)//can be improved by binary search
      {
          for(auto it=elements.begin();it!=elements.end();it++)
          {
              for(int i=0;i<(*it).second.size();i++)
              {
                  if(it->second[i]==element) return make_pair(it->first,i);
              }
          }
          return make_pair(-1,-1);
      }
      void shift_up(pair<int,int> index)
      {
          pair<int,int> up=getParentIndex(index);
          if(up.first!=-1) {
              swap(up, index);
          }
      }
      void shift_down(pair<int,int> index)
      {
          pair<int,int> left=getLeftIndex(index);
          if(left.first!=-1){
              swap(left,index);
          }
      }

    public:
      /*
       * Constructor: Heap()
       * Usage: Heap<greater<int>> maxHeap
       */
      Heap();

      /*
       * Constructor: Heap(vector<int> init_elements)
       * Usage: Heap<greater<int>> maxHeap(init_elements)
       * ------------------------------------------------
       * You should implement this Method with O(mlog(n)) time complexity (m = init_elements.size(), n = elements.size())
       */
      Heap(vector<int> init_elements);

      /*
       * Destructor: ~Heap()
       * Usage: usually implicit
       */
      ~Heap();

      /*
       * Method: insert(int element)
       * Usage: maxHeap.insert(1)
       * ------------------------
       * Add the new element in to the end of elements and shift_up this element
       * You should implement this Method with O(log(n)) time complexity (n = elements.size())
       */
      void insert(int element);

      /*
       * Method: insert(vector<int> new_elements)
       * Usage: maxHeap.insert(new_elements)
       * ------------------------
       * Add the new element in to the end of elements and shift_up this element one by one
       * You should implement this Method with O(mlog(n)) time complexity (m = new_elements.size(), n = elements.size())
       */
      void insert(vector<int> new_elements);

      /*
       * Method: erase(int element)
       * Usage: maxHeap.erase(1)
       * ------------------------
       * Swap this element with the elements's last element, delete the last element, and shift_down the swapped element
       * You should implement this Method with O(log(n)) time complexity (n = elements.size())
       */
      bool erase(int element);

      /*
       * Method: pop()
       * Usage: maxHeap.pop()
       * ------------------------
       * Swap the top element with the elements's last element, delete and return the last element, and shift_down the swapped element
       * You should implement this Method with O(log(n)) time complexity (n = elements.size())
       */
      int pop();

      /*
       * Method: top()
       * Usage: maxHeap.top()
       * ------------------------
       * return the top element
       * You should implement this Method with O(log(1)) time complexity
       */
      int top();

      /*
       * Method: size()
       * Usage: maxHeap.size()
       * ------------------------
       * return the number of element in the Heap
       * You should implement this Method with O(log(1)) time complexity
       */
      int size();
};

template<class Compare>
Heap<Compare>::Heap()
{
    // you code here
}

template<class Compare>
Heap<Compare>::~Heap()
{
    // you code here
}

template<class Compare>
Heap<Compare>::Heap(vector<int> init_elements)
{
    sort(init_elements,cmp);
    int key=0;
    vector<int> value;
    for(int i=0;i<init_elements.size();i++)
    {
        value.push_back(init_elements[i]);
        if(i==(1<<key)-1) {
            elements.insert(key,value);
            value.clear();
            key++;
        }
    }
    if(value.size()>0) {elements.insert(key+1,value);}
}

template<class Compare>
void Heap<Compare>::insert(int element)
{
    pair<int,int> bottom=make_pair(elements.size()-1,elements[elements.size()-1].size()-1);
    if(bottom.second<(1<<bottom.first)-1){
        elements[bottom.first].push_back(element);
        //parent=getParentIndex(make_pair(bottom.first,elements[bottom.first].size()-1));
    }
    else {
        vector<int> v(1,element);
        elements.insert(make_pair(bottom.first+1,v));
        //parent=getParentIndex(make_pair(bottom.first+1,0));
    }
    pair<int,int> pos=findIndex(element);
    pair<int,int> parent=getParentIndex(pos);
    while (cmp(element,elements[parent.first][parent.second]))
    {
        swap(pos,parent);
    }
}

template<class Compare>
void Heap<Compare>::insert(vector<int> new_elements)
{
    // you code here
}

template<class Compare>
bool Heap<Compare>::erase(int element)
{
    // you code here
}

template<class Compare>
int Heap<Compare>::pop()
{
    // you code here
}

template<class Compare>
int Heap<Compare>::top()
{
    // you code here
}

template<class Compare>
int Heap<Compare>::size()
{
    // you code here
}

#endif
