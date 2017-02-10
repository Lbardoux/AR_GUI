/**
 * @file
 */
#include "Player.hpp"

Player::Player(nite::UserTracker & user_tracker) : m_user_tracker(user_tracker)
{}

bool Player::update()
{
	//On choppe une frame
	nite::UserTrackerFrameRef user_tracker_frame;
	nite::Status status = m_user_tracker.readFrame(&user_tracker_frame);
	if(status != nite::STATUS_OK)
	{
		printf("GetNextData failed\n");
		one_player_visible = false;
		return false;
	}

	//On choppe les utilisateurs
	const nite::Array<nite::UserData>& users = user_tracker_frame.getUsers();

	//On vérifie qu'il n'y en a qu'un avant de le garder
	unsigned int nb_users = users.getSize();
	if(nb_users != 1) 
	{
		one_player_visible = false;
		return false;
	}
	m_user = &(users[0]);

	//Si il est nouveau, on commence à le traquer
	if(m_user->isNew())
	{
		m_user_tracker.startSkeletonTracking(m_user->getId());
		m_user_tracker.startPoseDetection(m_user->getId(), nite::POSE_CROSSED_HANDS);
	}

	one_player_visible = true;
	return true;
}

bool Player::isVisible() const
{
	return (m_user->isVisible() && one_player_visible);
}

Point Player::getPointOf(PlayerMember member) const
{
	nite::Point3f point = getPositionOf(member);
	return Point(point.x, point.y, point.z);
}

nite::Point3f Player::getPositionOf(PlayerMember member) const
{
	if(!isVisible() || !one_player_visible) return nite::Point3f();
	switch(member)
	{
		case HEAD: 
			return getPositionOf(nite::JOINT_HEAD);
		case NECK:
			return getPositionOf(nite::JOINT_NECK);
		case TORSO:
			return getPositionOf(nite::JOINT_TORSO);
		case LEFT_SHOULDER:
			return getPositionOf(nite::JOINT_LEFT_SHOULDER);
		case LEFT_ELBOW:
			return getPositionOf(nite::JOINT_LEFT_ELBOW);
		case LEFT_HAND:
			return getPositionOf(nite::JOINT_LEFT_HAND);
		case RIGHT_SHOULDER:
			return getPositionOf(nite::JOINT_RIGHT_SHOULDER);
		case RIGHT_ELBOW:
			return getPositionOf(nite::JOINT_RIGHT_ELBOW);
		case RIGHT_HAND: 
			return getPositionOf(nite::JOINT_RIGHT_HAND);
		case LEFT_HIP:
			return getPositionOf(nite::JOINT_LEFT_HIP);
		case LEFT_KNEE:
			return getPositionOf(nite::JOINT_LEFT_KNEE);
		case RIGHT_HIP:
			return getPositionOf(nite::JOINT_RIGHT_HIP);
		case RIGHT_KNEE:
			return getPositionOf(nite::JOINT_RIGHT_KNEE);
		default:
			assert(false);
	}
}

nite::Point3f Player::getPositionOf(nite::JointType member) const
{
	nite::Point3f point = m_user->getSkeleton().getJoint(member).getPosition();
}

