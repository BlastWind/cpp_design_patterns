 g++ badDemo0.cpp -o badDemo.out -lsfml-graphics -lsfml-window -lsfml-system &
 process_id=$!
 wait $!
 ./badDemo0.out