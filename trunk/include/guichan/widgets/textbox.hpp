/*
 *    _aaaa,  _aa.  sa,  aaa              _aaaa,_  ac  .aa.   .aa.  .aa,  _a, sa
 *  .wWV!!!T  |Wm;  dQ[  $WF            _mWT!"?Y  ]QE  :Q#:   ]QW[  :WWk. ]Q[ dW
 * .jWf       :WW: .dQ[  dQ[           .mW(       )WE  :Q#:  .mSQh. :mWQa.]W[ dQ
 * |QW:       :Wm;  mQ[  dQ[           ]Qk        )Qmi_aQW:  <B:$Qc :WBWQ()W[ dQ
 * |W#:  .ww  ;WW;  dQ[  dQ[  .......  ]Qk        )QB?YYW#:  jf ]Qp.:mE)Qm]Q[ )W
 * +WQ;  :Wm  |Wm; .mQ[  dQ[ :qgggggga ]Qm.       ]WE  :Q# :=QasuQm;:Wk 3QQW[ )Y
 *  ]Wmi.:Wm  +$Q; .mW(  dQ[  !"!!"!!^ dQk,  ._   ]WE  :Q# :3D"!!$Qc.Wk -$WQ[   
 *   "?????? ` "?!=m?!   ??'            -??????!  -?!  -?? -?'   "?"-?"  "??' "?
 *
 * Copyright (c) 2004 darkbits                              Js_./
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
 * 3. Neither the name of darkbits nor the     :$we` _! + _/ .        j?
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

#ifndef GCN_TEXTBOX_HPP
#define GCN_TEXTBOX_HPP

#include <string>
#include <vector>

#include "guichan/platform.hpp"
#include "guichan/widget.hpp"

namespace gcn
{
	/**
	 * This is a TextBox. It is used for displaying text. A TextBox can also
	 * be used for editing of text.
	 *
	 * NOTE: A plain TextBox is really uggly and looks much better inside a
	 *       ScrollArea.
	 */
	class DECLSPEC TextBox:
		public Widget,
		public MouseListener,
		public KeyListener
	{
	public:
		/**
		 * Constructor.
		 */
		TextBox();

		/**
		 * Constructor.
		 *
		 * @param text the text of the TextBox.
		 */
		TextBox(const std::string& text);

		/**
		 * Sets the text of the TextBox.
		 *
		 * @param text the text of the TextBox.
		 */
		virtual void setText(const std::string& text);

		/**
		 * @return the text of the TextBox.
		 */
		virtual std::string getText() const;

		/**
		 * @return the text of a certain row in the TextBox.
		 */
		virtual const std::string& getTextRow(int row) const;

		/**
		 * Sets the text of a certain row in a TextBox.
		 *
		 * @param row the row number.
		 * @param text the text of a certain row in the TextBox.
		 */
		virtual void setTextRow(int row, const std::string& text);

		/**
		 * @return the number of rows in the TextBox.
		 */
		virtual unsigned int getNumberOfRows() const;   

		/**
		 * @return the caret position in the text.
		 */
		virtual unsigned int getCaretPosition() const;

		/**
		 * Sets the position of the caret in the text.
		 *
		 * @param position the positon of the caret.
		 */
		virtual void setCaretPosition(unsigned int position);

		/**
		 * @return the row the caret is in in the text.
		 */
		virtual unsigned int getCaretRow() const;

		/**
		 * Sets the row the caret should be in in the text.
		 *
		 * @param row the row number.
		 */
		virtual void setCaretRow(int row);
				
		/**
		 * @return the column the caret is in in the text.
		 */
		virtual unsigned int getCaretColumn() const;

		/**
		 * Sets the column the caret should be in in the text.
		 *
		 * @param column the column number.
		 */		
		virtual void setCaretColumn(int column);
		
		/**
		 * Sets the row and the column the caret should be in in the text.
		 *
		 * @param row the row number.
		 * @param the column number.
		 */
		virtual void setCaretRowColumn(int row, int column);

		/**
		 * Scrolls the TextBox to the caret if the TextBox is in a ScrollArea.
		 */
		virtual void scrollToCaret();

		/**
		 * @return true it the TextBox is editable.
		 */     
		virtual bool isEditable() const;
		
		/**
		 * Sets if the TextBox should be editable or not.
		 *
		 * @param editable true if the TextBox should be editable.
		 */
		virtual void setEditable(bool editable);

		/**
		 * Adds a text row to the text.
		 *
		 * @param row a row.
		 */
		virtual void addRow(const std::string row);

		
		// Inherited from Widget
		
		virtual void draw(Graphics* graphics);

		virtual void fontChanged();
		
		virtual void lostFocus();


		// Inherited from KeyListener

		virtual void keyPress(const Key& key);

		
		// Inherited from MouseListener
		
		virtual void mousePress(int x, int y, int button);

		
	protected:
		/**
		 * Draws the caret.
		 *
		 * @param graphis a Graphics object.
		 * @param x the x position.
		 * @param y the y position.
		 */
		virtual void drawCaret(Graphics* graphics, int x, int y);
		
		/**
		 * Adjusts the TextBox size to fit the font size.
		 */
		virtual void adjustSize();
    
		std::vector<std::string> mTextRows;
		int mCaretColumn;
		int mCaretRow;
		bool mEditable;
    
	}; // end TextBox
  
} // end gcn

#endif // end GCN_TEXTBOX_HPP