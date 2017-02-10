/**
 * @file
 */
#include "Clothe.hpp"

Clothe::Clothe(Player & player, PlayerMember member1, PlayerMember member2, const Mesh & mesh) : 
	m_player(player), m_member1(member1), m_member2(member2), m_mesh(mesh)
{}

void Clothe::draw() const
{
	Point position1 = m_player.getPointOf(m_member1);
	Point position2 = m_player.getPointOf(m_member2);
	Vector v_translate = Vector(center(position1, position2));
	Vector p1_p2 = Vector(position2, position1);

	float scale = length(p1_p2) * 1.0;
	Transform model = Scale(scale, scale, scale) /* Rotate(angle(p1_P2))*/ * Translation(v_translate);
	m_mesh.draw();
}