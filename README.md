# zuoya gmk70用のqmk-firmwareのソース

とりあえず、ビルドができるもの。

## ベースソース

1. http://www.mathewkb.com/wp-content/uploads/2024/11/ZUOYA-GMK70.7zをダウンロード

2. keyboard/zouya/gmk70にZOUYA-GMK70.7zを展開したのを配置。

3. https://github.com/hangshengkeji/qmk_firmware.gitをqmk_wkにclone。

4. qmk_wkにて、tri-modeをcheckout。

5. qmk_wkから、keyboard/linkerとepomaker_split65以下のファイルをコピー。

6. epomaker_split65のソースをマージしつつ調整して完成。

## ビルド手順

|make build|ビルドする。|
|make clean|クリーンする。|
|make rebuild|クリーンしてビルドする。|

## 元ファームとの違い

- ブートモードに入るにはエンコーダーを長押しする。
- 数字キーの列のキーコードを入れ替え。

## できること

- ビルドができてなんとなく動く。

## 未確認のこと

- Wireless・Bluetoothは動くか不明。

## 不良っぽいこと

- しばらく放置していると、右手が切断される。
