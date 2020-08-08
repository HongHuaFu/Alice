#pragma once
#include <Shape.hpp>
#include <memory>
#include <AABB.hpp>
#include <Scene.hpp>

namespace Alice
{
	class BVH_Node : public Shape
	{
	public:
		std::shared_ptr<Shape> left;
		std::shared_ptr<Shape> right;
		AABB box;
	public:
		BVH_Node() = default;
		BVH_Node(Scene& scene, float time0, float time1) : BVH_Node(scene.shapes, 0, scene.shapes.size(), time0, time1)
		{}

		// 在这里构建BVH树
		BVH_Node(std::vector<std::shared_ptr<Shape>>& shapes,size_t start,size_t end,float time0,float time1)
		{
			// 随机选择分割轴
			int axis = Random::GetRandom1dInt(0,2);
			auto comparator = (axis == 0) ? BBox_X_Compare : (axis == 1) ? BBox_Y_Compare : BBox_Z_Compare;

			auto object_span = end - start;

			// 退化情况 只有一个物体
			if (object_span == 1) 
			{
				left = right = shapes[start];
			} 
			else if (object_span == 2)// 退化情况 只有两个个物体
			{
				if (comparator(shapes[start], shapes[start+1]))
				{
					left = shapes[start];
					right = shapes[start+1];
				}
				else 
				{
					left = shapes[start+1];
					right = shapes[start];
				}
			} 
			else 
			{
				// 排序
				std::sort(shapes.begin() + start, shapes.begin() + end, comparator);

				auto mid = start + object_span/2;

				// 分而治之
				left = std::make_shared<BVH_Node>(shapes, start, mid, time0, time1);
				right = std::make_shared<BVH_Node>(shapes, mid, end, time0, time1);
			}

			AABB box_left, box_right;

			if (  !left->GetBBox (time0, time1, box_left) || !right->GetBBox(time0, time1, box_right) )
				std::cerr << "No bounding box in bvh_node constructor.\n";

			box = SurroundingBox(box_left, box_right);
		}

		virtual bool Intersect(const Ray& r,float tmin,float tmax,Hit& rec) const override
		{
			if (!box.Intersect(r, tmin, tmax))
				return false;

			// 递归式遍历
			bool hit_left = left->Intersect(r, tmin, tmax, rec);
			bool hit_right = right->Intersect(r, tmin, hit_left ? rec.t : tmax, rec);

			return hit_left || hit_right;
		}

		virtual bool GetBBox(float t0,float t1,AABB& output_box) const override
		{
			output_box = box;
			return true;
		}
	};
}