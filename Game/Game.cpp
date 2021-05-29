// Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Game.h"
#include "PrimitiveComponent.h"
#include "PrimitiveComponentWithMatrixColor.h"

#include <Engine.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <chrono>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, Game& vulkan);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Game* g_vulkan;
glm::mat4 g_camera_matrix;
glm::vec3 cameraPosition{ 0.0f, 0.0f, -10.0f };
glm::vec3 cameraTarget{ 0.0f, 0.0f, 0.0f };
glm::vec3 upVector{ 0.0f, -1.0f, 0.0f };
PrimitiveComponentWithMatrixColor* component0;
PrimitiveComponentWithMatrixColor* component1;

PrimitiveComponentWithMatrixColor* component2;
PrimitiveComponentWithMatrixColor* component3;

glm::mat4 translation_matrix = glm::translate(glm::mat4(1), glm::vec3(3, 0, 0));

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    Game vulkan; g_vulkan = &vulkan;

    if (!InitInstance (hInstance, nCmdShow, vulkan))
    {
        return FALSE;
    }
    /*
    vulkan.AddGameComponent(new PrimitiveComponent(vulkan,
    { PrimitiveVertex{0.25f, 0.75f, 0.5f},
      PrimitiveVertex{0.25f,  0.25f, 0.5f},
      PrimitiveVertex{0.75f, 0.75f, 0.5f},

      PrimitiveVertex{0.25f,  0.25f, 0.5f},
      PrimitiveVertex{0.75f, 0.25f, 0.5f},
      PrimitiveVertex{0.75f, 0.75f, 0.5f}
    }));
    vulkan.AddGameComponent(new PrimitiveComponent(vulkan,
        { PrimitiveVertex{-0.25f, 0.75f, 0.5f},
          PrimitiveVertex{-0.5f,  0.25f, 0.5f},
          PrimitiveVertex{-0.75f, 0.75f, 0.5f}
        }));
    */

    g_camera_matrix = glm::lookAt(
        cameraPosition, // ������� ������ � ������� ������������
        cameraTarget,   // ��������� ���� �� �������� � ������� ������������
        upVector        // ������, ����������� ����������� �����. ������ (0, 1, 0)
    );

    glm::mat4 projectionMatrix = glm::perspective(
        static_cast<float>(glm::radians(60.0f)),  // ������������ ���� ������ � ��������. ������ ����� 90&deg; (����� �������) � 30&deg; (�����)
        16.0f / 9.0f,                          // ��������� ������. ������� �� �������� ������ ����. ��������, ��� 4/3 == 800/600 == 1280/960
        0.1f,                                  // ������� ��������� ���������. ������ ���� ������ 0.
        100.0f                                 // ������� ��������� ���������.
    );

    component0 = new PrimitiveComponentWithMatrixColor(vulkan,
        { PrimitiveColoredVertex{-3.0,   0.0, -3.0,   {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-3.0,   0.0,  3.0,   {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{ 3.0,   0.0, -3.0,   {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{ 3.0,   0.0,  3.0,   {1.0f, 0.0f, 0.0f, 1.0f}}
        },
        { 0, 1, 3,
          0, 3, 2
        },
        { 0, -3.0, 0 },
        { 0, 0, 0 },
        { 1, 1, 1 },
        g_camera_matrix,
        projectionMatrix);
    vulkan.AddGameComponent(component0);

    component1 = new PrimitiveComponentWithMatrixColor(vulkan,
        { PrimitiveColoredVertex{-0.25f, 0.75f, 0.5f, {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.5f, {0.0f, 1.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.5f, {0.0f, 0.0f, 1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.5f, {0.0f, 0.0f, 1.0f, 1.0f}},

          PrimitiveColoredVertex{-0.25f, 0.75f, 0.7f, {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.7f, {0.0f, 1.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.7f, {0.0f, 0.0f, 1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.7f, {0.0f, 0.0f, 1.0f, 1.0f}}
        },
        { 0, 1, 2,
          1, 3, 2,
          0, 4, 5,
          0, 5, 1,
          2, 6, 7,
          2, 7, 3,
          4, 5, 6,
          5, 7, 6,
          1, 5, 7,
          1, 7, 3,
          0, 4, 6,
          0, 6, 2},
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 1, 1, 1 },
        g_camera_matrix,
        projectionMatrix);
    vulkan.AddGameComponent(component1);



    component2 = new PrimitiveComponentWithMatrixColor(vulkan,
        { PrimitiveColoredVertex{-0.25f, 0.75f, 0.5f, {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.5f, {0.0f, 1.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.5f, {0.0f, 0.0f, 1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.5f, {0.0f, 0.0f, 1.0f, 1.0f}},

          PrimitiveColoredVertex{-0.25f, 0.75f, 0.7f, {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.7f, {0.0f, 1.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.7f, {0.0f, 0.0f, 1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.7f, {0.0f, 0.0f, 1.0f, 1.0f}}
        },
        { 0, 1, 2,
          1, 3, 2,
          0, 4, 5,
          0, 5, 1,
          2, 6, 7,
          2, 7, 3,
          4, 5, 6,
          5, 7, 6,
          1, 5, 7,
          1, 7, 3,
          0, 4, 6,
          0, 6, 2 },
        { 3.0, 0, 0 },
        { 0, 0, 0 },
        { 1, 1, 1 },
        g_camera_matrix,
        projectionMatrix);
    vulkan.AddGameComponent(component2);

    component3 = new PrimitiveComponentWithMatrixColor(vulkan,
        { PrimitiveColoredVertex{-0.25f, 0.75f, 0.5f, {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.5f, {0.0f, 1.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.5f, {0.0f, 0.0f, 1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.5f, {0.0f, 0.0f, 1.0f, 1.0f}},

          PrimitiveColoredVertex{-0.25f, 0.75f, 0.7f, {1.0f, 0.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.25f, 0.25f, 0.7f, {0.0f, 1.0f, 0.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.75f, 0.7f, {0.0f, 0.0f, 1.0f, 1.0f}},
          PrimitiveColoredVertex{-0.75f, 0.25f, 0.7f, {0.0f, 0.0f, 1.0f, 1.0f}}
        },
        { 0, 1, 2,
          1, 3, 2,
          0, 4, 5,
          0, 5, 1,
          2, 6, 7,
          2, 7, 3,
          4, 5, 6,
          5, 7, 6,
          1, 5, 7,
          1, 7, 3,
          0, 4, 6,
          0, 6, 2 },
        { -3.0, 0, 0 },
        { 0, 0, 0 },
        { 1, 1, 1 },
        g_camera_matrix,
        projectionMatrix);
    vulkan.AddGameComponent(component3);






    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));


    glm::mat4 translation_matrix = glm::translate(glm::mat4(1), glm::vec3(3, 0, 0));

    glm::mat4 rotation_matrix(1);
    glm::vec3 RotationZ(0, 0, 1.0);

    std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();

    MSG msg;
    while (TRUE) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            /*
            if (std::chrono::steady_clock::now() - time_point > std::chrono::milliseconds(1)) {
                rotation_matrix = glm::rotate(rotation_matrix, 0.01f, RotationZ);
                component1->UpdateWorldMatrix(rotation_matrix * translation_matrix);

                time_point = std::chrono::steady_clock::now();
            }
            */
            vulkan.Draw();
        }
    }
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, Game & vulkan)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   vulkan.Initialize(hInstance, hWnd, 1904, 962);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
    {
        // Resize the application to the new window size, except when
        // it was minimized. Vulkan doesn't support images or swapchains
        // with width=0 and height=0.
        if (wParam != SIZE_MINIMIZED) {
            auto width = lParam & 0xffff;
            auto height = (lParam & 0xffff0000) >> 16;

            g_vulkan->Update(width, height);
        }
        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 'w':
        case 'W':
        {
            glm::vec3 direction = glm::normalize(cameraTarget - cameraPosition) * 0.1f;
            cameraPosition += direction;
            cameraTarget += direction;

            translation_matrix = glm::translate(translation_matrix, direction);
            component1->UpdateWorldMatrix(translation_matrix);
            break;
        }
        case 's':
        case 'S':
        {
            glm::vec3 direction = glm::normalize(cameraTarget - cameraPosition) * 0.1f;
            cameraPosition -= direction;
            cameraTarget -= direction;

            translation_matrix = glm::translate(translation_matrix, -direction);
            component1->UpdateWorldMatrix(translation_matrix);
            break;
        }
        case 'a':
        case 'A':
        {
            glm::vec3 forward_vec = glm::normalize(cameraTarget - cameraPosition);
            glm::vec3 direction = glm::cross(forward_vec, upVector) * 0.1f;
            cameraPosition -= direction;
            cameraTarget -= direction;

            translation_matrix = glm::translate(translation_matrix, -direction);
            component1->UpdateWorldMatrix(translation_matrix);
            break;
        }
        case 'd':
        case 'D':
        {
            glm::vec3 forward_vec = glm::normalize(cameraTarget - cameraPosition);
            glm::vec3 direction = glm::cross(forward_vec, upVector) * 0.1f;
            cameraPosition += direction;
            cameraTarget += direction;

            translation_matrix = glm::translate(translation_matrix, direction);
            component1->UpdateWorldMatrix(translation_matrix);
            break;
        }
        case VK_SPACE:
        {
            cameraPosition += glm::vec3(upVector * 0.1f);
            cameraTarget += glm::vec3(upVector * 0.1f);
            break;
        }
        case VK_SHIFT:
        {
            cameraPosition -= glm::vec3(upVector * 0.1f);
            cameraTarget -= glm::vec3(upVector * 0.1f);
            break;
        }
        default:
            break;
        }
        g_camera_matrix = glm::lookAt(
            cameraPosition, // ������� ������ � ������� ������������
            cameraTarget,   // ��������� ���� �� �������� � ������� ������������
            upVector        // ������, ����������� ����������� �����. ������ (0, 1, 0)
        );
        component0->UpdateViewMatrix(g_camera_matrix);
        component1->UpdateViewMatrix(g_camera_matrix);
        component2->UpdateViewMatrix(g_camera_matrix);
        component3->UpdateViewMatrix(g_camera_matrix);
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}