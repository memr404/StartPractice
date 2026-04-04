#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/EditLevelLayer.hpp>

using namespace geode::prelude;

bool practice = false;

class $modify(PracticeButtonInfoLayer, LevelInfoLayer) {

    bool init(GJGameLevel* level, bool p1){
		if (!LevelInfoLayer::init(level, p1)) return false;

		practice = false;

		auto playMenu = this->getChildByID("play-menu");
		auto playBtn = static_cast<CCMenuItemSpriteExtra*>(this->querySelector("play-menu > play-button"));
		auto practiceSprite = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
		auto practiceBtn = CCMenuItemSpriteExtra::create(practiceSprite, this, menu_selector(PracticeButtonInfoLayer::togglePractice));

		if (Mod::get()->getSettingValue<bool>("show-only-practice") && not(Mod::get()->getSettingValue<bool>("use-menu-buttons"))){
			practiceBtn->setPosition(playBtn->getPosition());
			playMenu->addChild(practiceBtn);

			playBtn->setVisible(false);
			playBtn->setEnabled(false);

			return true;
		}

        if (!Mod::get()->getSettingValue<bool>("use-menu-buttons") && playBtn && playMenu) {
        	playBtn->setPosition(playBtn->getPosition() - ccp(20, 0));
			practiceBtn->setPosition(playBtn->getPosition() + ccp(67, 0));
			practiceBtn->setScale(0.7f);
			playMenu->addChild(practiceBtn);
		} else if (auto leftMenu = this->getChildByID("left-side-menu")) {
			leftMenu->addChild(practiceBtn);
			leftMenu->updateLayout();
		} else return true;

		practiceBtn->setID("practice-mode-button"_spr);

        return true;
	}

	void togglePractice(CCObject* target) {
		practice = true;
		this->onPlay(target);
	}
};


class $modify(PracticeButtonEditLayer, EditLevelLayer) {

    bool init(GJGameLevel* level){
		if (!EditLevelLayer::init(level)) return false;

		practice = false;

        auto practiceSprite = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
        auto practiceBtn = CCMenuItemSpriteExtra::create(practiceSprite, this, menu_selector(PracticeButtonEditLayer::togglePractice));
		
		auto playMenu = this->getChildByID("level-edit-menu");
		auto playBtn = static_cast<CCMenuItemSpriteExtra*>(this->querySelector("level-edit-menu > play-button"));

		if (Mod::get()->getSettingValue<bool>("show-only-practice-on-editor") && not(Mod::get()->getSettingValue<bool>("use-menu-buttons"))){
			practiceBtn->setPosition(playBtn->getPosition());
			playMenu->addChild(practiceBtn);

			playBtn->setVisible(false);
			playBtn->setEnabled(false);

			return true;
		}

        if (!Mod::get()->getSettingValue<bool>("use-menu-buttons") && playBtn && playMenu) {
			playMenu->addChild(practiceBtn);
			playMenu->updateLayout();
		} else if (auto Menu = this->getChildByID("level-actions-menu")) {
			Menu->addChild(practiceBtn);
			Menu->updateLayout();
		} else return true;

		practiceBtn->setID("practice-mode-button"_spr);

        return true;
	}

	void togglePractice(CCObject* target) {
		practice = true;
		this->onPlay(target);
	}
};

class $modify(AutoPractice, PlayLayer) {
    void setupHasCompleted() {
		PlayLayer::setupHasCompleted();
		if (practice) this->togglePracticeMode(true);
		practice = false;
	}
};