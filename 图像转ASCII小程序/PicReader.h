/******************************************************************
* ��ע�⣡                                                         *
* ��ͷ�ļ���Ϊ���װ��WinAPI��WIC�ײ㺯�������������ͼƬ��ȡ��������  *
* ���װ�������ⲿ�⣬����������һ����Լ��������������ϸ�Ķ����¹涨  *
*     ��ͷ�ļ����κ�û��TO-DO�ĵط����㲻Ҫ�޸ģ��������������⣬      *
* �뼰ʱ��ϵ��ʦ�����̣�                                            *
*     ÿһ��TO-DO����TO-DO��˵�� (TO-DO) END ����������ɿ��·�����  *
*     readPic()����Ϊ���װ��WinAPI�еķ��������Խ�ͼƬ��ȡΪRGBA��   *
* bitmap���ݣ����Ⲣ�����������ͨ���޸��������ֱ�Ӵﵽ��ȡ�Ҷ�ͼ��   *
* Ŀ�ġ�                                                           *
*     getData()����������Ҫ���Ƶĺ���������ȡ������һάBYTE����ת��   *
* ����ʵ�ֵ�Array�ࡣ                                              *
*     testReader()��demo���ṩ��ȡ���ݵ�����һ��˼·��               *
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
		// ��ȡ��������С��ת��Ϊsize_t����
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
				cerr << "�ڴ�����ʧ��" << endl;
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
		// ��ȡ��������С��ת��Ϊsize_t����
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
		// ��ȡ��������С��ת��Ϊsize_t����
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
		// �������޸��Ӿ����nowAxis��ֵ�Լ������б�Ҫ��ֵ���Է���һ���Ӿ���     
		if (nowAxis == axisNum)
		{
			cerr << "�ѵ�������СԪ��" << endl;
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
			cerr << "�ڴ�����ʧ��" << endl;
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
			cout << "����ͬ��" << endl;
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
			cout << "����ͬ��" << endl;
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
			cout << "����ͬ��" << endl;
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
			cout << "����ͬ��" << endl;
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
	int* data;//�ײ�洢����
	int index;//ָ��ײ��ָ��
	int shape[16];//ÿһά�ȵ���Ϣ
	int axisNum;//��ά����
	int nowAxis;//��ǰ����ά��
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

	/*TO-DO��������ܻ���������Ҫ���ڲ���Ա END*/
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

void /*TO-DO����������Ҫ�޸ķ������� END*/ PicReader::getData(Array &arr,Array & gray,int& width,int& height) {
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
	*  ʵ��һ��Array�࣬���������dataת�������Array��                  *
	*                                                                 *
	*  ����˵������Bitmap Copy���������ݣ�ÿ4��Ϊһ�����һ������         *
	*           ����Ϊһ������Ϊͼ���(��*��*4)��һά����                *
	*           �������Ų�Ϊ R G B A R G B A R G B A.....              *
	*                                                                 *
	*  ��ע�⣡  �������ֻ�Ķ��Ӵ˿�ʼ����һ��TO-DO ENDλ�õĴ��룡       *
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