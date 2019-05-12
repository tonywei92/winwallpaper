#include <iostream>
#include <windows.h>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#define LOG(format, ...) wprintf(format L"\n", __VA_ARGS__)

enum WPSTYLE { TILE = 0, CENTER = 1, STRETCH = 2, FIT = 3, FILL = 4 };
void setWallpaper(LPCWSTR path, WPSTYLE style);
void setWallpaperStyle(WPSTYLE style);
std::wstring s2ws(const std::string& s);

int main(int argc, char** argv)
{
	WPSTYLE style = WPSTYLE::FILL;
	std::string path;
	std::string styleStr;
	po::options_description desc("Winwallpaper (c) Tony Song <tonywei92@gmail.com>\nUsage: winwallpaper.exe [options]\nAllowed options");
	desc.add_options()
		("help", "show this help message")
		("path,p", po::value<std::string>(&path)->default_value(""), "image path")
		("style,s", po::value<std::string>(&styleStr)->default_value("fill"), "style eg. tile, center, stretch, fit, and fill");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || argc == 1) {
		std::cout << desc << "\n";
		return 1;
	}

	if (path == "") {
		std::cout << "Invalid path\n";
		return 1;
	}

	if (styleStr == "tile") {
		style = WPSTYLE::TILE;
	}
	else if (styleStr == "center") {
		style = WPSTYLE::CENTER;
	}
	else if (styleStr == "stretch") {
		style = WPSTYLE::STRETCH;
	}
	else if (styleStr == "fit") {
		style = WPSTYLE::FIT;
	}
	else if (styleStr == "fill") {
		style = WPSTYLE::FILL;
	}
	else {
		std::cout << "invalid style, allowed style: tile, center, stretch, fit, and fill\n";
		return 1;
	}

	std::cout << "Done." << "\n";

	setWallpaper(s2ws(path).c_str(), style);

}

void setWallpaper(LPCWSTR path, WPSTYLE style) {

	setWallpaperStyle(style);

	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (void*)path, SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}

void setWallpaperStyle(WPSTYLE style) {
	HRESULT hr = S_OK;
	HKEY hKey = NULL;
	hr = HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, &hKey));
	if (SUCCEEDED(hr))
	{
		PWSTR pszWallpaperStyle;
		PWSTR pszTileWallpaper;


		switch (style)
		{
		case WPSTYLE::TILE:
			pszWallpaperStyle = L"0";
			pszTileWallpaper = L"1";
			break;

		case WPSTYLE::CENTER:
			pszWallpaperStyle = L"0";
			pszTileWallpaper = L"0";
			break;

		case WPSTYLE::STRETCH:
			pszWallpaperStyle = L"2";
			pszTileWallpaper = L"0";
			break;

		case WPSTYLE::FIT: // (Windows 7 and later)
			pszWallpaperStyle = L"6";
			pszTileWallpaper = L"0";
			break;

		case WPSTYLE::FILL: // (Windows 7 and later)
			pszWallpaperStyle = L"10";
			pszTileWallpaper = L"0";
			break;
		default:
			std::cout << "Invalid style";
			return;
		}

		DWORD cbData = lstrlen(pszWallpaperStyle) * sizeof(*pszWallpaperStyle);
		hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, L"WallpaperStyle", 0, REG_SZ,
			reinterpret_cast<const BYTE*>(pszWallpaperStyle), cbData));
		if (SUCCEEDED(hr))
		{
			cbData = lstrlen(pszTileWallpaper) * sizeof(*pszTileWallpaper);
			hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, L"TileWallpaper", 0, REG_SZ,
				reinterpret_cast<const BYTE*>(pszTileWallpaper), cbData));
		}

		RegCloseKey(hKey);
	}


}

std::wstring s2ws(const std::string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}