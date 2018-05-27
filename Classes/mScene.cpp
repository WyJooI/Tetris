#include "mScene.h"
#include<iostream>
#include "audio/include/AudioEngine.h"
USING_NS_CC;
using namespace cocos2d::experimental;
Scene* mScene::createScene()
{
	return mScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool mScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"eixt.png",
		"eixt.png",
		CC_CALLBACK_1(mScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else


	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	auto pauseItem = MenuItemImage::create(
		"pause.png",
		"pause.png",
		CC_CALLBACK_1(mScene::menuPCallback, this));
	pauseItem->setPosition(Vec2(origin.x + visibleSize.width  - pauseItem->getContentSize().width / 2-5, origin.y + pauseItem->getContentSize().height / 2+40));
	
	auto setItem = MenuItemImage::create(
		"return.png",
		"return.png",
		CC_CALLBACK_1(mScene::menuRCallback, this));
	setItem->setPosition(Vec2(origin.x + visibleSize.width - setItem->getContentSize().width / 2 - 5, origin.y + setItem->getContentSize().height / 2+80));
	
	auto chanItem = MenuItemImage::create(
		"chan.png",
		"chan.png",
		CC_CALLBACK_1(mScene::menuChCallback, this));
	chanItem->setPosition(Vec2(origin.x + visibleSize.width - chanItem->getContentSize().width / 2 - 5, origin.y + chanItem->getContentSize().height / 2 + 120));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, setItem,pauseItem,chanItem ,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	
	auto label = Label::createWithTTF("score:", "fonts/Marker Felt.ttf", 30);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + 12 * 28+70,origin.y + 9 * 40 + 50));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}
	auto jb = Sprite::create("jb.png");
	jb->setPosition(Vec2(origin.x + 12 * 28 + 50, origin.y + 6 * 40 + 50));
	jbb = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 30);
	jbb->setPosition(Vec2(origin.x + 12 * 28 + 40+jb->getContentSize().width, origin.y + 6 * 40 + 50));
	// add "HelloWorld" splash screen"
	auto list = EventListenerKeyboard::create();
	list->onKeyReleased=CC_CALLBACK_2(mScene::keyoprR,this);
	list->onKeyPressed= CC_CALLBACK_2(mScene::keyoprP, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(list, this);
	disp = 0;
	ndu = 1;
	auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg);
	fkx = new int[6];
	fky = new int[6];
	yl = new int[4];
	map = new int*[26];
	for (int i = 0; i < 25; i++)
		map[i] = new int[14];

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 12; i++) {
			auto fk = Sprite::create("fk.png");
			fk->setAnchorPoint(Vec2(0, 0));
			fk->setPosition(Vec2(origin.x + i * 28, origin.y + j * 28));
			fk->setOpacity(0);
			addChild(fk,0,j*12+i+1);
		}
	}
	speed = 10.0;
	auto fk2 = Sprite::create("fk.png");
	auto fk3 = Sprite::create("fk.png");
	fk2->setAnchorPoint(Vec2(0, 0));
	fk2->setPosition(Vec2(origin.x + 14 * 28, origin.y + 19 * 28));
	fk3->setAnchorPoint(Vec2(0, 0));
	fk3->setPosition(Vec2(origin.x + 14 * 28, origin.y + 18 * 28));
	addChild(fk2, 0, 241);
	addChild(fk3, 0, 242);
	fk2->setOpacity(0);
	fk3->setOpacity(0);
	addChild(jb);
	addChild(jbb);

	_audioProfile.name = "AudioProfileTest";
	_audioProfile.maxInstances = 3;
	_audioProfile.minDelay = 1.0;
	AudioEngine::play2d("Danny Baranowsky - Disco Descent (1-1).mp3", true, 1.0f, &_audioProfile);

	auto defaultScheduler = Director::getInstance()->getScheduler();
	sched1 = new (std::nothrow) Scheduler();
	defaultScheduler->scheduleUpdate(sched1, 0, false);
	sched1->schedule(CC_SCHEDULE_SELECTOR(mScene::move),this,speed,false);
	sched1->setTimeScale(speed);

	for (int i = 0; i<2; i++)
		for (int j = 0; j < 3; j++) {
			auto fk = Sprite::create("fk.png");
			fk->setAnchorPoint(Vec2(0, 0));
			fk->setPosition(Vec2(origin.x + (13 + j) * 28, origin.y + (17 - i) * 28));
			fk->setOpacity(0);
			addChild(fk, 0, 240 + i * 3 + j + 3);
		}
	for (int i = 0; i<3; i++)
	for (int j = 0; j < 10; j++) {
		char tpname[] = "num0.png";
		tpname[3] += j;
		auto Isum = Sprite::create(tpname);
		Isum->setAnchorPoint(Vec2(0, 0));
			Isum->setPosition(Vec2(origin.x +12*28+(2-i)*26+40, origin.y + 8 * 40+20));
			Isum->setOpacity(0);
			addChild(Isum, 0,i*10+249+j);
	}
	for (int j = 0; j < 24; j++)
		for (int i = 0; i < 12; i++)
			map[j][i] = 0;
	soc = 0; speed = 10; ischan = false; ischch = true; ispause = false;
	romd= CCRANDOM_0_1();
	fkcreate(romd);
	canc = true;
	
	schedule(CC_SCHEDULE_SELECTOR(mScene::mjc),(1.0/60));
