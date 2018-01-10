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
#include <QtWidgets>
#include <qlayout.h>

#include "tetrixboard.h"
#include "tetrixwindowWWK.h"
#include "tetrixcontroller.h"

/*
2015-10-29
�N��ܫO�d���Label�s�W��Layout
*/
TetrixWindowWWK::TetrixWindowWWK()
{
	board = new TetrixBoard;
	m_pController = new TetrixController(nullptr, board);
	board->m_pController = m_pController;
	board->setStyleSheet("background-color : rgb(249, 188, 255);");

	holdPieceLabel = new QLabel;
	holdPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
	holdPieceLabel->setAlignment(Qt::AlignCenter);
	holdPieceLabel->setStyleSheet("background-color : rgb(241, 248, 255);");
	board->setHoldPieceLabel(holdPieceLabel);

	nextPieceLabel = new QLabel;
	nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
	nextPieceLabel->setAlignment(Qt::AlignCenter);
	nextPieceLabel->setStyleSheet("background-color : rgb(241, 248, 255);");
	board->setNextPieceLabel(nextPieceLabel);

	scoreLcd = new QLCDNumber(5);
	scoreLcd->setSegmentStyle(QLCDNumber::Filled);
	scoreLcd->setStyleSheet("background-color : rgb(241, 248, 255);");
	levelLcd = new QLCDNumber(2);
	levelLcd->setSegmentStyle(QLCDNumber::Filled);
	levelLcd->setPalette(Qt::black);
	levelLcd->setStyleSheet("background-color : rgb(241, 248, 255);");
	linesLcd = new QLCDNumber(5);
	linesLcd->setSegmentStyle(QLCDNumber::Filled);
	linesLcd->setStyleSheet("background-color : rgb(241, 248, 255);");

	startButton = new QPushButton(tr("&Start"));
	startButton->setFocusPolicy(Qt::NoFocus);
	quitButton = new QPushButton(tr("&Quit"));
	quitButton->setFocusPolicy(Qt::NoFocus);
	pauseButton = new QPushButton(tr("&Pause"));
	pauseButton->setFocusPolicy(Qt::NoFocus);

	connect(startButton, SIGNAL(clicked()), m_pController, SLOT(start()));
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(pauseButton, SIGNAL(clicked()), m_pController, SLOT(pause()));

	connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
	connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
	connect(board, SIGNAL(linesRemovedChanged(int)),
			linesLcd, SLOT(display(int)));

	QGridLayout *layout = new QGridLayout;

	layout->addWidget(createLabel(tr("NEXT")), 0, 0);
	layout->addWidget(nextPieceLabel, 1, 0);
	layout->addWidget(createLabel(tr("HOLD")), 2, 0);
	layout->addWidget(holdPieceLabel, 3, 0);

	layout->addWidget(createLabel(tr("LEVEL")), 4, 0);
	layout->addWidget(levelLcd, 5, 0);
	layout->addWidget(startButton, 6, 1);
	layout->addWidget(board, 0, 1, 6, 1);
	layout->addWidget(createLabel(tr("SCORE")), 0, 2);
	layout->addWidget(scoreLcd, 1, 2);
	layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
	layout->addWidget(linesLcd, 3, 2);
	layout->addWidget(quitButton, 4, 2);
	layout->addWidget(pauseButton, 5, 2);

	//layout->addWidget(multiPlayerBoard, 0, 3, 6, 1);
	///createMultiPlayerBoard(layout);
	setLayout(layout);

	//multiPlayerBoard->setEnabled(false);
	setWindowTitle(tr("Tetrix@WWK"));
	resize(450, 370);
}

QLabel *TetrixWindowWWK::createLabel(const QString &text)
{
	QLabel *lbl = new QLabel(text);
	lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	lbl->setStyleSheet("color: rgb(183, 0, 51);");
	return lbl;
}