#include "./json.hpp"


class json {
    private:
        kpt::str key;
        std::vector<kpt::str> value;
        nlohmann::json memory;
    public:
        json() : key(NULL_COMMAND), value({}), memory(NULL_COMMAND) {
        }
        json(kpt::str key, std::vector<kpt::str> value) {
            memory[key.to_cstring()] = value;
        }
        ~json() {
            value.clear();
        }
        void convert_to_json() {
        }
        void upend() {
        }
        json(kpt::str key) {

        }
        json& operator[](kpt::str arr) {
            this->key = arr;
            return *this;
        }
        json& operator=(std::vector<kpt::str> arr) {
            this->memory = arr;
            return *this;
        }
};

void create_empty_json(kpt::str filename) {
    return;
}
int main(int argc, char* argv[]) {
    json j[""] = {{"H","e","l","l","o"}};
    return 0;
}