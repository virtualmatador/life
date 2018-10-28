#include "control.h"

Control::Control(int iX, int iY, GLfloat scale,
		GLfloat red, GLfloat green, GLfloat blue,
		const char* szText,	void (*OnClick)(void*), void* pArg)
		: m_iX{iX}
		, m_iY{iY}
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
	float fX, fY;
	GetTopLeft(&fX, &fY, fScaleX, fScaleY);
	for (int i = 0; i < m_Text.size(); ++i)
	{
		float fData;
		fData = fX + m_fScalse * fScaleX * 0.33 / 2.0 + i * m_fScalse * fScaleX;
		stream.write((char*)&fData, sizeof(GLfloat));
		fData = fY - m_fScalse * fScaleY * 0.33 / 2.0;
		stream.write((char*)&fData, sizeof(GLfloat));
		fData = m_fScalse * fScaleX * 0.67;
		stream.write((char*)&fData, sizeof(GLfloat));
		fData = m_fScalse * fScaleY * 0.67;
		stream.write((char*)&fData, sizeof(GLfloat));
		int iData = m_Text[i] - 32;
		stream.write((char*)&iData, sizeof(GLint));
		stream.write((char*)m_fColor, sizeof(GLfloat) * 3);
	}
	return m_Text.size();
}

void Control::GetTopLeft(float* pfX, float* pfY, float fScaleX, float fScaleY)
{
	*pfX = +m_iX * fScaleX - 1.0 + 0.5 * fScaleX;
	*pfY = -m_iY * fScaleY + 1.0 - 0.5 * fScaleY;
}

bool Control::Click(float x, float y, float fScaleX, float fScaleY)
{
	float fX, fY;
	GetTopLeft(&fX, &fY, fScaleX, fScaleY);
	if (m_OnClick &&
		x > fX && x < fX + m_Text.size() * m_fScalse * fScaleX &&
		y < fY && y > fY - m_fScalse * fScaleY)
	{
		m_OnClick(m_pArg);
		return true;
	}
	return false;
}
