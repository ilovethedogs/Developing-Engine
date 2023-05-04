#pragma once

#include <d3d12.h>

namespace Developing::Graphics {
    class GraphicsDevice;
    class CommandQueue;

    class Fence {
    public:
        Fence(GraphicsDevice& _device);
        ~Fence();

        void SetSignal(CommandQueue& _cmdQueue);
        void SetSignalNext(CommandQueue& _cmdQueue);
        void Wait();
    private:
        Microsoft::WRL::ComPtr<ID3D12Fence> _fence;
        uint32_t                            _fenceValue  {0};
        HANDLE                              _fenceHandle {INVALID_HANDLE_VALUE};
    };
}

