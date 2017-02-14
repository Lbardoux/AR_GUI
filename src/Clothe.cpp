/**
 * @file
 */
#include "Clothe.hpp"

Clothe::Clothe(Player & player, PlayerMember member1, PlayerMember member2, const Mesh & mesh) : 
	m_player(player), m_member1(member1), m_member2(member2), m_mesh(mesh)
{}

void Clothe::draw(Transform & view, Transform & projection) const
{
	Point position1 = m_player.getPointOf(m_member1);
	Point position2 = m_player.getPointOf(m_member2);
	Vector v_translate = center(position1, position2);
	Vector p1_p2 = position2 - position1;

	float scale = p1_p2.normL2() * 1.0;
	Transform model = scaleMatrix(scale, scale, scale) /* Rotate(angle(p1_P2))*/ * translationMatrix(v_translate);
	m_mesh.draw(model, view, projection);
}
