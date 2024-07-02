cls
del *.exe
del *.obj
cl.exe src\*.cc dependencies\src\glad.c /I dependencies\include /EHsc /MD opengl32.lib user32.lib gdi32.lib shell32.lib dependencies\lib\glfw3.lib 
main.exe