/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.DwmHelpers.cpp
 * PURPOSE:   Implementation for Windows DWM Helpers
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.DwmHelpers.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

namespace
{
    bool IsWindowsVersionOrLater(
        DWORD const& MajorVersion,
        DWORD const& MinorVersion,
        DWORD const& BuildNumber)
    {
        OSVERSIONINFOEXW OSVersionInfoEx = { 0 };
        OSVersionInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
        OSVersionInfoEx.dwMajorVersion = MajorVersion;
        OSVersionInfoEx.dwMinorVersion = MinorVersion;
        OSVersionInfoEx.dwBuildNumber = BuildNumber;
        return ::VerifyVersionInfoW(
            &OSVersionInfoEx,
            VER_BUILDNUMBER,
            ::VerSetConditionMask(
                ::VerSetConditionMask(
                    ::VerSetConditionMask(
                        0,
                        VER_MAJORVERSION,
                        VER_GREATER_EQUAL),
                    VER_MINORVERSION,
                    VER_GREATER_EQUAL),
                VER_BUILDNUMBER,
                VER_GREATER_EQUAL));
    }

    static bool IsWindows10Version20H1OrLater()
    {
        static bool CachedResult = IsWindowsVersionOrLater(10, 0, 19041);
        return CachedResult;
    }

    static bool IsSupportSystemBackdrop()
    {
        static bool CachedResult = IsWindowsVersionOrLater(10, 0, 22523);
        return CachedResult;
    }
}

EXTERN_C HRESULT WINAPI MileSetUseImmersiveDarkModeAttribute(
    _In_ HWND WindowHandle,
    _In_ BOOL Value)
{
    static const auto SetPreferredAppMode =
        reinterpret_cast<HRESULT(CALLBACK*)(DWORD)>(::GetProcAddress(
            ::GetModuleHandleW(L"UxTheme.dll"),
            MAKEINTRESOURCEA(135)));
    const DWORD UxThemePreferredAppModeAllowDark = 1;
    const DWORD UxThemePreferredAppModeForceDark = 2;
    const DWORD UxThemePreferredAppModeForceLight = 3;
    SetPreferredAppMode(UxThemePreferredAppModeAllowDark);
    const DWORD DwmWindowUseImmersiveDarkModeBefore20H1Attribute = 19;
    const DWORD DwmWindowUseImmersiveDarkModeAttribute = 20;
    return ::DwmSetWindowAttribute(
        WindowHandle,
        (::IsWindows10Version20H1OrLater()
            ? DwmWindowUseImmersiveDarkModeAttribute
            : DwmWindowUseImmersiveDarkModeBefore20H1Attribute),
        &Value,
        sizeof(BOOL));
}

EXTERN_C HRESULT WINAPI MileSetCaptionColorAttribute(
    _In_ HWND WindowHandle,
    _In_ COLORREF Value)
{
    const DWORD DwmWindowCaptionColorAttribute = 35;
    return ::DwmSetWindowAttribute(
        WindowHandle,
        DwmWindowCaptionColorAttribute,
        &Value,
        sizeof(COLORREF));
}

EXTERN_C HRESULT WINAPI MileSetWindowFrameMargins(
    _In_ HWND WindowHandle,
    _In_ int LeftWidth,
    _In_ int TopHeight,
    _In_ int RightWidth,
    _In_ int BottomHeight)
{
    MARGINS Value{ 0 };
    Value.cxLeftWidth = LeftWidth;
    Value.cyTopHeight = TopHeight;
    Value.cxRightWidth = RightWidth;
    Value.cyBottomHeight = BottomHeight;
    return DwmExtendFrameIntoClientArea(
        WindowHandle,
        &Value);
}

EXTERN_C HRESULT WINAPI MileSetSystemBackdropAttribute(
    _In_ HWND WindowHandle,
    _In_ DwmSystemBackdropType Type)
{
    if (!::IsSupportSystemBackdrop())
    {
        return E_NOINTERFACE;
    }
    ::MileSetCaptionColorAttribute(WindowHandle, static_cast<COLORREF>(-1));
    const DWORD DwmWindowSystemBackdropTypeAttribute = 38;
    return ::DwmSetWindowAttribute(
        WindowHandle,
        DwmWindowSystemBackdropTypeAttribute,
        &Type,
        sizeof(DWORD));
}

EXTERN_C BOOL WINAPI MileShouldAppsUseImmersiveDarkMode()
{
    DWORD Type = REG_DWORD;
    DWORD Value = 0;
    DWORD ValueLength = sizeof(DWORD);
    DWORD Error = ::RegGetValueW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme",
        RRF_RT_REG_DWORD | RRF_SUBKEY_WOW6464KEY,
        &Type,
        &Value,
        &ValueLength);
    if (Error == ERROR_SUCCESS)
    {
        if (Type == REG_DWORD && ValueLength == sizeof(DWORD))
        {
            return (Value == 0) ? TRUE : FALSE;
        }
    }
    return FALSE;
}
