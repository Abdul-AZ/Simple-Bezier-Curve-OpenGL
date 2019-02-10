#include "Shader.h"

std::string ReadEntireTextFile(const std::string & path)
{
	std::string file_content;

	FILE* file;
	file = fopen(path.c_str(), "r");
	fseek(file, 0, SEEK_END);
	int content_length = ftell(file);
	file_content.resize(content_length + 1);
	fseek(file, 0, SEEK_SET);

	fread((void*)file_content.data(), sizeof(char), content_length, file);

	fclose(file);

	return file_content;
}
