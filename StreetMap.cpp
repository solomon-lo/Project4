#include <string>
#include "ExpandableHashMap.h"
#include <vector>
#include <functional>
#include "provided.h"

//from file i/o writeup on UCLA cs32 website
#include <iostream> // needed for any I/O
#include <fstream>  // needed in addition to <iostream> for file I/O
#include <sstream>  // needed in addition to <iostream> for string stream I/O

using namespace std;

unsigned int hash(const GeoCoord& g)
{
	return std::hash<string>()(g.latitudeText + g.longitudeText);
}

class StreetMapImpl
{
public:
	StreetMapImpl();
	~StreetMapImpl();
	bool load(string mapFile);
	bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
	ExpandableHashMap<GeoCoord, StreetSegment> GeoCoordToStreetSegmentHashMap;
	vector<StreetSegment> vectorOfStreetSegments;
};

StreetMapImpl::StreetMapImpl()
{
}

StreetMapImpl::~StreetMapImpl()
{
}

bool StreetMapImpl::load(string mapFile)
{
	ifstream infile(mapFile);
	if (!infile)
	{
		cerr << "Error: the StreetMapImpl() function in StreetMap.cpp can't open mapdata.txt!" << endl;
		return false;
	}

	string s;
	while (getline(infile, s))
	{
		StreetSegment tempStreetSegment;
		StreetSegment reveresedTempStreetSegment;	//the same as tempStreetSegment, but it's actually has switched end and start coordinates
		tempStreetSegment.name = s;
		reveresedTempStreetSegment.name = s;

		int numOfSegmentsOnStreet = 0;
		infile >> numOfSegmentsOnStreet;
		infile.ignore(10000, '\n');
		for (int i = 0; i < numOfSegmentsOnStreet; i++)
		{
			getline(infile, s);
			string X_X_ForStartCoord = s.substr(0, s.find(" "));
			string Y_Y_ForStartCoord = s.substr(s.find(" ") + 1, s.find(" "));

			GeoCoord startGeoCoord(X_X_ForStartCoord, Y_Y_ForStartCoord);
			tempStreetSegment.start = startGeoCoord;
			reveresedTempStreetSegment.end = startGeoCoord;

			s = s.substr(s.find(Y_Y_ForStartCoord) + 1, s.size() - 1);
			string X_X_ForEndingCoord = s.substr(0, s.find(" "));
			string Y_Y_ForEndingCoord = s.substr(s.find(" ") + 1, s.size() - 1);


			GeoCoord endGeoCoord(X_X_ForEndingCoord, Y_Y_ForEndingCoord);
			tempStreetSegment.end = endGeoCoord;
			reveresedTempStreetSegment.start = endGeoCoord;

			vectorOfStreetSegments.push_back(tempStreetSegment);
			vectorOfStreetSegments.push_back(reveresedTempStreetSegment);
		}

	}
	return true;	//if everything works to plan , this will return true since it reaches end of the text file.

}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
	for (int i = 0; i < vectorOfStreetSegments.size(); i++)
	{
		bool foundAtLeastOneMatchingSegment = false;
		if (vectorOfStreetSegments[i].start == gc)
		{
			segs.push_back(vectorOfStreetSegments[i]);
			foundAtLeastOneMatchingSegment = true;
		}
		return foundAtLeastOneMatchingSegment;
	}
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
	m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
	delete m_impl;
}

bool StreetMap::load(string mapFile)
{
	return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
	return m_impl->getSegmentsThatStartWith(gc, segs);
}

int main()
{
	StreetMapImpl thing;
	thing.load("mapdata.txt");
}
