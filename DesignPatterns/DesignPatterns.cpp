#include "pch.h"
#include <iostream>

/*
Creational Designs are all about class instantiation or object creation
They include Factory Method, Abstract Factory, Builder, Singleton, Object Pool, and Prototype

Structural Design Patterns are about organizing different classes and objects to form larger structures,
they include patterns such as Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Private Class Data, and proxy

Behavorial are about indentifying common communication patterns between objects and realizing these patterns.
they include chain of responsbility, command, interpreter , iterator, mediator, memento, Null object, observer, state, Strategy,
template method, visitor.

Summuary of patterns:

Singleton Pattern: its Job is to maintain a single instance (object) throughout the lifetime of the program.
Factroy Pattern:   A single static function in the base class which produces derived classes objects.
Observer Pattern : one to many relationship, think of the youtube channel and subscriber, where a pulisher uploads a new video, and each subscriber
                   gets notified.
Decorator Pattern : Adds differernt AddOns to a basic base object, i.e adding a scope or a magazine to an AK47
Adapter Pattern : a wrapper class that maps new inputs to old inputs

*/


/*********************************************** Singleton Pattern ***********************************************

The Singleton pattern is a design pattern that restricts the instantiation of a class to one object.
*/

class SingleTon
{
private:
   string name = "";
   static SingleTon* SingleObj;
   SingleTon() { name = "FadiYousif"; };
   ~SingleTon() { delete SingleObj; };

public:
   static SingleTon* getInstance() {
      if (SingleObj == nullptr) {
         //create an object on the heap if it doesnt already exists
         SingleObj = new SingleTon();
      }
      return SingleObj;
   }

   string getName() {
      return name;
   }
};

//Must initilize the Singleton object to nullptr this way since the private member variable is static
SingleTon* SingleTon::SingleObj = nullptr;

int main_SingleTon()
{
   SingleTon* Obj = SingleTon::getInstance();
   cout << Obj->getName() << endl;
   return 0;
}

/************************************************ Factory Design Pattern ***********************************************

The idea is to use a static member function (static Vehicle* createVehicle(carTypes Type))
which creates & returns instances, hiding the details of class modules from user.

instead of  creating new objects for the client, we can reuse old objects if the client want the same type of car again.
To do this correctly, we will maintain an object pool (ObjectPool_HT), which is just a hash map that links the carType -> (Type Ptr, ref count);
when the ref count hits 0, then we can safely remove the contents being pointed by the ptr;

*/

enum carTypes {HondaType, ToyotaType};

class Vehicle {
public:
  static unordered_map<carTypes, pair<Vehicle*,int>> ObjectPool_HT;

  virtual void printVehicle() = 0; //pure virtual function which needs to be defined, making this class and abstract class
  static Vehicle* createVehicle(carTypes Type); //this function is what makes a factory pattern, its job is to get a type and return an object of that type
  static void printObjectPool();

  virtual ~Vehicle() { cout << "Vehicle destructor is called" << endl; };
};

class Honda : public Vehicle {
public:
  void printVehicle() override { cout << "Honda Car"; }
  ~Honda() { cout << "Honda destructor is called" << endl; };
};

class Toyota : public Vehicle {
public:
  void printVehicle() override { cout << "Toyota Car"; }
  ~Toyota() { cout << "Toyota destructor is called" << endl; };
};

unordered_map<carTypes, pair<Vehicle*,int>> Vehicle::ObjectPool_HT = {};

Vehicle* Vehicle::createVehicle(carTypes Type) {
  switch (Type) {
  case HondaType:
  {
    if (ObjectPool_HT.count(HondaType) == 0)
      ObjectPool_HT[HondaType] = { new Honda(), 1};
    else
      ObjectPool_HT[HondaType].second++;
    return ObjectPool_HT[HondaType].first;
  }
  case ToyotaType:  
  {
    if (ObjectPool_HT.count(ToyotaType) == 0)
      ObjectPool_HT[ToyotaType] = { new Toyota(), 1 };
    else
      ObjectPool_HT[ToyotaType].second++;
    return ObjectPool_HT[ToyotaType].first;
  }
  default: return nullptr;
  }
}

void Vehicle::printObjectPool() {
  cout << "HashTable contains" << endl;
  for (auto [k, v] : ObjectPool_HT) {
    cout << k << " --> ";
    v.first->printVehicle();
    cout << ": count = " << v.second << endl;
  }
}

//the client's job is to only call the createVehicle method
class Client {
private:
  carTypes Type;
  Vehicle* ptr;

public:
  Client(carTypes Type) {
    this->Type = Type;
    ptr = Vehicle::createVehicle(Type); //this is where the client calls the factory design function and get an object
  }

