/****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
 **     the names of its contributors may be used to endorse or promote
 **     products derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #include <QtCore>

 #include <stdlib.h>

 #include "tetrixpiece.h"

 void TetrixPiece::setRandomShape()
 {
     setShape(TetrixShape(qrand() % 7 + 1));
 }

 void TetrixPiece::setShape(TetrixShape shape)
 {
     static const int coordsTable[8][4][2] = {
         { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
         { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
         { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
         { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
         { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
         { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
         { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
         { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
     };

     for (int i = 0; i < 4 ; i++) {
         for (int j = 0; j < 2; ++j)
             coords[i][j] = coordsTable[shape][i][j];
     }
     pieceShape = shape;
 }

 int TetrixPiece::minX() const
 {
     int min = coords[0][0];
     for (int i = 1; i < 4; ++i)
         min = qMin(min, coords[i][0]);
     return min;
 }

 int TetrixPiece::maxX() const
 {
     int max = coords[0][0];
     for (int i = 1; i < 4; ++i)
         max = qMax(max, coords[i][0]);
     return max;
 }

 int TetrixPiece::minY() const
 {
     int min = coords[0][1];
     for (int i = 1; i < 4; ++i)
         min = qMin(min, coords[i][1]);
     return min;
 }

 int TetrixPiece::maxY() const
 {
     int max = coords[0][1];
     for (int i = 1; i < 4; ++i)
         max = qMax(max, coords[i][1]);
     return max;
 }

 TetrixPiece *TetrixPiece::rotatedLeft() 
 {
     if (pieceShape == SquareShape)
         return this;
	 numOfRotated--; 
     TetrixPiece* result = new TetrixPiece;
	 *result = *this;
     result->pieceShape = pieceShape;
     for (int i = 0; i < 4; ++i) {
         result->setX(i, y(i));
         result->setY(i, -x(i));
     }
     return result;
 }

 TetrixPiece *TetrixPiece::rotatedRight() 
 {
     if (pieceShape == SquareShape)
         return this;
	 numOfRotated++;
     TetrixPiece *result = new TetrixPiece;
	 *result = *this;
     result->pieceShape = pieceShape;
     for (int i = 0; i < 4; ++i) {
         result->setX(i, -y(i));
         result->setY(i, x(i));
     }
     return result;
 }

 void TetrixPiece::changeShape(TetrixShape shape, int rotated)
 {
	 numOfRotated = rotated;
	 setShape(shape);
	 int direction = rotated < 0 ? 1 : -1;
	 rotated = qAbs(rotated);
	 for (int i = 0; i < rotated % 4; ++i) {
		 setX(i, direction * y(i));
		 setY(i, direction * - x(i));
	 }
 }