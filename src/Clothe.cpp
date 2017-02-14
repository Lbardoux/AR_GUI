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

Vector normalize(const Vector & v)
{
	float k = 1/v.normL2();
	return Vector(k * v.x(), k * v.y(), k * v.z());
}

/*
 *Ne pas oublier de demander matrix.normal() à Laurent !
 *
 */

void Clothe::draw(const Point & position1, const Point & position2, const Transform & view, const Transform & projection) const
{
	//La translation
	Vector v_translate = center(position1, position2);
	Vector p1_p2 = position2 - position1;
	Matrix translation_matrix = translationMatrix(v_translate);

	//Le scale
	//float scale = p1_p2.normL2() * 1.0;
	Matrix scale_matrix = scaleMatrix(0.1, 0.1, 0.1);

	//La rotation selon z
	Vector p1_p2_z = Vector(p1_p2.x(), p1_p2.y(), 0); 
	p1_p2_z = normalize(p1_p2_z);
	float cos_angle_z = dot(p1_p2_z, Vector(0, 1, 0));
	float angle_z = acos(cos_angle_z);
	Matrix rotation_z_matrix = rotationZMatrix(angle_z);

	//La rotation selon x
	/*Vector p1_p2_x = Vector(0, p1_p2.y(), 0); 
	float angle_x = dot(p1_p2, Vector(1, 0, 0));
	Matrix rotation_x_matrix = scaleMatrix(0.1, 0.1, 0.1);*/

	Transform model = translation_matrix * rotation_z_matrix * scale_matrix;
	m_mesh.draw(model, view, projection);
}
