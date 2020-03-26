#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// [と]がきちんと対応しているか
bool is_valid(std::string code){
    int cnt = 0;
    for(int pos = 0; pos < code.size(); ++pos){
        if(code[pos] == '[') ++cnt;
        if(code[pos] == ']') --cnt;
    }
    return cnt == 0;
}

// array, ptr: bf実行時の配列, ポインタのindex; code: 実行するbfのコード(変更不可)
// run(std::string) 引数をbfのコードとみなして実行
// run() this->codeをbfのコードとみなして実行
class BrainFucker{
private:
    std::vector<char> array;
    int ptr;
    std::string code;
public:
    BrainFucker(std::string code) : array(1), code(code) ,ptr(0) {}
    BrainFucker() : array(1), code(""), ptr(0) {}

    void run(std::string code) {
        for(int pos = 0; pos < code.size(); ++pos){
            switch(code[pos]){
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
                    for(int i = pos + 1, cnt = 1; i < code.size(); ++i){
                        if(code[i] == '[') ++cnt;
                        if(code[i] == ']') --cnt;
                        if(cnt == 0) {
                            pos = i-1;
                            break;
                        }
                    }
                    break;
                case ']':
                    if(array[ptr] == 0) break;
                    for(int i = pos - 1, cnt = 1; i >= 0; --i){
                        if(code[i] == '[') --cnt;
                        if(code[i] == ']') ++cnt;
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

    void run(){
        run(code);
    }
};

std::string read_file(std::string file_name) {
    std::string result;
    std::ifstream ifs(file_name);
    if(!ifs.fail()) {
        std::string line;
        while(std::getline(ifs, line)) result += line + '\n';
    }
    return result;
}

void intaractive_mode_run(){
    std::string command;
    BrainFucker bf;
    std::cout << "type 'exit' to quit." << std::endl;

    while(true){
        std::cout << "$ ";
        std::cin >> command;
        if(command == "exit") break;
        while(!is_valid(command)){
            std::string addition;
            std::cin >> addition;
            command += addition;
        }
        bf.run(command);
    }
}

int main(int argc, char *argv[]) {
    if(argc == 1) intaractive_mode_run();
    if(argc == 2) {
        std::string code = read_file(argv[1]);
        BrainFucker bf(code);
        bf.run();
    }
    if(argc >= 3) {
        std::cerr << "Too many arguments." << std::endl;
        return 1;
    }
    return 0;
}