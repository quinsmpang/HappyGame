//*****************************************************************************************
//�������ƣ� Lesion2
//2015��9�� simon
//������ ��Win32 ���ڳ��򴴽�����������
//***************************************************************************************** 




//*****************************************************************************************
// Desc: ͷ�ļ����岿��  
//*****************************************************************************************                                                                                       
#include <d3d9.h>



//*****************************************************************************************
// Desc: ���ļ����岿��  
//***************************************************************************************** 
#pragma comment(lib,"d3d9.lib")



//*****************************************************************************************
// Desc: �궨�岿��   
//*****************************************************************************************
#define SCREEN_WIDTH	800							//Ϊ���ڿ��ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڿ���
#define SCREEN_LEIGHT	600							//Ϊ���ڸ߶ȶ���ĺ꣬�Է����ڴ˴��޸Ĵ��ڸ߶�
#define WINDOW_TITLE	L"���ڴ����Ĳ���"				//Ϊ���ڱ��ⶨ��ĺ�
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }      //�Զ���һ��SAFE_RELEASE()��,������Դ���ͷ�



//*****************************************************************************************
// Desc: ȫ�ֱ�����������  
//
//*****************************************************************************************
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; //Direct3D�豸����



//*****************************************************************************************
// Desc: ȫ�ֺ����������� ,��ֹ"δ�����ı�ʶ"ϵ�д��� 
//
//***************************************************************************************** 
LRESULT CALLBACK	WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT				Direct3D_Init(HWND hwnd);
void				Direct3D_Render();
void				Direct3D_CleanUp();



//*****************************************************************************************
// Name: WinMain( )
// Desc: WindowsӦ�ó�����ں���
//*****************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	//1.��ʼ���һ�������Ĵ�����
	WNDCLASSEX wndClass = { 0 };				//��WINDCLASSEX������һ�������࣬����wndClassʵ������WINDCLASSEX������֮�󴰿ڵĸ����ʼ��    
	wndClass.cbSize = sizeof(WNDCLASSEX);	//���ýṹ����ֽ�����С
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndClass.lpfnWndProc = WndProc;				//����ָ�򴰿ڹ��̺�����ָ��
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;				//ָ���������ڹ��̵ĳ����ʵ�������
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); //��ȫ�ֵ�::LoadImage�����ӱ��ؼ����Զ���icoͼ��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //ָ��������Ĺ������
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //ΪhbrBackground��Աָ��һ����ɫ��ˢ���
	wndClass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndClass.lpszClassName = L"ForTheDreamOfGameDevelop";		//��һ���Կ���ֹ���ַ�����ָ������������֡�

	//2.����괰�ں���Ҫ�Դ��������ע�ᣬ�������ܴ��������͵Ĵ���
	if (!RegisterClassEx(&wndClass))				
		return -1;

	//3.ϲ���ּ��Ĵ������ں���CreateWindow
	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE,			
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH,
		SCREEN_LEIGHT, NULL, NULL, hInstance, NULL);

	//4.����������ʾʱ��λ�ã��������Ͻ�λ����Ļ���꣨200��50����
	MoveWindow(hwnd, 200, 50, SCREEN_WIDTH, SCREEN_LEIGHT, true);   
	ShowWindow(hwnd, nShowCmd);    //����Win32����ShowWindow����ʾ����
	UpdateWindow(hwnd);  //�Դ��ڽ��и��£��������������·���Ҫװ��һ��

	//Direct3D��Դ�ĳ�ʼ�����ɹ�����ʧ�ܶ���messagebox������ʾ
	if (S_OK == Direct3D_Init(hwnd))
	{
		MessageBox(hwnd, L"Direct3D��ʼ�����~��", L"ǳī����Ϣ����", 0); //ʹ��MessageBox����������һ����Ϣ����  
	}
	else
	{
		MessageBox(hwnd, L"Direct3D��ʼ��ʧ��~��", L"ǳī����Ϣ����", 0); //ʹ��MessageBox����������һ����Ϣ���� 
	}



	//5.��Ϣѭ������
	MSG msg = { 0 };  //��ʼ��msg
	while (msg.message != WM_QUIT)			//ʹ��whileѭ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);		//�ú����ַ�һ����Ϣ�����ڳ���
		}
		else
		{
			Direct3D_Render();
		}
	}

	//6.�������ע��
	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);
	return 0;
}



