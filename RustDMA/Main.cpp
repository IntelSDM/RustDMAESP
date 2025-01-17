#include "pch.h"
#include "memory.h"
#include "CheatFunction.h"
#include <dwmapi.h>
enum class DebugFilter
{
	Off = 0,
	Dynamic = 1,
	Static = 2,
	Grid = 4,
	All = 7
};

void main()
{
	if (!TargetProcess.Init("RustClient.exe"))
	{
		printf("Failed to initialize process\n");
		return;
	}
	TargetProcess.GetBaseAddress("GameAssembly.dll");
	TargetProcess.FixCr3();

	uint64_t occlusioncullingclass = 233977000;
	uint64_t klass = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress("GameAssembly.dll") + occlusioncullingclass);
	uint64_t staticclass = TargetProcess.Read<uint64_t>(klass + 0xb8);
	printf("StaticClass: %llx\n", staticclass);
//	Sleep(5000);
	uint64_t instance = TargetProcess.Read<uint64_t>(staticclass + 0x570);
	uint64_t debugsettings = TargetProcess.Read<uint64_t>(instance + 0x1A8);


	TargetProcess.Write<DebugFilter>(debugsettings + 0x1c, DebugFilter::Dynamic);
	TargetProcess.Write<int>(debugsettings + 0x20, 131072);
}
