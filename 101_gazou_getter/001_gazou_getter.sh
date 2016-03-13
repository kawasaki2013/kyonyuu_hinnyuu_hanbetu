#!/bin/bash


#画像ゲッター
#引数で人名等を与えると、../001_gazou_original/kyonyuu_hogehoge_00001.jpg等という連番で画像を保存してくれる。
#  getter (kyonyuu or hinnyuu) (人名をローマ字で) (人名を日本語で)
#  getter kyonyuu "hogehoge" "ほげほげ"


GAZOU_DIR='../001_gazou_original/'


function getter() {

  if [ $# -ne 3 ]; then
    echo 'too few arguments'
    return -100
  fi

  kyohin=$1
  name_en=$2
  name_ja=$3

  targettext_encoded=`echo "${name_ja}" | perl -MURI::Escape -lne 'print uri_escape($_)'`
  url='https://www.bing.com/images/search?FORM=HDRSC2&q='${targettext_encoded}
  echo target is "${kyohin}" "${name_en}" "${name_ja}" "${url}"

  if [ -f ${GAZOU_DIR}/${kyohin}_${name_en}_00001.jpg ]; then
    echo "already downloaded ${GAZOU_DIR}/${kyohin}_${name_en}_00001.jpg return"
    return 0
  fi

  mkdir ${GAZOU_DIR}/temp_${kyohin}_${name_en}
  pushd ${GAZOU_DIR}/temp_${kyohin}_${name_en}

  wget -r -l 1 -H "${url}"
  rm -rf tse1.mm.bing.net/ tse2.mm.bing.net/ tse3.mm.bing.net/ tse4.mm.bing.net/ www.bing.com/ www.bingfudosan.jp/
  find ./ -not -name '*.jpg' -a -not -name '*.jpeg' -a -not -name '*.JPG' -type f -print0 | xargs -0 rm

  find ./ -type f | awk '{printf("mv '"'"'%s'"'"' ../'${kyohin}_${name_en}_'%05d.jpg\n", $0, NR);}' | grep -a -v filename_henkan.sh > filename_henkan.sh

  bash filename_henkan.sh

  popd
}


getter "$@"