//*****************************************************************************************
// Name: WndProc()
// Desc: �Դ�����Ϣ���д���
//*****************************************************************************************
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //���ڹ��̺���WndProc
{
	switch (message)				//switch��俪ʼ
	{
	case WM_PAINT:					 // �ͻ����ػ���Ϣ
		Direct3D_Render();          //����Direct3D_Render���������л���Ļ���
		ValidateRect(hwnd, NULL);   // ���¿ͻ�������ʾ
		break;									//������switch���

	case WM_KEYDOWN:                // ���̰�����Ϣ
		if (wParam == VK_ESCAPE)    // ESC��
			DestroyWindow(hwnd);    // ���ٴ���, ������һ��WM_DESTROY��Ϣ
		break;
	case WM_DESTROY:				//����������Ϣ
		Direct3D_CleanUp();     //����Direct3D_CleanUp����������COM�ӿڶ���
		PostQuitMessage(0);		//��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;						//������switch���

	default:						//������case�����������ϣ���ִ�и�default���
		return DefWindowProc(hwnd, message, wParam, lParam);		//����ȱʡ�Ĵ��ڹ�����ΪӦ�ó���û�д����Ĵ�����Ϣ�ṩȱʡ�Ĵ�����
	}

	return 0;					//�����˳�
}


//*****************************************************************************************
// Name: Direct3D_Init( )
// Desc: ��ʼ��Direct3D
// Point:��Direct3D��ʼ���Ĳ�����
//		1.��ʼ���Ĳ���֮һ������Direct3D�ӿڶ���
//		2.��ʼ���Ĳ���֮������ȡӲ���豸��Ϣ
//		3.��ʼ���Ĳ���֮�������ṹ��
//		4.��ʼ���Ĳ���֮�ģ�����Direct3D�豸�ӿ�
//*****************************************************************************************

HRESULT Direct3D_Init(HWND hwnd)
{

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮һ�����ӿڡ�������Direct3D�ӿڶ���, �Ա��ø�Direct3D���󴴽�Direct3D�豸����
	//--------------------------------------------------------------------------------------
	LPDIRECT3D9  pD3D = NULL; //Direct3D�ӿڶ���Ĵ���
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION))) //��ʼ��Direct3D�ӿڶ��󣬲�����DirectX�汾Э��
		return E_FAIL;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮��,ȡ��Ϣ������ȡӲ���豸��Ϣ
	//--------------------------------------------------------------------------------------
	D3DCAPS9 caps; int vp = 0;
	if (FAILED(pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //֧��Ӳ���������㣬���ǾͲ���Ӳ���������㣬���׵�
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //��֧��Ӳ���������㣬����ֻ�ò���������������

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮���������ݡ������D3DPRESENT_PARAMETERS�ṹ��
	//--------------------------------------------------------------------------------------
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_LEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//--------------------------------------------------------------------------------------
	// ��Direct3D��ʼ���Ĳ���֮�ģ����豸��������Direct3D�豸�ӿ�
	//--------------------------------------------------------------------------------------
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, vp, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;



	SAFE_RELEASE(pD3D) //LPDIRECT3D9�ӿڶ����ʹ����ɣ����ǽ����ͷŵ�

		return S_OK;
}



//*****************************************************************************************
// Name: Direct3D_Render()
// Desc: ʹ��Direct3D������Ⱦ
//*****************************************************************************************
void Direct3D_Render()
{
	//��ʱΪ�գ�����ǳī�»طֽ� 
}


//*****************************************************************************************
// Name: Direct3D_CleanUp()
// Desc: ��Direct3D����Դ��������
//*****************************************************************************************
void Direct3D_CleanUp()
{
	//�ͷ�Direct3D�豸����
	SAFE_RELEASE(g_pd3dDevice)
}
