@echo off

rem �ڹ���������download�ļ��У�����������ļ�

cd *-Release
set R_dir=%CD%
cd ..

IF not EXIST download  md download 
cp -u %R_dir%/release/*.exe download
cp -u readme.txt download
cp -u source/*.xml download