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
  virtual ~Honda() { cout << "Honda destructor is called" << endl; };
};

class Toyota : public Vehicle {
public:
  void printVehicle() override { cout << "Toyota Car"; }
  virtual ~Toyota() { cout << "Toyota destructor is called" << endl; };
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

int main() {

  
}