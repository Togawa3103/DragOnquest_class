#include <time.h>
#include "DxLib.h"
#include "Player.h"
#include "MAP.h"
#include "Mode.h"

//�Z�[�u�f�[�^�̃f�[�^�\��
typedef struct {
	int Player_Lv;
	//PLAYER_STATUS Player_Status;    
	int Player_X;
	int Player_Y;
	int MAP_Num;
	int Screen_X;
	int Screen_Y;
	int Move_Count_X;
	int Move_Count_Y;
	int ItemBox_size;
	//std::vector<int> ItemBox;
}SaveData;

//�X�^�[�g��ʂ̑I����
enum {
	StartMenu_Start,
	StartMenu_Continue,
	StartMenu_Max,
};

//�X�^�[�g��ʂ̑I�����̕�����
typedef struct {
	const char* startmenu_name;
}StartMenu;

//�X�^�[�g��ʂ̑I�����̕�����
static StartMenu start[] = {
	{"�͂��߂���"},
	{"�Â�����"},
};

class Game {
public:
	Game(); //�R���X�g���N�^
	~Game(); //�f�X�g���N�g
	static void Initialize(); //������
	static void Game_Start(); //�X�^�[�g���
	static void Game_Main(); //���C�����[�v
	static int Game_StartDraw(); //�X�^�[�g��ʂ̕\��
	static void Save_Data(); //�Z�[�u
	static void Load_Date(); //���[�h
	static void Start(); //���߂���J�n
public:
	static int Game_Mode; //�Q�[���̏��
	static int FPS; //FPS
	static float mFPS; //1�t���[���̎���
	static clock_t end; //�O�t���[���̏I������
	static clock_t now; //���݂̎���
	static double looptime; //1�t���[���ɂ�����������
	static int comand; //�퓬���̃R�}���h
	static int select_magic; //�퓬���I�����Ă��閂�@
	static int select_item; //�퓬���I�����Ă���A�C�e��
	static bool Talk_now; //��b���Ă��邩
	
};