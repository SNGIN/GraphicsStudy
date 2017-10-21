#pragma once
class File
{
public:
	File();
	File(const char* filename);
	~File();
	int GetSize() const;
	const char* GetData() const;
	unsigned GetUnsigned(int position) const;
private:
	int mSize;
	char* mData;
};

