#include "control.h"

Control::Control(GLfloat x, GLfloat y, GLfloat scale,
		GLfloat red, GLfloat green, GLfloat blue,
		const char* szText,	void (*OnClick)(void*), void* pArg)
		: m_fX{x}
		, m_fY{y}
		, m_fScalse{scale}
{
	if (szText)
		m_Text = std::string(szText);
	m_fColor[0] = red;
	m_fColor[1] = green;
	m_fColor[2] = blue;
	m_OnClick = OnClick;
	m_pArg = pArg;
}

Control::~Control()
{
}

void Control::SetText(std::string && str)
{
	m_Text = str;
}

int Control::Write(std::stringstream & stream, float fScaleX, float fScaleY)
{
	for (int i = 0; i < m_Text.size(); ++i)
	{
		float fData = m_fX + m_fScalse * fScaleX * i;
		stream.write((char*)&fData, sizeof(GLfloat));
		stream.write((char*)&m_fY, sizeof(GLfloat));
		fData = m_fScalse * fScaleX * 0.66;
		stream.write((char*)&fData, sizeof(GLfloat));
		fData = m_fScalse * fScaleY * 0.66;
		stream.write((char*)&fData, sizeof(GLfloat));
		int iData = m_Text[i] - 32;
		stream.write((char*)&iData, sizeof(GLint));
		stream.write((char*)m_fColor, sizeof(GLfloat) * 3);
	}
	return m_Text.size();
}

bool Control::Click(float x, float y, float fScaleX, float fScaleY)
{
	if (m_OnClick &&
		x > m_fX && x < m_fX + m_Text.size() * m_fScalse * fScaleX &&
		y > m_fY && y < m_fY + m_Text.size() * m_fScalse * fScaleY * m_fScalse)
	{
		m_OnClick(m_pArg);
		return true;
	}
	return false;
}
