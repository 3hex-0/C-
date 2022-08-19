#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
//#include <winuser.h>
#include "main.h"
#include "gui_menu_tool.h"

short cur_block_coord_x ,cur_block_coord_y; //��ǰ����ĺ����꼰������
int blockRandColor = 0, colorCount=0;
int nowLevel = DEF_LEVEL;

//int game_arr[UI_HEIGHT][UI_WIDTH]; //��Ϸ�Ľ�������
short next_blockarr[4][4];			//���������һ�����������
short cur_boxindex,next_boxindex; //��¼��ǰ������±����һ��������±�
int score;  //�ɼ�
char player_name[10] = "3hex" ;    //��ҵ�����
HANDLE hOutput;

int levelSpeed[11] = {30,25,21,17,14,11,8,5,3,1,0};

ST_BLOCK block[19]= {
	//��ʼ��������Ϸ����, �ܹ���19�ܷ�����״
	{1,1,1,2,1,3,2,3,1},
	{0,2,1,2,2,2,0,3,2},
	{0,1,1,1,1,2,1,3,3},
	{2,1,0,2,1,2,2,2,0},
	{1,1,1,2,0,3,1,3,5},
	{0,1,0,2,1,2,2,2,6},
	{1,1,2,1,1,2,1,3,7},
	{0,2,1,2,2,2,2,3,4},
	{1,1,0,2,1,2,2,2,9},
	{1,1,1,2,2,2,1,3,10},
	{0,2,1,2,2,2,1,3,11},
	{1,1,0,2,1,2,1,3,8},
	{1,1,1,2,2,2,2,3,13},
	{1,2,2,2,0,3,1,3,12},
	{2,1,1,2,2,2,1,3,15},
	{0,2,1,2,1,3,2,3,14},
	{1,0,1,1,1,2,1,3,17},
	{0,2,1,2,2,2,3,2,16},
	{1,1,2,1,1,2,2,2,18},
};

int GMT_F_Array[COLOR_LEN] = {GMT_F_HALF_BLUE, GMT_F_HALF_GREEN,
                              GMT_F_HALF_LIGHT_BLUE, GMT_F_HALF_RED,
                              GMT_F_HALF_PURPLE, GMT_F_HALF_YELLOW, GMT_F_HALF_GRAY,
                              GMT_F_BLUE, GMT_F_GREEN, GMT_F_LIGHT_BLUE,
                              GMT_F_RED, GMT_F_PURPLE
                             };

void main() {
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(TEXT("����˹����"));

	srand((unsigned int)time(NULL));

	SMALL_RECT rc = {0,0,UI_WIDTH*3+15,UI_HEIGHT+3};  //���ô��ڴ�С����Ⱥ͸߶�
	SetConsoleWindowInfo(hOutput,TRUE,&rc);
	srand(time(NULL));

GMMenu:
	// ��Ϸ��ʼ�˵�
	switch(gameMainMenu()){
		case -1:
			exit(0);
			break;
		case 1:
			break;
		case 2:
			drawDes(); 
			goto GMMenu;
	}

	initia();
	//���ػ������Ĺ��
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize =1;
	SetConsoleCursorInfo(hOutput, &cci);

	produceBlock();
	moveBlock();
}
void initia() {
	//��ʼ����һЩ����
	short i,j;
	
	for(i = 0; i < UI_HEIGHT; i++) {
		for(j = 0; j < UI_WIDTH; j++) {
			if(i == 0 || i == UI_HEIGHT-1) {
				game_arr[i][j].info = WALL;    //.var=1��ʾ�õ㱻ռ��
				game_arr[i][j].var = 1;
				continue;
			}
			if(j == 0 || j == UI_WIDTH-1)  {
				game_arr[i][j].info = WALL;
				game_arr[i][j].var = 1;
				continue;
			}
		}
	}
	//printf("\n\n\t��ӭ��ĵ���\n\t��������һ���ǳư�!>:");
	//scanf("%s",&player_name);
	next_boxindex =  rand() % 19;	 //��һ��Ҫ���������������
}

