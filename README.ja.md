# ZUOYA GMK70 — QMK Firmware (Custom Build)

- ZUOYA GMK70 用の QMK Firmware ソースです。  
- 有線 USB 接続でのビルドと動作確認を行っています。  
- `qmk_firmware` は **0.26.11 まで対応**しています。

> ⚠️ **注意:**  
> 無線（Wireless / Bluetooth）動作は未検証です。

---

## 概要

このリポジトリは、公開されている GMK70 用ファームウェアをベースに、  
`qmk_firmware` の tri-mode ブランチ、および epomaker 系 split キーボードのソースをマージして調整したものです。

目的は **とりあえずビルドできて動く GMK70 用 QMK ファームウェア環境**を作ることです。

---

## ベースソース

1. 以下のアーカイブをダウンロードし展開  
   - `http://www.mathewkb.com/wp-content/uploads/2024/11/ZUOYA-GMK70.7z`

2. `keyboard/zouya/gmk70` に展開したデータを配置

3. tri-mode対応したQMK Firmware を clone  
   ```
   git clone https://github.com/hangshengkeji/qmk_firmware.git qmk_wk
   ```

4. tri-mode ブランチを checkout  
   ```
   cd qmk_wk
   git checkout tri-mode
   ```

5. `qmk_wk` から以下をコピー  
   - `keyboard/linker`
   - `keyboard/epomaker_split65` 以下のファイル一式

6. `epomaker_split65` のソースを取り込みつつ調整  
   → マージして GMK70 用に修正

---

## ビルド方法

> QMK コマンドではなく、Makefile ベースの簡易ビルドです。

| コマンド | 説明 |
|--------|-----|
| `make build` | ビルドする |
| `make clean` | クリーンする |
| `make rebuild` | クリーンしてからビルドする |

---

## 元ファームとの違い

- **ブートモード:**  
  エンコーダー **長押し**でブートモードに入る仕様
- **レイアウト修正:**  
  数字キー列のキーコードを入れ替え（配列調整）

---

## 動作状況

### ✔ できること

- ビルドが可能
- 有線接続でなんとなく動作確認済み

### ❔ 未確認項目

- Wireless / Bluetooth 動作

### ⚠️ 既知の問題・不具合っぽい項目

- 一定時間放置すると **右手の接続が切れる**  

---

## メモ

このプロジェクトは、GMK70 のファームウェア解析・QMK 移植を目的としています。  
とりあえず自分のキーボードで動くものを作りたい人向けです。
