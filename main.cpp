#include <iostream>
#include <vector>
#include <span>
#include <memory>
#include "Entity.h"
#include "Topology.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
	span args(argv,argc);

	cout << "* Simulador Algoritmos Distribuídos" << endl;
	cout << "* Prof. Luiz Lima Jr." << endl;

	unique_ptr<Topology> topo;

	if (args.size() < 2)
		topo = make_unique<Topology>(10, 4, 1.0);// Topology top{10,4,1.0};
	else
		topo = make_unique<Topology>(args[1]);

	cout << *topo << endl;

	Simulator sim{*topo};
	sim.start(1);
}