void drawDes(void) {
	short i,j;

	system("cls");
	
	setConsoleTextColor(GMT_B_BLACK, GMT_F_WHITE);
	printf("\n\n\n\n\t\t    ���������������������~�}�|�z�y\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_BLUE);
	printf("\t\t    �� �� �� ˹ �� �� ���~�}�|�z�y\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_RED);
	printf("\t\t    ���������������������~�}�|�z�y\n\n\n");
	resetAll();

	for(i = 0; i < UI_HEIGHT; i++) {
		if(i==2) {
			printf("\t\t��ͨ���̶����򰴼����������ƶ�����ת\n\n");
		}else if(i==4){
			printf("\t\t��ʹ����Ϸ��ʹ��Space������ͣ�ͻָ�\n\n");
		}else if(i==6){
			printf("\t\t����Ϸ�Ѷ���÷����Ӷ����ӣ���11���Ѷ�\n\n");
		}else if(i==8){
			printf("\t\tף����Ϸ��죡������������˵�...");
		}
	}
	fflush(stdin);
	getchar();
}


void drawMainMenu(int nowIndex) {
	short i,j;

	system("cls");
	
	setConsoleTextColor(GMT_B_BLACK, GMT_F_WHITE);
	printf("\n\n\n\n\t\t    ���������������������~�}�|�z�y\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_BLUE);
	printf("\t\t    �� �� �� ˹ �� �� ���~�}�|�z�y\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_RED);
	printf("\t\t    ���������������������~�}�|�z�y\n\n\n");
	resetAll();

	for(i = 0; i < UI_HEIGHT; i++) {
		if(i==2) {
			if(nowIndex == 1) {
				setConsoleTextColor(GMT_B_WHITE, GMT_F_RED);
				puts("\t\t\t >> 1.��ʼ��Ϸ  ");
				resetAll();
			} else {
				puts("\t\t\t     1.��ʼ��Ϸ  ");
			}
		} else if(i==4) {
			if(nowIndex == 2) {
				setConsoleTextColor(GMT_B_WHITE, GMT_F_RED);
				puts("\t\t\t >> 2.��Ϸ����  ");
				resetAll();
			} else {
				puts("\t\t\t     2.��Ϸ����  ");
			}
		} else if(i==6) {
			if(nowIndex == 3) {
				setConsoleTextColor(GMT_B_WHITE, GMT_F_RED);
				puts("\t\t\t >> 3.�˳���Ϸ  ");
				resetAll();
			} else {
				puts("\t\t\t     3.�˳���Ϸ  ");
			}
		} else if(i==7) 	puts("\n\n\n\t\t       ������λѡ��Enterȷ��  ");
		else if(i==8)   break;
	}

	printf("    			\n\
						(           \n\
					     ��(.)��	  	\n \
					       /)		  	\n \
					       \\ ���		\n \
					  ��� |/			\n \
					      \\|			\n \
					       |	3hex.\n");

}

int gameMainMenu(void) {
	int nowIndex=1;
	int ch = _VK_ENTER;
	drawMainMenu(nowIndex);
GBAgain:
	//fflush(stdin);
	while(ch = getch()) { //�û�����
		//printf("%#X\t", getch());
		//fflush(stdin);
		switch(ch) {
			case _VK_UP:
				nowIndex--;
				if(nowIndex==0) nowIndex = 3;
				break;
			case _VK_DOWN:
				nowIndex++;
				if(nowIndex==4) nowIndex = 1;
				break;
			case _VK_ENTER:
				if(nowIndex == 1) return 1;
				else if(nowIndex == 2) return 2;
				else if(nowIndex == 3) return -1;
				return 0;
			default:
				goto GBAgain;
		}
		// ˢ�½���
		drawMainMenu(nowIndex);
	}

}

/*��Ϸ��ʾ����*/
void gameShow() {
	//1��ʾ�߿򣬿ո񣬷���
	short i,j;
	system("cls");
	puts("\n\t\t<����˹����>");
	for(i = 0; i < UI_HEIGHT; i++) {
		for(j = 0; j < UI_WIDTH; j++) {
			if(game_arr[i][j].info == 0) {
				printf(GAME_DIV);
				continue;
			}
			if(game_arr[i][j].info == WALL) {
				if(i == 0 || i == UI_HEIGHT-1) printf(GAME_WALL_W);//����
				else printf(GAME_WALL_H);
				continue;
			}
			if(game_arr[i][j].info == BLOCK) {
				setConsoleTextColor(GMT_B_WHITE, blockRandColor);
				printf(GAME_BLOCK);
				resetAll();
			}
		}
		if(i == 1)  printf("\t��һ������");
		if(i >= 2 && i <= 5) { //��һ������
			printf("\t");
			for(j = 0; j < 4; j++) {
				if(next_blockarr[i-2][j] == 0) printf("  "); //Ҫ��2����Ϊ��i�´�2��ʼ��
				else {
					setConsoleTextColor(GMT_B_WHITE, (blockRandColor+1)%COLOR_LEN);
					printf(GAME_BLOCK);
					resetAll();
				}
			}
		}
		if(i==9)    printf("\t��ǰ�Ѷȣ�%d",nowLevel);
		if(i == 10) printf("\t��ң�%s",player_name);
		if(i == 11) printf("\t�÷֣�%d",score);
		if(i == UI_HEIGHT-7) printf("\t��Ϸ����");
		if(i == UI_HEIGHT-5) printf("\t����ת\tSpace ��ͣ");
		if(i == UI_HEIGHT-4) printf("\t������\t Esc  �˳�");
		if(i == UI_HEIGHT-3) printf("\t������");
		if(i == UI_HEIGHT-2) printf("\t������");
		printf("\n");
	}
}
/*ÿһ������Ĳ���*/
void produceBlock() {
	//����Ϸ������м���÷���
	short i,j;

	blockRandColor = GMT_F_Array[(colorCount++)%COLOR_LEN]; // �����ɫ

	cur_boxindex = next_boxindex;
	next_boxindex = rand() % 19; //����ı���������
	cur_block_coord_x = (UI_WIDTH-2)/2; //���м�����
	cur_block_coord_y = 1;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			next_blockarr[i][j] = 0; //ÿ�β����µķ��飬��Ҫ�������һ���������������
	for(i = 0; i < 4; i++) {
		game_arr[cur_block_coord_y+block[cur_boxindex].a[i][1]][cur_block_coord_x+block[cur_boxindex].a[i][0]].info = BLOCK ;
		next_blockarr[block[next_boxindex].a[i][1]][block[next_boxindex].a[i][0]] = BLOCK;
	}
	if(!isCanMoveBlock(cur_block_coord_x,cur_block_coord_y)) { //�����·��������ط���ռ���ˣ��˳�
		printf("��Ϸ�������ٽ�������");
		getch();
		exit(0);
	}
}
/*������ƶ�*/
void moveBlock() {
	short i,j,to_bottom = FALSE;	//����
	short old_x = cur_block_coord_x,old_y = cur_block_coord_y; //������¼�ɵķ����λ��
	short old_boxindex = cur_boxindex;    //��¼������±꣬���ϼ�ʱ�ı䷽����
	while(1) {
		old_x = cur_block_coord_x,old_y = cur_block_coord_y;
		old_boxindex = cur_boxindex;
		while(kbhit()) { //�û�����
			// getch();
			switch(getch()) {
				case _VK_UP:
					cur_boxindex = block[cur_boxindex].next;
					if(!isCanMoveBlock(cur_block_coord_x, cur_block_coord_y))
						cur_boxindex =	old_boxindex;  //���������ת�Ļ�Ҫ��ԭ
					break;
				case _VK_DOWN:
					for(i = 0; i < 4; i++) //һ�ο����½�4��
						if(isCanMoveBlock(cur_block_coord_x, cur_block_coord_y + 1)) cur_block_coord_y++;
						else  {
							to_bottom = TRUE;    //����
							break;
						}
					break;
				case _VK_LEFT:
					if(isCanMoveBlock(cur_block_coord_x - 1, cur_block_coord_y)) cur_block_coord_x--;
					break;
				case _VK_RIGHT:
					if(isCanMoveBlock(cur_block_coord_x + 1, cur_block_coord_y)) cur_block_coord_x++;
					break;
				case _VK_SPACE:
					wait();
					clearScreen();
					fflush(stdin);
					break;
				case _VK_ESC:
					return;
			}

			if(score>=10) nowLevel = score/10;
		}

		if(to_bottom) {
			if(old_x != cur_block_coord_x || old_y != cur_block_coord_y || old_boxindex != cur_boxindex) {
				for(i = 0; i < 4; i++)
					game_arr[old_y+block[old_boxindex].a[i][1]][old_x+block[old_boxindex].a[i][0]].info = 0;
				for(i = 0; i < 4; i++)
					game_arr[cur_block_coord_y+block[cur_boxindex].a[i][1]][cur_block_coord_x+block[cur_boxindex].a[i][0]].info = BLOCK;
				gameShow();  //Ҫ����֮���ˢ��
			}
			to_bottom = FALSE;
			toBottom(cur_block_coord_x, cur_block_coord_y);
			gameShow();//����
		} else {
			if(j++ % 10 == 0) { //�Զ�����,Ҫ��ǰ�棬
				if(isCanMoveBlock(cur_block_coord_x, cur_block_coord_y + 1)) cur_block_coord_y++;
				else  to_bottom = TRUE; //����
			}
			if(old_x != cur_block_coord_x || old_y != cur_block_coord_y || old_boxindex != cur_boxindex) {
				for(i = 0; i < 4; i++)
					game_arr[old_y+block[old_boxindex].a[i][1]][old_x+block[old_boxindex].a[i][0]].info = 0;
				for(i = 0; i < 4; i++)
					game_arr[cur_block_coord_y+block[cur_boxindex].a[i][1]][cur_block_coord_x+block[cur_boxindex].a[i][0]].info = BLOCK;
				gameShow();  //Ҫ����֮���ˢ��
			}
		}
		Sleep(levelCalc(nowLevel)); // Speed
	}
}

int levelCalc(int level) {
	return levelSpeed[level];
}

// ��ͣ��Ϸ
void wait(void) {
	char ch;

	while(1) {
		setConsoleTextColor(GMT_B_RED, GMT_F_WHITE);
		setConsoleTextPositionByXY(UI_WIDTH/2,UI_HEIGHT/2);
		printf("%s", "->��Ϸ��ͣ<-");

		fflush(stdin);
		ch = getch();
		if(ch == _VK_SPACE) break;
	}
	resetAll();
}

short isCanMoveBlock(short x, short y) {
	//�Ƿ����ƶ�����
	short i;
	for(i=0; i<4; i++)
		if(game_arr[y+block[cur_boxindex].a[i][1]][x+block[cur_boxindex].a[i][0]].var)
			return FALSE;	//�����λ���Լ��з�����䣬�����ƶ�
	return TRUE;
}
void toBottom(short x, short y) {
	//���鵽��֮��Ĳ�����1.�������λ�õ�״̬��Ϊ1����ʾ��ռ�á�2.�Ƿ����飬���У��ı�״̬ 3.�����µķ���
	short i,j;
	for(i = 0; i < 4; i++)
		game_arr[y+block[cur_boxindex].a[i][1]][x+block[cur_boxindex].a[i][0]].var = 1;
	//2.�Ƿ����飬���У��ı�״̬
	for(i = UI_HEIGHT - 2; i >= 1; i--) { //��������ǽ ,�ӵ׿�ʼ������
		for(j = 1; j <= UI_WIDTH - 2; j++) {
			if( !game_arr[i][j].var)
				break;//һ���пյľ��������ѭ�� ����������һ��
			if(j == UI_WIDTH - 2) {	//һ�ж�����,����,��ʱ��i��������
				score += 10;
				int h,v;
				for(v = i; v >= 2; v--) { //��i�п�ʼ,
					for(h = 1; h <= UI_WIDTH - 2; h++) {
						game_arr[v][h].info = game_arr[v-1][h].info;
						game_arr[v][h].var = game_arr[v-1][h].var;
					}
				}//Ҫ�ӵ�������,֮��i--,i =  UI_HEIGHT - 2,�ͻ���ֶ���һ����ʱ����������
				i = UI_HEIGHT - 1;
			}
		}
	}
	produceBlock();
}
