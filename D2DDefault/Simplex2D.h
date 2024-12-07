#pragma once
#include "Vector3.h"


struct Simplex2D
{
private:
	std::array<Vector3, 3> m_points;
	unsigned m_size;

public:
	Simplex2D()
		:m_points({ Vector3(),Vector3(),Vector3() })
		, m_size(0)
	{
	}

	Simplex2D& operator = (std::initializer_list<Vector3> list)
	{
		for (auto v = list.begin(); v != list.end(); v++)
		{
			m_points[std::distance(list.begin(), v)] = *v;
		}
		m_size = list.size();

		return *this;
	}

	void push_front(Vector3 _point)
	{
		m_points = { _point, m_points[0], m_points[1] };
		m_size = min(m_size + 1, 3u);
	}

	Vector3& operator[](unsigned i) { return m_points[i]; }
	unsigned size() const { return m_size; }
	auto begin() const { return m_points.begin(); }
	auto end() const { return m_points.end() - (3 - m_size); }
};