#pragma once
#define SINGLE(type) static type* GetInst()\
					{\
						 static type mgr;\
						return &mgr;\
					}
#define WINDOW_NAME L"Gameframework"
#define fDT TimeMgr::GetInst()->GetfDT()
#define DT TimeMgr::GetInst()->GetDT()
#define KEY_CHECK(key, state) KeyMgr::GetInst()->GetKey(key) == state
#define KEY_STAY(key) KEY_CHECK(key, KEY_STATE::STAY)
#define KEY_DOWN(key) KEY_CHECK(key, KEY_STATE::DOWN)
#define KEY_UP(key) KEY_CHECK(key, KEY_STATE::UP)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define CLONE(type) type* Clone() {return new type(*this);}
#define PI 3.1415926535897932384f

#define SCREEN_WIDTH 650	
#define SCREEN_HEIGHT 700

#define MAX_BLOCK_COUNT 12
#define DEFAULT_MAX_TIME 60

enum class KEY_STATE
{
	NONE, // ������ �ʾҰ�, �������� ������ �ʴ� ����
	DOWN, // �� ���� ����
	STAY, // ������ �ִ�
	UP, // �� �� ����(���� ������ �������ִ�)
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,
	ALT, LSHIFT, CTRL, SPACE, ENTER, ESC,
	LBTN, RBTN,
	LAST // �� (END=�� �����ϱ�)
};

enum class GROUP_TYPE
{
	DEFAULT,
	UI,
	END = 32,
};

enum class SCENE_TYPE
{
	DEFAULT,
	TITLE,
	END
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END,
};

enum class BOX_TYPE
{
	NONE = -1,
	GFC,
	HOSIC,
	KYOCHON,
	PERICANA,
	PURADAC,

	END,
};

enum class GAME_STATE
{
	TITLE,
	SPAWNBLOCK,
	GAME,
	GAMEOVER,
	GAMECLEAR
};