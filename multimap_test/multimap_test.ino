#include <xmem.h>

#include <iterator>
#include <string>
#include <map>
#include <serstream>
#include <pnew.cpp>


using namespace std;


void setup() {
  
  xmem::begin(true);
  xmem::setMemoryBank(0, true);
  
  Serial3.begin(9600);
  std::ohserialstream serial(Serial3);


  serial << "\n\r";
  serial << "--------";
  serial << "\n\r";
  
  
  
  std::multimap<int,string> days;
  int i;

  days.insert(pair<int, string>(0, "Sunday"));
  days.insert(pair<int, string>(1, "Monday"));
  days.insert(pair<int, string>(2, "Tuesday"));
  days.insert(pair<int, string>(2, "Wednesday"));
  days.insert(pair<int, string>(4, "Thursday"));
  days.insert(pair<int, string>(5, "Friday"));
  days.insert(pair<int, string>(2, "Saturday"));

  multimap<int, string>::iterator it;

  serial << "\n\r";
  serial << "\n\r";

  for (it = days.begin(); it != days.end(); ++it)
  {
    serial << (*it).first << ", " << (*it).second << std::crlf;
  }

  serial << "\n\r";
  serial << "\n\r";

  pair<multimap<int, string>::iterator, multimap<int, string>::iterator> rng = days.equal_range(2);

  multimap<int, string>::iterator it2;
  for (it2 = rng.first; it2 != rng.second; ++it2)
  {
    serial << (*it2).first << ", " << (*it2).second << "\n\r";
  }
  
  
  serial << "\n\r";
  serial << "\n\r";

  days.erase(2);
  
  for (it = days.begin(); it != days.end(); ++it)
  {
    serial << (*it).first << ", " << (*it).second << std::crlf;
  }
  

}


void loop() {

}

