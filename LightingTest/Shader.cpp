#include "Shader.h"

static GLchar *ReadShaderSource(const char *name){
	//ファイル名がNULLならNULLを返す
	if (name == NULL)return NULL;

	// ソースファイルを開く
	std::ifstream file(name, std::ios::binary);
	if (file.fail())
	{
		// 開けなかった
		std::cerr << "Error: Can't open source file: " << name << std::endl;
		return NULL;
	}

	// ファイルの末尾に移動しファイルサイズを得る
	file.seekg(0L, std::ios::end);
	GLsizei length(static_cast<GLsizei>(file.tellg()));


	// ファイルサイズのメモリを確保
	GLchar *buffer(new(std::nothrow) GLchar[length + 1]);
	if (buffer == NULL)
	{
		// メモリ不足
		std::cerr << "Error: Too large file: " << name << std::endl;
		file.close();
		return NULL;
	}

	// ファイルを先頭から読み込む
	file.seekg(0L, std::ios::beg);
	file.read(buffer, length);
	buffer[length] = '\0';

	if (file.bad())
	{
		// うまく読み込めなかった
		std::cerr << "Error: Could not read souce file: " << name << std::endl;
		delete buffer;
		buffer = NULL;
	}
	file.close();

	// 読み込んだソースプログラムのメモリ
	return buffer;
}

GLuint CreateShader(const char *vsrc, const char *fsrc, const char *gsrc,
	GLint nvarying, const char **varyings, const char *vtext, const char *ftext, const char *gtext){

	//空のプログラムオブジェクト
	const GLuint program(glCreateProgram());

	if (program > 0){
		if (vsrc != NULL){
			//バーテックスシェーダオブジェクトの作成
			const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
			glShaderSource(vobj, 1, &vsrc, NULL);
			glCompileShader(vobj);

			//バーテックスシェーダをアタッチ
			if (printShaderInfoLog(vobj, vtext)){
				glAttachShader(program, vobj);
			}
			glDeleteShader(vobj);
		}

		if (fsrc != NULL){
			//フラグメントシェーダオブジェクトの作成
			const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
			glShaderSource(fobj, 1, &fsrc, NULL);
			glCompileShader(fobj);

			//フラグメントシェーダをアタッチ
			if (printShaderInfoLog(fobj, ftext)){
				glAttachShader(program, fobj);
			}
			glDeleteShader(fobj);
		}

		if (gsrc!=NULL)
		{
			// ジオメトリシェーダのシェーダオブジェクトを作成
			const GLuint geomShader(glCreateShader(GL_GEOMETRY_SHADER));
			glShaderSource(geomShader, 1, &gsrc, NULL);
			glCompileShader(geomShader);

			// ジオメトリシェーダのシェーダをあタッチ
			if (printShaderInfoLog(geomShader, gtext)){
				glAttachShader(program, geomShader);
			}
			glDeleteShader(geomShader);
		}

		if (nvarying > 0){
			glTransformFeedbackVaryings(program, nvarying, varyings, GL_SEPARATE_ATTRIBS);
		}

		//プログラムオブジェクトのリンク
		glLinkProgram(program);
	}

	//作成したプログラムオブジェクトを返す
	if (printProgramInfoLog(program)){
		return program;
	}
	else{
		glDeleteProgram(program);
		return 0;
	}
}

GLuint LoadShader(const char *vert, const char *frag, const char *geom,
	GLint nvarying, const char **varyings){
	// シェーダのソースファイルを読み込む
	const GLchar *const vsrc(ReadShaderSource(vert));
	const GLchar *const fsrc(ReadShaderSource(frag));
	const GLchar *const gsrc(ReadShaderSource(geom));

	// プログラムオブジェクトを作成する
	const GLuint program(CreateShader(vsrc, fsrc, gsrc, nvarying, varyings, vert, frag, geom));

	// ソースファイルの読み込みに使ったメモリを解放する
	delete[] vsrc;
	delete[] fsrc;
	delete[] gsrc;

	// 作成したプログラムオブジェクトを返す
	return program;
}

void Shader::loadMatrix(const Matrix &mp, const Matrix &mw){
	// 変換
	glUniformMatrix4fv(loc_matrix.mc, 1, GL_FALSE, (mp * mw).get());
	glUniformMatrix4fv(loc_matrix.mw, 1, GL_FALSE, mw.get());
}

static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
	// コンパイル結果を取得する
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

	// シェーダのコンパイル時のログの長さを取得する
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		// シェーダのコンパイル時のログの内容を取得する
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}
	return static_cast<GLboolean>(status);
}

static GLboolean printProgramInfoLog(GLuint program)
{
	// リンク結果を取得する
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

	// シェーダのリンク時のログの長さを取得する
	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		// シェーダのリンク時のログの内容を取得する
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}