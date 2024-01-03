# 応用プロジェクト　ラダー飛行機
## Contents

- `main`フォルダ
  - arduinoを動かすメイン関数とそのライブラリ
  - pythonコードで送られたジョイコン座標を送信し、サーボに出力する。
- `python`フォルダ
  - `main.py`はxinputでpcに送られたデータをarduinoに送信し、arduinoから送られたサーボのPWM信号などを受信しprintで書き出す
  - `Xinput.py`はxinputを単純なfloat形式のデータに落とし込むライブラリ。https://github.com/Haven-Lau/Arduino-Libraries/tree/master/USB_Host_Shield_2.0-master
  より
  - `XinputTest.py`も同リンクからのテストパイソンファイル
- `mid_presentation_v1116`は中間コンペまでに作成したセンサデータ取得のarduino用プログラムファイル


## 実行環境
- arduino IDE
  
- python
  - pandas