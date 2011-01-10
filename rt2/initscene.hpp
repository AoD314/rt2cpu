
	vec4 cam_pos(6.0f , 0.0f ,  2.0f  , 0.0f);
	vec4 cam_dir(0.0f , 0.0f ,  2.0f  , 0.0f);
	vec4 cam_upd(6.0f , 0.0f ,  3.0f  , 0.0f);


	vec4 mat_amb(0.25f , 0.25f , 0.25f , 0.0f);
	vec4 mat_spc(0.55f , 0.55f , 0.55f , 0.0f);
	vec4 mat_dif(0.95f , 0.95f , 0.95f , 0.0f);
	vec4 mat_ref(0.95f , 0.95f , 0.95f , 0.0f);
	vec4 mat_rf2(0.35f , 0.35f , 0.35f , 0.0f);
	vec4 mat_rf0(0.00f , 0.00f , 0.00f , 0.0f);


	// for mirror
	vec4 mat_mir_a(0.05f , 0.05f , 0.05f , 0.0f);
	vec4 mat_mir_d(0.15f , 0.15f , 0.15f , 0.0f);
	vec4 mat_mir_s(1.00f , 1.00f , 1.00f , 0.0f);
	vec4 mat_rfm  (1.00f , 1.00f , 1.00f , 0.0f);

	Camera cam (cam_pos, cam_dir, cam_upd, _w, _h, pi/3.0f);

	vec4 Red(1, 0, 0, 0);
	TextureColor tc1(Red);
	MaterialSimple mtr1;
	mtr1.AddTexture(&tc1);
	mtr1.SetColor(mat_amb, mat_dif, mat_spc, mat_rf2, 32);

	vec4 Green(0, 1, 0, 0);
	TextureColor tc2(Green);
	MaterialSimple mtr2;
	mtr2.AddTexture(&tc2);
	mtr2.SetColor(mat_amb, mat_dif, mat_spc, mat_rf2, 32);

	vec4 Blue(0, 0, 1, 0);
	TextureColor tc3(Blue);
	MaterialSimple mtr3;
	mtr3.AddTexture(&tc3);
	mtr3.SetColor(mat_amb, mat_dif, mat_spc, mat_rf2, 32);

	vec4 Black(0.0f, 0.0f, 0.0f, 0);
	TextureColor tc4(Black);
	MaterialSimple mirror;
	mirror.AddTexture(&tc4);
	mirror.SetColor(mat_mir_a, mat_mir_d, mat_mir_s, mat_rfm, 32);

	vec4 Grey(0.95f, 0.95f, 0.95f, 0);
	TextureColor tc5(Grey);
	MaterialSimple mtr5;
	mtr5.AddTexture(&tc5);
	mtr5.SetColor(mat_amb, mat_dif, mat_spc, mat_rf0);



	vec4 pl01_pos   ( 2, 0, 0, 0);
	vec4 pl01_normal( 3, 0, 0, 0);
	Plane pl01(pl01_pos, pl01_normal);
	pl01.SetMaterial(&mtr5);

	vec4 pl02_pos   ( 0, 0, 0, 0);
	vec4 pl02_normal( 0, 0, 1, 0);
	Plane pl02(pl02_pos, pl02_normal);
	pl02.SetMaterial(&mtr5);


	//-- kernel --//

	float RAD = 0.85f;

	Sphere  sp1(2.0f,  2.0f, 2.0f, RAD);
	sp1.SetMaterial(&mtr1);

	Sphere  sp2    (2.0f,  0.0f, 2.0f, RAD);
	vec4 pos_sp2(2.0f,  0.0f, 2.0f, 0.0f);
	sp2.SetMaterial(&mtr2);

	Sphere  sp3(2.0f, -2.0f, 2.0f, RAD);
	sp3.SetMaterial(&mtr3);

	//vec4 pos_sr(3.61f, 0.3f, 3.57f, 0.0f);

	//-- electrons --//

	float rade = 0.25f;

/*
	Sphere  sp6(0, 0, 0, rade);
	vec4 sp6_pos = pos_sr;
	sp6.SetMaterial(&mtr2);

	Sphere  sp7(0, 0, 0, rade);
	vec4 sp7_pos = pos_sr;
	sp7.SetMaterial(&mtr2);

	Sphere  sp8(0, 0, 0, rade);
	vec4 sp8_pos = pos_sr;
	sp8.SetMaterial(&mtr2);

	Sphere  sp9(0, 0, 0, rade);
	vec4 sp9_pos = pos_sr;
	sp9.SetMaterial(&mtr2);

	Sphere  sp10(0, 0, 0, rade);
	vec4 sp10_pos = pos_sr;
	sp10.SetMaterial(&mtr2);
*/

	Scene s1(cam);

	/////////////////////////////////////////////////////////////////

	int N = _lights;

	vec4 light01_a (0.05f/(float)N , 0.05f/(float)N , 0.05f/(float)N , 0.0f);
	vec4 light01_s (1.00f/(float)N , 1.00f/(float)N , 1.00f/(float)N , 0.0f);
	vec4 light01_d (0.85f/(float)N , 0.85f/(float)N , 0.85f/(float)N , 0.0f);

	vec4 light_pos;

	Lights ** ln  = new_memory<Lights*>(N);

	for (int i=0; i<N; i++)
	{
		light_pos.set(5.0f,(2.0f * (float)i/(float)N) - 1.0f, 4.0f, 0.0f);
		ln[i] = new_memory<PointLight>(1);
		ln[i]->settings(light_pos, light01_a, light01_s, light01_d);
	}

	/////////////////////////////////////////////////////////////////


	vec4 orange(1.00f, 0.75f, 0.5f, 0);
	TextureColor tc6(orange);
	MaterialSimple mtr6;
	mtr6.AddTexture(&tc6);
	mtr6.SetColor(mat_mir_a, mat_mir_d, mat_mir_s, mat_ref, 32);

	vec4 a(8.0f,   0.0f, -4.0f, 0.0f);
	vec4 b(0.0f,   8.0f, -4.0f, 0.0f);
	vec4 c(-8.0f, -8.0f, 8.0f, 0.0f);

	Triangle tr(a,b,c);
	tr.SetMaterial(&mtr6);

	/////////////////////////////////////////////////////////////////


	s1.AddPrimitives(&tr);

	s1.AddPrimitives(&sp1);
	s1.AddPrimitives(&sp2);
	s1.AddPrimitives(&sp3);
	//s1.AddPrimitives(&sp4);
	//s1.AddPrimitives(&sp5);

	/*
	s1.AddPrimitives(&sp6);
	s1.AddPrimitives(&sp7);
	s1.AddPrimitives(&sp8);
	s1.AddPrimitives(&sp9);
	s1.AddPrimitives(&sp10);
*/
	s1.AddPrimitives(&pl01);
	s1.AddPrimitives(&pl02);

//	for (int i=0; i<N; i++)
//		s1.AddLight(ln[i]);

	s1.AddLights(ln, N);

	//s1.AddLight(&l01);
	//s1.AddLight(&l02);
	//s1.AddLight(&l03);
	//s1.AddLight(&l04);

	//////////////////////////////////////////////////////////////////
