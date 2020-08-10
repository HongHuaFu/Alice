#include <RayTracingCPU/Translate.hpp>
#include <RayTracingCPU/Ray.hpp>
#include <RayTracingCPU/Hit.hpp>
#include <RayTracingCPU/AABB.hpp>

namespace Alice::RayTracingCPU
{
	bool Translate::Intersect(const Ray& r, float t_min, float t_max, Hit& rec) const 
	{
		Ray moved_r(r.GetOrigin() - offset, r.GetDirection(), r.GetTime());
		if (!ptr->Intersect(moved_r, t_min, t_max, rec))
			return false;

		rec.pos += offset;

		return true;
	}

	bool Translate::GetBBox(float t0, float t1, AABB& output_box) const
	{
		if (!ptr->GetBBox(t0, t1, output_box))
			return false;

		output_box = AABB(
			output_box.GetMin() + offset,
			output_box.GetMax() + offset);

		return true;
	}

	Rotate_Y::Rotate_Y(std::shared_ptr<Shape> p, float angle) : ptr(p) 
	{
		float radians = (pi<float>() / 180.) * angle;
		sin_theta = sin(radians);
		cos_theta = cos(radians);
		auto bbox = AABB();
		hasbox = ptr->GetBBox(0, 1, bbox);
		vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
		vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					float x = i*bbox.GetMax().x + (1-i)*bbox.GetMin().x;
					float y = j*bbox.GetMax().y + (1-j)*bbox.GetMin().y;
					float z = k*bbox.GetMax().z + (1-k)*bbox.GetMin().z;
					float newx = cos_theta*x + sin_theta*z;
					float newz = -sin_theta*x + cos_theta*z;
					vec3 tester(newx, y, newz);
					for ( int c = 0; c < 3; c++ )
					{
						if ( tester[c] > max[c] )
							max[c] = tester[c];
						if ( tester[c] < min[c] )
							min[c] = tester[c];
					}
				}
			}
		}

		box_min = bbox.GetMin();
		box_max = bbox.GetMax();
	}   

	bool Rotate_Y::Intersect(const Ray& r, float t_min, float t_max, Hit& rec) const 
	{
		vec3 origin = r.GetOrigin();
		vec3 direction = r.GetDirection();
		origin[0] = cos_theta*r.GetOrigin()[0] - sin_theta*r.GetOrigin()[2];
		origin[2] =  sin_theta*r.GetOrigin()[0] + cos_theta*r.GetOrigin()[2];
		direction[0] = cos_theta*r.GetDirection()[0] - sin_theta*r.GetDirection()[2];
		direction[2] = sin_theta*r.GetDirection()[0] + cos_theta*r.GetDirection()[2];
		Ray rotated_r(origin, direction, r.GetTime());
		if (ptr->Intersect(rotated_r, t_min, t_max, rec)) {
			vec3 p = rec.pos;
			vec3 normal = rec.normal;
			p[0] = cos_theta*rec.pos[0] + sin_theta*rec.pos[2];
			p[2] = -sin_theta*rec.pos[0] + cos_theta*rec.pos[2];

			normal[0] = cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
			normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];

			rec.pos = p;
			rec.normal = normal;
			return true;
		}
		else 
			return false;
	}

	bool Rotate_Y::GetBBox(float t0, float t1, AABB& output_box) const
	{
		output_box = AABB(box_min,box_max); 
		return hasbox;
	}
}