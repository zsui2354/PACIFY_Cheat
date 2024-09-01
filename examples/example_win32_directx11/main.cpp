// Dear ImGui: standalone example application for DirectX 11

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "imconfig.h"
#include <cstdint>


//辅助所需环境
#include <tlhelp32.h>
#include <vector>
#include "lib_function.h"
#include "addressOffset.h"
#include "External_API.h"

// Data
static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions     辅助函数的前向声明
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    // Create application window创建应用程序窗口
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowExW(0,wc.lpszClassName, L"安抚辅助", WS_OVERLAPPEDWINDOW, 100, 100, 800, 1000, nullptr, nullptr, wc.hInstance, nullptr);
    HWND Console_hwnd = GetConsoleWindow();
    ::ShowWindow(Console_hwnd, SW_HIDE);
    //WS_EX_LAYERED             WS_POPUP                       WS_OVERLAPPEDWINDOW  Dear ImGui DirectX11 Example

    // Initialize Direct3D  初始化 Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context  设置 Dear ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd); 
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f); 
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);
       //ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\simfang.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    //ImGuiIO& io = ImGui::GetIO();
    
    
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\simhei.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    //
    //
    //
    ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull()); 

    //ImFont* font = io.Fonts->AddFontDefault(); 
    // 
    // Our state
    //
    //
    //
    //                    
    bool show_demo_window = false;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    External_API mapi;
    bool Global_Flying_status = false;



    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;



            ImGuiStyle* style = &ImGui::GetStyle();
            style->Colors[ImGuiCol_Button] = ImColor(84, 255, 159, 255);
            style->Colors[ImGuiCol_ButtonActive] = ImColor(255, 0, 0, 255);

            
            style->Colors[ImGuiCol_TitleBg] = ImColor(84, 255, 159, 255);
            style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 0, 0, 255);
            style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

            
            style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
            style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
            style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

            
            style->Colors[ImGuiCol_FrameBg] = ImColor(255, 171, 255, 255); 
            style->Colors[ImGuiCol_FrameBgActive] = ImColor(255, 0, 29, 250);  
            style->Colors[ImGuiCol_FrameBgHovered] = ImColor(66, 124, 250, 157);

            
            style->Colors[ImGuiCol_Header] = ImColor(84, 255, 159, 255);
            style->Colors[ImGuiCol_HeaderActive] = ImColor(84, 255, 159, 104);
            style->Colors[ImGuiCol_HeaderHovered] = ImColor(84, 255, 159, 104);

            
            style->Colors[ImGuiCol_Tab] = ImColor(255, 0, 0, 255);
            style->Colors[ImGuiCol_TabActive] = ImColor(84, 255, 159, 255);
            style->Colors[ImGuiCol_TabHovered] = ImColor(84, 255, 159, 255);
            





           
            //ImGui::Begin("王果冻的小面板");                          // Create a window called "Hello, world!" and append into it.
            // 

            //ImGui::Text("测试阶段软件");               // Display some text (you can use a format strings too)
            //ImGui::Checkbox("示例窗口", &show_demo_window);      // Edit bools storing our window open/close state
            //ImGui::Checkbox("扩展功能窗口", &show_another_window);

            






          //  ImGui::GetWindowDrawList()->AddRect({ 100.f,100.f }, { 200.f,200.f }, ImColor(255, 96, 0, 255));   


            //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color





            //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)  计数器
            //    counter++;
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", counter);

            //ImGui::Text("平均应用率 %.3f ms/frame       帧数：(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate); 
            //ImGui::End();


            //ImGui::GetWindowDrawList()->AddRect({ 100.f,100.f }, { 200.f,200.f }, ImColor(255, 96, 0, 255)); 
            

            //监控键盘输入 INS 则隐藏程序
            //if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
            //    bool value_cache = show_demo_window;      
            //    show_demo_window = !value_cache;
            //    Sleep(150);
            //    
            //}
            //监控键盘输入 ESC 则退出程序
            //if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            //    break;
            //}
            //扩展功能按钮
            if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
                bool value_cache = show_another_window;
                show_another_window = !value_cache;
                Sleep(150);
            }
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("王果冻的安抚辅助", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar(" ", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("主菜单"))
                {
                    if (ImGui::Button("初始化辅助")) {
                        //External_API mapi;

                        mapi.pid = 0;    // 目标进程ID
                        mapi.pid = GetPID("Pacify-Win64-Shipping.exe");
                        mapi.moduleName = L"Pacify-Win64-Shipping.exe";

                        mapi.hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, mapi.pid);
                        if (mapi.hProcess == nullptr) {
                            
                            std::cerr << "[ Error ]: hProcess is nullptr: " << GetLastError() << std::endl;
                            MessageBox(NULL, "你没有打开游戏，请先打开游戏再启动辅助", "提示", MB_OK);
                            return 1;
                        }

                        DWORD_PTR moduleBaseAddress = GetModuleBaseAddress(mapi.pid, mapi.moduleName);  //0x7FF6546B0000 
                        if (moduleBaseAddress == 0) {
                            std::cerr << "[ Error ]: moduleBaseAddress is null" << std::endl;
                            CloseHandle(mapi.hProcess);
                            return 1;
                        }

                        DWORD_PTR initialAddress;

                        initialAddress = moduleBaseAddress + roomLimit_baseAddressOffset;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        roomLimit_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, roomLimit_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << roomLimit_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Flying_baseAddressOffset;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Flying_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Flying_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Flying_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Unlimitedpower_baseAddressOffset;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Unlimitedpower_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Unlimitedpower_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Unlimitedpower_finalAddress << std::endl;

                        // Z Y X 
                        initialAddress = moduleBaseAddress + Zpos_baseAddressOffset;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Zpos_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Zpos_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Zpos_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Xpos_baseAddressOffset;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Xpos_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Xpos_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Xpos_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Ypos_baseAddressOffset;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Ypos_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Ypos_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Ypos_finalAddress << std::endl;

                        //  人
                        initialAddress = moduleBaseAddress + witch_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        witch_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, witch_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << witch_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Joey_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Joey_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Joey_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Joey_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Karen_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Karen_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Karen_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Karen_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Quinn_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Quinn_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Quinn_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Quinn_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Kit_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Kit_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Kit_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Kit_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Amelia_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Amelia_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Amelia_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Amelia_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Bouli_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Bouli_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Bouli_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Bouli_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Venusin_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Venusin_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Venusin_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Venusin_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + incinerator_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        incinerator_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, incinerator_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << incinerator_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + unit1_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        unit1_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, unit1_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << unit1_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + unit2_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        unit2_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, unit2_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << unit2_finalAddress << std::endl;

                        //二楼电源
                        initialAddress = moduleBaseAddress + hall_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        hall_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, hall_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << hall_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + toilet_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        toilet_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, toilet_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << toilet_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + diversion_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        diversion_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, diversion_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << diversion_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Officearea1_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Officearea1_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Officearea1_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Officearea1_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Officearea2_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Officearea2_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Officearea2_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Officearea2_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Officearea3_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Officearea3_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Officearea3_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Officearea3_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + warehouse_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        warehouse_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, warehouse_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << warehouse_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Ghosthouse_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Ghosthouse_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Ghosthouse_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Ghosthouse_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + Undergroundpassage_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        Undergroundpassage_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, Undergroundpassage_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << Undergroundpassage_finalAddress << std::endl;

                        initialAddress = moduleBaseAddress + cleanchannel_BaseAddress;
                        std::cout << "[address]: initialAddress: 0x" << std::hex << initialAddress << std::endl;
                        cleanchannel_finalAddress = ReadMultiLevelPointer(mapi.hProcess, initialAddress, cleanchannel_offsets);
                        std::cout << "[address]: finalAddress: 0x" << std::hex << cleanchannel_finalAddress << std::endl;
                    }





                    ImGui::Text("房间人数上限"); ImGui::Value("人数上限", roomLimit);
                    //房间人数上限
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)roomLimit_finalAddress, &roomLimit, sizeof(roomLimit), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        ImGui::SliderInt("房间人数上限", &roomLimit, 2, 80);
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)roomLimit_finalAddress, &roomLimit, sizeof(roomLimit), nullptr)) {
                            std::cout << "[succeed]: Changes Roomlimit num =" << roomLimit << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Roomlimit num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Roomlimit num" << std::endl;
                    }
                    //飞天
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Flying_finalAddress, &Flying, sizeof(Flying), nullptr)) {
                        std::cout << "Flying num：" << Flying << std::endl;
                        if (ImGui::Button("开启飞天")) {
                            Global_Flying_status = true;
                        }
                        if (ImGui::Button("关闭飞天")) {
                            Global_Flying_status = false;
                        }
                        if (Global_Flying_status)
                        {
                            Flying = 5;
                        }
                        if (GetAsyncKeyState(VK_UP) & 0x8000) {
                            Flying = 5;
                        }
                        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                            Flying = 1;
                        }
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Flying_finalAddress, &Flying, sizeof(Flying), nullptr)) {
                            std::cout << "[succeed]: Changes Flying num =" << Flying << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Flying num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Flying num" << std::endl;
                    }
                    //自身电池电量
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Unlimitedpower_finalAddress, &Unlimitedpower, sizeof(Unlimitedpower), nullptr)) {
                        std::cout << "Unlimitedpower num：" << Unlimitedpower << std::endl;
                        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                            Unlimitedpower = 100;
                        }
                        ImGui::SliderInt("电池电量", &Unlimitedpower, 0, 100);
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Unlimitedpower_finalAddress, &Unlimitedpower, sizeof(Unlimitedpower), nullptr)) {
                            std::cout << "[succeed]: Changes Unlimitedpower num =" << Unlimitedpower << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Unlimitedpower num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Unlimitedpower num" << std::endl;
                    }
                    //Zpos
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                            Zpos += 5.0f;  // 每次按下空格键时增加 5
                            // 限制 Zpos 的范围在 SliderFloat 的范围内
                            if (Zpos > 5000.0f) Zpos = 5000.0f;
                        }
                        if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                            Zpos -= 5.0f;  // 每次按下空格键时增减去 5
                            // 限制 Zpos 的范围在 SliderFloat 的范围内
                            if (Zpos < -5000.0f) Zpos = -5000.0f;
                        }
                        if (GetAsyncKeyState(VK_XBUTTON1) & 0x8000) {
                            Zpos += 120.0f;  
                            
                            if (Zpos > 5000.0f) Zpos = 5000.0f;
                        }
                        if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) {
                            Zpos -= 120.0f;  
                            
                            if (Zpos < -5000.0f) Zpos = -5000.0f;
                        }

                        ImGui::SliderFloat("高度", &Zpos, -1000.0f, 1000.0f);
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                            std::cout << "[succeed]: Changes Zpos num =" << Zpos << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Zpos num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Zpos num" << std::endl;
                    }
                    //Xpos
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                            std::cout << "[succeed]: Changes Xpos num =" << Xpos << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Xpos num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Xpos num" << std::endl;
                    }
                    //Ypos
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                            std::cout << "[succeed]: Changes Ypos num =" << Ypos << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Ypos num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Ypos num" << std::endl;
                    }

                    ImGui::Text("快捷键小键盘 ，上是开启飞天, 下是关闭飞天");
                    ImGui::Text("空格向上飞，Ctrl向下飞，鼠标侧键 m1 m2 分别向上和向下快飞");


                    //Flying
                    ImGui::Value("飞行状态:", Flying);
                    ImGui::Value("Z轴坐标:", Zpos);
                    ImGui::Value("X轴坐标:", Xpos);
                    ImGui::Value("Y轴坐标:", Ypos);


                    //右内 女巫艾格尼丝	房间电源 
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)witch_finalAddress, &witch, sizeof(witch), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)witch_finalAddress, &witch, sizeof(witch), nullptr)) {
                            std::cout << "[succeed]: Changes witch num =" << witch << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes witch num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read witch num" << std::endl;
                    }
                    //右内 乔伊			房间电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Joey_finalAddress, &Joey, sizeof(Joey), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Joey_finalAddress, &Joey, sizeof(Joey), nullptr)) {
                            std::cout << "[succeed]: Changes Joey num =" << Joey << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Joey num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Joey num" << std::endl;
                    }
                    //右外 凯伦
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Karen_finalAddress, &Karen, sizeof(Karen), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Karen_finalAddress, &Karen, sizeof(Karen), nullptr)) {
                            std::cout << "[succeed]: Changes Karen num =" << Karen << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Karen num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Karen num" << std::endl;
                    }
                    //右外 奎恩
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Quinn_finalAddress, &Quinn, sizeof(Quinn), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Quinn_finalAddress, &Quinn, sizeof(Quinn), nullptr)) {
                            std::cout << "[succeed]: Changes Quinn num =" << Quinn << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Quinn num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Quinn num" << std::endl;
                    }
                    //左外 吉特
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Kit_finalAddress, &Kit, sizeof(Kit), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Kit_finalAddress, &Kit, sizeof(Kit), nullptr)) {
                            std::cout << "[succeed]: Changes Kit num =" << Kit << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Kit num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Kit num" << std::endl;
                    }
                    //左外 艾米利亚
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Amelia_finalAddress, &Amelia, sizeof(Amelia), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Amelia_finalAddress, &Amelia, sizeof(Amelia), nullptr)) {
                            std::cout << "[succeed]: Changes Amelia num =" << Amelia << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Amelia num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Amelia num" << std::endl;
                    }
                    //左内 布利
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Bouli_finalAddress, &Bouli, sizeof(Bouli), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Bouli_finalAddress, &Bouli, sizeof(Bouli), nullptr)) {
                            std::cout << "[succeed]: Changes Bouli num =" << Bouli << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Bouli num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Bouli num" << std::endl;
                    }
                    //左内 维妮辛	
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Venusin_finalAddress, &Venusin, sizeof(Venusin), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Venusin_finalAddress, &Venusin, sizeof(Venusin), nullptr)) {
                            std::cout << "[succeed]: Changes Venusin num =" << Venusin << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Venusin num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Venusin num" << std::endl;
                    }
                    //焚烧炉电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)incinerator_finalAddress, &incinerator, sizeof(incinerator), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)incinerator_finalAddress, &incinerator, sizeof(incinerator), nullptr)) {
                            std::cout << "[succeed]: Changes incinerator num =" << incinerator << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes incinerator num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read incinerator num" << std::endl;
                    }
                    //小单元电源1
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)unit1_finalAddress, &unit1, sizeof(unit1), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)unit1_finalAddress, &unit1, sizeof(unit1), nullptr)) {
                            std::cout << "[succeed]: Changes unit1 num =" << unit1 << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes unit1 num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read unit1 num" << std::endl;
                    }
                    //小单元电源2
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)unit2_finalAddress, &unit2, sizeof(unit2), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)unit2_finalAddress, &unit2, sizeof(unit2), nullptr)) {
                            std::cout << "[succeed]: Changes unit2 num =" << unit2 << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes unit2 num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read unit2 num" << std::endl;
                    }
                    //大厅电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)hall_finalAddress, &hall, sizeof(hall), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)hall_finalAddress, &hall, sizeof(hall), nullptr)) {
                            std::cout << "[succeed]: Changes hall num =" << hall << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes hall num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read hall num" << std::endl;
                    }
                    //卫生间电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)toilet_finalAddress, &toilet, sizeof(toilet), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)toilet_finalAddress, &toilet, sizeof(toilet), nullptr)) {
                            std::cout << "[succeed]: Changes toilet num =" << toilet << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes toilet num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read toilet num" << std::endl;
                    }
                    //娱乐房电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)diversion_finalAddress, &diversion, sizeof(diversion), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)diversion_finalAddress, &diversion, sizeof(diversion), nullptr)) {
                            std::cout << "[succeed]: Changes diversion num =" << diversion << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes diversion num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read diversion num" << std::endl;
                    }
                    //办公区1电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Officearea1_finalAddress, &Officearea1, sizeof(Officearea1), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Officearea1_finalAddress, &Officearea1, sizeof(Officearea1), nullptr)) {
                            std::cout << "[succeed]: Changes Officearea1 num =" << Officearea1 << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Officearea1 num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Officearea1 num" << std::endl;
                    }
                    //办公区2电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Officearea2_finalAddress, &Officearea2, sizeof(Officearea2), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Officearea2_finalAddress, &Officearea2, sizeof(Officearea2), nullptr)) {
                            std::cout << "[succeed]: Changes Officearea2 num =" << Officearea2 << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Officearea2 num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Officearea2 num" << std::endl;
                    }
                    //办公区3电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Officearea3_finalAddress, &Officearea3, sizeof(Officearea3), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Officearea3_finalAddress, &Officearea3, sizeof(Officearea3), nullptr)) {
                            std::cout << "[succeed]: Changes Officearea3 num =" << Officearea3 << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Officearea3 num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Officearea3 num" << std::endl;
                    }
                    //仓库电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)warehouse_finalAddress, &warehouse, sizeof(warehouse), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)warehouse_finalAddress, &warehouse, sizeof(warehouse), nullptr)) {
                            std::cout << "[succeed]: Changes warehouse num =" << warehouse << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes warehouse num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read warehouse num" << std::endl;
                    }
                    //鬼房电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Ghosthouse_finalAddress, &Ghosthouse, sizeof(Ghosthouse), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Ghosthouse_finalAddress, &Ghosthouse, sizeof(Ghosthouse), nullptr)) {
                            std::cout << "[succeed]: Changes Ghosthouse num =" << Ghosthouse << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Ghosthouse num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Ghosthouse num" << std::endl;
                    }
                    //地下通道电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Undergroundpassage_finalAddress, &Undergroundpassage, sizeof(Undergroundpassage), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Undergroundpassage_finalAddress, &Undergroundpassage, sizeof(Undergroundpassage), nullptr)) {
                            std::cout << "[succeed]: Changes Undergroundpassage num =" << Undergroundpassage << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes Undergroundpassage num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read Undergroundpassage num" << std::endl;
                    }
                    //净化通道电源
                    if (ReadProcessMemory(mapi.hProcess, (BYTE*)cleanchannel_finalAddress, &cleanchannel, sizeof(cleanchannel), nullptr)) {
                        std::cout << "Roomlimit num：" << roomLimit << std::endl;
                        if (WriteProcessMemory(mapi.hProcess, (BYTE*)cleanchannel_finalAddress, &cleanchannel, sizeof(cleanchannel), nullptr)) {
                            std::cout << "[succeed]: Changes cleanchannel num =" << cleanchannel << std::endl;
                        }
                        else {
                            std::cerr << "[ Error ]: Changes cleanchannel num" << std::endl;
                        }
                    }
                    else {
                        std::cerr << "[ Error ]: Read cleanchannel num" << std::endl;
                    }

                    ImGui::TextColored(color_Changes(Kit), "左外 吉特	: %d", Kit);
                    ImGui::TextColored(color_Changes(Amelia), "左外 艾米利亚	: %d", Amelia);
                    ImGui::TextColored(color_Changes(Bouli), "左内 布利	: %d", Bouli);
                    ImGui::TextColored(color_Changes(Venusin), "左内 维妮辛	: %d", Venusin);
                    ImGui::TextColored(color_Changes(witch), "右内 女巫	: %d", witch);
                    ImGui::TextColored(color_Changes(Joey), "右内 乔伊	: %d", Joey);
                    ImGui::TextColored(color_Changes(Karen), "右外 凯伦	: %d", Karen);
                    ImGui::TextColored(color_Changes(Quinn), "右外 奎恩	: %d", Quinn);
                    ImGui::Separator();
                    ImGui::TextColored(color_Changes(incinerator), "焚烧炉电源	: %d", incinerator);
                    ImGui::TextColored(color_Changes(unit1), "小单元电源1	: %d", unit1);
                    ImGui::TextColored(color_Changes(unit2), "小单元电源2	: %d", unit2);
                    ImGui::Separator();
                    ImGui::Text("二楼电源");
                    ImGui::TextColored(color_Changes(hall), "大厅电源	: %d", hall);
                    ImGui::TextColored(color_Changes(toilet), "净化通道电源: %d", toilet);
                    ImGui::TextColored(color_Changes(diversion), "娱乐房电源: %d", diversion);
                    ImGui::TextColored(color_Changes(Officearea1), "办公区1电源: %d", Officearea1);
                    ImGui::TextColored(color_Changes(Officearea2), "办公区2电源: %d", Officearea2);
                    ImGui::TextColored(color_Changes(Officearea3), "办公区3电源: %d", Officearea3);
                    ImGui::TextColored(color_Changes(warehouse), "仓库电源: %d", warehouse);
                    ImGui::TextColored(color_Changes(Ghosthouse), "鬼房电源: %d", Ghosthouse);
                    ImGui::TextColored(color_Changes(Undergroundpassage), "地下通道电源	: %d", Undergroundpassage);
                    ImGui::TextColored(color_Changes(cleanchannel), "卫生间电源: %d", cleanchannel);
                    ImGui::Separator();
                    ImGui::Text("传送功能");
                    if (ImGui::Button("资源区"))
                    {
                        //Zpos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                            Zpos = 1022.016;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                                std::cout << "[succeed]: Changes Zpos num =" << Zpos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Zpos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Zpos num" << std::endl;
                        }
                        //Xpos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                            Xpos = 3793.890;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                                std::cout << "[succeed]: Changes Xpos num =" << Xpos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Xpos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Xpos num" << std::endl;
                        }
                        //Ypos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                            Ypos = 5046.566;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                                std::cout << "[succeed]: Changes Ypos num =" << Ypos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Ypos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Ypos num" << std::endl;
                        }
                    }
                    //if (ImGui::Button("焚烧炉"))
                    //{
                    //    //Zpos
                    //    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                    //        Zpos = -251.381;
                    //        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                    //            std::cout << "[succeed]: Changes Roomlimit num =" << Zpos << std::endl;
                    //        }
                    //        else {
                    //            std::cerr << "[ Error ]: Changes Roomlimit num" << std::endl;
                    //        }
                    //    }
                    //    else {
                    //        std::cerr << "[ Error ]: Read Roomlimit num" << std::endl;
                    //    }
                    //    //Xpos
                    //    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                    //        Xpos = 1512.888;
                    //        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                    //            std::cout << "[succeed]: Changes Roomlimit num =" << Xpos << std::endl;
                    //        }
                    //        else {
                    //            std::cerr << "[ Error ]: Changes Roomlimit num" << std::endl;
                    //        }
                    //    }
                    //    else {
                    //        std::cerr << "[ Error ]: Read Roomlimit num" << std::endl;
                    //    }
                    //    //Ypos
                    //    if (ReadProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                    //        Ypos = 4961.291;
                    //        if (WriteProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                    //            std::cout << "[succeed]: Changes Roomlimit num =" << Ypos << std::endl;
                    //        }
                    //        else {
                    //            std::cerr << "[ Error ]: Changes Roomlimit num" << std::endl;
                    //        }
                    //    }
                    //    else {
                    //        std::cerr << "[ Error ]: Read Roomlimit num" << std::endl;
                    //    }
                    //}
                    if (ImGui::Button("净化通道")) {
                        //Zpos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                            Zpos = 982.411;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                                std::cout << "[succeed]: Changes Zpos num =" << Zpos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Zpos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Zpos num" << std::endl;
                        }
                        //Xpos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                            Xpos = 941.970;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                                std::cout << "[succeed]: Changes Xpos num =" << Xpos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Xpos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Xpos num" << std::endl;
                        }
                        //Ypos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                            Ypos = 6383.516;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                                std::cout << "[succeed]: Changes Ypos num =" << Ypos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Ypos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Ypos num" << std::endl;
                        }
                    }
                    if (ImGui::Button("地下充电房"))
                    {
                        //Zpos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                            Zpos = 159.955;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Zpos_finalAddress, &Zpos, sizeof(Zpos), nullptr)) {
                                std::cout << "[succeed]: Changes Zpos num =" << Zpos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Zpos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Zpos num" << std::endl;
                        }
                        //Xpos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                            Xpos = 1882.329;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Xpos_finalAddress, &Xpos, sizeof(Xpos), nullptr)) {
                                std::cout << "[succeed]: Changes Xpos num =" << Xpos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Xpos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Xpos num" << std::endl;
                        }
                        //Ypos
                        if (ReadProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                            Ypos = 2863.134;
                            if (WriteProcessMemory(mapi.hProcess, (BYTE*)Ypos_finalAddress, &Ypos, sizeof(Ypos), nullptr)) {
                                std::cout << "[succeed]: Changes Ypos num =" << Ypos << std::endl;
                            }
                            else {
                                std::cerr << "[ Error ]: Changes Ypos num" << std::endl;
                            }
                        }
                        else {
                            std::cerr << "[ Error ]: Read Ypos num" << std::endl;
                        }
                    }


                    ImGui::Text("平均应用率 %.3f ms/frame       帧数：(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                    ImGui::EndTabItem();
                }
                ImGui::EndTabItem(); 
            }



            if (ImGui::Button("关闭程序"))
                exit(0);
                //show_another_window = false;

            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w }; 
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr); 
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        Sleep(10); //锁帧数
        g_pSwapChain->Present(1, 0); // Present with vsync 垂直同步
        //g_pSwapChain->Present(0, 0); // Present without vsync 
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
