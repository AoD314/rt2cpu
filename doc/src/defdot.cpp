inline float dot(const vec4 & a, const vec4 & b)
{
	_align_ float res;
	_align_ __m128 m3;
	m3 = _mm_dp_ps(a.data, b.data, 0xF1);
	_mm_store_ss(&res, m3);
	return res;
}
