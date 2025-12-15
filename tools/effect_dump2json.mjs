import { readFileSync } from "node:fs";
import jsonStringifyPrettyPrint from "json-stringify-pretty-compact";

const stringify = (obj) => jsonStringifyPrettyPrint(obj, { indent: 2, maxLength: 120 })

function parseEffectJsonl(path) {
  const lines = readFileSync(path, "utf8").split("\n");

  const effects = [];
  let effect = {};
  let frames = [];
  let currentFrame = [];

  for (const line of lines) {
    if (!line.trim()) continue;

    const data = JSON.parse(line);
    if (data.length === 3) {
      // effect定義
      const [name, rows, cols] = data;
      currentFrame = [];
      frames = [];
      effect = { name, rows, cols, frames };
      effects.push(effect);
      continue;
    }
    if (data.length === 4) {
      const [, r, g, b] = data;
      currentFrame.push({ r, g, b });
      continue;
    }
    if (data.length === 0) {
      // frame終了
      if (currentFrame.length > 0) {
        frames.push(currentFrame);
        currentFrame = [];
      }
    }
  }

  return effects;
}

// 実行
const effects = parseEffectJsonl("effect_dump.jsonl");
console.log(stringify(effects));
