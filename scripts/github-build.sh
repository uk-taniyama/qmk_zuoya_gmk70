cd $(dirname "$0")
cd ..

set -e -x

rsync -a --delete keyboards/zuoya/* qmk_firmware/keyboards/zuoya
rsync -a --delete keyboards/linker/* qmk_firmware/keyboards/linker

cd qmk_firmware
# patch docker_cmd.sh's docker image
sed -i.bak 's|ghcr.io/qmk/qmk_cli[^ ]* |ghcr.io/qmk/qmk_cli@sha256:d8ebfab96c46d3ab948dd4e87be8a976095bd31268700021a74716cbd6e5b4c1 |g' util/docker_cmd.sh
bash util/docker_build.sh "zuoya/gmk70:default"
bash util/docker_build.sh "zuoya/gmk70:via"
bash util/docker_build.sh "zuoya/gmk70:mine"

cd ..
mkdir dist
mv qmk_firmware/*.bin dist/
