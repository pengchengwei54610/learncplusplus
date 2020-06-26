/******************************************************************
* ！注意！                                                         *
* 本头文件中为你封装了WinAPI中WIC底层函数，方便你进行图片读取而不必引  *
* 入或安装其他的外部库，但是我们有一定的约束条件，请你仔细阅读以下规定  *
*     本头文件中任何没有TO-DO的地方请你不要修改，若函数存在问题，      *
* 请及时联系老师或助教！                                            *
*     每一个TO-DO块以TO-DO：说明 (TO-DO) END 结束，具体可看下方代码  *
*     readPic()函数为你封装了WinAPI中的方法，可以将图片读取为RGBA的   *
* bitmap数据，但这并不代表你可以通过修改这个函数直接达到读取灰度图的   *
* 目的。                                                           *
*     getData()是你最终需要完善的函数，将读取出来的一维BYTE数组转换   *
* 成你实现的Array类。                                              *
*     testReader()是demo中提供读取数据的其中一个思路。               *
******************************************************************/
#ifndef PIC_READER_H
#define PIC_READER_H

#include <windows.h>
#include <wincodec.h>
#include <commdlg.h>
#include<iostream>
using namespace std;

template <typename T>
inline void SafeRelease(T *&p) {
	if (nullptr != p) {
		p->Release();
		p = nullptr;
	}
}

#define max_array_axis 16
class Array {
public:
	template<typename ...Args>
	Array(Args... args) {
		// 获取参数包大小并转换为size_t数组
		is_data = 0;
		auto num = sizeof...(args);
		size_t list[max_array_axis] = { args... };
		index = 0;
		axisNum = num;
		nowAxis = 0;
		int temp1 = 1;
		for (unsigned int i = 0; i < num; i++)
		{
			temp1 *= list[i];
		}
		if (num != 0)
		{
			data = new(nothrow)int[temp1];
			if (data == NULL)
			{
				cerr << "内存申请失败" << endl;
				exit(0);
			}
		}
		else
			data = NULL;
		temp1 = 1;
		shape[num] = temp1;
		for (int i = num - 1; i >= 0; i--)
		{
			temp1 *= list[i];
			shape[i] = temp1;
		}
		is_original = 1;
	}
	~Array()
	{
		if (is_original)
			delete data;
	}
	template<typename ...Args>
	Array at(Args... args) {
		// 获取参数包大小并转换为size_t数组
		auto num = sizeof...(args);
		size_t list[] = { args... };
		Array temp;
		temp.data = data;
		temp.index = index;
		temp.nowAxis = nowAxis;
		temp.axisNum = axisNum;
		for (int i = 0; i < 16; ++i)
		{
			temp.shape[i] = shape[i];
		}
		temp.is_original = false;
		temp.index = 0;
		for (int i = 1; i <= temp.axisNum; ++i)
		{
			temp.index += list[i - 1] * temp.shape[i];
		}
		return temp;
	}
	template<typename ...Args>
	void reshape(Args... args)
	{
		// 获取参数包大小并转换为size_t数组
		auto num = sizeof...(args);
		size_t list[] = { args... };
		index = 0;
		axisNum = num;
		nowAxis = 0;
		int sum = 1;
		for (int i = 0; i < num; ++i)
		{
			sum *= list[i];
		}
		sum = 1;
		shape[num] = 1;
		for (int i = num - 1; i >= 0; --i)
		{
			sum *= list[i];
			shape[i] = sum;
		}
	}
	int* get_content() {
		return data;
	}
	void set(int value) {
		*(data + index) = value;
	}
	Array operator[](int index) {
		// 在这里修改子矩阵的nowAxis的值以及其他有必要的值，以返回一个子矩阵     
		if (nowAxis == axisNum)
		{
			cerr << "已到数组最小元素" << endl;
			exit(0);
		}
		else
		{
			Array temp;
			temp.data = data;
			temp.index = this->index;
			temp.nowAxis = nowAxis;
			temp.axisNum = axisNum;
			for (int i = 0; i < 16; ++i)
			{
				temp.shape[i] = shape[i];
			}
			temp.is_original = false;
			temp.nowAxis++;
			temp.index += index * temp.shape[temp.nowAxis];
			return temp;
		}
	}
	Array& operator=(int data) {
		this->data[index] = data;
		return *this;
	}
	Array& operator =(const Array& temp)
	{
		delete data;
		index = temp.index;
		axisNum = temp.axisNum;
		nowAxis = temp.nowAxis;
		for (int i = 0; i < 16; ++i)
		{
			shape[i] = temp.shape[i];
		}
		data = new int[shape[0]];
		if (data == NULL)
		{
			cerr << "内存申请失败" << endl;
			exit(-1);
		}
		for (int i = 0; i < shape[0]; ++i)
		{
			data[i] = temp.data[i];
		}
		return *this;
	}

