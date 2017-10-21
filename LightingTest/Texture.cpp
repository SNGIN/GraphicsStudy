#include "Texture.h"


Texture::Texture()
{
	//テクスチャオブジェクトを作る
	glGenTextures(1, &texture);
}

Texture::Texture(GLuint tex):texture(tex){}

/*Texture::Texture(GLsizei width, GLsizei height, GLenum internal = GL_RGBA, GLenum format = GL_RGBA, const GLubyte *image = 0){
	//渡されたポインタを使ってテクスチャメモリへ読み込む

	//テクスチャオブジェクトを作る
	glGenTextures(1, &texture);
	//2Dテクスチャとして使用する宣言
	glBindTexture(GL_TEXTURE_2D, texture);
	//テクスチャのロード
	LoadTexture(width, height, internal, format, image);
}*/

Texture::Texture(char *name, GLenum internal = GL_RGBA){
	//指定した名前ファイルをテクスチャメモリへ読み込む

	//テクスチャオブジェクトを作る
	glGenTextures(1, &texture);
	//2Dテクスチャとして使用する宣言
	glBindTexture(GL_TEXTURE_2D, texture);
	//テクスチャの読み込み
	LoadImage(name, internal);
}

//tgaファイルをメモリに読む
GLuint Texture::LoadImage(const char *name, GLenum internal){
	GLsizei width, height;
	GLenum format;

	const GLubyte* image = LoadTGA(name, &width, &height, &format);
	if (image == NULL)return 0;
	// internal == 0 なら内部フォーマットを読み込んだファイルに合わせる
	if (internal == 0)
	{
		switch (format)
		{
		case GL_BGR:
			internal = GL_RGB;
			break;
		case GL_BGRA:
			internal = GL_RGBA;
			break;
		default:
			internal = format;
			break;
		}
	}

	// テクスチャメモリに読み込む
	const GLuint tex(LoadTexture(width, height, internal, format, image));

	// 画像の読み込みに使ったメモリを解放する
	delete[] image;

	// テクスチャオブジェクト名を返す
	return tex;
}

//tgaファイルを読む
GLubyte* Texture::LoadTGA(const char *name, GLsizei *width, GLsizei *height, GLenum *format){
	// ファイルを開く
	std::ifstream file(name, std::ios::binary);

	// ファイルが開けなかったら戻る
	if (file.fail())
	{
		std::cerr << "Waring: Can't open file: " << name << std::endl;
		return NULL;
	}

	// ヘッダを読み込む(tgaのヘッダ部は18バイト)
	unsigned char header[18];
	file.read(reinterpret_cast<char *>(header), sizeof header);

	// ヘッダの読み込みに失敗したら戻る
	if (file.bad())
	{
		std::cerr << "Waring: Can't read file header: " << name << std::endl;
		file.close();
		return NULL;
	}

	// 幅と高さ
	*width = header[13] << 8 | header[12];
	*height = header[15] << 8 | header[14];

	// 深度
	const size_t depth(header[16] / 8);
	switch (depth)
	{
	case 1:
		*format = GL_RED;
		break;
	case 2:
		*format = GL_RG;
		break;
	case 3:
		*format = GL_BGR;
		break;
	case 4:
		*format = GL_BGRA;
		break;
	default:
		// 取り扱えないフォーマットだったら戻る
		std::cerr << "Waring: Unusable format: " << depth << std::endl;
		file.close();
		return NULL;
	}

	// データサイズ
	const size_t size(*width * *height * depth);

	// 読み込みに使うメモリを確保する
	GLubyte *const buffer(new(std::nothrow) GLubyte[size]);

	// メモリが確保できなければ戻る
	if (buffer == NULL)
	{
		std::cerr << "Waring: Too large file: " << name << std::endl;
		file.close();
		return NULL;
	}

	// データを読み込む
	if (header[2] & 8)
	{
		// RLE
		size_t p(0);
		char c;
		while (file.get(c))
		{
			if (c & 0x80)
			{
				// run-length packet
				//TODO:理解が必要
				const size_t count((c & 0x7f) + 1);
				if (p + count * depth > size) break;
				char tmp[4];
				file.read(tmp, depth);
				for (size_t i = 0; i < count; ++i)
				{
					for (size_t j = 0; j < depth;) buffer[p++] = tmp[j++];
				}
			}
			else
			{
				// raw packet
				const size_t count((c + 1) * depth);
				if (p + count > size) break;
				file.read(reinterpret_cast<char *>(buffer + p), count);
				p += count;
			}
		}
	}
	else
	{
		// 非圧縮
		file.read(reinterpret_cast<char *>(buffer), size);
	}

	// 読み込みに失敗していたら警告を出す
	if (file.bad())
	{
		std::cerr << "Waring: Can't read image data: " << name << std::endl;
	}
	// ファイルを閉じる
	file.close();

	// 画像を読み込んだメモリを返す
	return buffer;
}

//紐づけを切ってテクスチャを解放
Texture::~Texture()
{
	if (last()){
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &texture);
	}
}

//使うテクスチャの宣言
void Texture::Use(GLuint loc,GLuint unit=0)const{
	glUniform1i(loc, 0);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}

//テクスチャの開放
void Texture::Release()const{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

//テクスチャの取得
GLuint Texture::Get()const{
	return texture;
}

//テクスチャのロード
GLuint Texture::LoadTexture(GLsizei width, GLsizei height, GLenum internal, GLenum format, const GLubyte *image){
	// アルファチャンネルがついていれば 4 バイト境界に設定する
	glPixelStorei(GL_UNPACK_ALIGNMENT, (format == GL_BGRA || format == GL_RGBA) ? 4 : 1);

	// テクスチャを割り当てる
	glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	// バイリニア（ミップマップなし），エッジでクランプ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

//TODO:矩形クラスを作る(メンバーにテクスチャクラス、シェーダーくらすを持つ四角形オブジェクラス)