@echo off

set cur_dir=%CD%

cd *-Release
set R_dir=%CD%
cd ..

rem �ڹ���������download�ļ��У�����������ļ�
md download 
cp %R_dir%/release/*.exe download
cp README.md download/readme.txt
cp source/*.xml download