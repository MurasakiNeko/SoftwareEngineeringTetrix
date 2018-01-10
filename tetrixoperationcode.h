#ifndef TETRIXOPERATIONCODE
#define TETRIXOPERATIONCODE

enum class TetrixServerOperation
{
    /*
     Master Server Operation
    */
    mConnectRespond = 0x01,
    mWaitingForPlayer,
    mPlayerInfoRespond,
    mPrepareHostP2PServer,
    /*
     P2P Operation
    */
	mP2PConnectEchoRespond = 0x0601,
	mP2PPlayerActionInfo,
};

enum class TetrixClientOperation
{
    /*
     Master Server Operation
    */
    mConnectFlag = 0x01,
    mAskPlayerInfo,

    /*
     P2P Operation
    */
    mP2PConnectEcho = 0x0601,
    mP2PPlayerActionInfo,
};

enum class TetrixAction
{
	mEcho = 0x00,
	mStartGame,
	mChangeShape,
	mNewPiece,
	mOneLineDown,
	mMoveLeft,
	mMoveRight,
	mMoveDown,
	mRotateLeft,
	mRotateDown,
	mPieceDown,
	mKeyEvent,
};

#endif // TETRIXOPERATIONCODE

