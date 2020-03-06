#include "ExpandableHashMap.h"
#include <string>
#include <iostream>
//credit:adapted from Carey Nachenberg's slides

unsigned int hash(const std::string& k, int numOfBuckets)
{
	unsigned int h = 216613261U;
	for (int i = 0; i != k.size(); i++)
	{
		h += k[i];
		h *= 16777619;
	}

	return h % numOfBuckets;
}

int main()
{
	{
		// Define a hashmap that maps strings to doubles and has a maximum
		// load factor of 0.2. It will initially have 8 buckets when empty.
		ExpandableHashMap<std::string, double> nameToGPA(0.25);
		// Add new items to the hashmap. Inserting the third item will cause
	   // the hashmap to increase the number of buckets (since the maximum
	   // load factor is 0.2), forcing a rehash of all items.
		nameToGPA.associate("Carey", 3.5); // Carey has a 3.5 GPA
		nameToGPA.associate("David", 3.99); // David beat Carey
		nameToGPA.associate("Abe", 3.2);
		nameToGPA.associate("Linda", 3.2);// Abe has a 3.2 GPA

		double* davidsGPA = nameToGPA.find("David");
		if (davidsGPA != nullptr)
			*davidsGPA = 1.5; // after a re-grade of David’s exam
		nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0
		// replaces old 3.5 GPA
		double* lindasGPA = nameToGPA.find("Linda");
		if (lindasGPA == nullptr)
			std::cout << "Linda is not in the roster!" << std::endl;
		else
			std::cout << "Linda's GPA is: " << *lindasGPA << std::endl;
	}
}