  ~Client() {
    int& refCount = Vehicle::ObjectPool_HT[Type].second;
    refCount--;

    if (refCount == 0) {
      Vehicle::ObjectPool_HT.erase(Type);
      delete this->ptr;
      this->ptr = nullptr;
    }
  }

  void getVehicleName() {
    if (ptr != nullptr) ptr->printVehicle();
  }

  void printObjectPool() {
    Vehicle::printObjectPool();
  }
};

int main_Factory()
{
  Client A(HondaType);
  A.getVehicleName();
  A.printObjectPool();


  Client B(HondaType);
  B.getVehicleName();
  B.printObjectPool();

  return 0;
}

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


/*-----------------------Decorator Pattern----------------------------------
Attach additional responsibilities to an object dynamically, without changing the content of the object itself.
instead we can wrap it with another object.

when to use:
You want to add behavior or state to individual objects at run - time.
Inheritance is not feasible because it is static and applies to an entire class.
*/

class Gun {
public:
  virtual int cost() = 0; //pure virtual function
};

class AK47: public Gun {
private:
  const int AK47_Cost = 47;
public:
  int cost() override {
    return AK47_Cost; //47 dollars
  }
};


class AddOns : public Gun { //is a gun
private:
  Gun* GunPtr; //has a gun

public:
  AddOns(Gun& GunObj) {
    this->GunPtr = &GunObj;
  }

  //Delegate cost functionality to the Gun Base class which will calls the derived AK47 class
  int cost() {
    return GunPtr->cost(); //return the value of the base case (cost of gun)
  }
};

//A scope addone for the gun
class Scope : public AddOns { //AddOns is a Gun because AddOns is a gun
private:
  const int ScopeCost = 8;
public:
  Scope(Gun& GunObj) : AddOns(GunObj) {};
  int cost() {
    //return whatever the current Gun Cost is + the ScopeCost
    return AddOns::cost() + ScopeCost;
  }
};

//A magazine clip addone for the gun
class Magazine : public AddOns { //Magazine is a gun because AddOns is a gun
private:
  const int MagazineCost = 2;
public:
  Magazine(Gun& GunObj) : AddOns(GunObj) {};
  int cost() {
    return AddOns::cost() + MagazineCost;
  }
};

int main_Decrator()
{
  //create a normal AK47 gunObject
  AK47 AK47_Gun;
  cout << "Cost of AK47_Gun = " << AK47_Gun.cost() << endl; //47

  //Add a scope to the AK47 Gun
  Scope AK47_Gun_Scoped(AK47_Gun);
  cout << "Cost of AK47_Gun + Scope = " << AK47_Gun_Scoped.cost() << endl; //47 + 8 == 55

  //Add a magazine to the scoped AK47 Gun
  Magazine AK47_Gun_Magazine(AK47_Gun);
  cout << "Cost of AK47_Gun + Magazine = " << AK47_Gun_Magazine.cost() << endl; //47+2 = 49
  
  //Now we can create an AK47 with a scope and a magazine, we will choose to add a mag to the already scoped AK47 Gun
  Magazine AK47_Gun_Scoped_Magazine(AK47_Gun_Scoped);
  cout << "Cost of AK47_Gun + Scope + Magazine = " << AK47_Gun_Scoped_Magazine.cost() << endl; //47+8+2 = 57

  //Now add a double magazine to the already scoped+magazined AK47 Gun
  Magazine AK47_Gun_Scoped_Magazine_Magazine(AK47_Gun_Scoped_Magazine);
  cout << "Cost of AK47_Gun + Scope + Magazine + Magazine = " << AK47_Gun_Scoped_Magazine_Magazine.cost() << endl;

  return 0;
}

/*-----------------------Adapter Pattern----------------------------------
Intent
Adapter is a way to connect two things that are otherwise incompatible.
it is about defining a mapping between the new and the old.
*/

// Legacy component
class OldAPI {
  string data;
public:
  OldAPI(string s) {
    data = s;
  }
  void OldAPI_Print() {
    cout << "OldAPI printing : " << data << endl;
  }
};


class Adapter : private OldAPI {
public:
  //take in the new data, format it, then supply it to the old api interface
  Adapter(string s): OldAPI(formatData(s)){
  }
  string formatData(string s) {
    return s+s;
  }
  void NewAPI_Print() {
    OldAPI::OldAPI_Print();
  }
};

int main_Adapter() {
  Adapter NewApi("{12345}"); //NewAPI calles OldAPI internally
  NewApi.NewAPI_Print();
  return 0;
}

/*-----------------------Strategy Pattern----------------------------------
Define a family of algorithms, encapsulate each one, and make them interchangeable. 
Strategy lets the algorithm vary independently from the clients that use it.
Capture the abstraction in an interface, bury implementation details in derived classes.
*/

int main() {

}