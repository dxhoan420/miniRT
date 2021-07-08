# miniRT
My first RayTracer with miniLibX
![Не лучшее изображение, я плохой художник](https://github.com/dxhoan420/miniRT/blob/master/photo_2021-07-08_15-34-07.jpg "Тут видны все возможные фигуры")
Попиксельный генератор изображений с помощью трассировки лучей. Умеет рисовать:
* Фигуры любого цвета, размера и количества внутри и снаружи (с бликами по модели Блинна-Фонга):
1. Сфера
2. Плоскость
3. Квадрат с вертикально или горизонтально ориентированными сторонами
4. Треугольник
5. Цилиндр без крышки
* С неограниченным количеством точечных источников света в сцене
* С неограниченным количеством и положением камер в сцене

Написан полностью на C, выводит изображение в BMP-файл или интерактивное окно с помощью библиотеки miniLibX.
Пока работает только на MacOS с установленной статической библиотекой miniLibX.
Для создания исполняемого файла используйте make. Запускается приложение через командную строку с аргументом содержащим полный или относительный путь до конфигурационного файла сцены в расширении *.rt
Используйте готовые файлы сцен в папке scenes, либо создайте свою по руководству ниже
Per-pixel image generator using ray tracing. Knows how to draw:
* Figures of any color, size and quantity inside and outside (with highlights according to the Blinna-Fong model):
1. Sphere
2. Plane
3. Square with vertically or horizontally oriented sides
4. Triangle
5. Cylinder without cover
* With unlimited point lights in the scene
* With unlimited number and position of cameras in the scene
In the meantime, there is no need to worry about it. ”
Written entirely in C, it outputs an image to a BMP file or an interactive window using the miniLibX library.
So far, it only works on MacOS with the miniLibX static library installed.
Use make to create an executable file. The application is launched via the command line with an argument containing the full or relative path to the scene configuration file in the * .rt extension
Use ready-made scene files in the scenes folder, or create your own according to the guide below

◦ Each element first’s information is the type identifier (composed by one or two character(s)), followed by all specific information for each object in a strict order such as:
1. Ambient lightning:
"A 0.2 255,255,255"
* identifier: A
* ambient lighting ratio in range [0.0,1.0]: 0.2
* R,G,B colors in range [0-255]: 255, 255, 255
2. Camera:
"C -50.0,0,20 0,0,1 70"
* identifier: C
* x,y,z coordinates of the view point: 0.0,0.0,20.6
* 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0
* FOV : Horizontal field of view in degrees in range [0,180]
3. Light:
"@L -40.0,50.0,0.0 0.6 10,0,25"
* identifier: L
* x,y,z coordinates of the light point: 0.0,0.0,20.6
* the light brightness ratio in range [0.0,1.0]: 0.6
* (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
4. Sphere:
"sp 0.0,0.0,20.6 12.6 10,0,255"
* identifier: sp
* x,y,z coordinates of the sphere center: 0.0,0.0,20.6
* the sphere diameter: 12.6
* R,G,B colors in range [0-255]: 10, 0, 255
5. Plane:
"pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"
* identifier: pl
* x,y,z coordinates: 0.0,0.0,-10.0
* 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
* R,G,B colors in range [0-255]: 0, 0, 255
6. Cylinder:
"cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"
* identifier: cy
* x,y,z coordinates: 50.0,0.0,20.6
* 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
* the cylinder diameter: 14.2
* the cylinder height: 21.42
* R,G,B colors in range [0,255]: 10, 0, 255
