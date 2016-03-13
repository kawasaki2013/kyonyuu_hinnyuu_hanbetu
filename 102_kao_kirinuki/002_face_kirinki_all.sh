#!/bin/bash

#顔部分だけ切り抜く


SOURCE_PICTURE_DIR='../001_gazou_original'
OUTPUT_DIR='../002_gazou_face'


printenv OS|grep -Ii win
if [ $? -eq 0 ]; then
  #以下はwindows上で実行する場合
  EXE_PATH=./face_kirinuki_windows/x64/Debug/OpenCV_test001.exe
else
  #以下はlinux上で実行する場合
  EXE_PATH=./face_kirinuki_linux/face_kirinuki_linux
fi

CASCADEFILE_PATH=./000sample_data/haarcascade_frontalface_alt2.xml
echo EXE_PATH is $EXE_PATH
echo CASCADEFILE_PATH is $CASCADEFILE_PATH


for original_file_name in ${SOURCE_PICTURE_DIR}/*.jpg; do
  echo -e '\n'

  output_file_name=${original_file_name/$SOURCE_PICTURE_DIR/$OUTPUT_DIR}
  echo -e 'target file is' $original_file_name
  echo -e 'output file is' $output_file_name

  if [ -f ${output_file_name} ]; then
    echo 'already detected face. skip'
    continue
  fi

  $EXE_PATH ${original_file_name} ${output_file_name} ${CASCADEFILE_PATH}

  #もし判別に失敗してface_*.jpgのファイルができなかった場合、空のファイルを作る。
  if [ $? -ne 0 ]; then
    touch ${output_file_name}
    continue
  fi

  #サイズを同じにする
  mogrify -geometry 256x256 ${output_file_name}
done

