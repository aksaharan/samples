#include <iostream>
#include <set>
#include <list>
#include <map>

struct Point {
	long x;
	long y;

	Point() : x(0), y(0) {}
	Point(long lx, long ly) : x(lx), y(ly) {}
};

struct building {
	long x;
	long width;
	long height;
};

// Ths could also be a simple lambda expression
class building_comparer {
public:
	bool operator() (const building& bldg1, const building& bldg2) const {
		long diff = bldg1.x - bldg2.x;
		if (diff == 0) {
			// both buildings start at same x-cordinate, then check for the wider one to come first
			diff = bldg2.width - bldg1.width;
			if (diff == 0) {
				// both building start have same start/end cordinates on x-axis, check for taller to come first
				diff = bldg2.height - bldg1.height;
			}
		}

		return (diff < 0);
	}
};

/*
	A few assumptions made in this implementation:
	- All building are unique in their dimensions of x / y axis
	- If there are building with same x / y dimensions, they are considered to be only one here
	- The X-axis start from 0 and so does Y-axis
	- A building is rectangular and is defined by x-offset, height and width of the building
	- Building is always assumed to start at Y = 0 on Y-axis and at some offset x >= 0 on x-axis
	- Building always has some height defined by Y-axis cordinate i.e. y > 0
*/
class City {
public:
	bool addBldg(const building& bldg) {
		/*
			Could be validating couple of conditions for assumtions and return false
			if these conditions are not met
		*/


		buildings.insert(bldg);
		// Failure to add a bldg because it is duplicate, should not be an error

		for (long i = bldg.x; i <= (bldg.x + bldg.width); ++i) {
			std::map<long, long>::iterator it = heightMap.find(i);
			if (it == heightMap.end()) {
				heightMap[i] = bldg.height;
			} else if (it->second < bldg.height) {
				it->second = bldg.height;
			}
		}
		return true;
	}

	/*
		Return the skyline as a series of points that makeup the skyline
	*/
	std::list<Point> getSkylineByHeights() const {
		std::list<Point> skyline;
		if (heightMap.empty()) {
			// Return empty skyline in case there are no buildings
			return skyline;
		}

		Point prev = {0, 0};
		skyline.push_back(prev);
		for (std::map<long, long>::const_iterator it = heightMap.begin();
				it != heightMap.end();
				++it) {
			if (prev.y == it->second) {
				prev.x = it->first;
				continue;
			}

			if (prev.y > it->second) {
				// Skyline coming down
				skyline.push_back(Point{prev.x, prev.y});
				skyline.push_back(Point{prev.x, it->second});
			} else {
				// Skyline going up
				skyline.push_back(Point{it->first, prev.y});
				skyline.push_back(Point{it->first, it->second});
			}
			prev = {it->first, it->second};
		}

		if (prev.x != 0 && prev.y != 0) {
			skyline.push_back(Point{prev.x, prev.y});
			skyline.push_back(Point{prev.x, 0});
		}

		return skyline;
	}

	void printBuildings() {
		std::cout << "Buldings [";
		for (std::set<building>::const_iterator it = buildings.begin();
				it != buildings.end();
				++it) {
			std::cout << "{(" << it->x << ", 0) - (" << it->x << ", " << it->height
					<< ") - (" << it->x + it->width << ", " << it->height
					<< ") - (" << it->x + it->width << ", 0)}, ";
		}
		std::cout << "]" << std::endl;
	}

private:
	std::set<building, building_comparer> buildings;
	std::map<long, long> heightMap;
};

std::ostream& operator << (std::ostream& out, const std::list<Point>& skyline) {
	std::cout << "Skyline [";
	for (std::list<Point>::const_iterator it = skyline.begin();
			it != skyline.end();
			++it) {
		std::cout << "(" << it->x << ", " << it->y << ") ";
	}
	std::cout << "]" << std::endl;
	return out;
}

int main(void) {
	std::cout << "---- Skyline Problem ----" << std::endl;

	{
		City city;
		city.addBldg({10, 10, 10});
		city.addBldg({15, 25, 5});
		city.addBldg({30, 15, 20});
		city.addBldg({35, 15, 15});

		city.printBuildings();
		std::cout << city.getSkylineByHeights();
	}

	return 0;
}