	Array operator+(int num)
	{
		Array temp;
		temp = *this;
		temp.is_original = 0;
		for (int i = 0; i < shape[0]; ++i)
		{
			temp.data[i] = data[i] + num;
		}
		return temp;
	}
	Array operator+(const Array& b)
	{

		if (axisNum != b.axisNum)
		{
			cout << "矩阵不同形" << endl;
			return *this;
		}
		else
		{
			Array temp;
			temp = *this;
			temp.is_original = 0;
			for (int i = 0; i < shape[0]; ++i)
			{
				temp.data[i] = data[i] + b.data[i];
			}
			return temp;
		}
	}
	Array operator-(int num)
	{
		Array temp;
		temp = *this;
		temp.is_original = 0;
		for (int i = 0; i < shape[0]; ++i)
		{
			temp.data[i] = data[i] - num;
		}
		return temp;
	}
	Array operator-(const Array& b)
	{

		if (axisNum != b.axisNum)
		{
			cout << "矩阵不同形" << endl;
			return *this;
		}
		else
		{
			Array temp;
			temp = *this;
			temp.is_original = 0;
			for (int i = 0; i < shape[0]; ++i)
			{
				temp.data[i] = data[i] - b.data[i];
			}
			return temp;
		}
	}
	Array operator*(const Array& b)
	{
		if (axisNum != b.axisNum)
		{
			cout << "矩阵不同形" << endl;
			return *this;
		}
		Array temp;
		temp = *this;
		temp.is_original = 0;
		for (int i = 0; i < shape[0]; ++i)
		{
			temp.data[i] = data[i] * b.data[i];
		}
		return temp;
	}
	Array operator*(int b)
	{
		Array temp;
		temp = *this;
		temp.is_original = 0;
		for (int i = 0; i < shape[0]; ++i)
		{
			temp.data[i] = data[i] * b;
		}
		return temp;
	}
	Array operator/(const Array& b)
	{
		if (axisNum != b.axisNum)
		{
			cout << "矩阵不同形" << endl;
			return *this;
		}
		Array temp;
		temp = *this;
		temp.is_original = 0;
		for (int i = 0; i < shape[0]; ++i)
		{
			temp.data[i] = data[i] / b.data[i];
		}
		return temp;
	}
	Array operator/(int b)
	{
		Array temp;
		temp = *this;
		temp.is_original = 0;
		for (int i = 0; i < shape[0]; ++i)
		{
			temp.data[i] = data[i] / b;
		}
		return temp;
	}
	operator int() {
		return data[index];
	}
	int* data;//底层存储数据
	int index;//指向底层的指针
	int shape[16];//每一维度的信息
	int axisNum;//总维度数
	int nowAxis;//当前所在维度
	bool is_original;
	bool is_data;
};

class PicReader {
public:
	PicReader();
	~PicReader();

	void readPic(LPCSTR);
	void getData(Array &arr,Array &a,int &x,int &y);
	void testReader(BYTE *&,UINT &, UINT &);
private:
	void init();
	bool checkHR(HRESULT);
	void quitWithError(LPCSTR);

	HWND                    hWnd;
	HANDLE                  hFile;
	IWICImagingFactory     *m_pIWICFactory;
	IWICFormatConverter    *m_pConvertedSourceBitmap;

	/*TO-DO：这里可能会增加你需要的内部成员 END*/
};

PicReader::PicReader() : m_pConvertedSourceBitmap(nullptr), m_pIWICFactory(nullptr) {
	init();
}

PicReader::~PicReader() {
	if (hFile != NULL) CloseHandle(hFile);
	SafeRelease(m_pConvertedSourceBitmap);
	SafeRelease(m_pIWICFactory);
	CoUninitialize();
}

bool PicReader::checkHR(HRESULT hr) {
	return (hr < 0);
}

void PicReader::quitWithError(LPCSTR message) {
	MessageBoxA(hWnd, message, "Application Error", MB_ICONEXCLAMATION | MB_OK);
	quick_exit(0xffffffff);
}

void PicReader::init() {
	hWnd = GetForegroundWindow();

	// Enables the terminate-on-corruption feature.
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	HRESULT hr = S_OK;

	//Init the WIC
	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// Create WIC factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pIWICFactory)
	);

	// Throw error if create factor failed
	if (checkHR(hr)) { quitWithError("Init Reader Failed"); }
}

