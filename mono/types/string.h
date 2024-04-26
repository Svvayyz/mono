class CMonoString : CMonoObject {
public:
	CMonoString(MonoString* pString) {
		m_pString = pString;
	}

	std::string GetString() {
		if (
			m_pString == nullptr ||
			MonoStringLength(m_pString) < 1
			)
			return "";

		MonoError err;
		char* szUTF8 = MonoStringToUTF8Checked(m_pString, &err);

		std::string szResult(szUTF8);
		MonoFree(szUTF8);

		return szResult;
	}

private:
	IMPORT(MonoFree, tMonoFree, MONO_DLL, "mono_free");

	IMPORT(MonoStringLength, tMonoStringLength, MONO_DLL, "mono_string_length");
	IMPORT(MonoStringToUTF8Checked, tMonoStringToUTF8Checked, MONO_DLL, "mono_string_to_utf8_checked");

	MonoString* m_pString = nullptr;
};