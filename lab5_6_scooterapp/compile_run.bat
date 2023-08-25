echo compiling...
g++ -std=c++20 ./Controller/*.cpp ./Domain/*.cpp ./Repository/*.cpp ./Tests/*.cpp ./UI/*.cpp main.cpp -o app.exe

echo done

echo program starts...
app.exe