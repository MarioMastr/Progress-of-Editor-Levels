#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>

class $modify(MyEditLevelLayer, EditLevelLayer)
{
	// can't copy a node so i have to recreate it ughhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
	void setupProgressBars()
	{
		// Normal Mode Related
		CCLabelBMFont *normalModeLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");
		normalModeLabel->setAnchorPoint(ccp(0.5, 0.5));
		normalModeLabel->setPosition(ccp(256.0, 127.0));
		normalModeLabel->setScale(0.4);
		normalModeLabel->setZOrder(4);

		normalModeLabel->setID("normal-mode-label");
		this->addChild(normalModeLabel);

        CCSprite *normalModeBar = CCSprite::create("GJ_progressBar_001.png");
        normalModeBar->setAnchorPoint(ccp(0.5, 0.5));
        normalModeBar->setPosition(ccp(256.0, 112.0));
        normalModeBar->setScale(0.7);
        normalModeBar->setColor({ 0, 0, 0 });
        normalModeBar->setOpacity(125);
        normalModeBar->setContentHeight(20.0);
        normalModeBar->setContentWidth(340.0);
		normalModeBar->setZOrder(3);

		CCSprite *normalModeBarInside = CCSprite::create("GJ_progressBar_001.png");
        normalModeBarInside->setAnchorPoint(ccp(0.0, 0.5));
        normalModeBarInside->setPosition(ccp(1.360, 10.000));
        normalModeBarInside->setScaleX(0.992);
		normalModeBarInside->setScaleY(0.860);
        normalModeBarInside->setColor({ 0, 255, 0 });
        normalModeBarInside->setContentHeight(20.0);
        normalModeBarInside->setContentWidth(this->m_level->m_normalPercent * 3.4);
		normalModeBarInside->setTextureRect({normalModeBarInside->getTextureRect().origin.x, normalModeBarInside->getTextureRect().origin.y, static_cast<float>(this->m_level->m_normalPercent * 3.4), 20.0});
		normalModeBarInside->setZOrder(1);

		CCLabelBMFont *normalModePercentage = CCLabelBMFont::create(std::to_string(this->m_level->m_normalPercent).append("%").c_str(), "bigFont.fnt");
		normalModePercentage->setAnchorPoint(ccp(0.5, 0.5));
		normalModePercentage->setPosition(ccp(256.0, 112.0));
		normalModePercentage->setScale(0.4);
		normalModePercentage->setID("normal-mode-percentage");
		normalModePercentage->setZOrder(4);

        normalModeBar->setID("normal-mode-bar");
        normalModeBar->addChild(normalModeBarInside);
		this->addChild(normalModePercentage);
		this->addChild(normalModeBar);

		// Practice Mode Related
		CCLabelBMFont *practiceModeLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");
		practiceModeLabel->setAnchorPoint(ccp(0.5, 0.5));
		practiceModeLabel->setPosition(ccp(256.0, 95.0));
		practiceModeLabel->setScale(0.4);
		practiceModeLabel->setZOrder(4);

		practiceModeLabel->setID("practice-mode-label");
		this->addChild(practiceModeLabel);

        CCSprite *practiceModeBar = CCSprite::create("GJ_progressBar_001.png");
        practiceModeBar->setAnchorPoint(ccp(0.5, 0.5));
        practiceModeBar->setPosition(ccp(256.0, 80.0));
        practiceModeBar->setScale(0.7);
        practiceModeBar->setColor({ 0, 0, 0 });
        practiceModeBar->setOpacity(125);
        practiceModeBar->setContentHeight(20.0);
        practiceModeBar->setContentWidth(340.0);
		practiceModeBar->setZOrder(3);

		CCSprite *practiceModeBarInside = CCSprite::create("GJ_progressBar_001.png");
        practiceModeBarInside->setAnchorPoint(ccp(0.0, 0.5));
        practiceModeBarInside->setPosition(ccp(1.360, 10.000));
        practiceModeBarInside->setScaleX(0.992);
		practiceModeBarInside->setScaleY(0.860);
        practiceModeBarInside->setColor({ 0, 255, 255 });
        practiceModeBarInside->setContentHeight(20.0);
        practiceModeBarInside->setContentWidth(this->m_level->m_practicePercent * 3.4);
		practiceModeBarInside->setTextureRect({practiceModeBarInside->getTextureRect().origin.x, practiceModeBarInside->getTextureRect().origin.y, static_cast<float>(this->m_level->m_practicePercent * 3.4), 20.0});
		practiceModeBarInside->setZOrder(1);

		CCLabelBMFont *practiceModePercentage = CCLabelBMFont::create(std::to_string(this->m_level->m_practicePercent).append("%").c_str(), "bigFont.fnt");
		practiceModePercentage->setAnchorPoint(ccp(0.5, 0.5));
		practiceModePercentage->setPosition(ccp(256.0, 80.0));
		practiceModePercentage->setScale(0.4);
		practiceModePercentage->setZOrder(4);
		practiceModePercentage->setID("practice-mode-percentage");

        practiceModeBar->setID("practice-mode-bar");
        practiceModeBar->addChild(practiceModeBarInside);
		this->addChild(practiceModePercentage);
        this->addChild(practiceModeBar);
	}

    bool init(GJGameLevel *p0)
    {
        if (!EditLevelLayer::init(p0))
            return false;

        NodeIDs::provideFor(this);   

        CCNode *levelEditMenu = this->getChildByID("level-edit-menu");
        levelEditMenu->setPositionY(161.0);
        levelEditMenu->setScale(0.6);

		this->setupProgressBars();

        return true;
    }
};