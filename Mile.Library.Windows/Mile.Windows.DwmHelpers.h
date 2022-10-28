/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.DwmHelpers.h
 * PURPOSE:   Definition for Windows DWM Helpers
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#pragma once

#ifndef MILE_WINDOWS_DWMHELPERS
#define MILE_WINDOWS_DWMHELPERS

#include <Windows.h>

/**
 * @brief Allows the window frame for this window to be drawn in dark mode
 *        colors when the dark mode system setting is enabled.
 * @param WindowHandle The handle to the window for which the attribute value
 *                     is to be set.
 * @param Value TRUE to honor dark mode for the window, FALSE to always use
 *              light mode.
 * @return If the function succeeds, it returns S_OK. Otherwise, it returns an
 *         HRESULT error code.
*/
EXTERN_C HRESULT WINAPI MileSetUseImmersiveDarkModeAttribute(
    _In_ HWND WindowHandle,
    _In_ BOOL Value);

/**
 * @brief Specifies the color of the caption.
 * @param WindowHandle The handle to the window for which the attribute value
 *                     is to be set.
 * @param Value The color of the caption.
 * @return If the function succeeds, it returns S_OK. Otherwise, it returns an
 *         HRESULT error code.
*/
EXTERN_C HRESULT WINAPI MileSetCaptionColorAttribute(
    _In_ HWND WindowHandle,
    _In_ COLORREF Value);

/**
 * @brief Extends the window frame into the client area.
 * @param WindowHandle The handle to the window for which the attribute value
 *                     is to be set.
 * @param LeftWidth describes the left margins to use when extending the frame
 *                  into the client area.
 * @param TopHeight describes the top margins to use when extending the frame
 *                  into the client area.
 * @param RightWidth describes the right margins to use when extending the frame
 *                   into the client area.
 * @param BottomHeight describes the bottom margins to use when extending the frame
 *                     into the client area.
 * @return If the function succeeds, it returns S_OK. Otherwise, it returns an
 *         HRESULT error code.
*/
EXTERN_C HRESULT WINAPI MileSetWindowFrameMargins(
    _In_ HWND WindowHandle,
    _In_ int LeftWidth,
    _In_ int TopHeight,
    _In_ int RightWidth,
    _In_ int BottomHeight);

/**
 * @brief Retrieves or specifies the system-drawn backdrop material of a
 *        window, including behind the non-client area.
 * @param WindowHandle The handle to the window for which the attribute value
 *                     is to be set.
 * @param SystemBackdropType Flags for specifying the system-drawn backdrop
 *                           material of a window, including behind the
 *                           non-client area.
 * @return If the function succeeds, it returns S_OK. Otherwise, it returns an
 *         HRESULT error code.
*/
EXTERN_C HRESULT WINAPI MileSetSystemBackdropAttribute(
    _In_ HWND WindowHandle,
    _In_ DWORD SystemBackdropType);

/**
 * @brief Tests if the dark mode system setting is enabled on the computer.
 * @return True if the dark mode system setting is enabled. Otherwise, this
 *         function returns false.
*/
EXTERN_C BOOL WINAPI MileShouldAppsUseImmersiveDarkMode();

#endif // !MILE_WINDOWS_DWMHELPERS
