/**
 * @file
 */
#include "Player.hpp"
#include "Matrix.hpp"

Player::Player() : m_user_tracker(), m_user_tracker_frame(), one_player_visible(false)
{}

Player::Player(Camera & camera) : one_player_visible(false)
{
	init(camera);
}

void Player::init(Camera & camera)
{
	openni::Device & device = camera.getDevice();
    mtl::log::info("Initialisation de NiTE ...", mtl::log::hold_on());
	nite::NiTE::initialize();
    mtl::log::info("Fait!");

    //Création du tracker
    //m_user_tracker = nite::UserTracker;
    if(m_user_tracker.create(&device) != nite::STATUS_OK)
    {
        mtl::log::error("Failed to create tracker");
        assert(false);
    }

    mtl::log::info("Player initialisé");
}

bool Player::update()
{
	//On choppe une frame
	one_player_visible = false;

    if(!m_user_tracker.isValid())
        return false;

    nite::Status status = m_user_tracker.readFrame(&m_user_tracker_frame);/////////////////////////////////////////////
    if(status != nite::STATUS_OK)
    {
        mtl::log::warning("GetNextData failed");
		return false;
	}

    //On choppe les utilisateurs
    const nite::Array<nite::UserData>* users = &m_user_tracker_frame.getUsers();

    //On vérifie qu'il n'y en a qu'un avant de le garder
    unsigned int nb_users = users->getSize();
    if(nb_users < 1) 
    {
        return false;
    }
    m_user = &((*users)[0]);

    //Si il est nouveau, on commence à le traquer
    if(m_user->isNew())
    {
        m_user_tracker.startSkeletonTracking(m_user->getId());
		m_user_tracker.startPoseDetection(m_user->getId(), nite::POSE_PSI);
    }

    one_player_visible = true;
    return true;
}

bool Player::isVisible() const
{
    return (one_player_visible && m_user->isVisible());
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
        case LEFT_FOOT:
            return getPositionOf(nite::JOINT_LEFT_FOOT);
        case RIGHT_FOOT:
            return getPositionOf(nite::JOINT_RIGHT_FOOT);
        default:
            assert(false);
    }
}

nite::Point3f Player::getPositionOf(nite::JointType member) const
{
    return m_user->getSkeleton().getJoint(member).getPosition();
}

nite::Point3f Player::getCameraPositionOf(PlayerMember member) const
{
	nite::Point3f afterConversion;
	nite::Point3f beforeConversion = getPositionOf(member);
	m_user_tracker.convertJointCoordinatesToDepth(	beforeConversion.x, beforeConversion.y, beforeConversion.z, 
													&afterConversion.x, &afterConversion.y);
	//return afterConversion;
	afterConversion.x *= 2;
	afterConversion.y *= 2;
	return afterConversion;
}

Point Player::getPointOf(PlayerMember member) const
{
    nite::Point3f point = getPositionOf(member);
    return Point(-point.x, point.y, point.z);
}

void f(const Point & p)
{
    glVertex3f(p.x(), p.y(), p.z());
}

void Player::draw() const
{
    glBegin(GL_LINES);
    	f(getPointOf(HEAD)); f(getPointOf(NECK));
    	f(getPointOf(LEFT_ELBOW)); f(getPointOf(LEFT_ELBOW));
    	f(getPointOf(LEFT_SHOULDER)); f(getPointOf(LEFT_HAND));
   		f(getPointOf(RIGHT_ELBOW)); f(getPointOf(RIGHT_ELBOW));
    	f(getPointOf(RIGHT_SHOULDER)); f(getPointOf(RIGHT_HAND));
    	f(getPointOf(LEFT_SHOULDER)); f(getPointOf(RIGHT_SHOULDER));
    	f(getPointOf(LEFT_SHOULDER)); f(getPointOf(TORSO));
    	f(getPointOf(RIGHT_SHOULDER)); f(getPointOf(TORSO));
    	f(getPointOf(TORSO)); f(getPointOf(LEFT_HIP));
    	f(getPointOf(TORSO)); f(getPointOf(RIGHT_HIP));
    	f(getPointOf(LEFT_HIP)); f(getPointOf(RIGHT_HIP));
    	f(getPointOf(LEFT_HIP)); f(getPointOf(LEFT_KNEE));
    	f(getPointOf(LEFT_KNEE)); f(getPointOf(LEFT_FOOT));
    	f(getPointOf(RIGHT_HIP)); f(getPointOf(RIGHT_KNEE));
    	f(getPointOf(RIGHT_KNEE)); f(getPointOf(RIGHT_FOOT));
    glEnd();
}
