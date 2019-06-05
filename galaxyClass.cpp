// galaxyClass
// a class that defines galaxy objects with the parameters [hubbleType, Redshift, totalMass, stellarMassFraction]
// Elliot Goodwin
// OOP - Assignment 4
// 18/02/19

// Class information:
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
using namespace std;

// -------- Class definition ----------------------------------------------------------
// ------------------------------------------------------------------------------------
// Galaxy
// A class that stores information about the hubble type, redshift, total mass and mass fraction of a galaxy
class Galaxy {

// private (hidden from main program)
private:

	// declare variables
	string hubbleType;           // E0, E1, E2, E3, E4, E5, E6, E7, S0, Sa, Sb, Sc, SBa, SBb, SBc, Irr
	double redshift;             // redshift [0, 10]
	double totalMass;            // totalMass [1e7, 1e12] (solar units)
	double stellarMassFraction;  // f_* [0, 0.05]
	vector<Galaxy> mySatellites; // vector containing a galaxy's satellites (galaxy objects)

	// private function prototypes
	void checkGalaxyValues();    // check galaxy object has valid input parameters

// public (accessible from main program)
public:

	// constructors
	// default constructor
	Galaxy() : hubbleType("SBb"), redshift(0), totalMass(0), stellarMassFraction(0.01) {};
	// parameterised constructor (initalise galaxy object with specified values)
	Galaxy(string a, double b, double c, double d) : hubbleType(a), redshift(b), totalMass(c), stellarMassFraction(d) { checkGalaxyValues(); };

	// default destructor
	~Galaxy() { cout << "Galaxy has been deleted." << endl; };

	// functions kept inside class since they are simple
	// functions for setting parameters in the object belonging to Galaxy class
	void setType(string newType) { hubbleType = newType; checkGalaxyValues(); }
	void setRedshift(double newRedshift) { redshift = newRedshift; checkGalaxyValues(); }
	void settotalMass(double newtotalMass) { totalMass = newtotalMass; checkGalaxyValues(); }
	void setstellarMassFraction(double newstellarMassFraction) { stellarMassFraction = newstellarMassFraction; checkGalaxyValues(); }
	// functions for returning parameters in the object belonging to Galaxy class
	string getType() { return hubbleType; }
	double getRedshift() { return redshift; }
	double getTotalMass() { return totalMass; }
	double getstellarMassFraction() { return stellarMassFraction; }

	// prototype functions
	double getStellarMass();                                         // get stellar mass
	void printData();                                                // print the contents of an object
	void printData(vector<Galaxy> myGalaxies);                       // print a vector of galaxies
	void addSatellite(Galaxy mySatellites);                          // add a satellite galaxy to a vector of satellites
	void printData(bool printSatellites);                            // if printSatellites == true, prints satellite obejcts

};




// ----------- Member function definitions --------------------------------------------
// ------------------------------------------------------------------------------------
// checkGalaxyValues
// a function that checks that galaxy objects have values within a valid range, and 
// defaults to the values [SBb, 0, 8E11, 0.01] otherwise
void Galaxy::checkGalaxyValues() {
	if (hubbleType == "E0" || hubbleType == "E1" || hubbleType == "E2" || hubbleType == "E3" ||
	               hubbleType == "E4" || hubbleType == "E5" || hubbleType == "E6" || hubbleType == "E7" ||
	               hubbleType == "S0" || hubbleType == "Sa" || hubbleType == "Sb" || hubbleType == "Sc" ||
				   hubbleType == "SBa" || hubbleType == "SBb" || hubbleType == "SBc" || hubbleType == "Irr") {}
	else { 
		cout << "Error. Invalid Hubble type." << endl;
		cout << "Defaulting to SBb." << endl;
		setType("SBb"); 
    }
	if (redshift < 0 || redshift > 10) {
		cout << "Error. Invalid redshift." << endl;
		cout << "Defaulting to z = 0." << endl;
		setRedshift(0);
	}
	if (totalMass < 1E7 || totalMass > 1E12) {
		cout << "Error. Invalid total mass." << endl;
		cout << "Defaulting to M_tot = 8E11*M_sun." << endl;
		settotalMass(8E11);
	}
	if (stellarMassFraction < 0 || stellarMassFraction > 0.05) {
		cout << "Error. Invalid stellar mass fraction." << endl;
		cout << "Defaulting to f_* = 0.01." << endl;
		setstellarMassFraction(0.01);
	}
};

