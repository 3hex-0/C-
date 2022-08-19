#ifndef _MAIN_H_
#define _MAIN_H_

#define UI_WIDTH  16 //��ʾ����Ŀ��
#define UI_HEIGHT 25 //����ĸ߶�
#define WALL 	  1
#define BLOCK     2
#define _VK_UP     72   //������������ҵĵڶ���ֵ,�����������ֵ,��һ����224,�ֱ���72,...
#define _VK_DOWN   80
#define _VK_LEFT   75
#define _VK_RIGHT  77
#define _VK_SPACE  0x20
#define _VK_ESC    0x1B
#define _VK_ENTER  0x0D
#define TRUE 	  1
#define FALSE     0
#define DEF_LEVEL 1
#define COLOR_LEN 12

#define GAME_DIV "  "
#define GAME_BLOCK "��"
#define GAME_WALL_H "��"
#define GAME_WALL_W "=="

void initia();			//��ʼ����һЩ����
void gameShow(); 	/*��Ϸ��ʾ����*/
void moveBlock(); 	/*������ƶ�*/
short isCanMoveBlock(short x, short y); 	//�Ƿ����ƶ�����
void produceBlock();   //��������
void toBottom(short x, short y);				//���鵽����֮��Ĳ��� ��bottom����
void wait(void);
int levelCalc(int level);
int gameMainMenu(void); 
void drawMainMenu(int nowIndex);
void drawDes(void);

struct _game_arr{
	short info;  //���������Ϸ���������
	short  var;  //������¼�������ĳ��λ���Ƿ�ռ�� ��������û���ƶ��ˣ�
	//��λ�òű�ռ�ã����ƶ��������Ǹ��ط���ռ�þͲ����ƶ��� ,��1��ʾռ�ã�0��ʾδռ��
}game_arr[UI_HEIGHT][UI_WIDTH];


typedef struct _block
{
    short a[4][2]; /*���巽����״�����飬ÿ�����鹲��4��С����ɣ�
	 ��4��2������¼ÿ��С�������� ���꣬ */
    short next; //��һ������ĺ���
}ST_BLOCK;

#endif

