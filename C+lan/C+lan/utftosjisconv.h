#pragma once
//
//
// ���ƃT���v������擾�����t�@�C���ł��B
// �ύX�A�C�����Ă���ӏ��͂���܂����A
// �����O����쐬�������̂ł͂������܂���B
//
//
#include	<string>

std::string wide_to_multi_winapi(std::wstring const& src);
std::wstring utf8_to_wide_winapi(std::string const& src);
std::string utf8_to_multi_winapi(std::string const& src);
std::wstring sjis_to_wide_winapi(std::string const& src);