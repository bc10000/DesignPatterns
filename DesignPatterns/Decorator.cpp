#include "pch.h"

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

class AK47 : public Gun {
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
