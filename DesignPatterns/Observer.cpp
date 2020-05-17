#include "pch.h"

//******************** Observer Pattern ********************
/*
The Observer Pattern defines a relationship of one to many, think of a magazine publishing company.
People (observers) subscribe to the magazine publishing company (subject) and they get magazine (data)
delievered to them once the company publishes a new magazine. The magazine company does not know anything
about the observers, therefor there is no dependancy between the subject and the observers.
*/


class observer {
  int observerState = 0;
public:
  observer(int initVal) {
    observerState = initVal;
  }
  void update(int observableNewState) {
    observerState = observableNewState;
  }
};

class observable {
private:
  int state = 0;
  set<observer> observers;

public:
  bool AddObserver(const observer& obs) {
    auto r = observers.insert(obs);
    return r.second; //return true is insertion was successful
  }
  bool RemoveObserver(const observer& obs) {
    return observers.erase(obs);
  }
  void update_State(int s) {
    this->state = s;
    notifyObservers();
  }
  void notifyObservers() {
    for (auto obs : observers) {
      obs.update(state);
    }
  }
};

//-----------------------another implementation of the observer pattern---------------------------------------
//in this example, we pass a reference of the observable object to each observer.
//and when the update methond is called from the observable, each observer need to 'pull' the updates from the 
//observable object.


class Observer;

class Observable {
  vector <Observer*> views;
  int value;

public:
  void attach(Observer* obs) {
    views.push_back(obs);
  }

  void setVal(int val) {
    value = val;
    notify();
  }

  int getVal() {
    return value;
  }
  void notify() {
    // 5. Publisher broadcasts
    for (int i = 0; i < views.size(); i++) {
      views[i]->update(); //tell the observers that something has changes, and each observer needs to 'pull'
    }
  }
};

//This is an interface
class Observer {
  Observable* model;

public:
  Observer(Observable* mod) {
    model = mod;
    //Observers register themselves with the Subject
    model->attach(this);
  }
  virtual void update() = 0;

protected:
  Observable* getSubject() {
    return model;
  }
};

class DivObserver : public Observer {
public:
  DivObserver(Observable* mod) : Observer(mod) {}

  void update() {
    int v = getSubject()->getVal(); //"Pull" information of interest
  }

};

int main_observer() {
  Observable subj;
  DivObserver divObs1(&subj);
  DivObserver divObs2(&subj);
  subj.setVal(14);
}
