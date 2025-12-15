# QMK RGB Matrix Preview

QMK の `rgb_matrix` アニメーションを**PC 上で簡易的に可視化・確認する**ことを目的としています。

## Preview

👉 **結果はこちらを参照してください**

- [effects/index.md](effects/index.md)

各 RGB Matrix エフェクトのプレビュー画像・アニメーションを一覧で確認できます。

## How it works

- effect_dump.sh  
  effect_dump.c をコンパイルして実行。
  その他nodeを用いて変換。

- effect_dump.c  
  エフェクトをそれっぽく再現し、`effect_dump.jsonl` を出力

- effect_dump2json.mjs  
  jsonl をまとめて `effect_dump.json` に変換

- effect_dump2gif.mjs  
  `effect_dump.json`  を再生して GIF を生成
