#include"pch.h"
#include"CollisionManager.h"

//���Ƌ��̓����蔻��
bool CollisionManager::DetectCollisionSphereToSphere(SphereCollider& sphere1, SphereCollider& sphere2)
{
	//���S�Ԃ̋����̕������v�Z
	DirectX::SimpleMath::Vector3 dist1 = sphere1.GetCenter() - sphere2.GetCenter();
	float dist2 = dist1.Dot(dist1);
	//�������������������������a�̍��v�����������ꍇ�ɋ��͂������Ă���
	float radiusSum = sphere1.GetRadius() + sphere2.GetRadius();
	return dist2 <= radiusSum * radiusSum;
}

//�{�b�N�X�ƃ{�b�N�X�̏Փ˔���֐�
bool CollisionManager::DetectCollisionBoxToBox(BoxCollider& box1, BoxCollider& box2)
{
	//���S�_�Ɣ��a����v�Z����
	if (fabsf(box1.GetCenter().x - box2.GetCenter().x) > (box1.GetRadius().x + box2.GetRadius().x)) return false;
	if (fabsf(box1.GetCenter().y - box2.GetCenter().y) > (box1.GetRadius().y + box2.GetRadius().y)) return false;
	if (fabsf(box1.GetCenter().z - box2.GetCenter().z) > (box1.GetRadius().z + box2.GetRadius().z)) return false;
	return true;
}