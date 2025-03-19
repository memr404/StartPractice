#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/cocos/sprite_nodes/CCSprite.h>

class $modify(MyButtonInfoLayer, LevelInfoLayer) {
	void onPracticeMode(CCObject* target) {
        auto level = m_level;
        if (level) {
			log::info("TESTS", this->getChildrenCount());
            //PlayLayer::togglePracticeMode(true); // Запуск уровня в режиме практики
        }
    }
    bool init(GJGameLevel* level, bool p1){
		if (!LevelInfoLayer::init(level, p1)) {
			return false;
		}

		auto menu = this->getChildByID("play-menu");
        if (!menu) {
			return true;
		}

        auto practiceSprite = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
        auto practiceBtn = CCMenuItemSpriteExtra::create(practiceSprite, this, menu_selector(MyButtonInfoLayer::onPracticeMode));

        auto playBtn = static_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("play-button"));
        if (playBtn) {
			playBtn->setPosition(playBtn->getPosition() - ccp(20, 0));
            practiceBtn->setPosition(playBtn->getPosition() + ccp(67, 0));
			practiceBtn->setScale(0.7f); 
        }
		menu->addChild(practiceBtn);
        return true;
	}
};