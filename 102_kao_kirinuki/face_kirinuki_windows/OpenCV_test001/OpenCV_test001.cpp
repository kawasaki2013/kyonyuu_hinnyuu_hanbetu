/*

��F���B
  http://nonbiri-tereka.hatenablog.com/entry/2015/05/13/063713

�摜�̐؂蔲���B
  http://reiji1020.hatenablog.com/entry/2014/10/28/225829

���R���悭�킩��Ȃ����Alinux�ł��R���p�C�����邽�߂�stdafx.h��ifdef�ň͂��Ă����܂������Ȃ��B
�K���C���N���[�h����w�b�_�Ƃ��Ďw�肵���B
  http://d.hatena.ne.jp/runicalp/20100519/1274258386
*/

#ifdef __GNUC__
  #include <stdio.h>
  #include <stdlib.h>
#else
  #include <windows.h>
#endif

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define FACE_KAKUDAI_WARIAI 1.2 //�Ⴆ�Ό��o���ꂽ�炪100px�l�����Ƃ�����A100�~FACE_KAKUDAI_WARIAIpx�̃T�C�Y�Ő؂蔲��

//���s���@�͈ȉ��B
//  hoge.exe �^�[�Q�b�g�̃t�@�C���� �o�̓t�@�C���� cascade�t�@�C����
//�߂�l�́A0������I���A100��艺�͈����s�����̎��s���ُ̈�A100�ȏ��OpenCV�͑����������o�o���Ȃ�������
int main(int argc, char const *argv[]) {
	if(argc!=4){
		printf("error. too few argument.\n");
		exit(1);
	}
	printf("target file is %s\n", argv[1]);

	Mat image = imread(argv[1]);
	if(image.data==NULL){
		printf("error. can not read source picture file.\n");
		exit(2);
	}
	printf("image size width=%d height=%d\n", image.size().width, image.size().height);

	string cascade_filename = argv[3];
	CascadeClassifier cascade;
	if(cascade.load(cascade_filename)!=true){
		printf("error. can not read cascade file.\n");
		exit(3);
	}

	vector<Rect> faces;
	cascade.detectMultiScale(image, faces, 1.1, 3, 0);
	printf("detect %zu faces.\n", faces.size());

	if(faces.size()!=1){
		printf("too many faces or no faces detected. exit.\n");
		exit(100);
	}

	for (unsigned int i = 0; i < faces.size(); i++) {
		printf("face[%d] x=%d y=%d width=%d height=%d\n", i, faces[i].x, faces[i].y, faces[i].width, faces[i].height);

		//�؂蔲���T�C�Y�������傫���������ɉ摜���͂ݏo�邩�ǂ����m�F�B
		int kakudai_size = (int)(faces[i].width * (FACE_KAKUDAI_WARIAI-1) / 2); //���E�Ŋg�傷��̂�2�Ŋ����Ă���B
		int kirinuki_x = faces[i].x-kakudai_size; 
		int kirinuki_y = faces[i].y-kakudai_size;
		int kirinuki_width  = faces[i].width + kakudai_size*2;
		int kirinuki_height = faces[i].height+ kakudai_size*2;
		if( kirinuki_x<0 ||
			kirinuki_y<0 ||
			image.size().width  <= kirinuki_x+kirinuki_width ||
			image.size().height <= kirinuki_y+kirinuki_height ){
			printf("face[%d] located on corner. skip.\n", i);
			exit(101);
		}

		Mat cut_img(image, Rect(kirinuki_x, kirinuki_y, kirinuki_width, kirinuki_height));
		imwrite(argv[2], cut_img);
		printf("face[%d] outputed as \"%s\"\n", i, argv[2]);

		rectangle(image, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 200, 0), 1, CV_AA);
		rectangle(image, Point(kirinuki_x, kirinuki_y), Point(kirinuki_x + kirinuki_width, kirinuki_y + kirinuki_height), Scalar(200, 0, 0), 1, CV_AA);
	}

	//imshow("detect face", image);
	//waitKey(0);

	return 0;
}
