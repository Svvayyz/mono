class CMonoError : CMonoObject {
public:
	CMonoError(MonoError Error) {
		m_errError = Error;
	}

	~CMonoError() {
		MonoErrorCleanup(&m_errError);
	}

	bool IsValid() {
		return !MonoErrorOK(&m_errError);
	}

	const char* GetExceptionMessage() {
		return MonoErrorGetMessage(&m_errError);
	}

	unsigned short GetErrorCode() {
		return MonoErrorGetErrorCode(&m_errError);
	}

private:
	MonoError m_errError;

	IMPORT(MonoErrorOK, tMonoErrorOK, MONO_DLL, "mono_error_ok");

	IMPORT(MonoErrorGetErrorCode, tMonoErrorGetErrorCode, MONO_DLL, "mono_error_get_error_code");
	IMPORT(MonoErrorGetMessage, tMonoErrorGetMessage, MONO_DLL, "mono_error_get_message");

	IMPORT(MonoErrorCleanup, tMonoErrorCleanup, MONO_DLL, "mono_error_cleanup");
};