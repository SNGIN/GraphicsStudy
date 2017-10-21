#include "Block.h"


Block::Block()
{
}

Block::Block(GLfloat width, GLfloat height,GLfloat depth,Vector3 pos,Physics* a_physics){
	m_Cube = new CubeObject(Vector3(width, height, depth),"PBR.vert","PBR.frag",ambColor,diffColor,specColor,shiness);	
	rigidBodyIndex = physics->CreateRigidBody(m_Cube->GetVertices(), m_Cube->GetNumvertices(), m_Cube->GetFaces(), m_Cube->GetNumFaces(), Vector3(width, height, depth), MotionType::TypeStatic, pos, 1.0, false);
}

Block::~Block()
{
	Common::Delete(m_Cube);
}

StaticObj* Block::Update(){
	StaticObj* s = this;
	return this;
}

StaticObj* Block::Draw(){
	StaticObj* s = this;
	//シェーダの使用
	m_Cube->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();

	Matrix mp = Window::getMp();
	Quat q = physics->GetRigidBodyState(rigidBodyIndex).m_orientation;
	Matrix mw = mv.rotateQuat(q)*Translate(GetPos().getX(), GetPos().getY(), GetPos().getZ());

	m_Cube->GetMaterial()->GetShader()->loadMatrix(mp, mw, (Translate(GetPos().getX(), GetPos().getY(), GetPos().getZ())));
	//描画
	m_Cube->Draw();
	return s;
}