mkdir -p .bin
gcc \
    -I ../qmk_firmware \
    -I ../qmk_firmware/platforms \
    -I ../qmk_firmware/quantum \
    -I ../qmk_firmware/quantum/logging \
    -I ../qmk_firmware/quantum/rgb_matrix \
    -I ../qmk_firmware/quantum/rgb_matrix/animations \
    -I ../qmk_firmware/quantum/rgb_matrix/animations/runners \
    effect_dump.c \
    -o .bin/effect_dump
.bin/effect_dump > effect_dump.jsonl
node effect_dump2json.mjs > effect_dump.json
rm -rf effects/*
node effect_dump2gif.mjs