//	schedule(CC_SCHEDULE_SELECTOR(mScene::oprat),speed/2);
	//schedule(CC_SCHEDULE_SELECTOR(mScene::move), speed);
	return true;
}

void mScene::mjc(float dt) {
	int max = 0;
	for (int i = 0; i < 20; i++) 
		for (int j = 0; j < 12; j++) {
				int num = i * 12 + j + 1;
				if (max < num)max = num;
				auto sprite = static_cast<Sprite*>(getChildByTag(num));
			if (map[i][j] == 0)sprite->setOpacity(0);
			else sprite->setOpacity(255);
		}
	if (ischan) {
		ischan = false;
		for (int i = 241; i < 249; i++)
		{
			auto sprite = static_cast<Sprite*>(getChildByTag(i));
			sprite->setOpacity(0);
		}
		for (int i = 0; i < 4; i++) {
			int num = yl[i] + 240;
			auto sprite = static_cast<Sprite*>(getChildByTag(num));
			sprite->setOpacity(255);
		}
	}
	if (ischch) {
		ischch = false;
		for (int i = 0; i<3; i++)
			for (int j = 0; j < 10; j++) {
				int num = 249 + i * 10+j;
				auto sprite = static_cast<Sprite*>(getChildByTag(num));
				sprite->setOpacity(0);
			}
		int lfs = soc;
		int sum[3];
		sum[2] = lfs / 100;
		lfs %= 100;
		sum[1] = lfs / 10;
		sum[0] = lfs % 10;
		for (int i = 0; i < 3; i++)
		{
			int num = sum[i] + 249 + i * 10;
			auto sprite = static_cast<Sprite*>(getChildByTag(num));
			sprite->setOpacity(255);
		}
	}
	//this->removeChild(sprite);
}
void mScene::oprat(float dt) {
	if (disp == 3) {
		move(0.5f);
	}
	if (disp == 1) {
		bool isdown = true;
		for (int i = 0; i < 4; i++)
			if (fky[i] <= 0 || map[fkx[i]][fky[i] - 1] == 1) {
				isdown = false;
				break;
			}
		if (isdown) {
			for (int i = 0; i < 4; i++) {
				int x = fkx[i]; int y = fky[i];
				map[x][y] = 0;
				fky[i] = fky[i] - 1;
			}
			for (int i = 0; i < 4; i++) {
				int x = fkx[i]; int y = fky[i];
				map[x][y] = 2;
			}
		}
	}
	if (disp == 2) {
		bool isdown = true;
		for (int i = 0; i < 4; i++)
			if (fky[i] >= 11 || map[fkx[i]][fky[i] + 1] == 1) {
				isdown = false;
				break;
			}
		if (isdown) {
			for (int i = 0; i < 4; i++) {
				int x = fkx[i]; int y = fky[i];
				map[x][y] = 0;
				fky[i] = fky[i] + 1;
			}
			for (int i = 0; i < 4; i++) {
				int x = fkx[i]; int y = fky[i];
				map[x][y] = 2;
			}
		}
	}
	if (disp == 4) {
		spin();
	}
	//this->removeChild(sprite);
}
void mScene::move(float dt) {
	bool isdown=true;
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 12; j++)if(map[i][j]==2) {
			if (i == 0|| map[i - 1][j] == 1) {
				isdown = false;
				break;
			}
		}
	if (isdown&&canc) {
			for (int i = 0; i < 4; i++) {
				int x = fkx[i]; int y = fky[i];
				map[x][y] = 0;
				fkx[i] = fkx[i] - 1;
			}
			for (int i = 0; i < 4; i++) {
				int x = fkx[i]; int y = fky[i];
				map[x][y] = 2;
			}
	}
	else {
		for (int i = 0; i < 24; i++)
			for (int j = 0; j < 12; j++)
				if (map[i][j] == 2)map[i][j] = 1;

		for (int i = 0; i < 20; i++) {
		    bool isxq=true;
			for (int j = 0; j < 12; j++)if (map[i][j] == 0) { isxq = false; break; }
				if (isxq) {
					for (int j = 0; j < 12; j++) {
						map[i][j] = 0;
					}
					for(int k=i;k<20;k++)
						for (int j = 0; j < 12; j++) {
							map[k][j] = map[k + 1][j];
						}
					i = i - 1;
					soc += 1;
					ischch = true;
				}
		    }
		fkcreate(romd);
	}
}

