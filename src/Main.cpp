#include "../tests/Texturing/Code/TextureTest.h"
#include "../Core/Logger.h"

int main()
{
	LOG_INFO << "Test Initialized!";

	TextureTest* Test = new TextureTest();

	Test->Init();

	LOG_INFO << "Test Concluded!";

	return 0;
}