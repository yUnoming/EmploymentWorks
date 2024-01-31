#pragma once
//
//
// 授業サンプルから取得したファイルです。
// 変更、修正している箇所はありますが、
// 私が０から作成したものではございません。
//
//
#include	<string>

std::string wide_to_multi_winapi(std::wstring const& src);
std::wstring utf8_to_wide_winapi(std::string const& src);
std::string utf8_to_multi_winapi(std::string const& src);
std::wstring sjis_to_wide_winapi(std::string const& src);