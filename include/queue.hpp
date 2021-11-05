#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <thread>
#include <condition_variable>
#include <iostream>

template<class T>
class Queue{
  private:
    T* container;
    int size_;
    int head;
    int tail;
    bool isFull;
    bool isEmpty;
    std::mutex container_mutex;
    std::condition_variable condition;
    bool data_ready;
    bool production;
  public:
    Queue(const int size):
    size_{size},
    head{0},
    tail{0},
    isFull{false},
    isEmpty{true},
    production{true},
    data_ready{false}{
      //static_assert(size > 0);
      container = new T[size];
    }
    ~Queue(){ delete[] container;}
    Queue(const Queue& o) = delete;
    Queue(Queue&& o) = delete;
    Queue& operator=(const Queue& o) = delete;
    Queue& operator=(Queue&& o) = delete;
    bool push(const T data){
      bool success = true;
      std::unique_lock<std::mutex> lock(container_mutex);
      if(!isFull){
        container[tail] = data;
        tail = (tail + 1) % size_;
        if(tail == head) isFull = true;
        isEmpty = false;
      }else{
        success = false;
      }
      if(success){
        data_ready = true;
        condition.notify_one();
      }
      return success;
    }
    bool pop(T* storage){
      bool success = true;
      std::unique_lock<std::mutex> lock(container_mutex);
      condition.wait(lock, [this](){
        return this -> data_ready;
      });
      if(!isEmpty){
        *storage = container[head];
        head = (head + 1) % size_;
        isFull = false;
        if(head == tail) isEmpty = true;
      }else{
        success = false;
      }
      return success;
    }
    bool isFullOfData(){
      std::unique_lock<std::mutex> lock(container_mutex);
      return isFull;
    }
    int size(){return size_;} 
    bool isEmptyOfData(){return isEmpty;}
    bool isProductionRunning(){return production;}
    void setProductionState(bool info){ 
      std::unique_lock<std::mutex> lock(container_mutex);
      production = info;
      condition.notify_all();
    }
    void print(){
      std::cout <<"head "<< container[head]<< std::endl;
    }
};

#endif