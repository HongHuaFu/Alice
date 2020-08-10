#include <RayTracingCPU/Medium.hpp>
#include <RayTracingCPU/Random.hpp>

namespace Alice::RayTracingCPU
{
	bool Medium_Constant::Intersect(const Ray& r,float t0,float t1,Hit& hit) const
	{
		Hit rec1, rec2;
		auto infinity = std::numeric_limits<float>::infinity();
		if (!boundary->Intersect(r, -infinity, infinity, rec1))
			return false;

		if (!boundary->Intersect(r, rec1.t+0.0001f, infinity, rec2))
			return false;

		if (rec1.t < t0) rec1.t = t0;
		if (rec2.t > t1) rec2.t = t1;

		if (rec1.t >= rec2.t)
			return false;

		if (rec1.t < 0)
			rec1.t = 0;

		const auto ray_length = r.GetDirection().length();
		const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
		const auto hit_distance = neg_inv_density * log(Random::GetRandom1d());

		if (hit_distance > distance_inside_boundary)
			return false;

		hit.t = rec1.t + hit_distance / ray_length;
		hit.pos = r.At(hit.t);

		
		hit.normal = vec3(1,0,0);  // arbitrary
		hit.material = phase_function;

		return true;
	}
}