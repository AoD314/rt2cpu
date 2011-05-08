inline vec4 Engine::reflect(const vec4 & n, const vec4 & i)
{
	return i - 2.0f * n * dot (n, i);
}
