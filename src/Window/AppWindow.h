#pragma once

#include "Window.h"

namespace Apex {

	class AppWindow : public Window
	{
	public:
		AppWindow();
		~AppWindow();

		// Inherited via Window
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
	};

}