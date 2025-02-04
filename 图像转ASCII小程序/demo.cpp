/*****************************************
*  Author: Root
*  本demo提供PicReader和FastPrinter的测试方法，可重点关注FastPrinter的方法。
*  function list:
*      testR()          测试PicReader图片读取与检查读取数据，提供五张demo图片，分别为纯黑、纯白、纯红、纯绿、纯蓝
*      testP_Text()		测试FastPrinter的随机文字位置绘制，2000次，位置随机，文字颜色固定
*      testP_HRect()	测试FastPrinter的随机空心矩阵绘制，2000次，位置文字颜色随机
*      testP_SRect()	测试FastPrinter的随机实心矩阵绘制，2000次，位置文字颜色随机
*      testP_RandCF()	测试FastPrinter的随机全屏幕数据绘制，20次，性能瓶颈在过多随机的颜色
*      testP_RandCA()	测试FastPrinter的随机区域数据绘制，200次，性能瓶颈在过多随机的颜色
*  提示：通过测试，如果你需要做动画，你应该尽可能地不指定颜色进行绘制
*****************************************/

#include "PicReader.h"
#include "FastPrinter.h"
#include <stdio.h>

void testR() {
	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;

	/******************************************
	*  说明：readPic()接受一个字符串指针读取图片
	*       testReader(
	*            BYTE*&, 传入BYTE指针引用，用于接收像素信息
	*            UINT&,  读取图像的宽度信息
	*			 UINT&)  读取图像的高度信息
	*       像素信息每四个一组(R G B A)，即接下来每次输出的一行四个数字代表着原图一个像素
	*       由于testReader实现的是直接使用函数内申请的内存指针，故每次检查完数据后需要释放一次data
	*******************************************/

	// Pure black
	imread.readPic("test\\black.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("black data, should be 0 0 0 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure white
	imread.readPic("test\\white.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("white data, should be 255 255 255 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure red
	imread.readPic("test\\red.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("red data, should be 255 0 0 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure green
	imread.readPic("test\\green.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("green data, should be 0 255 0 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure blue
	imread.readPic("test\\blue.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("blue data, should be 0 0 255 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();
}

void testP_Text() {
	/******************************************
	*  说明：FastPrinter(DWORD, DWORD)的初始化参数为两个整数，代表着窗口的宽度和高度
	*        COORD为一个结构体，内部储存着两个变量X Y，表示即将输出文字第一个字在窗口内的坐标(X, Y)
	*       FastPrinter::setText提供三个重载函数，参数分别如下
	*       (COORD, const char*) 在指定坐标绘制文字，颜色默认黑色背景，白色前景
	*       (COORD, const char*, WORD) 在指定坐标绘制文字，并伴随颜色
	*       (COORD, const char*, WORD, WORD)  在指定坐标绘制文字，并伴随颜色，由于给出了字串的长度，故该效率会微微微微高于上面一个
	*       颜色命名空间fp_color：提供前景色16种、背景色16种，f开头的为前景色（字体颜色），b开头的为背景色（字体底色），带l的为淡色
	*                           组合方式为(fp_color::f_color | fp_color::b_color)
	*                           如下面第二个setText，则改文字拥有的颜色为前景淡紫色和背景淡蓝色
	*******************************************/
	FastPrinter printer(120, 50);
	COORD textXY;
	for (int i = 0; i < 2000; i++) {
		// Note: it will faster if all func give length
		printer.cleanSrceen();
		textXY.X = rand() % 100; textXY.Y = rand() % 50;
		printer.setText(textXY, "Hello world!!!");

		textXY.X = rand() % 100; textXY.Y = rand() % 50;
		printer.setText(textXY, "I have color!!!", rand(), rand(), rand(), rand(), rand(), rand());

		textXY.X = rand() % 100; textXY.Y = rand() % 50;
		printer.setText(textXY, "ABCDEFG?", 8, rand(), rand(), rand(), rand(), rand(), rand()); // 8 is the len of str without '\0'

		printer.draw(true);
	}
}

void testP_HRect() {
	/******************************************
	*  说明：FastPrinter::setRect(SMALL_RECT, char, WORD)，该函数将会在SMALL_RECT结构体描述的区域描边
	*                            使用char作为描边字符，并全部刷上第三个参数描述的颜色
	*******************************************/
	FastPrinter printer(120, 50);
	SMALL_RECT rectPOS;
	for (int i = 0; i < 2000; i++) {
		printer.cleanSrceen();

		rectPOS.Left = rand() % 58 + 1;
		rectPOS.Right = rectPOS.Left + rand() % 58;
		rectPOS.Top = rand() % 24 + 1;
		rectPOS.Bottom = rectPOS.Top + rand() % 24;

		printer.setRect(rectPOS, rand() % 70 + 48, rand(), rand(), rand(), rand(), rand(), rand());

		printer.draw(true);
	}
}

void testP_SRect() {
	/******************************************
	*  说明：FastPrinter::setRect(SMALL_RECT, char, WORD)，该函数将会在SMALL_RECT结构体描述的区域填充
	*                            使用char作为填充字符，并全部刷上第三个参数描述的颜色
	*******************************************/
	FastPrinter printer(120, 50);
	SMALL_RECT rectPOS;
	for (int i = 0; i < 2000; i++) {
		printer.cleanSrceen();

		rectPOS.Left = rand() % 58 + 1;
		rectPOS.Right = rectPOS.Left + rand() % 58;
		rectPOS.Top = rand() % 24 + 1;
		rectPOS.Bottom = rectPOS.Top + rand() % 24;

		printer.fillRect(rectPOS, rand() % 70 + 48, rand(), rand(), rand(), rand(), rand(), rand());

		printer.draw(true);
	}
}

void testP_RandCF() {
	/******************************************
	*  说明：FastPrinter::setData(const char*, const WORD*)
	*                     该函数用于传入和控制台窗口大小一致的一维数组描述的dataBuffer，
	*                     需要注意的是传入的是一维数组指针
	*******************************************/
	FastPrinter printer(120, 50);
	char* dataBuffer = new char[120 * 50];
	BYTE* frontColorBuffer = new BYTE[120 * 50 * 3];
	BYTE* backColorBuffer = new BYTE[120 * 50 * 3];

	for (int i = 0; i < 20; i++) {
		printer.cleanSrceen();

		for (int i = 0; i < 120 * 50; i++) {
			dataBuffer[i] = rand() % 70 + 48;
			frontColorBuffer[i * 3] = rand() % 255;
			frontColorBuffer[i * 3 + 1] = rand() % 255;
			frontColorBuffer[i * 3 + 2] = rand() % 255;
			backColorBuffer[i * 3] = rand() % 255;
			backColorBuffer[i * 3 + 1] = rand() % 255;
			backColorBuffer[i * 3 + 2] = rand() % 255;
		}

		printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);

		printer.draw(true);
	}

	delete[] dataBuffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;
}

void testP_RandCA() {
	/******************************************
	*  说明：FastPrinter::setData(const char*, const WORD*, SMALL_RECT)
	*                     该函数用于传入和SMALL_RECT描述区域大小一致的一维数组描述的dataBuffer，
	*                     需要注意的是传入的是一维数组指针
	*
	*                     与上一个函数的区别是，这将只会在指定矩形区域进行绘制
	*******************************************/
	FastPrinter printer(120, 50);
	SMALL_RECT drawArea;
	char* dataBuffer = new char[120 * 50];
	BYTE* frontColorBuffer = new BYTE[120 * 50 * 3];
	BYTE* backColorBuffer = new BYTE[120 * 50 * 3];

	for (int i = 0; i < 200; i++) {
		printer.cleanSrceen();

		drawArea.Left = rand() % 58 + 1;
		drawArea.Right = drawArea.Left + rand() % 58;
		drawArea.Top = rand() % 24 + 1;
		drawArea.Bottom = drawArea.Top + rand() % 24;

		for (int i = 0; i < (drawArea.Right - drawArea.Left) * (drawArea.Bottom - drawArea.Top); i++) {
			dataBuffer[i] = rand() % 70 + 48;
			frontColorBuffer[i * 3] = rand() % 255;
			frontColorBuffer[i * 3 + 1] = rand() % 255;
			frontColorBuffer[i * 3 + 2] = rand() % 255;
			backColorBuffer[i * 3] = rand() % 255;
			backColorBuffer[i * 3 + 1] = rand() % 255;
			backColorBuffer[i * 3 + 2] = rand() % 255;
		}

		printer.setData(dataBuffer, frontColorBuffer, backColorBuffer, drawArea);

		printer.draw(true);
	}

	delete[] dataBuffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;
}

int main()
{
	PicReader imread;
	BYTE* data = nullptr;
	UINT x, y;


	// 将灰度分为15级，每一级由一个ascii字符表示，强度越大ascii字符内容越少(越白)
	char asciiStrength[] = { 'M','N','H','Q','$','O','C','?','7','>','!',':','-',';','.' };

	unsigned char grayData[] = { 154,80,97,15,214,32,68,90 };

//	imread.readPic("classic_picture\\airplane.jpg");
//	imread.readPic("classic_picture\\lena.jpg");
	imread.readPic("classic_picture\\lena.jpg");
	Array a1, g1;
	int width, height;
	imread.getData(a1, g1, width, height);




	int zoom_factor =4;//缩放倍数，可手动更改
	int width1, height1;

	width1 = (width/zoom_factor)*2;
	height1 = height / zoom_factor;
	
	FastPrinter printer(width1, height1);
	char* dataBuffer = new char[width * height];
	BYTE* frontColorBuffer = new BYTE[width * height * 3];
	BYTE* backColorBuffer = new BYTE[width * height * 3];


	printer.cleanSrceen();
	unsigned int asciiIndex;
	int count3 = 0;
	for (int count1 = 0; count1 < height1; count1 += 1)
	{
		for (int count2 = 0; count2 < width1; count2 += 2)
		{
			asciiIndex = 0;
			for (int count4 = 0;count4<zoom_factor; count4++)
			{
				for (int count5 = 0; count5 < zoom_factor; count5++)
				{
					asciiIndex += g1.data[(count1 * zoom_factor+count4) * width + count2*zoom_factor/2+count5];
				}
			}
			asciiIndex = (asciiIndex / 18) / zoom_factor/zoom_factor;
			dataBuffer[count3] = asciiStrength[asciiIndex];
			dataBuffer[count3 + 1] = asciiStrength[asciiIndex];
			frontColorBuffer[count3 * 3] = 0;
			frontColorBuffer[count3 * 3 + 1] = 0;
			frontColorBuffer[count3 * 3 + 2] = 0;
			frontColorBuffer[count3 * 3 + 3] = 0;
			frontColorBuffer[count3 * 3 + 4] = 0;
			frontColorBuffer[count3 * 3 + 5] = 0;
			backColorBuffer[count3 * 3] = 255;
			backColorBuffer[count3 * 3 + 1] = 255;
			backColorBuffer[count3 * 3 + 2] = 255;
			backColorBuffer[count3 * 3 + 3] = 255;
			backColorBuffer[count3 * 3 + 4] = 255;
			backColorBuffer[count3 * 3 + 5] = 255;
			count3 += 2;
		}
	}




	printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);

	printer.draw(true);
	delete[] dataBuffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;

	getchar();
	return 0;
}