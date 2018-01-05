

// D3D- specific includes
// Include headers for the graphics APIs we support
#if SUPPORT_D3D11
#include <d3d11.h>

#include "Unity/IUnityGraphicsD3D11.h"
#include <osvr/RenderKit/GraphicsLibraryD3D11.h>
#include <osvr/RenderKit/RenderManagerD3D11C.h>

#endif // SUPPORT_D3D11

#include "OsvrUnityRenderer.h"
class OsvrD3DRenderer : public OsvrUnityRenderer{
public:
	OsvrD3DRenderer();
	virtual OSVR_ReturnCode ConstructRenderBuffers();
	virtual OSVR_ReturnCode CreateRenderManager(OSVR_ClientContext context);
	virtual OSVR_Pose3 GetEyePose(std::uint8_t eye);
	virtual OSVR_ProjectionMatrix GetProjectionMatrix(std::uint8_t eye);
	virtual OSVR_ViewportDescription GetViewport(std::uint8_t eye);
	virtual void OnRenderEvent();
	virtual void OnInitializeGraphicsDeviceEvent();
	virtual void SetFarClipDistance(double distance);
	virtual void SetIPD(double ipdMeters);
	virtual void SetNearClipDistance(double distance);
	virtual void ShutdownRenderManager();
	virtual void UpdateRenderInfo();
	virtual void* GetEyeTexture(int eye, int buffer);


protected:

private:
	struct FrameInfoD3D11 {
		// Set up the vector of textures to render to and any framebuffer
		// we need to group them.
		std::vector<OSVR_RenderBufferD3D11> renderBuffers;
		ID3D11Texture2D* depthStencilTexture;
		ID3D11DepthStencilView* depthStencilView;
		IDXGIKeyedMutex* keyedMutex;
		FrameInfoD3D11() : renderBuffers(2)
		{
		}

	};
	std::vector<FrameInfoD3D11*> frameInfo;
	OSVR_RenderParams s_renderParams;
	OSVR_RenderManager s_render = nullptr;
	OSVR_RenderManagerD3D11 s_renderD3D = nullptr;
	OSVR_ClientContext s_clientContext = nullptr;
	std::vector<OSVR_RenderInfoD3D11> s_renderInfo;
	std::vector<OSVR_RenderInfoD3D11> s_lastRenderInfo;
	OSVR_GraphicsLibraryD3D11 s_libraryD3D;
	OSVR_RenderInfoCount numRenderInfo;
	OSVR_ProjectionMatrix lastGoodProjMatrix;
	OSVR_Pose3 lastGoodPose;
	OSVR_ViewportDescription lastGoodViewportDescription;
	D3D11_TEXTURE2D_DESC s_textureDesc;
	void *s_leftEyeTexturePtr = nullptr;
	void *s_rightEyeTexturePtr = nullptr;
	void *s_leftEyeTexturePtrBuffer2 = nullptr;
	void *s_rightEyeTexturePtrBuffer2 = nullptr;

	OSVR_ReturnCode ConstructBuffersD3D11(int eye, int buffer, FrameInfoD3D11* fInfo);

};