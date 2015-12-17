#include "btPhysicSystem.h"

#if _DEBUG
#pragma comment(lib,"BulletCollision_Debug.lib")
#pragma comment(lib,"BulletDynamics_Debug.lib")
#pragma comment(lib,"LinearMath_Debug.lib")
#endif

//Bullet Demos : BasicDemoを参考

#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Y 8
#define ARRAY_SIZE_Z 2

#define MAX_PROXIES (ARRAY_SIZE_X*ARRAY_SIZE_Y*ARRAY_SIZE_Z + 1024)

#define SCALING 1.
#define START_POS_X -5
#define START_POS_Y -5
#define START_POS_Z -3

Physics::Physics()
{
	_config = std::make_shared<btDefaultCollisionConfiguration>();
	_dispatcher = std::make_shared<btCollisionDispatcher>(_config.get());
	_broadphase = std::make_shared<btDbvtBroadphase>();
	_solver = std::make_shared<btSequentialImpulseConstraintSolver>();

}

Physics::~Physics()
{
	Exit();
}

void Physics::Init()
{
	// 地面作成、ワールドに追加
	{
		// コリジョン形状　箱
		btBoxShape* ground_shape = new btBoxShape(btVector3(btScalar(80.0f), btScalar(80.0f), btScalar(80.0f)));
		aCollisionShapes.push_back(ground_shape);

		btTransform ground_pos;
		ground_pos.setIdentity();
		ground_pos.setOrigin(btVector3(0, -80, 0));

		// 動かないので質量0　慣性0
		btScalar mass(0.0f);
		btVector3 inertia(0, 0, 0);
		
		btDefaultMotionState* motion_state = new btDefaultMotionState(ground_pos);
		btRigidBody::btRigidBodyConstructionInfo rb_cinfo(mass, motion_state, ground_shape, inertia);
		btRigidBody* body = new btRigidBody(rb_cinfo);
	}

	{
	btBoxShape* colBox = new btBoxShape(btVector3(SCALING * 1, SCALING * 1, SCALING * 1));
	btCollisionShape* colSphere = new btSphereShape(SCALING*btScalar(1.));
	btCapsuleShape* colCapsule = new btCapsuleShape(SCALING*1.0f, SCALING*2.0f);
	aCollisionShapes.push_back(colBox);
	aCollisionShapes.push_back(colSphere);
	aCollisionShapes.push_back(colCapsule);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar	mass(1.f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertiaBox(0, 0, 0);
	btVector3 localInertiaSphere(0, 0, 0);
	btVector3 localInertiaCapsule(0, 0, 0);
	if (isDynamic){
		colBox->calculateLocalInertia(mass, localInertiaBox);
		colSphere->calculateLocalInertia(mass, localInertiaSphere);
		colCapsule->calculateLocalInertia(mass, localInertiaCapsule);
	}
	float start_x = START_POS_X - ARRAY_SIZE_X / 2;
	float start_y = START_POS_Y;
	float start_z = START_POS_Z - ARRAY_SIZE_Z / 2;

	for (int k = 0; k<ARRAY_SIZE_Y; k++)
	{
		for (int i = 0; i<ARRAY_SIZE_X; i++)
		{
			for (int j = 0; j<ARRAY_SIZE_Z; j++)
			{
				startTransform.setOrigin(SCALING*btVector3(
					btScalar(2.0*i + start_x),
					btScalar(20 + 2.0*k + start_y),
					btScalar(2.0*j + start_z)));

				btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
				btRigidBody* body = nullptr;
				switch ((k + i + j) % 3){
				case 0:
					body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
						mass, myMotionState, colBox, localInertiaBox));
					break;
				case 1:
					body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
						mass, myMotionState, colSphere, localInertiaSphere));
					break;
				case 2:
					body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
						mass, myMotionState, colCapsule, localInertiaCapsule));
					break;
				}
			}
		}
	}
}
}

void Physics::Exit()
{
/*	int i;
	for (i = _world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = _world->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		_world->removeCollisionObject(obj);
		delete obj;
	}

	for (int j = 0; j<aCollisionShapes.size(); j++)
	{
		btCollisionShape* shape = aCollisionShapes[j];
		delete shape;
	}

	aCollisionShapes.clear();*/
}

