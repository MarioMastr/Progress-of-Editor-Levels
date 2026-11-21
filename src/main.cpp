#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>

class $modify(ProgELL, EditLevelLayer) {
	CCSprite *addProgressBar(cocos2d::CCPoint p0, int p1, cocos2d::ccColor3B p2, char const* p3, char const* p4) {
		std::string nameForID = std::string(p3).substr(0, std::string(p3).find(" "));
		std::transform(nameForID.begin(), nameForID.end(), nameForID.begin(), ::tolower);

		CCSprite *progressBar = GameToolbox::createProgressBar(0.7, p1, p2);
		progressBar->setPosition(p0);
		progressBar->setID(nameForID + "-mode-bar");
		addChild(progressBar, 3);

		CCLabelBMFont *progressLabel = CCLabelBMFont::create(p3, "bigFont.fnt");
		progressLabel->setPosition(p0 + ccp(0, 15));
		progressLabel->setScale(0.4);
		progressLabel->setID(nameForID + "-mode-label");
		addChild(progressLabel, 4);

		CCLabelBMFont *progressPercentage = CCLabelBMFont::create(p4, "bigFont.fnt");
		progressPercentage->setPosition(p0);
		progressPercentage->setScale(0.4);
		progressPercentage->setID(nameForID + "-mode-percentage");
		addChild(progressPercentage, 4);

		return progressBar;
	}

	void setupProgressBars() {
		CCDirector *director = CCDirector::get();

		CCSprite *normalModeBar = addProgressBar(
			{
				director->getWinSize().width / 2,
				director->getScreenBottom() + 95
			},
			m_level->m_normalPercent,
			{ 0, 255, 0 },
			"Normal Mode",
			std::to_string(m_level->m_normalPercent).append("%").c_str()
		);

		addProgressBar(
			normalModeBar->getPosition() + ccp(0, -32),
			m_level->m_practicePercent,
			{ 0, 255, 255 },
			"Practice Mode",
			std::to_string(m_level->m_practicePercent).append("%").c_str()
		);
	}

	void setupPlatformerStats() {
		CCDirector *director = CCDirector::get();
		std::string bestTimeString{};

		if (m_level->m_bestTime == 0)
			bestTimeString = "No Best Time";
		else {
			std::string formattedTimeString{};

			int bestTimeMilliseconds          = m_level->m_bestTime;
			int bestTimeMillisecondsRemainder = bestTimeMilliseconds % 1000;
			int bestTimeSeconds               = bestTimeMilliseconds / 1000;
			int bestTimeSecondsRemainder      = bestTimeSeconds % 60;
			int bestTimeMinutes               = bestTimeSeconds / 60;
			int bestTimeMinutesRemainder      = bestTimeMinutes % 60;
			int bestTimeHours                 = bestTimeMinutes / 60;

			if (bestTimeHours == 0) {
				if (bestTimeMinutes == 0)
					formattedTimeString = std::format("{}.{:03d}", bestTimeSeconds, bestTimeMillisecondsRemainder);
				else
					formattedTimeString = std::format("{:02d}:{:02d}.{:03d}", bestTimeMinutes, bestTimeSecondsRemainder, bestTimeMillisecondsRemainder);
			}
			else
				formattedTimeString = std::format("{:02d}:{:02d}:{:02d}.{:03d}", bestTimeHours, bestTimeMinutesRemainder, bestTimeSecondsRemainder, bestTimeMillisecondsRemainder);

			bestTimeString = std::string("Best Time: ").append(formattedTimeString);
		}

		CCLabelBMFont *bestTimeLabel = CCLabelBMFont::create(bestTimeString.c_str(), "goldFont.fnt");
		bestTimeLabel->setPosition({director->getWinSize().width / 2, director->getScreenBottom() + 83});
		bestTimeLabel->setScale(0.6);
		bestTimeLabel->limitLabelWidth(200, 0.6, 0);
		bestTimeLabel->setID("best-time-label");
		addChild(bestTimeLabel);

		if (m_level->m_savedPoints) {
			bestTimeLabel->setPosition(bestTimeLabel->getPosition() + ccp(0, 14));

			CCLabelBMFont *bestPointsLabel = CCLabelBMFont::create(std::format("Best Points: {}", m_level->m_bestPoints).c_str(), "goldFont.fnt");
			bestPointsLabel->setPosition(bestTimeLabel->getPosition() + ccp(0, -28));
			bestPointsLabel->setScale(0.6);
			bestPointsLabel->limitLabelWidth(200, 0.6, 0);
			bestPointsLabel->setID("best-points-label");
			addChild(bestPointsLabel);
		}
	}

	bool init(GJGameLevel *p0) {
		if (!EditLevelLayer::init(p0))
		    return false;

		NodeIDs::provideFor(this);   

		CCNode *levelEditMenu = getChildByID("level-edit-menu");
		levelEditMenu->setPosition({CCDirector::get()->getWinSize().width / 2, 153.0});
		levelEditMenu->setScale(0.85);

		CCNode *levelLength = getChildByID("level-length");
		levelLength->setPositionY(37.0);

		CCNode *levelSong = getChildByID("level-song");
		levelSong->setPositionY(37.0);

		CCNode *levelVerified = getChildByID("level-verified");
		levelVerified->setPositionY(37.0);

		if (p0->isPlatformer())
			setupPlatformerStats();
		else
			setupProgressBars();

		return true;
	}
};
