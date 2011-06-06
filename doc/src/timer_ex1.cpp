int main(int argc, char ** argv)
{
	size_t count = 100;
	Timer timer(mode_sum);

	for (size_t i = 0; i < count; i++)
	{
		timer.Start();
		work1();
		timer.Stop();
		something1();
	}

	size_t tt1 = timer.GetTotalTimeInTick();
	timer.Reset();

	for (size_t i = 0; i < count; i++)
	{
		timer.Start();
		work2();
		timer.Stop();
		something2();
	}

	size_t tt2 = timer.GetTotalTimeInTick();

	cout << "time: " << tt1 << ", " << tt2 << endl;
	return 0;
}