void mScene::fkcreate(float random) {
	romd = CCRANDOM_0_1();
	int j = 6;
	if (random < 0.142)
	{
		//竖条
		map[20][j] = 2;map[21][j] = 2;map[22][j] = 2;map[23][j] = 2;
		fkx[0] = 20; fky[0] = j; fkx[1] = 21; fky[1] = j; fkx[2] = 22; fky[2] = j; fkx[3] = 23; fky[3] = j;
		fkx[4] = 1; fkx[5] = 1;
	}
	else if (random < 0.142*2)
	{
		//l反
		map[20][j] = 2;map[20][j+1] = 2;map[20][j-1] = 2;map[21][j-1] = 2;
		fkx[0] = 20; fky[0] = j-1; fkx[1] = 20; fky[1] = j; fkx[2] = 20; fky[2] = j+1; fkx[3] = 21; fky[3] = j-1;
		fkx[4] = 5; fkx[5] = 1;
	}
	else if (random < 0.142*3)
	{
		//正方
		map[20][j] = 2;map[20][j-1] = 2;map[21][j] = 2;map[21][j-1] = 2;
		fkx[0] = 20; fky[0] = j - 1; fkx[1] = 20; fky[1] = j; fkx[2] = 21; fky[2] = j - 1; fkx[3] = 21; fky[3] = j;
		fkx[4] = 4; fkx[5] = 1;
	}
	else if (random < 0.142*4)
	{
		//z
		map[20][j] = 2;map[20][j+1] = 2;map[21][j] = 2;map[21][j-1] = 2;
		fkx[0] = 20; fky[0] = j ; fkx[1] = 20; fky[1] = j+1; fkx[2] = 21; fky[2] = j-1 ; fkx[3] = 21; fky[3] = j ;
		fkx[4] = 2; fkx[5] = 1;
	}
	else if (random < 0.142 * 5)
	{
		//倒z
		map[20][j] = 2; map[20][j - 1] = 2;map[21][j] = 2;map[21][j + 1] = 2;
		fkx[0] = 20; fky[0] = j - 1; fkx[1] = 20; fky[1] = j; fkx[2] = 21; fky[2] = j ; fkx[3] = 21; fky[3] = j + 1;
		fkx[4] = 3; fkx[5] = 1;
	}
	else if (random < 0.142 * 6)
	{
		//L
		map[20][j] = 2; map[20][j + 1] = 2; map[20][j - 1] = 2; map[21][j + 1] = 2;
		fkx[0] = 20; fky[0] = j - 1; fkx[1] = 20; fky[1] = j; fkx[2] = 20; fky[2] = j + 1; fkx[3] = 21; fky[3] = j + 1;
		fkx[4] = 6; fkx[5] = 1;
	}
	else
	{
		//凸
		map[20][j] = 2;map[20][j-1] = 2;map[20][j+1] = 2;map[21][j] = 2;
		fkx[0] = 20; fky[0] = j - 1; fkx[1] = 20; fky[1] = j; fkx[2] = 20; fky[2] = j + 1; fkx[3] = 21; fky[3] = j ;
		fkx[4] = 7; fkx[5] = 1;
	}

	if (romd < 0.142) {yl[0] = 1; yl[1] = 2; yl[2] = 4; yl[3] = 7;}
	else if (romd < 0.142*2){	yl[0] = 3; yl[1] = 6; yl[2] = 7; yl[3] = 8;}
	else if (romd < 0.142*3) { yl[0] = 3; yl[1] = 4; yl[2] = 6; yl[3] = 7; }
	else if (romd < 0.142*4) { yl[0] = 3; yl[1] = 4; yl[2] = 7; yl[3] = 8; }
	else if (romd < 0.142 * 5) { yl[0] = 4; yl[1] = 5; yl[2] = 6; yl[3] = 7; }
	else if (romd < 0.142 * 6) { yl[0] = 5; yl[1] = 6; yl[2] = 7; yl[3] = 8; }
	else { yl[0] = 4; yl[1] = 6; yl[2] = 7; yl[3] = 8; }
	ischan = true;
}
void mScene::keyoprP(EventKeyboard::KeyCode keycode, Event* e) {
	if (keycode == EventKeyboard::KeyCode::KEY_A&&!ispause) disp = 1;
	else if (keycode == EventKeyboard::KeyCode::KEY_D && !ispause) disp = 2;
	else if (keycode == EventKeyboard::KeyCode::KEY_S && !ispause) disp = 3;
	else if (keycode == EventKeyboard::KeyCode::KEY_W && !ispause) disp = 4;
	oprat(1.1);
	CCLOG("autoremove scheduler: Time: %d", soc);
}
void mScene::keyoprR(EventKeyboard::KeyCode keycode, Event* e) {
	disp = 0;
	CCLOG("autoremove scheduler: Time: %d", soc);
}
void mScene::spin() {
	canc = false;
	if (fkx[4] == 1) {
		//竖条
		if (fkx[5] == 1) {
			int x=fkx[0],y=fky[0];
			bool iss = true;
			if (y + 3 > 11)iss = false;
			if (map[x][y + 1] == 1 || map[x][y + 2] == 1 || map[x][y + 3] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 2][y] = 0; map[x + 3][y] = 0;
				map[x][y+1] = 2; map[x][y+2] = 2; map[x][y+3] = 2;
				fkx[1] = x; fky[1] = y+1;
				fkx[2] = x; fky[2] = y + 2;
				fkx[3] = x; fky[3] = y + 3;
				fkx[5] = 2;
			}
		}
		else {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (map[x+1][y] == 1 || map[x+1][y] == 1 || map[x+1][y] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 2; map[x + 2][y] = 2; map[x + 3][y] = 2;
				map[x][y + 1] = 0; map[x][y + 2] = 0; map[x][y + 3] = 0;
				fkx[1] = x+1; fky[1] = y ;
				fkx[2] = x+2; fky[2] = y ;
				fkx[3] = x+3; fky[3] = y ;
				fkx[5] = 1;
			}
		}
	}
	else if (fkx[4] == 2) {
		//z
		if (fkx[5] == 1) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y + 1 > 11)iss = false;
			if (map[x+1][y] == 1 || map[x+1][y + 1] == 1 || map[x+2][y + 1] == 1)iss = false;
			if (iss) {
				map[x][y-1] = 0; map[x+1][y-1] = 0; map[x + 1][y-2] = 0;
				map[x+1][y ] = 2; map[x+1][y +1] = 2; map[x+2][y + 1] = 2;
				fkx[1] = x+1; fky[1] = y ;
				fkx[2] = x+1; fky[2] = y + 1;
				fkx[3] = x+2; fky[3] = y + 1;
				fkx[5] = 2;
			}
		}
		else {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y -2 <0)iss = false;
			if (map[x][y-1] == 1 || map[x + 1][y -1] == 1 || map[x + 1][y-2] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 1][y + 1] = 0; map[x + 2][y + 1] = 0;
				map[x][y - 1] = 2; map[x + 1][y - 1] = 2; map[x + 1][y - 2] = 2;
				fkx[1] = x ; fky[1] = y-1;
				fkx[2] = x + 1; fky[2] = y - 1;
				fkx[3] = x + 1; fky[3] = y -2;
				fkx[5] = 1;
			}
		}
	}
	else if (fkx[4] == 3) {
		//到z
		if (fkx[5] == 1) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y -1 <0)iss = false;
			if (map[x + 1][y] == 1 || map[x + 1][y - 1] == 1 || map[x + 2][y - 1] == 1)iss = false;
			if (iss) {
				map[x][y + 1] = 0; map[x + 1][y + 1] = 0; map[x + 1][y + 2] = 0;
				map[x + 1][y] = 2; map[x + 1][y - 1] = 2; map[x + 2][y - 1] = 2;
				fkx[1] = x + 1; fky[1] = y;
				fkx[2] = x + 1; fky[2] = y - 1;
				fkx[3] = x + 2; fky[3] = y - 1;
				fkx[5] = 2;
			}
		}
		else {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y + 2 >11)iss = false;
			if (map[x][y+1] == 1 || map[x + 1][y + 1] == 1 || map[x + 1][y +2] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 1][y - 1] = 0; map[x + 2][y - 1] = 0;
				map[x][y + 1] = 2; map[x + 1][y + 1] = 2; map[x + 1][y + 2] = 2;
				fkx[1] = x; fky[1] = y+1 ;
				fkx[2] = x + 1; fky[2] = y + 1;
				fkx[3] = x + 1; fky[3] = y + 2;
				fkx[5] = 1;
			}
		}
	}
	else if (fkx[4] == 4) {
		//正方;
	}
	else if (fkx[4] == 5) {
		if (fkx[5] == 1) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (map[x + 1][y] == 1 || map[x + 2][y] == 1 || map[x + 2][y + 1] == 1)iss = false;
			if (iss) {
				map[x+1][y] = 0; map[x ][y + 1] = 0; map[x][y + 2] = 0;
				map[x + 1][y] = 2; map[x + 2][y] = 2; map[x + 2][y + 1] = 2;
				fkx[1] = x + 1; fky[1] = y;
				fkx[2] = x + 2; fky[2] = y ;
				fkx[3] = x + 2; fky[3] = y + 1;
				fkx[5] = 2;
			}
		}
		else if(fkx[5]==2){
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y - 2 <0)iss = false;
			if (map[x+1][y] == 1 || map[x + 1][y - 1] == 1 || map[x + 1][y - 2] == 1)iss = false;
			if (iss) {				
				map[x + 1][y] = 0; map[x + 2][y] = 0; map[x + 2][y + 1] = 0;
				map[x+1][y] = 2; map[x + 1][y - 1] = 2; map[x + 1][y - 2] = 2;
				fkx[1] = x + 1; fky[1] = y;
				fkx[2] = x + 1; fky[2] = y - 1;
				fkx[3] = x + 1; fky[3] = y - 2;
				fkx[5] = 3;
			}
		}
		else if (fkx[5] == 3) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y+1 >11)iss = false;
			if (map[x][y+1] == 1 || map[x + 1][y + 1] == 1 || map[x + 2][y + 1] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 1][y - 1] = 0; map[x + 1][y - 2] = 0;
				map[x][y + 1] = 2; map[x + 1][y + 1] = 2; map[x + 2][y + 1] = 2;			
				fkx[1] = x ; fky[1] = y+1;
				fkx[2] = x + 1; fky[2] = y + 1;
				fkx[3] = x + 2; fky[3] = y + 1;
				fkx[5] = 4;
			}
		}
		else {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y + 2 >11)iss = false;
			if (map[x][y + 1] == 1 || map[x ][y + 2] == 1 || map[x + 1][y] == 1)iss = false;
			if (iss) {
				map[x][y + 1] = 0; map[x + 1][y + 1] = 0; map[x + 2][y + 1] = 0;
				map[x + 1][y] = 2; map[x][y + 1] = 2; map[x][y + 2] = 2;
				fkx[1] = x+1; fky[1] = y;
				fkx[2] = x ; fky[2] = y + 1;
				fkx[3] = x ; fky[3] = y + 2;
				fkx[5] = 1;
			}
		}
	}
	else if (fkx[4] == 6) {
		if (fkx[5] == 1) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (map[x ][y+1] == 1 || map[x + 1][y] == 1 || map[x + 2][y] == 1)iss = false;
			if (iss) {
				map[x + 1][y+2] = 0; map[x][y + 1] = 0; map[x][y + 2] = 0;
				map[x][y+1] = 2; map[x + 1][y] = 2; map[x + 2][y] = 2;
				fkx[1] = x; fky[1] = y+1;
				fkx[2] = x + 1; fky[2] = y;
				fkx[3] = x + 2; fky[3] = y;
				fkx[5] = 2;
			}
		}
		else if (fkx[5] == 2) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y + 2 >11)iss = false;
			if (map[x + 1][y] == 1 || map[x + 1][y + 1] == 1 || map[x + 1][y + 2] == 1)iss = false;
			if (iss) {
				map[x][y + 1] = 0; map[x + 1][y] = 0; map[x + 2][y] = 0;
				map[x + 1][y] = 2; map[x + 1][y + 1] = 2; map[x + 1][y + 2] = 2;
				fkx[1] = x + 1; fky[1] = y;
				fkx[2] = x + 1; fky[2] = y + 1;
				fkx[3] = x + 1; fky[3] = y + 2;
				fkx[5] = 3;
			}
		}
		else if (fkx[5] == 3) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y - 1 <0)iss = false;
			if (map[x+1][y] == 1 || map[x + 2][y] == 1 || map[x + 2][y - 1] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 1][y + 1] = 0; map[x + 1][y + 2] = 0;
				map[x+1][y] = 2; map[x + 2][y] = 2; map[x + 2][y - 1] = 2;
				fkx[1] = x+1; fky[1] = y ;
				fkx[2] = x + 2; fky[2] = y ;
				fkx[3] = x + 2; fky[3] = y - 1;
				fkx[5] = 4;
			}
		}
		else {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y + 2 >11)iss = false;
			if (map[x][y + 1] == 1 || map[x][y + 2] == 1 || map[x + 1][y+2] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 2][y] = 0; map[x + 2][y - 1] = 0;
				map[x][y+1] = 2; map[x][y + 2] = 2; map[x+1][y + 2] = 2;
				fkx[1] = x; fky[1] = y+1;
				fkx[2] = x; fky[2] = y + 2;
				fkx[3] = x+1; fky[3] = y + 2;
				fkx[5] = 1;
			}
		}
	}
	else {
		if (fkx[5] == 1) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (map[x+1][y] == 1 || map[x + 1][y+1] == 1 || map[x + 2][y] == 1)iss = false;
			if (iss) {
				map[x][y + 1] = 0; map[x][y + 2] = 0; map[x+1][y + 1] = 0;
				map[x+1][y] = 2; map[x + 1][y+1] = 2; map[x + 2][y] = 2;
				fkx[1] = x+1; fky[1] = y;
				fkx[2] = x + 1; fky[2] = y+1;
				fkx[3] = x + 2; fky[3] = y;
				fkx[5] = 2;
			}
		}
		else if (fkx[5] == 2) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y -1 <0)iss = false;
			if (map[x + 1][y-1] == 1 || map[x + 1][y] == 1 || map[x + 1][y + 1] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 1][y + 1] = 0; map[x + 2][y] = 0;
				map[x + 1][y-1] = 2; map[x + 1][y] = 2; map[x + 1][y + 1] = 2;
				fkx[1] = x + 1; fky[1] = y-1;
				fkx[2] = x + 1; fky[2] = y;
				fkx[3] = x + 1; fky[3] = y + 1;
				fkx[5] = 3;
			}
		}
		else if (fkx[5] == 3) {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (map[x + 1][y] == 1 || map[x + 2][y] == 1 || map[x + 1][y - 1] == 1)iss = false;
			if (iss) {
				map[x + 1][y - 1] = 0; map[x + 1][y] = 0; map[x + 1][y + 1] = 0;
				map[x + 1][y] = 2; map[x + 2][y] = 2; map[x + 1][y - 1] = 2;
				fkx[1] = x + 1; fky[1] = y;
				fkx[2] = x + 2; fky[2] = y;
				fkx[3] = x + 1; fky[3] = y - 1;
				fkx[5] = 4;
			}
		}
		else {
			int x = fkx[0], y = fky[0];
			bool iss = true;
			if (y + 2 >11)iss = false;
			if (map[x][y + 1] == 1 || map[x][y + 2] == 1 || map[x + 1][y +1] == 1)iss = false;
			if (iss) {
				map[x + 1][y] = 0; map[x + 2][y] = 0; map[x + 1][y - 1] = 0;
				map[x][y + 1] = 2; map[x][y + 2] = 2; map[x + 1][y + 1] = 2;
				fkx[1] = x; fky[1] = y+1;
				fkx[2] = x; fky[2] = y + 2;
				fkx[3] = x + 1; fky[3] = y + 1;
				fkx[5] = 1;
			}
		}
	}
	canc = true;
}
void mScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
void mScene::menuPCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	if (ispause) {
		Director::getInstance()->getScheduler()->resumeTargets(_pausedTargets);
		ispause = false;
	}
	else {
		_pausedTargets = Director::getInstance()->getScheduler()->pauseAllTargets();
		ispause = true;
	}
}
void mScene::menuRCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	for (int j = 0; j < 24; j++)
		for (int i = 0; i < 12; i++)
			map[j][i] = 0;
	soc = 0;  ischan = false; ischch = true; ispause = false;
	romd = CCRANDOM_0_1();
	fkcreate(romd);
	canc = true;
}
void mScene::menuChCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	char xxx[2] = "0";
	ndu++;speed += 10;
	if (ndu > 4) { ndu = 1; speed = 10.0; }
	xxx[0] ='0'+ndu;
	jbb->setString(xxx);
	sched1->setTimeScale(speed);
}