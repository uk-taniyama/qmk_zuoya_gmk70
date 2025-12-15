import { mkdirSync, readFileSync, writeFileSync } from "node:fs";
import GIFEncoder from "gif-encoder-2";

function saveEffectAsGif(effect) {
  const { name, cols, rows, frames } = effect;

  const unit = 4;
  const h = rows * unit;
  const w = cols * unit;
  const enc = new GIFEncoder(w, h);
  enc.start();
  enc.setRepeat(0);
  enc.setDelay(100);
  enc.setQuality(10);

  for (const frame of frames) {
    const buffer = Buffer.alloc(w * h * 4); // RGBA

    for (let y = 0; y < rows; y++) {
      for (let x = 0; x < cols; x++) {
        const pixel = frame[y * cols + x];
        for (let dy = 0; dy < unit; dy++) {
          for (let dx = 0; dx < unit; dx++) {
            const px = ((y * unit + dy) * w + (x * unit + dx)) * 4;
            buffer[px + 0] = pixel.r;
            buffer[px + 1] = pixel.g;
            buffer[px + 2] = pixel.b;
            buffer[px + 3] = 255;
          }
        }
      }
    }

    enc.addFrame(buffer);
  }

  enc.finish();

  const path = `effects/${name.toLowerCase()}.gif`;
  console.log(`Saving GIF: ${path}`);
  writeFileSync(path, enc.out.getData());
}

function saveEffectsMd(effects) {
  let md = `# QMK RGB Matrix Effect GIFs

This directory contains GIF animations of various keyboard lighting effects.

| Effect Name | Preview |
|-------------|---------|
`;

  for (const effect of effects) {
    const name = effect.name;
    md += `| ${name} | ![](${name.toLowerCase()}.gif) |\n`;
  }

  writeFileSync("effects/index.md", md);
}

function main() {
  mkdirSync("effects", { recursive: true });
  const effects = JSON.parse(readFileSync("effect_dump.json", "utf8"));
  for (const effect of effects) {
    saveEffectAsGif(effect);
  }
  saveEffectsMd(effects);
}

main();
