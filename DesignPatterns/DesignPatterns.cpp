#include "pch.h"
#include <iostream>

//Creational Designs are all about class instantiation or object creation
//They include Factory Method, Abstract Factory, Builder, Singleton, Object Pool, and Prototype

//Structural Design Patterns are about organizing different classes and objects to form larger structures,
//they include patterns such as Adapter, Bridge, Composite, Decorator, Facade, Flyweight, Private Class Data, and proxy

//Behavorial are about indentifying common communication patterns between objects and realizing these patterns.
//they include chain of responsbility, command, interpreter , iterator, mediator, memento, Null object, observer, state, Strategy,
//template method, visitor.


//******************** Singleton Pattern ********************
/*
The Singleton pattern is a design pattern that restricts the instantiation
of a class to one object.
*/

class SingleTon
{
private:
   static SingleTon obj;
   SingleTon();
public:

};


int main()
{
   SingleTon st;
   return 0;
}