#include "cham.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cham;
void oup(bool s){cout << s << endl;}
int main(){
	event::manager man;
	event::listener lis;
	lis.setResponse("event", oup);
	man.reg("event", &lis);
	man.alert(event::event("event", "data"));
	return 0;
}
