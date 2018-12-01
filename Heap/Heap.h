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
#include <cmath>
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
          if(index.first==0) {return make_pair(-1,-1);}//return (-1,-1) when without parent node
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
          return elements[elements.size() - 1].size() > index.second && index.first >=0 && index.first < elements.size() && index.second < (1 << index.first);
      }
      bool isTop(pair<int,int> index)
      {
          return topIndex == index;
      }
      void swap(pair<int,int> index_1, pair<int,int> index_2)
      {
          if(index_1==index_2) return;
          int tmpValue=elements[index_1.first][index_1.second];
          elements[index_1.first][index_1.second]=elements[index_2.first][index_2.second];
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
          while (isInRange(up)&&cmp(elements[index.first][index.second],elements[up.first][up.second]))
          {
              swap(up,index);
	      index=up;
	      up=getParentIndex(index);
          }
      }
      void shift_down(pair<int,int> index)
      {
          pair<int,int> left=getLeftIndex(index);
          pair<int,int> right=getRightIndex(index);
          while(isInRange(left)||isInRange(right))
          {
              if(!isInRange(right)){
                  if(cmp(elements[left.first][left.second],elements[index.first][index.second])){
                      swap(left,index);
		      index=left;
		      left=getLeftIndex(index);
		      right=getRightIndex(index);
                  }
                  else break;
              }
              else{
                  if(cmp(elements[left.first][left.second],elements[index.first][index.second])&&
                     cmp(elements[right.first][right.second],elements[index.first][index.second])) {
                      if (cmp(elements[left.first][left.second], elements[right.first][right.second])) {
                          swap(left, index);
		          index=left;
		          left=getLeftIndex(index);
		          right=getRightIndex(index);
                      }
                      else {
                          swap(right, index);
		          index=right;
		          left=getLeftIndex(index);
		          right=getRightIndex(index);
                      }
                  }
                  else if(cmp(elements[left.first][left.second],elements[index.first][index.second])&&
                          !cmp(elements[right.first][right.second],elements[index.first][index.second])){
                      swap(left,index);
		      index=left;
		      left=getLeftIndex(index);
		      right=getRightIndex(index);
                  }
                  else if(!cmp(elements[left.first][left.second],elements[index.first][index.second])&&
                          cmp(elements[right.first][right.second],elements[index.first][index.second])){
                      swap(right,index);
		      index=right;
		      left=getLeftIndex(index);
		      right=getRightIndex(index);
                  }
		  else break;
              }
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
    sort(init_elements.begin(),init_elements.end(),cmp);
    int key=1;
    vector<int> value;
    for(int i=0;i<init_elements.size();i++)
    {
        if(i==pow(2,key)-1) {
            elements.insert(make_pair(key-1,value));
            value.clear();
            key++;
        }
        value.push_back(init_elements[i]);
    }
    if(value.size()>0) {elements.insert(make_pair(key-1,value));}
    topIndex=make_pair(elements.size()-1,elements[elements.size()-1].size()-1);
}

template<class Compare>
void Heap<Compare>::insert(int element)
{
    if(topIndex.second<pow(2,topIndex.first)-1){
        elements[topIndex.first].push_back(element);
        topIndex.second++;
    }
    else {
        vector<int> v(1,element);
        elements.insert(make_pair(topIndex.first+1,v));
        topIndex=make_pair(topIndex.first+1,0);
    }
    //pair<int,int> pos=topIndex;
    shift_up(topIndex);
}

template<class Compare>
void Heap<Compare>::insert(vector<int> new_elements)
{
    for(int i=0;i<new_elements.size();i++)
    {
        insert(new_elements[i]);
    }
}

template<class Compare>
bool Heap<Compare>::erase(int element)
{
    pair<int,int> pos=findIndex(element);
    if(!isInRange(pos)) return false;
    swap(pos,topIndex);
    if(topIndex.second==0){
	int key=elements.size()-1;
        elements.erase(key);
        topIndex=make_pair(elements.size()-1,elements[elements.size()-1].size()-1);
    }
    else {
        elements[topIndex.first].pop_back();
        topIndex.second--;
    }
    shift_down(pos);
    return true;
}

template<class Compare>
int Heap<Compare>::pop()
{
    int cache=elements[0][0];
    swap(make_pair(0,0),topIndex);
    if(topIndex.second==0){
	int key=elements.size()-1;
        elements.erase(key);
        topIndex=make_pair(elements.size()-1,elements[elements.size()-1].size()-1);
    }
    else {
        elements[topIndex.first].pop_back();
        topIndex.second--;
    }
    shift_down(make_pair(0,0));
    return cache;
}

template<class Compare>
int Heap<Compare>::top()
{
    return elements[0][0];
}

template<class Compare>
int Heap<Compare>::size()
{
    return pow(2, elements.size() - 1) - 1 + elements[elements.size() - 1].size();
}

#endif
