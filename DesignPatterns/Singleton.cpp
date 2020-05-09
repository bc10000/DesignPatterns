#include "pch.h"
#include <iostream>

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

int main()
{
  SingleTon* Obj = SingleTon::getInstance();
  cout << Obj->getName() << endl;
  return 0;
}