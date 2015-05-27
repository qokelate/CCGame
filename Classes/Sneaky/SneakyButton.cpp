#include "SneakyButton.h"

void SneakyButton::onEnterTransitionDidFinish()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SneakyButton::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SneakyButton::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SneakyButton::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SneakyButton::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SneakyButton::onExit()
{

}

bool SneakyButton::initWithRect(Rect rect)
{
	bool pRet = false;
	//if(CCSprite::init()){
		
		bounds = Rect(0, 0, rect.size.width, rect.size.height);
		center = Point(rect.size.width/2, rect.size.height/2);
		status = true; //defaults to enabled
		active = false;
		value = false;
		isHoldable = false;
		isToggleable = false;
		radius = 32.0f;
		rateLimit = 1.0f/120.0f;
		
		setPosition(rect.origin); //not sure about this
		pRet = true;
	//}
	return pRet;
}

void SneakyButton::limiter(float delta)
{
	value = false;
	this->unschedule(schedule_selector(SneakyButton::limiter));
	active = false;
}

void SneakyButton::setRadius(float r)
{
	radius = r;
	radiusSq = r*r;
}

bool SneakyButton::onTouchBegan(Touch *touch, Event *event)
{
	if (active) return false;
	
	Point location =
		Director::getInstance()->convertToGL(touch->getLocationInView());
	location = this->convertToNodeSpace(location);
		//Do a fast rect check before doing a circle hit check:
	if(location.x < -radius || location.x > radius 
		|| location.y < -radius || location.y > radius){
		return false;
	}else{
		float dSq = location.x*location.x + location.y*location.y;
		if(radiusSq > dSq){
			active = true;
			if (!isHoldable && !isToggleable){
				value = true;
				this->schedule(schedule_selector(SneakyButton::limiter), rateLimit);
			}
			if (isHoldable) value = true;
			if (isToggleable) value = !value;
			return true;
		}
	}
	return false;
}

void SneakyButton::onTouchMoved(Touch *touch, Event *event)
{
	if (!active) return;
	
	Point location = Director::getInstance()->convertToGL(touch->getLocationInView());
	location = this->convertToNodeSpace(location);
		//Do a fast rect check before doing a circle hit check:
	if(location.x < -radius || location.x > radius 
		|| location.y < -radius || location.y > radius){
		return;
	}else{
		float dSq = location.x*location.x + location.y*location.y;
		if(radiusSq > dSq){
			if (isHoldable) value = true;
		}
		else {
			if (isHoldable) value = false; active = false;
		}
	}
}

void SneakyButton::onTouchEnded(Touch *touch, Event *event)
{
	if (!active) return;
	if (isHoldable) value = false;
	if (isHoldable||isToggleable) active = false;
}

void SneakyButton::onTouchCancelled(Touch *touch, Event *event)
{
	this->onTouchEnded(touch, event);
}
