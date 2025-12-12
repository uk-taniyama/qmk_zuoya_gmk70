cd $(dirname "$0")
cd ..

set -e -x

rsync -a --delete keyboards/zuoya/* qmk_firmware/keyboards/zuoya
rsync -a --delete keyboards/linker/* qmk_firmware/keyboards/linker

cd qmk_firmware
sh util/docker_build.sh "zuoya/gmk70:default"
sh util/docker_build.sh "zuoya/gmk70:via"
sh util/docker_build.sh "zuoya/gmk70:mine"

cd ..
mkdir dist
mv qmk_firmware/*.bin dist/
