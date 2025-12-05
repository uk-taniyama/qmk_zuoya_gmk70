cd $(dirname "$0")
cd ..

set -e -x

cd qmk_firmware
rm -rf keyboards/zuoya/gmk70
rm -rf keyboards/linker/wireless
rm -rf .build
