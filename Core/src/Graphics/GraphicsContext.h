#pragma once

class ID3D12Device;
class ID3D12DescriptorHeap;

namespace Developing::Graphics {
    class GraphicsDevice;
    class CommandQueue;
    class DescriptorHeap;
    class SwapChain;

    struct WindowData {
        int width;
        int height;
        HWND nativeWnd;
        bool windowed;
    };
    
    class GraphicsContext {
    public:
        GraphicsContext(int width, int height, HWND nativeWnd, bool windowed);
        ~GraphicsContext();

        [[nodiscard]] ID3D12Device* GetDevice() const;
        [[nodiscard]] int16_t GetNumOfBackBuffers() const;

        [[nodiscard]] ID3D12DescriptorHeap GetDescHeap() const;
    private:
        WindowData _windowData;
    private:
        std::unique_ptr<GraphicsDevice>  p_device;
        std::unique_ptr<CommandQueue>    p_cmdQueue;
        std::unique_ptr<DescriptorHeap>  p_RTV;
        std::unique_ptr<SwapChain>       p_swapChain;
    };
}

