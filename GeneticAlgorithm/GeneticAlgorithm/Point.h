#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <vector>

using namespace std;

namespace GA
{
	class CPoint
	{
	public:
		void vAddCoordinate(double dCoordinate);
		double dCalculateDistance(const CPoint& cOther) const;

		const vector<double>& vGetCoordinates() const { return v_coordinates; }

	private:
		const double d_WRONG_DISTANCE_VALUE = -1;

		vector<double> v_coordinates;
	};
}

#endif