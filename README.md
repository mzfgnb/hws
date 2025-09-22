## Для Solar System

###  Запуск

Если при запуске программы возникает ошибка с библиотеками, то необходимо в терминале перед запуском программы прописать команду

`export LD_LIBRARY_PATH=/opt/sfml2/lib:$LD_LIBRARY_PATH`

где вместо `/opt/sfml2/lib` должен стоять ваш путь с sfml2 библиотеками

### Компиляция:
  **Для SolarSystem.cpp**
  
  ```g++ SolarSystem.cpp -o solar -I/opt/sfml2/include -L/opt/sfml2/lib -lsfml-graphics -lsfml-window -lsfml-system```

  **Для SolarSystem2.cpp**
  
  ```g++ SolarSystem2.cpp -o solar -I/opt/sfml2/include -L/opt/sfml2/lib -lsfml-graphics -lsfml-window -lsfml-system```
