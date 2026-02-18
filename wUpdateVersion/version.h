// version.h
#pragma once

#define APP_VERSION "0.1"

#ifdef _WIN64
#define APP_ARCH "x64"
#else
#define APP_ARCH "x86"
#endif // _WIN64

#ifdef _DEBUG
#define APP_CONF "d"
#else
#define APP_CONF ""
#endif // _DEBUG
