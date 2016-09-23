#include "Model.h"

// ベクトル
struct vec
{
	float x, y, z;
};

bool Model::FileLoad(const char *name, GLuint &nv, GLfloat(*&pos)[3], GLfloat(*&norm)[3],
	GLuint &nf, GLuint(*&face)[3], bool normalize){
	//OBJファイル読み込み
	std::ifstream file(name, std::ios::binary);

	// ファイルが開けなかったら戻る
	if (file.fail())
	{
		std::cerr << "Error: Can't open OBJ file: " << name << std::endl;
		return false;
	}

	// 一行読み込み用のバッファ
	std::string line;

	// データの数と座標値の最小値・最大値
	float xmin, xmax, ymin, ymax, zmin, zmax;
	xmax = ymax = zmax = -(xmin = ymin = zmin = FLT_MAX);

	// 頂点位置の一時保存
	std::vector<vec> _pos;
	std::vector<faceData> _face;

	// データを読み込む
	while (std::getline(file, line))
	{
		std::istringstream str(line);
		std::string op;
		str >> op;

		

		if (op == "v")
		{
			// 頂点位置
			vec v;

			// 頂点位置はスペースで区切られているので
			str >> v.x >> v.y >> v.z;

			// 位置の最大値と最小値を求める (AABB)
			xmin = std::min(xmin, v.x);
			xmax = std::max(xmax, v.x);
			ymin = std::min(ymin, v.y);
			ymax = std::max(ymax, v.y);
			zmin = std::min(zmin, v.z);
			zmax = std::max(zmax, v.z);

			// 頂点データを保存する
			_pos.push_back(v);
		}
		else if (op == "f")
		{
			// 面データ
			faceData f;

			// 頂点座標番号を取り出す
			for (int i = 0; i < 3; ++i)
			{
				// 1行をスペースで区切って個々の要素の最初の数値を取り出す
				std::string s;
				str >> s;
				f.p[i] = atoi(s.c_str());
			}

			//std::cout << vx << " " << vy << " " << vz << std::endl;

			// 面データを保存する
			_face.push_back(f);
		}
		
	}

	// ファイルの読み込みチェック
	if (file.bad())
	{
		// うまく読み込めなかった
		std::cerr << "Warning: Can't read OBJ file: " << name << std::endl;
	}
	file.close();

	// メモリの確保
	pos = norm = NULL;
	face = NULL;
	nv = _pos.size();
	nf = _face.size();
	try
	{
		pos = new GLfloat[nv][3];
		norm = new GLfloat[nv][3];
		face = new GLuint[nf][3];
	}
	catch (std::bad_alloc e)
	{
		delete[] pos;
		delete[] norm;
		delete[] face;

		pos = norm = NULL;
		face = NULL;

		return false;
	}

	// 位置と大きさの正規化のための係数
	GLfloat scale, cx, cy, cz;
	if (normalize)
	{
		const float sx(xmax - xmin);
		const float sy(ymax - ymin);
		const float sz(zmax - zmin);

		scale = sx;
		if (sy > scale) scale = sy;
		if (sz > scale) scale = sz;
		scale = (scale != 0.0f) ? 2.0f / scale : 1.0f;

		cx = (xmax + xmin) * 0.5f;
		cy = (ymax + ymin) * 0.5f;
		cz = (zmax + zmin) * 0.5f;
	}
	else
	{
		scale = 1.0f;
		cx = cy = cz = 0.0f;
	}

	// 図形の大きさと位置の正規化とデータのコピー
	for (std::vector<vec>::const_iterator it = _pos.begin(); it != _pos.end(); ++it)
	{
		const size_t v = it - _pos.begin();

		pos[v][0] = (it->x - cx) * scale;
		pos[v][1] = (it->y - cy) * scale;
		pos[v][2] = (it->z - cz) * scale;
	}

	// 頂点法線の値を 0 にしておく
	std::fill(static_cast<GLfloat *>(&norm[0][0]), static_cast<GLfloat *>(&norm[nv][0]), 0.0f);

	// 面の法線の算出とデータのコピー
	for (std::vector<faceData>::const_iterator it = _face.begin(); it != _face.end(); ++it)
	{
		const size_t f(it - _face.begin());

		// 頂点座標番号を取り出す
		const GLuint v0(face[f][0] = it->p[0] - 1);
		const GLuint v1(face[f][1] = it->p[1] - 1);
		const GLuint v2(face[f][2] = it->p[2] - 1);

		// v1 - v0, v2 - v0 を求める
		const GLfloat dx1(pos[v1][0] - pos[v0][0]);
		const GLfloat dy1(pos[v1][1] - pos[v0][1]);
		const GLfloat dz1(pos[v1][2] - pos[v0][2]);
		const GLfloat dx2(pos[v2][0] - pos[v0][0]);
		const GLfloat dy2(pos[v2][1] - pos[v0][1]);
		const GLfloat dz2(pos[v2][2] - pos[v0][2]);

		// 外積により面法線を求める
		const GLfloat nx(dy1 * dz2 - dz1 * dy2);
		const GLfloat ny(dz1 * dx2 - dx1 * dz2);
		const GLfloat nz(dx1 * dy2 - dy1 * dx2);

		// 面法線を頂点法線に積算する
		norm[v0][0] += nx;
		norm[v0][1] += ny;
		norm[v0][2] += nz;
		norm[v1][0] += nx;
		norm[v1][1] += ny;
		norm[v1][2] += nz;
		norm[v2][0] += nx;
		norm[v2][1] += ny;
		norm[v2][2] += nz;
	}

	// 頂点法線の正規化
	for (GLuint v = 0; v < nv; ++v)
	{
		// 頂点法線の長さ
		GLfloat a(sqrt(norm[v][0] * norm[v][0] + norm[v][1] * norm[v][1] + norm[v][2] * norm[v][2]));

		// 頂点法線の正規化
		if (a != 0.0)
		{
			norm[v][0] /= a;
			norm[v][1] /= a;
			norm[v][2] /= a;
		}
	}

	return true;
}

Model::Model()
{
}

//モデルを読みこんでメッシュデータをメンバにポインタとして保持
Model::Model(const char *name, bool normalize){
	GLuint nv, nf;
	GLfloat(*pos)[3], (*norm)[3];
	GLuint(*face)[3];

	if (FileLoad(name, nv, pos, norm, nf, face, normalize)){
		m_Elements = new ShapeElements(nv, pos, norm, nf, face, GL_TRIANGLES);
		// 作業用に使ったメモリを解放する
		delete[] pos;
		delete[] norm;
		delete[] face;
	}
	else{
		std::cout << "Model Open Error" << std::endl;
	}
}


Model::~Model()
{
}

void Model::Draw(){
	//シェーダの使用
	m_Material->m_shader->Use();
	//描画
	m_Elements->Draw();
}

void Model::MaterialSet(GLfloat(*amb), GLfloat(*diff), GLfloat(*spec), GLfloat *shi, Shader &shader){
	m_Material = new Material(amb, diff, spec, shi,shader);
}