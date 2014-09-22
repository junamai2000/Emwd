# ディレクトリ直下の .cc ファイルは勝手に対象にする
local_src := $(wildcard $(subdirectory)/*.cpp)

# このアーカイブのルールを生成
$(eval $(call make-so, $(subdirectory)/libemwdmysqldriver.so, $(local_src)))
