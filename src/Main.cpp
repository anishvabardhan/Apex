#include "../tests/Texturing/Code/TextureTest.h"
#include "../Core/Logger.h"

int main()
{
	LOG_INFO << "Application Initialized!";

	TextureTest* Test = new TextureTest();

	Test->Init();

	LOG_INFO << "Application CLosed!";

	return 0;
}