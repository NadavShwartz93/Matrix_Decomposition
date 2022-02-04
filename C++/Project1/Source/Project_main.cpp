#include "../Header/Project_main.hpp"

int main() {

	Project_main* runner = new Project_main();

	runner->run_project();

	delete runner;
	system("PAUSE");

	return 0;
}