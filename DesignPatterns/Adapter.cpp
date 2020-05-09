#include "pch.h"
#include <iostream>

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
  Adapter(string s) : OldAPI(formatData(s)) {
  }
  string formatData(string s) {
    return s + s;
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