#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/cocos/sprite_nodes/CCSprite.h>
#include <Geode/modify/PlayLayer.hpp>

class $modify(MyButtonInfoLayer, LevelInfoLayer) {
	static int practice;

    bool init(GJGameLevel* level, bool p1){
		if (!LevelInfoLayer::init(level, p1)) {
			return false;
		}

		auto menu = this->getChildByID("play-menu");
        if (!menu) {
			return true;
		}
		practice = 0;

        auto practiceSprite = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
        auto practiceBtn = CCMenuItemSpriteExtra::create(practiceSprite, this, menu_selector(MyButtonInfoLayer::togglePractice));

        auto playBtn = static_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("play-button"));
        if (playBtn) {
			playBtn->setPosition(playBtn->getPosition() - ccp(20, 0));
            practiceBtn->setPosition(playBtn->getPosition() + ccp(67, 0));
			practiceBtn->setScale(0.7f); 
        }
		menu->addChild(practiceBtn);
        return true;
	}

	void togglePractice(CCObject* target) {
		practice = 1;
		this->onPlay(target);
	}

	static int getPractice() {
		return practice;
	}
};

class $modify (AutoPractice, PlayLayer)
{
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects)
    {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

		auto practice = MyButtonInfoLayer::getPractice();

        this->togglePracticeMode(practice);
        return true;
    }
};

int MyButtonInfoLayer::practice = 0;