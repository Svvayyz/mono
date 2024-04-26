inline std::unordered_map<const char*, HMODULE> mapModules;
inline std::unordered_map<const char*, FARPROC> mapAddresses;

class CMonoObject {
public:
	HMODULE GetModule(const char* szName) {
		HMODULE hMod = nullptr;
		if (mapModules.contains(szName))
			hMod = mapModules.at(szName);
		else {
			hMod = GetModuleHandleA(szName);

			mapModules[szName] = hMod;

#ifdef _DEBUG
			uintptr_t nAddress = CAST(hMod, uintptr_t);

			if (nAddress == 0x0)
				std::cout << "[-] Failed to find " << szName << " at 0x" << nAddress << std::endl;
			else
				std::cout << "[+] Found " << szName << " at 0x" << nAddress << std::endl;
#endif
		}

		return hMod;
	}
	FARPROC GetProcAddr(HMODULE hMod, const char* szAddr) {
		FARPROC pPointer = nullptr;
		if (mapAddresses.contains(szAddr))
			pPointer = mapAddresses.at(szAddr);
		else {
			pPointer = GetProcAddress(hMod, szAddr);

			mapAddresses[szAddr] = pPointer;

#ifdef _DEBUG
			uintptr_t nAddress = CAST(pPointer, uintptr_t);

			if (nAddress == 0x0)
				std::cout << "[-] Failed to find " << szAddr << " at 0x" << nAddress << std::endl;
			else
				std::cout << "[+] Found " << szAddr << " at 0x" << nAddress << std::endl;
#endif
		}

		return pPointer;
	}
};