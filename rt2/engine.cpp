

#include "engine.hpp"

namespace engine
{
        Engine::Engine ( Scene& s, unsigned int * vbuffer )
        {
                sc = s;
                vbuf = vbuffer;
                width  = sc.GetCamera ( ).GetWidth ( );
                height = sc.GetCamera ( ).GetHeight ( );
                frame = 0;
                timer = 0;
                alltimer = 0;
                mintimer = std::numeric_limits<size_t>::max ();
        }

        void EngineRT2::SetParts ( int p )
        {
                parts = p;
        }

        inline int EngineRT2::GetParts ( )
        {
                return parts;
        }

        void EngineRT2::SetThreads ( int t )
        {
                threads = t;
        }

        int EngineRT2::GetThreads ( )
        {
                return threads;
        }

        size_t Engine::CountFrame ( )
        {
                return frame;
        }

        size_t Engine::CountTime ( )
        {
                return timer;
        }

        size_t Engine::AllTime ( )
        {
                return alltimer;
        }

        size_t Engine::MinTime ( )
        {
                return mintimer;
        }

        vec4 EngineRT2::Reflect ( vec4& d, vec4& n )
        {
                return d - (2.0f * dot ( n, d )) * n;
        }

        EngineRT2::EngineRT2 ( Scene& s, unsigned int * vbuffer, bool u_bvh ) : Engine ( s, vbuffer )
        {
                parts = 1;
                threads = 1;
                use_bvh = u_bvh;
                depth = 1;
        }

        void EngineRT2::SetDepth ( int d )
        {
                depth = d;
        }

        inline int EngineRT2::GetDepth ( )
        {
                return depth;
        }

        Primitives* EngineRT2::RayTrace ( Ray& R, vec4& color, int depth )
        {
                depth--;

                vec4 point_cross;

                Primitives* p = sc.Crossing ( R, point_cross, use_bvh);

                if ( p == 0 ) return p;

                //std::cout << "\np != 0";

                vec4 normal = p->CalcNormal ( point_cross );

                vec4 reflect = Reflect ( R.Direction ( ), normal );
                reflect.normalize();

                size_t cl = sc.GetCountLight ( );

                float shadow;

                vec4 direct;

                float distance;

                vec4 point_shadow;

                for ( size_t i = 0; i < cl; i++ )
                {
                        shadow = 1.0f;

                        direct = (sc.GetLights ( i )->Position ( ) - point_cross);
                        direct.normalize();

                        distance = CalcDistance ( sc.GetLights ( i )->Position ( ), point_cross );

                        vec4 vtemp;
                        vtemp = point_cross + (direct * 0.0025f);

                        Ray shadowray ( vtemp, direct );

                        Primitives * obj = 0;

                        obj = sc.Crossing ( shadowray, point_shadow );

                        distance -= CalcDistance ( point_shadow, point_cross );

                        if ( obj != 0 && distance > 0.0f ) shadow = 0.0f;

                        color = color +
                                (
                                        (sc.GetLights(i)->GetColor_Ia())*
                                        (p->Materials()->GetColorAmbient())
                                );

                        ////////////////////////////////////////

                        //color += 2*shadow*((p->Materials()->GetColorAmbient()));

                        float temp_dot = dot ( direct, normal ); // (L,N)

                        if ( temp_dot > 0.0f )
                        {
                                //std::cout << point_cross << " = (" << temp_dot << ")\n";
                                //*//
                                color = color +
                                        (
                                        ((temp_dot * shadow)*(p->Materials ( )->GetColorDeffuse ( )))
                                        *
                                        (
                                         (p->Materials ( )->GetColor ( point_cross ))*
                                         (sc.GetLights ( i )->GetColor_Id ( ))
                                         )
                                        );
                                //*/
                        }

                        temp_dot = dot ( R.Direction ( ), Normalize( Reflect ( direct, normal ) ) );

                        if ( temp_dot > 0.0f )
                        {
                                //if (temp_dot>0.45f) std::cout << "+" << temp_dot << "+";

                                color = color + powf ( temp_dot, p->Materials ( )->GetShininess ( ) ) *
                                        p->Materials ( )->GetColorSpecular ( ) * sc.GetLights ( i )->GetColor_Is ( );
                        }

                }


                if ( depth > 0 )
                {
                        vec4 newColor ( 0, 0, 0, 0 );


                        vec4 vtemp;

                        vtemp = point_cross + (reflect * 0.0025f);

                        Ray r ( vtemp, reflect );

                        RayTrace ( r, newColor, depth );

                        color = color + (newColor * p->Materials ( )->GetColorReflection ( ));
                }

                return p;
        }

        void EngineRT2::Rendering ( int p )
        {
                //Timer time;

                if ( threads > 0 )
                        omp_set_num_threads ( threads );

                const int AA = 1;
                const int NN = AA * AA;

                //time.Start();

#ifdef __TBB__

                if ( threads < 1 )
                        threads = 4;

                task_scheduler_init init ( threads );

                static affinity_partitioner ap;

                parallel_for
                        (

                                blocked_range<size_t >
                                (
                                        width * (p - 1) * height / parts,
                                        width * p * height / parts
                                ),

                                [&]( const blocked_range<size_t>& range)
                                {
                                        std::size_t i, j;

                                        vec4 color;
                                        Ray r;

                                        for ( std::size_t ii = range.begin ( ); ii < range.end ( ); ++ii )
                                        {
                                                i = ii / width;
                                                j = ii - i * width;
                                                vbuf[ii] = 0;

                                                for (std::size_t s = 0; s<NN; s++)
                                                {
                                                        color.zero ();

                                                        r = sc.GetCamera ().GenerateRay ( j, i , s, AA);

                                                        this->RayTrace ( r, color, depth );

                                                        color.clamp(0.0f , 1.0f);
                                                        color = color / static_cast<float>(NN);

                                                        vbuf[ii] += ToColor ( color );
                                                }
                                        }

                                }, ap
                        );

#else

                int i, j, s;

                vec4 color;
                Ray r;

                #pragma omp parallel for private(i,j,s,color,r) schedule(static, 2)
                for ( j = (p - 1) * height / parts; j < (p * height / parts); j++ )
                {
                        for ( i = 0; i < width; i++ )
                        {
                                vbuf[(j - (p - 1) * height / parts) * width + i] = 0;

                                for ( s = 0; s < NN; s++)
                                {
                                        color.zero ();

                                        r = sc.GetCamera ().GenerateRay ( i, j , s, AA);

                                        RayTrace ( r, color, depth );

                                        color.clamp( 0.0f, 1.0f);
                                        color = color / static_cast<float>(NN);

                                        vbuf[(j - (p - 1) * height / parts) * width + i] += ToColor(color);
                                }
                        }
                }
#endif

                //time.Stop();

                //timer = time.GetTimeInTick();

                //if ( timer < mintimer ) mintimer = timer;

                //frame++;

                //alltimer += timer;

        }

}
