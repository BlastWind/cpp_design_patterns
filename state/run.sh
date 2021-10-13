 g++ badDemo1.cpp -o badDemo1.out -lsfml-graphics -lsfml-window -lsfml-system &
 process_id=$!
 wait $!
 ./badDemo1.out