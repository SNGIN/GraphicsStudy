#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// 変換行列
uniform mat4 mw;                                    // 視点座標系への変換行列
uniform mat4 mc;                                    // クリッピング座標系への変換行列
uniform mat4 mg;                                    // 法線ベクトルの変換行列

// 頂点属性
layout (location = 0) in vec4 pv;                   // ローカル座標系の頂点位置
layout (location = 1) in vec4 nv;                   // 頂点の法線ベクトル

void main(){
	gl_Position =  pv;
}