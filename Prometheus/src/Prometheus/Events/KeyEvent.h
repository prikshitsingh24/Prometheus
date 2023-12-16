#pragma once
#include "ptpch.h"
#include "Event.h"


namespace Prometheus {

	class PROMETHEUS_API KeyEvent:public Event
	{
	public:
		inline int GetKeyCode() const { return m_keyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(int keycode)
			: m_keyCode(keycode){}

		int m_keyCode;
	};

	class PROMETHEUS_API KeyPressedEvent :public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode,int repeatCount)
			:KeyEvent(keycode),m_RepeatCount(repeatCount){}
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent" << m_keyCode << "(" << m_RepeatCount << "repeat)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(keyPressed);
	private:
		int m_RepeatCount;
	};

	class PROMETHEUS_API KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased);
	};
}