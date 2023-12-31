#!/bin/bash



function sdl2-latest {
  CHECKURL=https://github.com/libsdl-org/SDL/releases/latest
  HTMLTAG='<title>Release '

  LATESTSDL2VER=$(wget -q -O - $CHECKURL | grep "$HTMLTAG" | awk '{print $2}')

  if [ -z $LATESTSDL2VER ]; then echo ERROR; exit; fi	# We make sure wget was successful

  echo $LATESTSDL2VER
  }

VERSION=$(sdl2-latest)

if [ "$(sdl2-config --version)" == "$VERSION" ]; then
  echo SDL2 is already at the latest version \($VERSION\).
  exit
else
  if [ "${1,,}" != "nodep" ]; then
    echo Installing SDL2 dependencies...
    sudo apt-get install libfreetype6-dev libdrm-dev libgbm-dev libudev-dev libdbus-1-dev libasound2-dev liblzma-dev libjpeg-dev libtiff-dev libwebp-dev -y
    echo OpenGL ES 2 dependencies...
    sudo apt-get install libgles2-mesa-dev -y
  fi
  echo Build dependencies...
  sudo apt-get install build-essential -y
  cd ~
  echo Buiding SDL2 $VERSION...
  # Based from "Compile SDL2 from source"
  # https://github.com/midwan/amiberry/wiki/Compile-SDL2-from-source
  wget https://libsdl.org/release/SDL2-${VERSION}.zip
  unzip SDL2-${VERSION}.zip
  cd SDL2-${VERSION}
  ./configure --disable-video-opengl --disable-video-opengles1 --disable-video-x11 --disable-pulseaudio --disable-esd --disable-video-wayland --disable-video-rpi --disable-video-vulkan --enable-video-kmsdrm --enable-video-opengles2 --enable-alsa --disable-joystick-virtual --enable-arm-neon --enable-arm-simd

  make -j $(nproc) CFLAGS='-mtune=cortex-a72 -mfpu=neon-fp-armv8 -mfloat-abi=hard'

  sudo make install

  cd ~
  rm SDL2-${VERSION}.zip
  rm -R SDL2-${VERSION}
  sudo apt-get remove build-essential -y
fi
