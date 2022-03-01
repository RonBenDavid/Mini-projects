clear
close all
clc
warning( 'off', 'MATLAB:xlswrite:AddSheet' ) ;

%% 1
fileName = 'img2';
imgRGB = imread([fileName, '.jpg']);
imgGrayscale = rgb2gray(imgRGB);
success1 = image2excel([fileName, '.xlsx'], imgRGB);
success2 = image2excel([fileName, 'Grayscale.xlsx'], imgGrayscale);

%% 2
fileName = 'img2';
imgGrayscale = excel2image([fileName, 'Grayscale.xlsx']);
imgRGB = excel2image([fileName, '.xlsx']);

subplot(121)
imshow(imgGrayscale)
subplot(122)
imshow(imgRGB)

%% 3
fileName = 'img4.jpeg';
imgRGB = imread(fileName);
imgGray = rgb2gray(imgRGB);

width1 = -20;
width2 = 45;
width3 = 20000;

imgGL1 = RedLineDrawer(imgRGB, width1);
imgGL2 = RedLineDrawer(imgRGB, width2);
imgGL3 = RedLineDrawer(imgGray, width2);
imgGL4 = RedLineDrawer(imgRGB, width3);

subplot(221)
imshow(imgGL1)
title('imgRGB; width1 = -20')
subplot(222)
imshow(imgGL2)
title('imgRGB; width2 = 45')
subplot(223)
imshow(imgGL3)
title('imgGray; width2 = 45')
subplot(224)
imshow(imgGL4)
title('imgRGB; width3 = 20000')


%%
warning( 'on', 'MATLAB:xlswrite:AddSheet' ) ;
