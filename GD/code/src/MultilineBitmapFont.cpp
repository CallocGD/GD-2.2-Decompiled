#include "../headers/includes.h"

std::string MultilineBitmapFont::readColorInfo(std::string str)
{
	while (true)
	{
		std::string newstr = str;
		std::size_t colPos = newstr.find("<c");
		cocos2d::ccColor3B col;
		cocos2d::CCObject* textSection;

		if (colPos != std::string::npos)
		{
			std::string tag = newstr.at(colPos + 2);

			newstr.replace(colPos, 4, "");
			moveSpecialDescriptors(colPos, 4);

			std::size_t endTag = newstr.find("</c>");
			newstr.replace(endTag, 4, "");
			moveSpecialDescriptors(endTag, 4);

			switch (tag)
			{
			case 'b':
				col = { 0x4A, 0x52, 0xE1 };
				break;
			case 'g':
				col = { 0x40,0xE3,0x48 };
				break;
			case 'l':
				col = { 0x60, 0xAB, 0xEF };
				break;
			case 'j':
				col = { 0x32, 0xC8, 0xFF };
				break;
			case 'y':
				col = { 0xFF, 0xFF, 0x00 };
				break;
			case 'o':
				col = { 0xFF, 0xA5, 0x4B };
				break;
			case 'r':
				col = { 0xFF, 0x5A, 0x5A };
				break;
			case 'p':
				col = { 0xFF, 0x00 0xFF };
				break;
			default:
				col = { 0xFF, 0x00, 0x00 };
			}

			textSection = ColoredSection::create(col, colPos, endTag - 1);
			m_pColouredTextArray->addObject(textSection);;
			continue;
		}

		std::size_t iPos = newstr.find("<i>");
		if (iPos != std::string::npos)
		{
			newstr.replace(iPos, 3, "");
			moveSpecialDescriptors(iPos, 3);

			std::size_t iEnd = newstr.find("</i>");
			newstr.replace(iEnd, 4, "");
			moveSpecialDescriptors(iEnd, 4);

			textSection = InstantSection::create(iPos, iEnd - 1);
			m_pInstantTextArray->addObject(textSection);
			continue;
		}

		std::size_t dPos = newstr.find("<d");
		if (dPos == std::string::npos)
			break;

		int delay = atoi(newstr.substr(dPos + 2, 3));
		newstr.replace(dPos, 6, "");
		moveSpecialDescriptors(dPos, 6);

		textSection = DelaySection::create(dPos, delay / 100.0f);
		m_pDelayedTextArray->addObject(textSection);

	}
		return newstr;
}

void MultilineBitmapFont::moveSpecialDescriptors(int tStart, int tSize)
{

	for (int i = 0; i < m_pColouredTextArray->count(); ++i)
	{
		ColoredSection* section = m_pColouredTextArray->objectAtIndex(i);
		if (section->m_nStart <= tStart && section->m_nEnd <= tStart)
			continue;
		
		section->m_nStart -= tSize;
		section->m_nEnd -= tSize;
	}

	for (int i = 0; i < m_pInstantTextArray->count(); ++i)
	{
		InstantSection* section = m_pInstantTextArray->objectAtIndex(i);
		if (section->m_nStart <= tStart && section->m_nEnd <= tStart)
			continue;
		
		section->m_nStart -= tSize;
		section->m_nEnd -= tSize;
	}
}

void MultilineBitmapFont::setOpacity(unsigned __int8 opacity)
{
	for (int i = 0; i < m_pLetterArray->count(); ++i)
	{
		static_cast<cocos2d::CCSprite*>(m_pLetterArray->objectAtIndex(i))->setOpacity(opacity);
	}
	this->setOpacity(opacity);
}

MultilineBitmapFont* MultilineBitmapFont::create(const char* fontName, int* str, float scale, float width, cocos2d::CCPoint anchorPoint, bool bColourEnabled)
{
	auto pRet = new MultilineBitmapFont;

	if (pRet && pRet->initWithFont(fontName, str, scale, width, anchorPoint, bColourEnabled))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return nullptr;
}