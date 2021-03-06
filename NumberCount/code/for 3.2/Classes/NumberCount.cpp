#include "NumberCount.h"

USING_NS_CC;
using namespace ui;

NumberCount::NumberCount():
	m_ccLabelAtlas(0),
	m_uiLabelAtlas(0),
	m_number(0),
	m_increment(0),
	m_numberDelta(1),
	m_timeDelta(0.01f)
{
	CCDirector::getInstance()->getScheduler()->schedule(schedule_selector(NumberCount::updateNumber),this,0.0f,false);
}

bool NumberCount::setNumber(int number, bool bGradually)
{
	if(!m_ccLabelAtlas && !m_uiLabelAtlas)
		return false;

	if(!bGradually)
	{
		m_number = number;

		if(m_ccLabelAtlas)
			m_ccLabelAtlas->setString(__String::createWithFormat("%d",number)->getCString());

		if(m_uiLabelAtlas)
			m_ccLabelAtlas->setString(__String::createWithFormat("%d",number)->getCString());
	}
	else
	{
		m_increment = number - m_number;
	}

	m_timeEscape = 0.0f;
	
	return true;
}

void NumberCount::updateNumber(float fInterval)
{
	if(m_increment==0 || (!m_ccLabelAtlas && !m_uiLabelAtlas))
		return ;

	if(m_timeEscape > m_timeDelta)
	{
		if(m_increment>0)
		{
			if(m_increment - m_numberDelta > 0)
			{
				m_number     = m_number + m_numberDelta;
				m_increment -= m_numberDelta;
			}
			else
			{
				m_number    = m_number + m_increment;
				m_increment = 0;
			}
		}
		else
		{
			if(m_increment + m_numberDelta < 0)
			{
				m_number     = m_number - m_numberDelta;
				m_increment += m_numberDelta;
			}
			else
			{
				m_number    = m_number + m_increment;
				m_increment = 0;
			}
		}

		if(m_ccLabelAtlas)
			m_ccLabelAtlas->setString(__String::createWithFormat("%d",m_number)->getCString());

		if(m_uiLabelAtlas)
			m_ccLabelAtlas->setString(__String::createWithFormat("%d",m_number)->getCString());

		m_timeEscape = 0.0f;
	}
	else
		m_timeEscape+=fInterval;
}