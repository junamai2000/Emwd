# ディレクトリ直下の .cc ファイルは勝手に対象にする
local_src := $(wildcard $(subdirectory)/*.cpp)

# このアーカイブのルールを生成
$(eval $(call make-library, $(subdirectory)/controllers.a, $(local_src)))
