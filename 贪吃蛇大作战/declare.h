//改自渣哥大作业工具函数
#include <Windows.h>

/* 定义颜色（用宏定义取代数字，方便记忆） */
#define COLOR_BLACK		0	//黑
#define COLOR_BLUE		1	//蓝
#define COLOR_GREEN		2	//绿
#define COLOR_CYAN		3	//青
#define COLOR_RED		4	//红
#define COLOR_PINK		5	//粉
#define COLOR_YELLOW	6	//黄
#define COLOR_WHITE		7	//白
#define COLOR_HBLACK	8	//亮黑
#define COLOR_HBLUE		9	//亮蓝
#define COLOR_HGREEN	10	//亮绿
#define COLOR_HCYAN		11	//亮青
#define COLOR_HRED		12	//亮红
#define COLOR_HPINK		13	//亮粉
#define COLOR_HYELLOW	14	//亮黄
#define COLOR_HWHITE	15	//亮白

/*定义方向*/
#define right 77
#define left 75
#define up 72
#define down 80

/* 定义光标的形态 */
#define CURSOR_VISIBLE_FULL			0	//光标显示，全高色块
#define CURSOR_VISIBLE_HALF			1	//光标显示，半高色块
#define CURSOR_VISIBLE_NORMAL		2	//光标显示，横线（缺省为此方式）
#define CURSOR_INVISIBLE			3	//光标不显示

/* tcs_tool下的函数声明 */
/* 清屏、颜色设置、光标设置、字符/字符串显示 */
void cls(void);
void setcolor(const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE);
void gotoxy(const int X, const int Y);
void getxy(int& x, int& y);
void setcursor(const int options);