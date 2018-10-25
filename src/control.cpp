#include "control.h"

Control::Control(GLfloat x, GLfloat y, GLfloat scale,
		GLfloat red, GLfloat green, GLfloat blue,
		const char* szText,	void (*OnClick)())
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
}

Control::~Control()
{
}

std::string* Control::GetText()
{
	return &m_Text;
}

int Control::Write(std::stringstream & stream)
{
	for (int i = 0; i < m_Text.size(); ++i)
	{
		float fData = m_fX + m_fScalse * i;
		stream.write((char*)&fData, sizeof(GLfloat));
		stream.write((char*)&m_fY, sizeof(GLfloat));
		fData = m_fScalse * 0.7;
		stream.write((char*)&fData, sizeof(GLfloat));
		int iData = m_Text[i] - 32;
		stream.write((char*)&iData, sizeof(GLint));
		stream.write((char*)m_fColor, sizeof(GLfloat) * 3);
	}
	return m_Text.size();
}

bool Control::Click(float x, float y)
{
	if (m_OnClick &&
		x > m_fX && x < m_fX + m_Text.size() * m_fScalse &&
		y > m_fY && y < m_fX + 1.5 * m_fScalse)
	{
		m_OnClick();
		return true;
	}
	return false;
}
