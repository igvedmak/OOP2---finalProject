#include "Constants.h"
#include "GameManager.h"
//-----------------------Main Functions------------------------------------
int main() try
{
	GameManager game;    
	game.run();                   // run the editor program
	return(EXIT_SUCCESS);	
}
catch (std::exception& e) { // handle with the throw from std::exception
	std::cout << ER << e.what() << std::endl;
	std::cin.get();
	exit(EXIT_FAILURE);
}

catch (...)// handle any other throw
{
	std::cout << UNKNOW << std::endl;
	std::cin.get();
}