// printData
// a member function to the Galaxy class that prints out the details of an object
void Galaxy::printData() {
	// set precision to 2 dp
	cout.setf(ios::scientific, ios::floatfield);
	cout << "[" << getType() << ", " << std::setprecision(2) << getRedshift() << ", " << 
		std::setprecision(2) << getTotalMass() << ", " << std::setprecision(2) << 
		getstellarMassFraction() << "]" << endl;  // prints [hubbleType, redshift, totalMass, stellarMassFraction]
}
void Galaxy::printData(bool printSatellites) {
	cout << "Galaxy information:" << endl;
	printData();
	cout << endl;
	if (printSatellites == true) {
		if (!mySatellites.empty()) {
			cout << "Satellites information:" << endl;
			cout << "Galaxy contains " << mySatellites.size() << " satellte(s)." << endl;
			for (vector<Galaxy>::iterator it = mySatellites.begin(); it != mySatellites.end(); it++)
			    it->printData();
		}
		else {
			cout << "No satellite information found." << endl;
		}
	}
} // specify if satellites objects should also be printed

// a version of printData that prints a vector of Galaxies
void printData(vector<Galaxy> myGalaxies) {
	// set precision to 2 dp
	cout.setf(ios::scientific, ios::floatfield);
	if (!myGalaxies.empty()) {
		for (vector<Galaxy>::iterator it = myGalaxies.begin(); it != myGalaxies.end(); it++) {
			cout << "[" << it->getType() << ", " << std::setprecision(2) << it->getRedshift() 
				<< ", " << std::setprecision(2) << it->getTotalMass() << ", " << std::setprecision(2) 
				<< it->getstellarMassFraction() << "]" << endl;
		}
	}
	// prints [hubbleType, redshift, totalMass]
}

// getStellarMass
// a mumber function to the Galaxy class that returns the Stellar mass, (M_* = f_* x M_tot)
double Galaxy::getStellarMass() {
	double stellarMass = stellarMassFraction * totalMass;
	return stellarMass;
}

// addSatellite
// a member function that adds a satellite to a vector of satellite objects
void Galaxy::addSatellite(Galaxy satelliteGalaxy) { mySatellites.push_back(satelliteGalaxy); }




// ----------- Main program -----------------------------------------------------------
// ------------------------------------------------------------------------------------
int main()
{

	// Example using default constructor
	Galaxy g1;
	cout << "Print contents of g1:" << endl;
	g1.printData();
	cout << endl;

	// Example using a pointer
	Galaxy *ptr_g1 = &g1;
	cout << "Print contents of a pointer to g1:" << endl;
	ptr_g1->printData();
	cout << endl;

	// Example using parameterised constructor
	Galaxy g2("Irr", 4.2, 1.9E9, 0.01);
	// print g2 type
	string type = g2.getType();
	cout << "g2 type: " << type << endl; 

	// print out g2 data
	cout << "\nPrint contents of g2:" << endl;
	g2.printData();

	// Get and print out stellar mass
	cout << "g2_stellarMass = " << g2.getStellarMass() << endl;

	// Change Hubble type from Irr to S0
	if (g2.getType() == "Irr") {
		cout << "\nChanging type of g2..." << endl;
		g2.setType("S0");
	}

	// print g2 Data
	cout << "g2 information:" << endl;
	g2.printData();

	// Example of constructor checking for valid input
	cout << "\ng3 information:" << endl;
	Galaxy g3("hello", 11, 1.9E15, 0.6);
	g3.printData();

	// Example using vectors to store multiple Galaxy objects
	vector<Galaxy> myGalaxies;
	myGalaxies.push_back(g1);
	myGalaxies.push_back(g2);

	// Print contents of myGalaxies
	cout << "\nPrinting vector of galaxies:" << endl;
	// element by element
	myGalaxies[0].printData();
	myGalaxies[1].printData();
	cout << endl; // formatting

	// or through a function that iterates over all elements of myGalaxies
	printData(myGalaxies);
	cout << endl;

	// add satellite galaxies
	// initialise satellite galaxies
	cout << "Initialising satellite galaxies." << endl;
	Galaxy g1s1("SBa", 1.9, 8.3E8, 0.03);
	Galaxy g1s2("E3", 1.3, 9.2E11, 0.04);

	cout << "Creating vector of satellite galaxies." << endl;
	g1.addSatellite(g1s1);
	g1.addSatellite(g1s2);
	cout << endl;

	// print satellite objects
	bool printSatellites{ true };
	g1.printData(printSatellites);

	return 0;
}
