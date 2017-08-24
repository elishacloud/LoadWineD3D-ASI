#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define SET_DLL_EXPORTS(procName, procNum) \
	dllexports[procNum].Export = procName ## proc; \
	dllexports[procNum].ArraySize = (sizeof(procName ## proc) / sizeof(*procName ## proc)); \

// Designated Initializer does not work in VS 2015 so must pay attention to the order
#define VISIT_EXPORTS(visit) \
	visit(d3d8, 0) \
	visit(d3d9, 1) \
	visit(d3d10, 2) \
	visit(d3d10core, 3) \
	visit(d3d11, 4) \
	visit(ddraw, 5) \
	visit(dxgi, 6) \

// Designated Initializer does not work in VS 2015 so must pay attention to the order
static constexpr char* dllname[] = {
	"d3d8.dll",			// 0
	"d3d9.dll",			// 1
	"d3d10.dll",		// 2
	"d3d10core.dll",	// 3
	"d3d11.dll",		// 4
	"ddraw.dll",		// 5
	"dxgi.dll",			// 6
};
static constexpr size_t ArraySize = (sizeof(dllname) / sizeof(*dllname));

struct DLLEXPORTS
{
	char **Export;
	int ArraySize;
};
extern DLLEXPORTS dllexports[ArraySize];

#define CREATE_PROC_STUB(procNum) \
	FARPROC wrapper_proc ## procNum; \
	extern "C" __declspec(naked) void __stdcall func ## procNum() \
	{ \
		__asm jmp wrapper_proc ## procNum \
	} \

#define SET_FUNC_STUB(procNum) \
	wrapper_func[procNum] = (FARPROC)*func ## procNum; \

#define SET_PROC_STUB(procNum) \
	case procNum: \
	wrapper_proc ## procNum = Script_proc; \
	break; \

#define VISIT_PROCS(visit) \
	visit(0) \
	visit(1) \
	visit(2) \
	visit(3) \
	visit(4) \
	visit(5) \
	visit(6) \
	visit(7) \
	visit(8) \
	visit(9) \
	visit(10) \
	visit(11) \
	visit(12) \
	visit(13) \
	visit(14) \
	visit(15) \
	visit(16) \
	visit(17) \
	visit(18) \
	visit(19) \
	visit(20) \
	visit(21) \
	visit(22) \
	visit(23) \
	visit(24) \
	visit(25) \
	visit(26) \
	visit(27) \
	visit(28) \
	visit(29) \
	visit(30) \
	visit(31) \
	visit(32) \
	visit(33) \
	visit(34) \
	visit(35) \
	visit(36) \
	visit(37) \
	visit(38) \
	visit(39) \
	visit(40) \
	visit(41) \
	visit(42) \
	visit(43) \
	visit(44) \
	visit(45) \
	visit(46) \
	visit(47) \
	visit(48) \
	visit(49) \
	visit(50) \
	visit(51) \
	visit(52) \
	visit(53) \
	visit(54) \
	visit(55) \
	visit(56) \
	visit(57) \
	visit(58) \
	visit(59) \
	visit(60) \

static char* d3d8proc[] = {
	"D3D8GetSWInfo",
	"Direct3DCreate8",
	"ValidatePixelShader",
	"ValidateVertexShader",
};

static char* d3d9proc[] = {
	"Direct3DShaderValidatorCreate9",
	"D3DPERF_BeginEvent",
	"D3DPERF_EndEvent",
	"D3DPERF_GetStatus",
	"D3DPERF_QueryRepeatFrame",
	"D3DPERF_SetMarker",
	"D3DPERF_SetOptions",
	"D3DPERF_SetRegion",
	"Direct3DCreate9",
	"Direct3DCreate9Ex",
};

static char* d3d10proc[] = {
	"D3D10CompileEffectFromMemory",
	"D3D10CompileShader",
	"D3D10CreateBlob",
	"D3D10CreateDevice",
	"D3D10CreateDeviceAndSwapChain",
	"D3D10CreateEffectFromMemory",
	"D3D10CreateStateBlock",
	"D3D10DisassembleShader",
	"D3D10GetGeometryShaderProfile",
	"D3D10GetInputAndOutputSignatureBlob",
	"D3D10GetInputSignatureBlob",
	"D3D10GetOutputSignatureBlob",
	"D3D10GetPixelShaderProfile",
	"D3D10GetShaderDebugInfo",
	"D3D10GetVertexShaderProfile",
	"D3D10ReflectShader",
	"D3D10StateBlockMaskDifference",
	"D3D10StateBlockMaskDisableAll",
	"D3D10StateBlockMaskDisableCapture",
	"D3D10StateBlockMaskEnableAll",
	"D3D10StateBlockMaskEnableCapture",
	"D3D10StateBlockMaskGetSetting",
	"D3D10StateBlockMaskIntersect",
	"D3D10StateBlockMaskUnion",
};

static char* d3d10coreproc[] = {
	"D3D10CoreCreateDevice",
	"D3D10CoreRegisterLayers",
};

static char* d3d11proc[] = {
	"D3D11CoreCreateDevice",
	"D3D11CoreRegisterLayers",
	"D3D11CreateDevice",
	"D3D11CreateDeviceAndSwapChain",
};

static char* ddrawproc[] = {
	"DirectDrawCreate",
	"DirectDrawCreateClipper",
	"DirectDrawCreateEx",
	"DirectDrawEnumerateA",
	"DirectDrawEnumerateExA",
	"DirectDrawEnumerateExW",
	"DirectDrawEnumerateW",
	"DllCanUnloadNow",
	"DllGetClassObject",
	"DllRegisterServer",
	"DllUnregisterServer",
};

static char* dxgiproc[] = {
	"CreateDXGIFactory",
	"CreateDXGIFactory1",
	"DXGID3D10CreateDevice",
	"DXGID3D10RegisterLayers",
};
