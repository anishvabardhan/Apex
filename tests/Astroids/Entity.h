#pragma once

namespace Apex {

	class Entity
	{
	protected:
		virtual void OnUpdate(float dt) = 0;
		virtual void Render() = 0;
	};

}