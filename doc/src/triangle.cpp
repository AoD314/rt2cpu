float Triangle::crossing(const Ray & r)
{
	vec4 pos = r.pos();
	vec4 dir = r.dir();
	vec4 t = v0 - pos;
	vec4 q = cross(dir, t);

	vec4 tmp (dot(t, normal), dot(e2, q), dot(e1, q), 0.0f);
	vec4 tuv = tmp * 1.0f / dot (dir, normal);

	int b = ( 
			tuv[0]>=0.0f && 
			tuv[1]>=0.0f && 
			tuv[2]>=0.0f && 
			(tuv[1] + tuv[2] <= 1.0f
		));
	return b*tuv[0] + b - 1;
}
