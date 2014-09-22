### 非再帰的make(non-recursive make)
# ソースファイルツリーが常に整頓されている前提
#	使っていないソースファイルが紛れ込まないようにしなければならない、その辺はGitで管理する
# 内容的には "GNU Make 第3版、6章 大きなプロジェクトの管理" に載っているコードとほぼ同じ
#
### 参考
#論文: "Recursive Make Considered Harmful"
#http://miller.emu.id.au/pmiller/books/rmch/
#実際にnon-recursive makeを適用しているOSSプロダクト(OpenRADIUS)のMakefile解説(上記論文のサイトにもリンクが貼られている)
#http://evbergen.home.xs4all.nl/nonrecursive-make.html
#この例ではスタックポインタを利用して、ソースツリーの階層が増えた場合にでも対応できる非再帰的makeを実現している


#filter関数 Usage:$(filter pattern..., text)
#以下のsource-to-objectで言うと、$1で始まり.cppで終わる文字列のみを抽出する
# Usage:$(call source-to-object, source-file-list)
source-to-object = $(subst .cpp,.o,$(filter %.cpp, $1))

#patsubstで"/module.mk"を取り除く
#$(words $(MAKEFILE_LIST))で読み込まれたmakefileの数
#$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))で読み込まれたmakefileリストの最後のmakefile名(=現在処理中のmakefile)を取り出す
#最終的にsubdirectoryは現在処理中のサブディレクトリの名前となる(ver1のlocal_dirの代価)
# Usage:$(subdirectory)
subdirectory = $(patsubst %/module.mk,%,$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))

# makeの注意点:タブの後にあるものはコマンドとみなされる
# 以下のユーザ定義関数でコマンド以外の部分でタブを入れるとcommands commence before first target. Stop.などと言われる
# ライブラリ生成用ユーザ定義関数、同時に変数librariesとsourcesにモジュール情報を追加
# Usage:$(call make-library, library-name, source-file-list)
define make-library
  libraries		+= $1
  sources		+= $2

  $1: $(call source-to-object, $2)
	$(AR) $(ARFLAGS) $$@ $$^
endef

# Usage:$(call make-library, library-name, source-file-list, libraries)
define make-so
  libraries		+= $1
  sources		+= $2

  $1: $(call source-to-object, $2) $3
	$(CC) -shared -fPIC -o $$@ $$^
endef

# Usage:$(call make-exec-binary, exec-binary-name, source-file-list, libraries)
define make-exec-binary
  programs	+= $1
  sources	+= $2

$1: $(call source-to-object, $2) $3
endef

#各モジュールの情報を、次の４つの変数に収集する
#ここでは、単純変数として初期化する
modules		:= $(subst /module.mk,,$(shell find . -name module.mk))
programs	:= 
libraries	:=
sources		:=

#再帰変数として定義、モジュール情報が読まれる度に情報が蓄積する
objects			= $(call source-to-object, $(sources))
dependencies	= $(subst .o,.d,$(objects))

# ヘッダファイルがあるディレクトリを設定
# lib/foo/foo.hというヘッダがある時、ソースコード上では、
# include_dirsにlibをセットした場合 #include "foo/foo.h"
# include_dirsにlib/fooをセットした場合 #include "foo.h"
include_dirs	:=  /usr/include/apr-1.0 /usr/include/apache2 ../include	
CPPFLAGS		+=	$(addprefix -I ,$(include_dirs))
vpath %.h $(include_dirs)

#メモ - makeの変数名に関する慣例
#		ユーザがコマンドラインオプションで変更されうるものは大文字
#		makefile内で完結する変数は小文字
MV := mv -f
RM := rm -f
SED := sed
#C++コンパイラオプション
CXXFLAGS := -Wall -fPIC -O3
#リンクを担当する暗黙ルール%:%.oで呼び出される$(LINK.o)がデフォルトで$(CC)なので、CCも設定し直す
CC := g++
#リンカのオプション
LDFLAGS := -Wall 

CFLAGS := -fPIC

# includeでMakefileの断片を呼び出すと、内部で最初に出現したターゲットがデフォルトターゲットになってしまうので、
# allを先に空で定義してから、後で上書きすることでデフォルトターゲットをallにする
all:

### include modules, in random order
# サブディレクトリにあるmodule.mkを全てインクルードする
# 個々のmodule.mkから得られる情報は変数programs, libraries, sourcesに蓄積される
# 依存関係の解決は全てmakeが自動的に行うのでインクルードする順番を気にする必要はない
include $(addsuffix /module.mk,$(modules))

### Rules
.PHONY: all
all: $(programs) libraries

.PHONY: libraries
libraries: $(libraries)

.PHONY: debug
debug:
	@echo "programs=$(programs)"
	@echo "objects=$(objects)"
	@echo "sources=$(sources)"
	@echo "modules=$(modules)"
	@echo "libraries=$(libraries)"
	@echo "dependencies=$(dependencies)"

.PHONY: clean
clean:
	$(RM) $(objects) $(programs) $(libraries) $(dependencies)

#コマンドライン引数にcleanが入っていなければ、.dファイルをインクルードする
ifneq "$(MAKECMDGOALS)" "clean"
  #makeの便利な機能：.dファイルをインクルードしようとすると、自動的にmakeが.dファイルの生成を試みる
  #その時に適用されるルールが下の%.d:%.ccであり、そこでgccのオプション-MM,-MPが用いられれて、必要な依存関係ファイルが自動生成される
  include $(dependencies)
endif

### 依存関係の自動生成
#	gccの-MM -MMP オプションを利用している点がポイント
#-M:依存する(インクルードする)ヘッダファイルを調べる
#-MM:依存する(インクルードする)ヘッダファイルを調べる(システムヘッダファイルを除外する)
#-MF file:標準出力ではなく指定したファイルに依存関係情報を出力する
#-MG:対象のヘッダファイルがない場合にでもエラー扱いしない(ヘッダファイルが自動生成される場合に用いる)
#-MP:依存するヘッダファイルを偽のターゲットとして追加する(登録ヘッダファイル削除時のエラーを避けるため)
#-MMD:依存ヘッダを調べると共にコンパイルも行う
%.d: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MP $< |\
		$(SED) 's,\($(notdir $*)\.o\) *:,$(dir $@)\1 $@: ,' > $@.tmp
	$(MV) $@.tmp $@
