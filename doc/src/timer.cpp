inline void Start()
{
	asm volatile 
	(  
		"cpuid\n\t"
		"rdtsc\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t" : "=r"(time_edx), "=r"(time_eax) ::
		"%rax", "%rbx", "%rcx", "%rdx"
	);
}

inline void Stop ()
{
	asm volatile 
	(
		"rdtscp\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t"
		"cpuid\n\t" : "=r"(time_edx1), "=r"(time_eax1) ::
		"%rax", "%rbx", "%rcx", "%rdx"
	);
	
	time_last =
		((unsigned long long)(time_edx1) << 32 | 
		(unsigned long long)(time_eax1)) -
		((unsigned long long)(time_edx)  << 32 | 
		(unsigned long long)(time_eax));

	CalcSec();
}
