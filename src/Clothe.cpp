/**
 * @file
 */
#include "Clothe.hpp"

Clothe::Clothe(const Player & player, PlayerMember member1, PlayerMember member2, const Mesh & mesh) : 
    m_player(player), m_member1(member1), m_member2(member2), m_mesh(mesh)
{}

void Clothe::draw(const Transform & view, const Transform & projection) const
{
    Point position1 = m_player.getPointOf(m_member1);
    Point position2 = m_player.getPointOf(m_member2);
    draw(position1, position2, view, projection);
}

float dot(Vector v1, Vector v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Transform rotationMatrix(const float angle, Vector& axis)
{
    Vector a= axis.normalize();
    float s= sinf(angle);
    float c= cosf(angle);

    return Transform(
        a.x() * a.x() + (1 - a.x() * a.x() ) * c,
        a.x() * a.y() * (1 - c ) - a.z() * s,
        a.x() * a.z() * (1 - c ) + a.y() * s,
        0,

        a.x() * a.y() * (1 - c ) + a.z() * s,
        a.y() * a.y() + (1 - a.y() * a.y() ) * c,
        a.y() * a.z() * (1 - c ) - a.x() * s,
        0,

        a.x() * a.z() * (1 - c ) - a.y() * s,
        a.y() * a.z() * (1 - c ) + a.x() * s,
        a.z() * a.z() + (1 - a.z() * a.z() ) * c,
        0,

        0, 0, 0, 1);
}

Vector scale_product(Vector & u, Vector & v)
{
    return Vector(
        (u.y() * v.z()) - (u.z() * v.y()),
        (u.z() * v.x()) - (u.x() * v.z()),
        (u.x() * v.y()) - (u.y() * v.x()));
}

void Clothe::draw(const Point & position1, const Point & position2, const Transform & view, 
    const Transform & projection) const
{
    //La translation
    Vector v_translate = center(position1, position2);
    Vector p1_p2 = position2 - position1;
    Matrix translation_matrix = translationMatrix(v_translate);

    //Le scale
    float scale_with_proportion = p1_p2.normL2() * 0.52;
    Matrix scale_matrix = scaleMatrix(scale_with_proportion, scale_with_proportion, scale_with_proportion);

    //La rotation selon z
    Vector p1_p2_z = Vector(p1_p2.x(), p1_p2.y(), 0).normalize(); 
    float cos_angle_z = dot(p1_p2_z, Vector(1, 0, 0));
    float angle_z = acos(cos_angle_z);
    if(position1.y() > position2.y()) angle_z = -angle_z;
    Matrix rotation_z_matrix = rotationZMatrix(angle_z);

    
    /*//Vector normal = Vector(cos(angle_z + M_PI/2), sin(angle_z + M_PI/2), 0);
    Vector normal = Vector(cos(0 + M_PI/2), sin(0 + M_PI/2), 0);//OK
    //std::cout<<"normal 				: "<<normal.x()<<" "<<normal.y()<<" "<<normal.z()<<" "<<std::endl;
    Vector p1_p2_proj = ( p1_p2 + (normal * (-dot(p1_p2, normal))) ).normalize();//OK
    				 	//(http://forum.mathematex.net/exercices-problemes-superieur-f18/projection-d-un-point-sur-un-plan-t923.html)
    Vector z = Vector(0, 0, 1);
    Vector osef = scale_product(normal, z);
    float cos_angle_proj = dot(p1_p2_proj, osef);
    std::cout<<"p1_p2_proj 			: "<<p1_p2_proj.x()<<" "<<p1_p2_proj.y()<<" "<<p1_p2_proj.z()<<" "<<std::endl;
    std::cout<<"cos_angle_proj		: "<<cos_angle_proj<<std::endl;
    float angle_proj = acos(cos_angle_proj);
    std::cout<<"angle_proj avant	: "<<angle_proj * 180 / M_PI<<std::endl;
    //if(dot(p1_p2, z) < 0) angle_proj = -angle_proj;
    angle_proj += M_PI;
    if(angle_proj < 0) angle_proj += 2 * M_PI;
    std::cout<<"angle_proj apres	: "<<angle_proj * 180 / M_PI<<std::endl;
    Matrix rotation_proj_matrix = rotationYMatrix(angle_proj);//rotationMatrix(angle_proj, normal);
    Matrix rotation_proj_matrix = rotationYMatrix(0);*/

    Transform model = translation_matrix * rotation_z_matrix * /* rotation_proj_matrix */ scale_matrix;
    m_mesh.draw(model, view, projection);
}
