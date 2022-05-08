#include <iostream>
#include <vector>
#include "Entity.h"
#include "Topology.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "* Simulador Algoritmos Distribuídos" << endl;

	Topology top{10,4,1.0};
	cout << top << endl;

	Simulator sim{top};
	sim.start(1);
}