void PicReader::readPic(LPCSTR fileName) {
	HRESULT hr = S_OK;

	// Create a File Handle (WinAPI method not std c)
	if (hFile != NULL) CloseHandle(hFile);
	hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		quitWithError("Cannot find such file, please retry or check the access");
	}

	// Create a decoder
	IWICBitmapDecoder *pDecoder = nullptr;
	hr = m_pIWICFactory->CreateDecoderFromFileHandle((ULONG_PTR)hFile, nullptr, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (checkHR(hr)) { quitWithError("Create Decoder Failed"); }

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode *pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (checkHR(hr)) { quitWithError("Get Frame Failed"); }

	// Format convert the frame to 32bppRGBA
	SafeRelease(m_pConvertedSourceBitmap);
	hr = m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);
	if (checkHR(hr)) { quitWithError("Get Format Converter Failed"); }

	hr = m_pConvertedSourceBitmap->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
	if (checkHR(hr)) { quitWithError("Init Bitmap Failed"); }

	// Clean memory
	SafeRelease(pDecoder);
	SafeRelease(pFrame);
}

void /*TO-DO：可能你需要修改返回类型 END*/ PicReader::getData(Array &arr,Array & gray,int& width,int& height) {
	HRESULT hr = S_OK;

	// Get the size of Image
	UINT x, y;
	hr = m_pConvertedSourceBitmap->GetSize(&x, &y);
	if (checkHR(hr)) { quitWithError("Check Bitmap Size Failed"); }

	// Create the buffer of pixels, the type of BYTE is unsigned char
	BYTE *data;
	data = new BYTE[x * y * 4];
	memset(data, 0, x * y * 4);

	// Copy the pixels to the buffer
	UINT stride = x * 4;
	hr = m_pConvertedSourceBitmap->CopyPixels(nullptr, stride, x * y * 4, data);
	if (checkHR(hr)) { quitWithError("Copy Pixels Failed"); }

	/******************************************************************
	*  TO-DO:                                                         *
	*                                                                 *
	*  实现一个Array类，并将上面的data转存至你的Array内                  *
	*                                                                 *
	*  数据说明：从Bitmap Copy出来的数据，每4个为一组代表一个像素         *
	*           数据为一个长度为图像的(长*宽*4)的一维数组                *
	*           即数据排布为 R G B A R G B A R G B A.....              *
	*                                                                 *
	*  ！注意！  你仅可以只改动从此开始到下一个TO-DO END位置的代码！       *
	******************************************************************/
	if (!arr.is_data)
	{
		arr.data = new int[x * y * 4];
		arr.is_data = 1;
	}
	if (!gray.is_data)
	{
		gray.data = new int[x * y];
		gray.is_data = 1;
	}
	arr.reshape(y, x, 4);
	gray.reshape(y, x);
	for (int i = 0; i < x * y * 4; ++i)
	{
		arr.data[i] = data[i];
	}
	height = y;
	width = x;
	int color[3];
	for (int i = 0; i < y; i += 1)
	{
		for (int j = 0; j < x; j += 1)
		{
			color[0] = arr[i][j][0];
			color[1] = arr[i][j][1];
			color[2] = arr[i][j][2];
			gray[i][j] = (color[0] * 299 + color[1] * 587 + color[2] * 114 + 500) / 1000;
		}
	}
	delete[] data;

	/******************************************************************
	*  TO-DO END                                                      *
	******************************************************************/

	// Close the file handle
	CloseHandle(hFile);
	hFile = NULL;
}

void PicReader::testReader(BYTE* &_out, UINT& _x, UINT& _y){
	HRESULT hr = S_OK;

	// Get the size of Image
	UINT x, y;
	hr = m_pConvertedSourceBitmap->GetSize(&x, &y);
	if (checkHR(hr)) { quitWithError("Check Bitmap Size Failed"); }

	// Create the buffer of pixels, the type of BYTE is unsigned char
	BYTE *data;
	data = new BYTE[x * y * 4];
	memset(data, 0, x * y * 4);

	// Copy the pixels to the buffer
	UINT stride = x * 4;
	hr = m_pConvertedSourceBitmap->CopyPixels(nullptr, stride, x * y * 4, data);
	if (checkHR(hr)) { quitWithError("Copy Pixels Failed"); }


	_out = data; _x = x; _y = y;

	// Close the file handle
	CloseHandle(hFile);
	hFile = NULL;
}

#endif