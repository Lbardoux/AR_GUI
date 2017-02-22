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

    //La rotation selon x
    Vector p1_p2_y = Vector(p1_p2.x(), 0, p1_p2.z()).normalize(); 
    float cos_angle_y = dot(p1_p2_y, Vector(1, 0, 0));
    float angle_y = acos(cos_angle_y);
    if(position1.z() > position2.z()) angle_y = -angle_y;
    Matrix rotation_y_matrix = rotationYMatrix(angle_y);

    Transform model = translation_matrix * rotation_z_matrix * scale_matrix;
    m_mesh.draw(model, view, projection);
}
