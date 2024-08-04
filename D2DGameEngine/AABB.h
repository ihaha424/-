#pragma once

#include "framework.h"

/*
	AABB (Axis-Aligned Bounding Box) �� ���ĵ� ��� ����

		+y
		^
		|         +----------------------max
		|         |                      |
		|         |		 center        |
		|	        |          +---------- |
		|         |          |  extend.x |
		|         |  extend.y|           |
		|         min--------------------+
	--+------------------------------------> +x
	 0,0
*/
class AABB
{
public:
	AABB() : _center{ 0 }, _extent{ 0 } { }
public:
	Vec2f _center; // �߾�
	Vec2f _extent; // x,y�� Ȯ�尪	
	// minX = _center.x - _extent.x
	// maxX = _center.x + _extent.x
	// minY = _center.y - _extent.y
	// maxY = _center.y + _extent.y

	AABB(const AABB&) = default;
	AABB& operator=(const AABB&) = default;
	AABB(AABB&&) = default;
	AABB& operator=(AABB&&) = default;
	~AABB() = default;

	void SetCenter(float x, float y) { _center = { x, y }; }
	void SetExtent(float x, float y) { _extent = { x, y }; }
	float GetMinX() { return _center.x - _extent.x; }
	float GetMaxX() { return _center.x + _extent.x; }
	float GetMinY() { return _center.y - _extent.y; }
	float GetMaxY() { return _center.y + _extent.y; }

	bool CheckIntersect(const AABB& other) const
	{
		// self min,max
		float BoxA_xmin = _center.x - _extent.x;
		float BoxA_xmax = _center.x + _extent.x;
		float BoxA_ymin = _center.y - _extent.y;
		float BoxA_ymax = _center.y + _extent.y;

		// other min,max
		float BoxB_xmin = other._center.x - other._extent.x;
		float BoxB_xmax = other._center.x + other._extent.x;
		float BoxB_ymin = other._center.y - other._extent.y;
		float BoxB_ymax = other._center.y + other._extent.y;

		// Check for no overlap conditions
		if (BoxA_xmax < BoxB_xmin ||  // �����ʿ� ������ ��ĥ���� ����
			BoxA_xmin > BoxB_xmax ||  // ���ʿ� ������ ��ĥ���� ����
			BoxA_ymax < BoxB_ymin ||  // �Ʒ��� ������ ��ĥ���� ����
			BoxA_ymin > BoxB_ymax)	  // ���� ������ ��ĥ���� ����
		{
			return false;
		}

		return true;
	}
};

