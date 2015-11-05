/*
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * Full license: https://github.com/dimkanovikov/WidgetAnimationFramework/blob/master/LICENSE
 */

#include "Animation.h"
#include "AnimationPrivate.h"
#include "AbstractAnimator.h"

#include "SideSlide/SideSlideAnimator.h"
#include "Slide/SlideAnimator.h"

using WAF::Animation;
using WAF::AnimationPrivate;
using WAF::AbstractAnimator;
using WAF::SideSlideAnimator;
using WAF::SlideAnimator;


void Animation::sideSlideIn(QWidget* _widget, WAF::ApplicationSide _side)
{
	const bool IN = true;
	sideSlide(_widget, _side, IN);
}

void Animation::sideSlideOut(QWidget* _widget, WAF::ApplicationSide _side)
{
	const bool OUT = false;
	sideSlide(_widget, _side, OUT);
}

void Animation::sideSlide(QWidget* _widget, WAF::ApplicationSide _side, bool _in)
{
	const WAF::AnimatorType animatorType = WAF::SideSlide;
	AbstractAnimator* animator = 0;
	if (pimpl()->hasAnimator(_widget, animatorType)) {
		animator = pimpl()->animator(_widget, animatorType);
	} else {
		SideSlideAnimator* sideSlideAnimator = new SideSlideAnimator(_widget);
		sideSlideAnimator->setApplicationSide(_side);
		animator = sideSlideAnimator;

		pimpl()->saveAnimator(_widget, animator, animatorType);
	}

	if (_in) {
		animator->animateForward();
	} else {
		animator->animateBackward();
	}
}

void Animation::slideIn(QWidget* _widget, WAF::AnimationDirection _direction)
{
	const bool IN = true;
	slide(_widget, _direction, IN);
}

void Animation::slideOut(QWidget* _widget, WAF::AnimationDirection _direction)
{
	const bool OUT = false;
	slide(_widget, _direction, OUT);
}

void Animation::slide(QWidget* _widget, WAF::AnimationDirection _direction, bool _in)
{
	const WAF::AnimatorType animatorType = WAF::Slide;
	AbstractAnimator* animator = 0;
	if (pimpl()->hasAnimator(_widget, animatorType)) {
		animator = pimpl()->animator(_widget, animatorType);
	} else {
		SlideAnimator* slideAnimator = new SlideAnimator(_widget);
		slideAnimator->setAnimationDirection(_direction);
		animator = slideAnimator;

		pimpl()->saveAnimator(_widget, animator, animatorType);
	}

	if (_in) {
		animator->animateForward();
	} else {
		animator->animateBackward();
	}
}

AnimationPrivate* Animation::m_pimpl = 0;
AnimationPrivate* Animation::pimpl()
{
	if (m_pimpl == 0) {
		m_pimpl = new AnimationPrivate;
	}

	return m_pimpl;
}
