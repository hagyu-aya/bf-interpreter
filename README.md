$ これは何？

BrainFuckerのインタプリタ。独自仕様もあるよ。

$ 使い方

コンパイルして実行！実行したいbrainfuckのコードを入力してね。  
引数を与えると、そのファイルをbrainfuckのコードとして実行してくれるよ。

$ 独自仕様

$$ 配列

配列はメモリが溢れない限りどこまでも拡張されるよ。

$$ 独自コマンド@

コード中に@があると、その時点での配列とポインタの指す場所のインデックスが出力されるよ。本家とは違って@は無視されないから気をつけようね。デバッグに便利だよ。