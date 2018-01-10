#pragma once
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "tetrixboard.h"
#include "tetrixpiece.h"
#include "tetrixoperationcode.h"

class QLabel;
class TetrixController : public QFrame
{
	friend class TetrixBoard;

	Q_OBJECT
private:
	TetrixBoard* m_pBoard;

public:
	TetrixController(QWidget *parent, TetrixBoard* pBoard);

protected:
	void paintEvent(QPaintEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void timerEvent(QTimerEvent *event);

public slots:
	void start();
	void pause();

public:
	TetrixShape &shapeAt(int x, int y) { return m_pBoard->shapeAt(x, y); }
	int timeoutTime() { return 1000 / (m_nLevel); }

	void dropDown();
	void oneLineDown();
	void pieceDropped(int dropHeight);
	void removeFullLines();
	void newPiece();
	void showNextPiece();
	TetrixPiece* getNextPiece(); // 10-29 取得群組中的下一個方塊
	void generateNextPieces(); // 10-29 隨機產生 7 個不同方塊至群組中
	bool tryMove(TetrixPiece *newPiece, int newX, int newY);

private:
	const static int MAX_SHAPES = 7;
	enum { 
		BoardWidth = 10, 
		BoardHeight = 22 
	};

	QBasicTimer m_timer;
	bool m_bShiftPress,  // 10-29 表示shift按下?
		     m_bIsStarted, m_bIsPaused, m_bIsWaitingAfterLine, m_bIsControllable;

	TetrixPiece* m_pCurPiece, * m_pNextPiece, *m_pHoldPiece = nullptr; // 10-29 保留之方塊
	TetrixPiece* m_apNextPieceGroup[MAX_SHAPES]; // 10-29 方塊群組
	int m_nCurPieceIdx, m_nLinesRemoved, m_nPiecesDropped, m_nScore, m_nLevel;

};