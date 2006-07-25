/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004, 2005, 2006 Olof Naess�n and Per Larsson
 *
 *                                                         Js_./
 * Per Larsson a.k.a finalman                          _RqZ{a<^_aa
 * Olof Naess�n a.k.a jansem/yakslem                _asww7!uY`>  )\a//
 *                                                 _Qhm`] _f "'c  1!5m
 * Visit: http://guichan.darkbits.org             )Qk<P ` _: :+' .'  "{[
 *                                               .)j(] .d_/ '-(  P .   S
 * License: (BSD)                                <Td/Z <fP"5(\"??"\a.  .L
 * Redistribution and use in source and          _dV>ws?a-?'      ._/L  #'
 * binary forms, with or without                 )4d[#7r, .   '     )d`)[
 * modification, are permitted provided         _Q-5'5W..j/?'   -?!\)cam'
 * that the following conditions are met:       j<<WP+k/);.        _W=j f
 * 1. Redistributions of source code must       .$%w\/]Q  . ."'  .  mj$
 *    retain the above copyright notice,        ]E.pYY(Q]>.   a     J@\
 *    this list of conditions and the           j(]1u<sE"L,. .   ./^ ]{a
 *    following disclaimer.                     4'_uomm\.  )L);-4     (3=
 * 2. Redistributions in binary form must        )_]X{Z('a_"a7'<a"a,  ]"[
 *    reproduce the above copyright notice,       #}<]m7`Za??4,P-"'7. ).m
 *    this list of conditions and the            ]d2e)Q(<Q(  ?94   b-  LQ/
 *    following disclaimer in the                <B!</]C)d_, '(<' .f. =C+m
 *    documentation and/or other materials      .Z!=J ]e []('-4f _ ) -.)m]'
 *    provided with the distribution.          .w[5]' _[ /.)_-"+?   _/ <W"
 * 3. Neither the name of Guichan nor the      :$we` _! + _/ .        j?
 *    names of its contributors may be used     =3)= _f  (_yQmWW$#(    "
 *    to endorse or promote products derived     -   W,  sQQQQmZQ#Wwa]..
 *    from this software without specific        (js, \[QQW$QWW#?!V"".
 *    prior written permission.                    ]y:.<\..          .
 *                                                 -]n w/ '         [.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT       )/ )/           !
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY         <  (; sac    ,    '
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING,               ]^ .-  %
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF            c <   r
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR            aga<  <La
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          5%  )P'-3L
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR        _bQf` y`..)a
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          ,J?4P'.P"_(\?d'.,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES               _Pa,)!f/<[]/  ?"
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT      _2-..:. .r+_,.. .
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     ?a.<%"'  " -'.a_ _,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION)                     ^
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/basiccontainer.hpp"

#include <algorithm>

#include "guichan/exception.hpp"
#include "guichan/focushandler.hpp"
#include "guichan/graphics.hpp"
#include "guichan/mouseinput.hpp"

namespace gcn
{
    BasicContainer::BasicContainer()
    {
        mWidgetWithMouse = NULL;
        mMouseInputPolicy = NOT_ON_CHILD;
        mInternalFocusHandler = NULL;
    }

    BasicContainer::~BasicContainer()
    {
        clear();
    }

    void BasicContainer::moveToTop(Widget* widget)
    {
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if (*iter == widget)
            {
                mWidgets.erase(iter);
                mWidgets.push_back(widget);
                return;
            }
        }

        throw GCN_EXCEPTION("There is no such widget in this container.");
    }

    void BasicContainer::moveToBottom(Widget* widget)
    {
        WidgetListIterator iter;
        iter = find(mWidgets.begin(), mWidgets.end(), widget);

        if (iter == mWidgets.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this container.");
        }
        mWidgets.erase(iter);
        mWidgets.push_front(widget);
    }

    void BasicContainer::_announceDeath(Widget *widget)
    {
        if (mWidgetWithMouse == widget)
        {
            mWidgetWithMouse = NULL;
        }

        WidgetListIterator iter;
        iter = find(mWidgets.begin(), mWidgets.end(), widget);

        if (iter == mWidgets.end())
        {
            throw GCN_EXCEPTION("There is no such widget in this container.");
        }

        mWidgets.erase(iter);
    }

    Rectangle BasicContainer::getChildrenArea()
    {
        return Rectangle(0, 0, getWidth(), getHeight());
    }

    void BasicContainer::focusNext()
    {
        WidgetListIterator it;

        for (it = mWidgets.begin(); it != mWidgets.end(); it++)
        {
            if ((*it)->isFocused())
            {
                break;
            }
        }

        WidgetListIterator end = it;

        if (it == mWidgets.end())
        {
            it = mWidgets.begin();
        }

        it++;

        for ( ; it != end; it++)
        {
            if (it == mWidgets.end())
            {
                it = mWidgets.begin();
            }

            if ((*it)->isFocusable())
            {
                (*it)->requestFocus();
                return;
            }
        }
    }

    void BasicContainer::focusPrevious()
    {
        WidgetListReverseIterator it;

        for (it = mWidgets.rbegin(); it != mWidgets.rend(); it++)
        {
            if ((*it)->isFocused())
            {
                break;
            }
        }

        WidgetListReverseIterator end = it;

        it++;

        if (it == mWidgets.rend())
        {
            it = mWidgets.rbegin();
        }

        for ( ; it != end; it++)
        {
            if (it == mWidgets.rend())
            {
                it = mWidgets.rbegin();
            }

            if ((*it)->isFocusable())
            {
                (*it)->requestFocus();
                return;
            }
        }
    }

    Widget *BasicContainer::getWidgetAt(int x, int y)
    {
        Rectangle r = getChildrenArea();

        if (!r.isPointInRect(x, y))
        {
            return NULL;
        }

        x -= r.x;
        y -= r.y;

        WidgetListReverseIterator it;
        for (it = mWidgets.rbegin(); it != mWidgets.rend(); it++)
        {
            if ((*it)->isVisible() && (*it)->getDimension().isPointInRect(x, y))
            {
                return (*it);
            }
        }

        return NULL;
    }

    void BasicContainer::logic()
    {
        logicChildren();
    }

    void BasicContainer::_setFocusHandler(FocusHandler* focusHandler)
    {
        Widget::_setFocusHandler(focusHandler);

        if (mInternalFocusHandler != NULL)
        {
            return;
        }


        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            (*iter)->_setFocusHandler(focusHandler);
        }
    }

    void BasicContainer::_mouseInputMessage(const MouseInput& mouseInput)
    {
        Widget *newWidgetWithMouse;

        newWidgetWithMouse = getWidgetAt(mouseInput.x, mouseInput.y);

        if (newWidgetWithMouse != mWidgetWithMouse)
        {
            if (mWidgetWithMouse != NULL)
            {
                mWidgetWithMouse->_mouseOutMessage();
            }

            if (newWidgetWithMouse != NULL)
            {
                newWidgetWithMouse->_mouseInMessage();
            }

            mWidgetWithMouse = newWidgetWithMouse;
        }

        if (mWidgetWithMouse != NULL)
        {
            MouseInput mi = mouseInput;
            Rectangle ca = getChildrenArea();
            mi.x -= mWidgetWithMouse->getX() + ca.x;
            mi.y -= mWidgetWithMouse->getY() + ca.y;

            // Clamp the input to widget edges
            if (mi.x < 0)
            {
                mi.x = 0;
            }

            if (mi.y < 0)
            {
                mi.y = 0;
            }

            if (mi.x >= mWidgetWithMouse->getWidth())
            {
                mi.x = mWidgetWithMouse->getWidth() - 1;
            }

            if (mi.y >= mWidgetWithMouse->getHeight())
            {
                mi.y = mWidgetWithMouse->getHeight() - 1;
            }

            mWidgetWithMouse->_mouseInputMessage(mi);
        }

        if (mInternalFocusHandler != NULL)
        {
            Widget *f = mInternalFocusHandler->getFocused();
            Widget *d = mInternalFocusHandler->getDragged();

            if (f != NULL && !f->hasMouse() && isFocused())
            {
                MouseInput mi = mouseInput;
                Rectangle ca = getChildrenArea();
                mi.x -= f->getX() + ca.x;
                mi.y -= f->getY() + ca.y;

                f->_mouseInputMessage(mi);
            }

            if (d != NULL && f != d && !d->hasMouse() && isDragged())
            {
                MouseInput mi = mouseInput;
                Rectangle ca = getChildrenArea();
                mi.x -= d->getX() + ca.x;
                mi.y -= d->getY() + ca.y;

                d->_mouseInputMessage(mi);
            }
        }

        bool toContainer = isDragged();

        switch (mMouseInputPolicy)
        {
          case NEVER:
              break;
          case ALWAYS:
              toContainer = true;
              break;
          case NOT_ON_CHILD:
              if (mWidgetWithMouse == NULL)
              {
                  toContainer = true;
              }
              break;
          case NOT_IN_CHILDREN_AREA:
              if (!getChildrenArea().isPointInRect(mouseInput.x, mouseInput.y))
              {
                  toContainer = true;
              }
          default:
              throw GCN_EXCEPTION("Unknown mouse input policy");
        }

        if (toContainer)
        {
            Widget::_mouseInputMessage(mouseInput);
        }
    }

    void BasicContainer::_mouseOutMessage()
    {
        if (mWidgetWithMouse != NULL)
        {
            mWidgetWithMouse->_mouseOutMessage();
            mWidgetWithMouse = NULL;
        }

        Widget::_mouseOutMessage();
    }

    void BasicContainer::add(Widget* widget)
    {
        mWidgets.push_back(widget);
        /// @todo internal focushandler

        if (mInternalFocusHandler == NULL)
        {
            widget->_setFocusHandler(_getFocusHandler());
        }
        else
        {
            widget->_setFocusHandler(mInternalFocusHandler);
        }

        widget->_setParent(this);
    }

    void BasicContainer::remove(Widget* widget)
    {
        if (widget == mWidgetWithMouse)
        {
            mWidgetWithMouse = NULL;
        }

        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if (*iter == widget)
            {
                mWidgets.erase(iter);
                widget->_setFocusHandler(NULL);
                widget->_setParent(NULL);
                return;
            }
        }

        throw GCN_EXCEPTION("There is no such widget in this container.");
    }

    void BasicContainer::clear()
    {
        mWidgetWithMouse = NULL;

        WidgetListIterator iter;

        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            (*iter)->_setFocusHandler(NULL);
            (*iter)->_setParent(NULL);
        }

        mWidgets.clear();
    }

    void BasicContainer::drawChildren(Graphics* graphics)
    {
        graphics->pushClipArea(getChildrenArea());

        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if ((*iter)->isVisible())
            {
                // If the widget has a border,
                // draw it before drawing the widget
                if ((*iter)->getBorderSize() > 0)
                {
                    Rectangle rec = (*iter)->getDimension();
                    rec.x -= (*iter)->getBorderSize();
                    rec.y -= (*iter)->getBorderSize();
                    rec.width += 2 * (*iter)->getBorderSize();
                    rec.height += 2 * (*iter)->getBorderSize();
                    graphics->pushClipArea(rec);
                    (*iter)->drawBorder(graphics);
                    graphics->popClipArea();
                }

                graphics->pushClipArea((*iter)->getDimension());
                (*iter)->draw(graphics);
                graphics->popClipArea();
            }
        }

        graphics->popClipArea();
    }

    void BasicContainer::logicChildren()
    {
        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            (*iter)->logic();
        }
    }

    void BasicContainer::setMouseInputPolicy(unsigned int policy)
    {
        mMouseInputPolicy = policy;
    }

    unsigned int BasicContainer::getMouseInputPolicy()
    {
        return mMouseInputPolicy;
    }

    void BasicContainer::showWidgetPart(Widget* widget, Rectangle area)
    {
        Rectangle widgetArea = getChildrenArea();
        area.x += widget->getX();
        area.y += widget->getY();

        if (area.x + area.width > widgetArea.width)
        {
            widget->setX(widget->getX() - area.x - area.width + widgetArea.width);
        }

        if (area.y + area.height > widgetArea.height)
        {
            widget->setY(widget->getY() - area.y - area.height + widgetArea.height);
        }

        if (area.x < 0)
        {
            widget->setX(widget->getX() - area.x);
        }

        if (area.y < 0)
        {
            widget->setY(widget->getY() - area.y);
        }
    }

    FocusHandler* BasicContainer::getInternalFocusHandler()
    {
        return mFocusHandler;
    }

    void BasicContainer::setInternalFocusHandler(FocusHandler* focusHandler)
    {
        mInternalFocusHandler = focusHandler;

        WidgetListIterator iter;
        for (iter = mWidgets.begin(); iter != mWidgets.end(); iter++)
        {
            if (mInternalFocusHandler == NULL)
            {
                (*iter)->_setFocusHandler(_getFocusHandler());
            }
            else
            {
                (*iter)->_setFocusHandler(mInternalFocusHandler);
            }
        }
    }

    void BasicContainer::_keyInputMessage(const KeyInput& keyInput)
    {
        if (mInternalFocusHandler != NULL && mInternalFocusHandler->getFocused() != NULL)
        {
            mInternalFocusHandler->getFocused()->_keyInputMessage(keyInput);
        }
        else
        {
            Widget::_keyInputMessage(keyInput);
        }
    }
}
