#include "tkMath.h"

namespace tk {
	namespace math {
		
		/************************************************************************************************************************
		************************************************************************************************************************/
		
		Mat3::Mat3() {
			SetIdentity();
		}
		//TODO: create sin and cos instead of using standered math lib
		void Mat3::SetRotateX(float angle) {
			SetIdentity();
			m_col2.y = (float)cos(angle); m_col2.z = (float)sin(angle);
			m_col3.y = (float)-sin(angle); m_col3.z = (float)cos(angle);
		}
		void Mat3::SetRotateY(float angle) {
			SetIdentity();
			m_col1.x = (float)cos(angle); m_col1.z = (float)-sin(angle);
			m_col3.x = (float)sin(angle); m_col3.z = (float)cos(angle);
		}
		void Mat3::SetRotateZ(float angle) {
			SetIdentity();
			m_col1.x = (float)cos(angle); m_col1.y = (float)sin(angle);
			m_col2.x = (float)-sin(angle); m_col2.y = (float)cos(angle);
		}
		void Mat3::SetIdentity() {
			m_col1 = { 1, 0, 0 };
			m_col2 = { 0, 1, 0 };
			m_col3 = { 0, 0, 1 };
		}

		Mat3 Mat3::operator*(Mat3 other) {
			return Mat3(0);
		}

		Vec3 Mat3::operator*(Vec3 other) {
			return Vec3(
				other.x * m_col1.x + other.y * m_col1.y + other.z * m_col1.z,
				other.x * m_col2.x + other.y * m_col2.y + other.z * m_col2.z,
				other.x * m_col3.x + other.y * m_col3.y + other.z * m_col3.z
			);
		}

		Vec3 Mat3::operator[](int index) {
			switch (index) {
			case 0: return m_col1;
			case 1:	return m_col2;
			case 2:	return m_col3;
			default: return Vec3(0);
			}
		}

		/************************************************************************************************************************
		************************************************************************************************************************/

		Mat4::Mat4() {
			SetIdentity();
		}
		void Mat4::SetRotateX(float angle) {
			SetIdentity();
			m_col2.y = (float)cos(angle); m_col2.z = (float)sin(angle);
			m_col3.y = (float)-sin(angle); m_col3.z = (float)cos(angle);
		}
		void Mat4::SetRotateY(float angle) {
			SetIdentity();
			m_col1.x = (float)cos(angle); m_col1.z = (float)-sin(angle);
			m_col3.x = (float)sin(angle); m_col3.z = (float)cos(angle);
		}
		void Mat4::SetRotateZ(float angle) {
			SetIdentity();
			m_col1.x = (float)cos(angle); m_col1.y = (float)sin(angle);
			m_col2.x = (float)-sin(angle); m_col2.y = (float)cos(angle);
		}
		void Mat4::SetIdentity() {
			m_col1 = { 1, 0, 0, 0 };
			m_col2 = { 0, 1, 0, 0 };
			m_col3 = { 0, 0, 1, 0 };
			m_col4 = { 0, 0, 0, 1 };
		}

		Mat4 Mat4::operator*(Mat4 other) {
			return Mat4(0);
		}
		Vec4 Mat4::operator*(Vec4 other) {
			return Vec4(
				other.x * m_col1.x + other.y * m_col1.y + other.z * m_col1.z + other.w * m_col1.w,
				other.x * m_col2.x + other.y * m_col2.y + other.z * m_col2.z + other.w * m_col2.w,
				other.x * m_col3.x + other.y * m_col3.y + other.z * m_col3.z + other.w * m_col3.w,
				other.x * m_col4.x + other.y * m_col4.y + other.z * m_col4.z + other.w * m_col4.w
			);

		}
		Vec4 Mat4::operator[](int index) {
			switch (index) {
			case 0: return m_col1;
			case 1:	return m_col2;
			case 2:	return m_col3;
			case 3:	return m_col4;
			default: return Vec4(0);
			}
		}

		Mat4 Mat4::PerspectiveFOV(double fov, double aspect, double dNear, double dFar) {
			double D2R = 3.14159 / 180.0;
			double yScale = 1.0 / tan(D2R * fov / 2);
			double xScale = yScale / aspect;
			double nearmfar = dNear - dFar;
			Mat4 m = {
				math::Vec4{ (float)xScale, 0, 0, 0 },
				math::Vec4{0, (float)yScale, 0, 0},
				math::Vec4{0, 0, (float)(dFar + dNear) / (float)nearmfar, -1},
				math::Vec4{0, 0, 2 * (float)dFar*(float)dNear / (float)nearmfar, 0 }
			};
			return m;
		}
		
		/************************************************************************************************************************
		************************************************************************************************************************/

		Vec3 operator*(Vec3 index) {
			return Vec3();
		}

		float* Vec2::operator[](int index) {
			switch (index) {
			case 0: return &x;
			case 1: return &y;
			default:
				return nullptr;
			}
		}

		float* Vec3::operator[](int index) {
			switch (index) {
			case 0: return &x;
			case 1: return &y;
			case 2: return &z;
			default:
				return NULL;
			}
		}

		float* Vec4::operator[](int index) {
			switch (index) {
			case 0: return &x;
			case 1: return &y;
			case 2: return &z;
			case 3: return &w;
			default:
				return NULL;
			}
		}

}
}