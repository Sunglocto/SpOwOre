// OwO

#include "stdafx.h"

const char16_t* replacement = u"OwO";
void Initialize()
{
}

void Dispose()
{
	delete replacement;
}

member_detour(SetText_detour, LocalizedString, bool(int32_t tableID, uint32_t instanceID, const char16_t* pPlaceholderText)) {
	bool detoured(int32_t tableID, uint32_t instanceID, const char16_t* pPlaceholderText) {
		return original_function(this, id("mumReplaceNonExists"), id("mumReplaceNonExists"), replacement);
	}
};

member_detour(GetText_detour, LocalizedString, const char16_t* ()) {
	const char16_t* detoured() {
		return replacement;
	}
};

void AttachDetours()
{
	SetText_detour::attach(GetAddress(LocalizedString, SetText));
	GetText_detour::attach(GetAddress(LocalizedString, GetText));
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
