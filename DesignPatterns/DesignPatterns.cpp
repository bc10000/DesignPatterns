#include "pch.h"
#include <iostream>

//Creational Designs are all about class instantiation or object creation
//They include Factory Method, Abstract Factory, Builder, Singleton, Object Pool, and Prototype

//Structural Design Patterns are about organizing different classes and objects to form larger structures,
//they include patterns such as Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Private Class Data, and proxy

//Behavorial are about indentifying common communication patterns between objects and realizing these patterns.
//they include chain of responsbility, command, interpreter , iterator, mediator, memento, Null object, observer, state, Strategy,
//template method, visitor.


//******************** Factory Design Pattern ********************

//The idea is to let the Library do the work and take any creation process away from the client, which will free the cleint
//from the responsibility of creating new objects, and thus freeing it from the burden of recompling.
//the only thing that will need to be recompiled is the libaray itself
//The idea is to use a static member function which creates & returns instances, hiding the details of class modules from user.

enum carTypes { HondaType = 1, ToyotaType = 2 };

class Vehicle {
private:

public:
   virtual void printVehicle() = 0; //pure virtual function which needs to be defined, making this class and abstract class
   static Vehicle* createVehicle(carTypes Type);
};

class Honda : public Vehicle {
public:
   void printVehicle() override { cout << "Honda Car" << endl; }
};

class Toyota : public Vehicle {
public:
   void printVehicle() override { cout << "Toyota Car" << endl; }
};

Vehicle* Vehicle::createVehicle(carTypes Type) {
   switch (Type) {
   case HondaType: return new Honda();
   case ToyotaType: return new Toyota();
   default: return nullptr;
   }
}

//Notice how the creation of the vehicle is handled by the
//Vehicle class which is part of the library.
//the client's job is to only call the createVehicle method
class Client {
private:
   Vehicle* ptr;
public:
   Client(carTypes Type) {
      ptr = Vehicle::createVehicle(Type);
   }
   ~Client() {
      if (ptr != nullptr) {
         delete ptr;
         ptr = nullptr;
      }
   }

   void getVehicle() {
      if(ptr != nullptr) ptr->printVehicle();
   }
};


int main()
{
   Client C(HondaType);
   C.getVehicle();
   return 0;
}