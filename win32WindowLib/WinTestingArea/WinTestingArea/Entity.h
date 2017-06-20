#pragma once
#include "tkGraphics.h"

#include "tkexception.h"

namespace game {
	class Entity {
	public:
		Entity() {}
		virtual~Entity() = 0 {}
		virtual void Update() {
			m_entRect.SetRect(
				tk::math::Vec2{ m_entPos.x, m_entPos.y },
				tk::math::Vec2{ m_entPos.x + m_entPos.width, m_entPos.y },
				tk::math::Vec2{ m_entPos.x + m_entPos.width, m_entPos.y + m_entPos.height },
				tk::math::Vec2{ m_entPos.x, m_entPos.y + m_entPos.height }
			);
		}
		virtual void Draw(HDC hdc, HPEN hPen) {
			m_entRect.Draw(hdc, hPen);
		}
		virtual tk::graphics::Rect& rect() { return m_entPos; }
	protected:
		tk::graphics::gRectange m_entRect;
		tk::graphics::Rect m_entPos;
	};
}