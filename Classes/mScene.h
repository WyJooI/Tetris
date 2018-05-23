#ifndef __M_SCENE_H__
#define __M_SCENE_H__
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
class mScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	int** map;
	int* yl;
	int* fkx;
	int* fky;
	int soc;
	int ndu;
	float speed;
	float romd;
	bool ischan;
	bool ischch;
	bool canc;
	bool ispause;
	int disp;
	cocos2d::Label* jbb;
	cocos2d::Scheduler* sched1;
	cocos2d::experimental::AudioProfile _audioProfile;
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPCallback(cocos2d::Ref* pSender);
	void menuRCallback(cocos2d::Ref* pSender);
	void menuChCallback(cocos2d::Ref* pSender);
	void keyoprP(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e);
	void keyoprR(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e);
	void mjc(float dt);
	void move(float dt);
	void oprat(float dt);
	void fkcreate(float random);
	void spin();
	// implement the "static create()" method manually
	CREATE_FUNC(mScene);
private:
	std::set<void*> _pausedTargets;
};

#endif // __HELLOWORLD_SCENE_H__
