// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "RenderEngine.h"

using namespace RenderEngineNS;

int main()
{
	std::cout << "Console Alive" << std::endl;

	{
		RenderEngine engine;
	}
	

	system("pause");
    return 0;
}

