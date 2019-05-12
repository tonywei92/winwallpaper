# winwallpaper - Open  Source
A CLI utility for change Windows wallpaper along with scaling.


## Download
:+1: [Releases](https://github.com/tonywei92/winwallpaper/releases/latest)

## Usage
```
Usage: winwallpaper.exe [options]
Allowed options:
  --help                     show this help message
  -p [ --path ] arg          image path
  -s [ --style ] arg (=fill) style eg. tile, center, stretch, fit, and fill
```

## Build
This project using some [Boost.org](https://www.boost.org) C++ library, build boost library using bjam with static runtime link by running:
```
$ bjam runtime-link=static
```

## License
Copyright (c) Tony Song [tonywei92@gmail.com](mailto:tonywei92@gmail.com) at LiveWithCode. All rights reserved.

Licensed under the [MIT](LICENSE.txt) License.