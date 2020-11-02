#include"pch.h"
#include"CollisionManager.h"

//球と球の当たり判定
bool CollisionManager::DetectCollisionSphereToSphere(SphereCollider& sphere1, SphereCollider& sphere2)
{
	//中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 dist1 = sphere1.GetCenter() - sphere2.GetCenter();
	float dist2 = dist1.Dot(dist1);
	//平方した距離が平方した半径の合計よりも小さい場合に球はあたっている
	float radiusSum = sphere1.GetRadius() + sphere2.GetRadius();
	return dist2 <= radiusSum * radiusSum;
}

//ボックスとボックスの衝突判定関数
bool CollisionManager::DetectCollisionBoxToBox(BoxCollider& box1, BoxCollider& box2)
{
	//中心点と半径から計算する
	if (fabsf(box1.GetCenter().x - box2.GetCenter().x) > (box1.GetRadius().x + box2.GetRadius().x)) return false;
	if (fabsf(box1.GetCenter().y - box2.GetCenter().y) > (box1.GetRadius().y + box2.GetRadius().y)) return false;
	if (fabsf(box1.GetCenter().z - box2.GetCenter().z) > (box1.GetRadius().z + box2.GetRadius().z)) return false;
	return true;
}