cd $(dirname "$0")
cd ..

set -e -x

kb="${kb:-zuoya/gmk70}"
km="${km:-via}"

git submodule sync --recursive
git submodule update --init --recursive

rsync -a --delete keyboards/zuoya/* qmk_firmware/keyboards/zuoya
rsync -a --delete keyboards/linker/* qmk_firmware/keyboards/linker

cd qmk_firmware
sh util/docker_build.sh "${kb}:${km}"
cd ..
mv qmk_firmware/*.bin .
echo "Generated firmware:"
ls *.bin
