
#include "bvh-aabb.hpp"

namespace primitives
{

        BoundingVolume buildBoxForObjs(Primitives ** p, size_t size)
        {
                vec4 gmin, gmax;
                for (std::size_t i = 0 ; i < size; i++)
                {
                        vec4 min_v, max_v;
                        Triangle * tr = static_cast<Triangle *>(p[i]);
                        min_v = tr->GetMin();
                        max_v = tr->GetMax();

			gmin = min(min_v, gmin);
                        gmax = max(max_v, gmax);
                }

                return BoundingVolume(gmin, gmax);
        }

        BoundingVolume GetBoxForTriangle (Triangle * tr)
        {
                vec4 min, max;
                min = tr->GetMin();
                max = tr->GetMax();

                return BoundingVolume(min, max);
        }

        NodeBVH * buildBVH(std::vector<Primitives *> v, BoundingVolume b, size_t depth)
        {
                depth--;

                NodeBVH * node = new_memory<NodeBVH>(1);
                node->bv = b;

                if (depth <= 0)
                {
                        node->left = 0;
                        node->right = 0;
                        node->list = v;
                        return node;
                }

                BoundingVolume new_bv0 = b.split (0);
                BoundingVolume new_bv1 = b.split (1);

                std::vector<Primitives*> l1;
                std::vector<Primitives*> l2;


                for (std::size_t i = 0; i < v.size (); i++ )
                {
                        BoundingVolume tmp_bv = GetBoxForTriangle ( static_cast<Triangle*>( v[i] ) );

                        if (new_bv0.is_crossing_b (tmp_bv) == true)
                        {
                                l1.push_back (v[i]);
                        }

                        if (new_bv1.is_crossing_b (tmp_bv) == true)
                        {
                                l2.push_back (v[i]);
                        }
                }

                if (l1.size () > 0)
                        node->left = buildBVH (l1, new_bv0, depth);
                else
                        node->left = 0;

                if (l2.size () > 0)
                        node->right = buildBVH (l2, new_bv1, depth);
                else
                        node->right = 0;


                return node;
        }

        BVH::BVH(Primitives ** p, std::size_t size, std::size_t depth)
        {
                BoundingVolume bv = buildBoxForObjs (p, size);

                std::vector<Primitives*> list;

                for (std::size_t i = 0; i < size; i++ )
                        list.push_back (p[i]);

                root = buildBVH (list, bv, depth);
        }

        Primitives * BVH::BoxCrossing (Ray & r, vec4& point, NodeBVH * node)
        {
                Primitives * p = 0;

                //float near, far;

                //if (node->bv.is_crossing_r (r, near, far) == false) return 0;

                if (node->left != 0)
                        p = BoxCrossing (r,point, node->left);

                if (p == 0)
                {
                        if (node->right != 0)
                                p = BoxCrossing (r, point, node->right);
                }
                else
                        return p;

                float min = std::numeric_limits<float>::max ();
                Primitives * pp = 0;

                for (std::vector<Primitives*>::iterator it = node->list.begin (); it != node->list.end (); it++)
                {
                        float ret = (*it)->Crossing (r, point);

                        if (min > ret)
                        {
                                min = ret;
                                pp = *it;
                        }

                }

                if (pp != 0)
                        return pp;

                return 0;
        }

        Primitives * BVH::crossing (Ray & r, vec4& point)
        {
                return BoxCrossing (r, point, root);
        }

}

