#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<char> array(1);
    int ptr = 0;
    std::string command;

    std::cout << "type 'exit' to quit." << std::endl;

    while(true){
        std::cout << "$ ";
        std::cin >> command;
        if(command == "exit") break;
        for(int pos = 0; pos < command.size(); ++pos){
            switch(command[pos]){
                case '+':
                    ++array[ptr];
                    break;
                case '-':
                    --array[ptr];
                    break;
                case '>':
                    ++ptr;
                    if(ptr >= array.size()){
                        array.resize(array.size() + 1);
                    }
                    break;
                case '<':
                    --ptr;
                    if(ptr == -1) {
                        std::cerr << "Oops! You tried '<' beyond the array." << std::endl;
                        ptr = 0;
                    }
                    break;
                case '.':
                    std::cout << array[ptr];
                    break;
                case ',':
                    array[ptr] = std::cin.get();
                    break;
                // 1行の中で対応する[]がなければエラー
                case '[':
                    if(array[ptr]) break;
                    for(int i = pos + 1, cnt = 1; i < command.size(); ++i){
                        if(command[i] == '[') ++cnt;
                        if(command[i] == ']') --cnt;
                        if(cnt == 0) {
                            pos = i-1;
                            break;
                        }
                        if(i == command.size() - 1){
                            std::cerr << "Oops! You forgot ']'." << std::endl;
                        }
                    }
                    break;
                case ']':
                    if(array[ptr] == 0) break;
                    for(int i = pos - 1, cnt = 1; i >= 0; --i){
                        if(command[i] == '[') --cnt;
                        if(command[i] == ']') ++cnt;
                        if(cnt == 0) {
                            pos = i-1;
                            break;
                        }
                    }
                    break;
                // 独自拡張、配列をすべて表示
                case '@':
                    for(int i = 0; i < array.size(); ++i){
                        std::cout << "[" << (int)array[i] << "]";
                    }
                    std::cout << std::endl << "ptr: " << ptr << std::endl;
                    break;
                default:
                    break;
            }
        }
    }
}