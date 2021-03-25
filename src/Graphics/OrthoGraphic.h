#pragma once

#include "Maths/Maths.h"

namespace Apex {

	class OrthoGraphic
	{

// Member Variables-------------------------------------------------------------------------------------

		Mat4 m_Proj;
		Mat4 m_View;
		Mat4 m_ViewProj;

		Vec3 m_Position;

		float m_Rotation;
	public:

// Constructors---------------------------------------------------------------------------------------------

		explicit OrthoGraphic(float left, float right, float bottom, float top);

// Methods--------------------------------------------------------------------------------------------------

		const Mat4& GetProjMatrix() const { return m_Proj; }
		const Mat4& GetViewMatrix() const { return m_View; }
		const Mat4& GetViewProjMatrix() const { return m_ViewProj; }

		void SetViewMatrix(Mat4 matrix) { m_View = matrix; }

		const Vec3 GetPosition() const { return m_Position; }
		void SetPosition(const Vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
	private:
		void RecalculateViewMatrix();
	};

}