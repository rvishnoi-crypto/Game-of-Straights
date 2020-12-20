#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>


class Observer;

class Subject {
    std::vector<Observer*> observers;

  public:
    void attach(Observer *o);  
    void notifyObservers();
    virtual std::string getInfo() const = 0;
};

#endif
