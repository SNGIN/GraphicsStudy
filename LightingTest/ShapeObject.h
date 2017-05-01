#pragma once
#include "ShapeElements.h"
#include "Material.h"
#include "PhysicsInclude.h"

class ShapeObject:public ShapeElements
{
protected:
	//描画に使用する情報(頂点とか頂点インデックスとか)
	ShapeElements* m_Elements;
	//マテリアル
	Material* m_Material;

	//メッシュ情報(TODO:コンストラクタでメッシュデータの登録)

public:
	ShapeObject();
	~ShapeObject();

	void MaterialSet(Material* mat);

	Material* GetMaterial(){
		//std::cout << m_Material << std::endl;
		return m_Material;
	}

};

