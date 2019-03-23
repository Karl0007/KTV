#include"Controller.h"
using MyKTV::Controller;


int main()
{
	Controller &con = Controller::getInstance();
	con.First();
	con.Login();
	con.Last();
	return 0;
}