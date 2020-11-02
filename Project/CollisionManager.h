//“–‚½‚è”»’è‚ð‚·‚éƒNƒ‰ƒX
#pragma once
#include"BoxCollider.h"
#include"SphereCollider.h"
#include<memory>

class CollisionManager
{
public:
	bool DetectCollisionSphereToSphere(SphereCollider& sphere1, SphereCollider& sphere2);
	bool DetectCollisionBoxToBox(BoxCollider& box1, BoxCollider& box2);
};