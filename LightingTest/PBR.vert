#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// 光源
uniform vec4 lamb;       // 環境光成分
uniform vec4 ldiff;       // 拡散反射光成分
uniform vec4 lspec;                                 // 鏡面反射光成分
uniform vec4 pl;          // 位置

// 材質
uniform vec4 kamb;                                  // 環境光の反射係数
uniform vec4 kdiff;                                 // 拡散反射係数
uniform vec4 kspec;                                 // 鏡面反射係数
uniform float kshi;                                 // 輝き係数

// 変換行列
uniform mat4 modelMatrix; 			//モデル行列(ModelMatrix)
uniform mat4 modelViewMatrix;		// モデルビュー行列
uniform mat4 modelViewprojectionMatrix;	   // クリッピング座標系への変換行列
uniform mat4 viewMatrix;			//ビュー行列
uniform mat4 normalMatrix;			//法線ベクトルの行列

// 頂点属性
layout (location = 0) in vec4 pv;                   // ローカル座標系の頂点位置
layout (location = 1) in vec4 nv;                   // 頂点の法線ベクトル

// ラスタライザに送る頂点属性
out vec4 iamb;                                      // 環境光の反射光強度
out vec4 idiff;                                     // 拡散反射光強度
out vec4 ispec;                                     // 鏡面反射光強度

out vec3 vViewPosition;	//頂点位置から視点位置までのベクトル
out vec3 vNormal;			//法線ベクトルの行列で法線変換したもの

void main(){
	vViewPosition = -1.0*(modelViewMatrix * pv).xyz;
	vNormal = (normalMatrix * nv).xyz;
	gl_Position = modelViewprojectionMatrix * pv;

}